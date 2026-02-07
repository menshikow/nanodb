## Phase 0 — Workspace & Rust Tooling

* [ ] **Toolchain:** Stable Rust (1.75+). Nightly *optional* for experiments.
* [ ] **Edition:** `edition = "2021"` (or 2024 when stable).
* [ ] **Linting:** `cargo clippy -- -D warnings`
* [ ] **Formatting:** `rustfmt`
* [ ] **Errors:** Use **`Result<T, DbError>`** everywhere.

  * Rust’s `Result` already *is* `std::expected`.

```rust
fn fetch_page(id: PageId) -> Result<&Page, DbError>;
```

* [ ] **Logging:** `tracing` + `tracing-subscriber`

  * Faster, structured, async-friendly.
* [ ] **Build:** `cargo` (no equivalent CMake pain).

**Invariant:** `#![deny(unsafe_code)]` at crate root (temporarily relax later).

---

## Phase 1 — Disk Manager & Paging (Slices & Bytes)

* [ ] **Page Size:**

```rust
pub const PAGE_SIZE: usize = 4096;
```

* [ ] **Page View:** `&mut [u8; PAGE_SIZE]` or `&mut [u8]`

  * Rust slices already enforce bounds.

* [ ] **Disk Manager:**

  * `std::fs::File`
  * `read_exact_at` / `write_all_at` (via `std::os::unix::fs::FileExt`)
  * Or wrap with your own `DiskManager`.

* [ ] **Binary I/O:** `bytemuck` or manual encoding

  * Rust does **not** allow type-punning by default (good).

**Invariant:** No pointer arithmetic. All offsets are checked.

---

## Phase 2 — Buffer Pool (Ownership & Borrowing)

* [ ] **Replacer:** LRU or LRU-K

* [ ] **Frames:** `Vec<Frame>`

* [ ] **Page Table:** `HashMap<PageId, FrameId>`

* [ ] **Concurrency:**

  * `Mutex` / `RwLock` from `parking_lot` (faster than std)
  * No data races by construction.

```rust
type PageRef = Arc<RwLock<Page>>;
```

**Key difference:**
Rust forces you to *model pinning explicitly* (usually `Arc` + guard).

**Invariant:** No aliasing mutable page data without a lock guard.

---

## Phase 3 — Slotted Page (Explicit Layout)

* [ ] **Layout:**

```
| Header | Slot Array ↓ | Free Space | Tuple Data ↑ |
```

* [ ] **Header Access:**

```rust
#[repr(C)]
struct PageHeader { lsn: u64, page_id: PageId, free_ptr: u16 }
```

* [ ] **Safe Casting:**

  * `bytemuck::from_bytes`
  * Or manual `read_u16_le` etc.

* [ ] **Tuple Access:**

```rust
fn get_tuple(&self, slot: SlotId) -> Option<&[u8]>;
```

* [ ] **Compaction:** `copy_within`

**Invariant:** `unsafe` only allowed inside `page.rs`, audited.

---

## Phase 4 — Type System (Enums & Matching)

* [ ] **Value Type:**

```rust
enum Value {
    Null,
    Int(i32),
    Float(f64),
    Text(String),
}
```

* [ ] **Dispatch:** `match`

  * Faster and safer than `std::visit`.

* [ ] **Schema:** `Vec<Column>`

* [ ] **Serialization:** Explicit encoding

  * No `memcpy` foot-guns.

**Invariant:** No runtime type tags outside `enum`.

---

## Phase 5 — B+ Tree (Traits & Generics)

* [ ] **Key Constraint:**

```rust
trait Key: Ord + Clone {}
```

* [ ] **Node Types:**

```rust
enum Node {
    Internal(InternalNode),
    Leaf(LeafNode),
}
```

* [ ] **No Virtual Dispatch**

  * Enums compile to jump tables.

* [ ] **Iterators:**

```rust
impl Iterator for BPlusTreeIter { type Item = Tuple; }
```

**Invariant:** Tree invariants encoded in type system where possible.

---

## Phase 6 — Parser & Binder (String Slices)

* [ ] **Tokenizer:** `&str` + byte indices
* [ ] **AST:** Owns nothing; references original query.

```rust
struct Identifier<'a> { name: &'a str }
```

* [ ] **Errors:** `Result<Ast<'a>, ParseError>`

**Invariant:** Zero string allocations during parsing.

---

## Phase 7 — Execution (Iterators or Coroutines)

* [ ] **Baseline:** Rust Iterators (simpler than coroutines)
* [ ] **Advanced:** `async-stream` or generators (nightly)

```rust
fn execute(&self) -> impl Iterator<Item = Tuple>;
```

* [ ] **Pipeline:** Iterator composition

**Invariant:** No manual state machines.

---

## Phase 8 — Concurrency

* [ ] **Locks:** `RwLock`
* [ ] **Atomics:** `AtomicU64` for LSN, TXN IDs
* [ ] **Coordination:** `Barrier`, `Condvar`

**Key difference:**
Rust statically prevents data races—no TSAN archaeology.

---

## Phase 9 — Recovery

* [ ] **WAL:** Append-only file
* [ ] **Serialization:** Explicit endian encoding
* [ ] **Logging:** `tracing::info!`

**Invariant:** Recovery logic is deterministic and replayable.

---

## Project Layout

```text
nanodb/
├── Cargo.toml
├── src/
│   ├── lib.rs
│   ├── main.rs
│   ├── common/
│   │   ├── config.rs
│   │   ├── types.rs
│   │   └── error.rs
│   ├── storage/
│   │   ├── disk/
│   │   │   └── disk_manager.rs
│   │   ├── page/
│   │   │   ├── page.rs
│   │   │   ├── header.rs
│   │   │   └── btree_page.rs
│   │   └── index/
│   │       └── btree.rs
│   ├── buffer/
│   │   ├── buffer_pool.rs
│   │   └── lru.rs
│   ├── execution/
│   │   ├── executor.rs
│   │   └── seq_scan.rs
│   └── catalog/
│       ├── schema.rs
│       └── column.rs
├── tests/
└── benches/
```
