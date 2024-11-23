#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  setlocale(LC_ALL, "");
#ifdef TEXTDOMAINDIR
  bindtextdomain("messages", TEXTDOMAINDIR);
  textdomain("messages");
#endif

  int low = 1, high = 100;
  char ans[10];
  while (high - low > 1) {
    int mid = (low + high) / 2;
    printf(gettext("number is greater than %d?\n"), mid);
    int check;
    scanf("%s", ans);
    if (strcmp(ans, gettext("yes")) == 0) {
      low = mid;
    } else if (strcmp(ans, gettext("no")) == 0) {
      high = mid;
    } else {
      printf(gettext("unknown command. Valiable answers: yes/no.\n"));
    }
  }
  printf(gettext("number is greater than %d?\n"), low);
  int check;
  scanf("%s", ans);
  if (strcmp(ans, gettext("yes")) == 0) {
    printf(gettext("answer is %d!\n"), high);
  } else if (strcmp(ans, gettext("no")) == 0) {
    printf(gettext("answer is %d!\n"), low);
  } else {
  }
}
