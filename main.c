#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Row {
  int id;
  char username[32];
  char email[255];
};

const char *COMMANDS[] = {"insert"};

int main(void) {
  char buf[256];

  printf("NanoDB> ");

  while (true) {
    if (!fgets(buf, sizeof buf, stdin))
      break;

    buf[strcspn(buf, "\n")] = 0;

    char *command = strtok(buf, " ");
    if (command == NULL) {
      continue;
    }

    if (!strcmp(command, "q") || !strcmp(command, "quit"))
      break;
    else if (!strcmp(command, "insert")) {
      char *id_string = strtok(NULL, " ");
      char *username = strtok(NULL, " ");
      char *email = strtok(NULL, " ");

      if (id_string != NULL && username != NULL && email != NULL) {
        struct Row row;
        row.id = atoi(id_string);
        strcpy(row.username, username);
        strcpy(row.email, email);
        printf("inserted ID %d, user %s, email %s\n", row.id, row.username,
               row.email);
      } else {
        printf("syntax error: insert <id> <username> <email>\n");
      }
    } else {
      printf("Unrecognized command '%s'.\n", command);
    }

    printf("NanoDB> ");
  }

  return 0;
}
