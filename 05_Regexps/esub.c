#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXGR 10

/*
    С обратными слешами запутался, как это должно работать :(
*/

int main(int argc, char *argv[]) {
  char *buf;
  size_t len = 0;
  int rc;
  int chars;
  regex_t regex;
  regmatch_t bags[MAXGR];
  if (argc < 3) {
    printf("useage: ./esubc <substitution> <regexp>");
  }

  char *substitution = argv[1];
  size_t N = strlen(substitution);

  if ((rc = regcomp(&regex, argv[2], REG_EXTENDED)) != 0) {
    char buffer[100];
    regerror(rc, &regex, buffer, 100);
    printf("regcomp() failed with '%s'\n", buffer);
    exit(EXIT_FAILURE);
  }

  for (buf = NULL; (chars = getline(&buf, &len, stdin)) != -1; buf = NULL) {
    buf[chars - 1] = 0;
    if (regexec(&regex, buf, MAXGR, bags, REG_EXTENDED) == 0) {
      for (int i = 1; i < MAXGR; i++) {
        int b = bags[i].rm_so, e = bags[i].rm_eo;
        char group[3];
        group[0] = '\\', group[1] = '0' + i, group[2] = 0;

        char *s = strstr(substitution, group);
        if (s != NULL && bags[i].rm_so < 0) {
          printf("number of bags erros: %d\n", i);
          exit(i);
        }

        char *newsub;
        while (s = strstr(substitution, group)) {
          size_t n = s - substitution;
          newsub = calloc(100, sizeof(char));
          sprintf(newsub, "%.*s%.*s%s", n, substitution, e - b, buf + b, s + 2);
          sprintf(substitution, "%s", newsub);
          free(newsub);
        }
      }

      printf("%.*s%s%s\n", bags[0].rm_so, buf, substitution,
             buf + bags[0].rm_eo);
    } else {
      puts(buf);
    }
    free(buf);
  }
  regfree(&regex);
  return 0;
}
