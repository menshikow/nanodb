#include <algorithm>
#include <cstdint>
#include <optional>
#include <print>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace nanodb {

using RowId = std::uint64_t;
using Value = std::string;

struct Column {
  std::string name;
  std::string type;
  bool nullable{true};
};

struct Row {
  RowId id{};
  std::unordered_map<std::string, Value> fields;

  std::optional<Value> get(std::string_view column) const {
    const auto item = fields.find(std::string(column));
    if (item == fields.end()) {
      return std::nullopt;
    }

    return item->second;
  }
};

class Schema {
 public:
  void add_column(std::string name, std::string type, bool nullable = true) {
    columns_.push_back(Column{std::move(name), std::move(type), nullable});
  }

  bool has_column(std::string_view name) const {
    return std::ranges::any_of(columns_, [name](const Column& column) {
      return column.name == name;
    });
  }

  const std::vector<Column>& columns() const { return columns_; }

 private:
  std::vector<Column> columns_;
};

class Table {
 public:
  explicit Table(std::string name, Schema schema)
      : name_(std::move(name)), schema_(std::move(schema)) {}

  const std::string& name() const { return name_; }
  const Schema& schema() const { return schema_; }

  RowId insert(std::unordered_map<std::string, Value> fields) {
    const RowId id = next_id_++;
    rows_.push_back(Row{id, std::move(fields)});
    return id;
  }

  std::optional<Row> find(RowId id) const {
    const auto item = std::ranges::find_if(rows_, [id](const Row& row) {
      return row.id == id;
    });

    if (item == rows_.end()) {
      return std::nullopt;
    }

    return *item;
  }

  std::vector<Row> where(std::string_view column, std::string_view value) const {
    std::vector<Row> matches;
    for (const Row& row : rows_) {
      const auto field = row.get(column);
      if (field.has_value() && field.value() == value) {
        matches.push_back(row);
      }
    }
    return matches;
  }

  const std::vector<Row>& rows() const { return rows_; }

 private:
  std::string name_;
  Schema schema_;
  RowId next_id_{1};
  std::vector<Row> rows_;
};

class Database {
 public:
  Table& create_table(std::string name, Schema schema) {
    const auto [item, inserted] = tables_.emplace(
        name, Table{std::move(name), std::move(schema)});

    if (!inserted) {
      throw std::runtime_error("table already exists");
    }

    return item->second;
  }

  Table* table(std::string_view name) {
    const auto item = tables_.find(std::string(name));
    if (item == tables_.end()) {
      return nullptr;
    }
    return &item->second;
  }

 private:
  std::unordered_map<std::string, Table> tables_;
};

}  // namespace nanodb

int main() {
  nanodb::Schema users_schema;
  users_schema.add_column("name", "text", false);
  users_schema.add_column("email", "text", false);

  nanodb::Database db;
  nanodb::Table& users = db.create_table("users", std::move(users_schema));

  const nanodb::RowId ada = users.insert({{"name", "Ada"}, {"email", "ada@nano.db"}});
  users.insert({{"name", "Grace"}, {"email", "grace@nano.db"}});

  if (const auto row = users.find(ada)) {
    std::println("found user #{}: {}", row->id, row->get("name").value_or("unknown"));
  }

  for (const nanodb::Row& row : users.where("name", "Grace")) {
    std::println("matched user #{}: {}", row.id, row.get("email").value_or(""));
  }

  return 0;
}
