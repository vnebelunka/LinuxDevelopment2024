#include "rhash.h" /* LibRHash interface */
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifdef USE_READLINE
#include <readline/readline.h>
#endif

void removeChar(char *str, char c) {

  char *src, *dst;
  for (src = dst = str; *src != '\0'; src++) {
    *dst = *src;
    if (*dst != c)
      dst++;
  }
  *dst = '\0';
}

int main(int argc, char *argv[]) {
  char *line = NULL;
  size_t len = 100;
  unsigned char digest[64];
  char output[130];
  int nread;

  rhash_library_init(); /* initialize static data */

#ifdef USE_READLINE
  fprintf(stderr, "readline will be used\n");
  while ((line = readline(NULL)) != NULL) {
#else
  fprintf(stderr, "getline will be used\n");
  while ((nread = getline(&line, &len, stdin)) != -1) {
#endif
    if (line[nread - 1] == '\n') {
      line[nread - 1] = '\0';
    }
    char *tokens = line;
    char *mode, *msg, *saveptr;
    mode = strtok_r(tokens, " ", &saveptr);
    tokens = NULL;
    msg = strtok_r(tokens, " ", &saveptr);
    int MODE;
    if (strcmp(mode, "sha1") == 0 || strcmp(mode, "Sha1") == 0) {
      MODE = RHASH_SHA1;
    } else if (strcmp(mode, "tth") == 0 || strcmp(mode, "Tth") == 0) {
      MODE = RHASH_TTH;
    } else if (strcmp(mode, "md5") == 0 || strcmp(mode, "Md5") == 0) {
      MODE = RHASH_MD5;
    } else {
      fprintf(stderr, "unknown mode : %s none of [s|Sha1, t|Tth, m|Md5]\n",
              mode);
      continue;
    }
    int OUT_MODE;
    if ('A' <= mode[0] && mode[0] <= 'Z') {
      OUT_MODE = RHPR_HEX;
    } else {
      OUT_MODE = RHPR_BASE64;
    }
    int res;
    if (msg[0] == '\"') {
      removeChar(msg, '\"');
      res = rhash_file(MODE, msg, digest);
      printf("file ");
      if (res < 0) {
        fprintf(stderr, "LibRHash error: %s: %s\n", msg, strerror(errno));
        continue;
      }
    } else {
      printf("string ");
      res = rhash_msg(MODE, msg, strlen(msg), digest);
      if (res < 0) {
        fprintf(stderr, "message digest calculation error\n");
        continue;
      }
    }
    rhash_print_bytes(output, digest, rhash_get_digest_size(MODE), OUT_MODE);
    printf("%s (%s) = \n%s\n", rhash_get_name(MODE), msg, output);
  }
  free(line);
  return 0;
}
