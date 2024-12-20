#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static jmp_buf escape;

static void test_abort(void) {
  printf("jumped\n");
  longjmp(escape, 1);
}

#define BUF_ABORT test_abort()
#include "buf.h"

#if _WIN32
#define C_RED(s) s
#define C_GREEN(s) s
#else
#define C_RED(s) "\033[31;1m" s "\033[0m"
#define C_GREEN(s) "\033[32;1m" s "\033[0m"
#endif

char *test;

#define TEST(s, x)                                                             \
  if (strcmp(s, test) == 0) {                                                  \
    do {                                                                       \
      if (x) {                                                                 \
        exit(0);                                                               \
      } else {                                                                 \
        exit(1);                                                               \
      }                                                                        \
    } while (0);                                                               \
  }

static uint32_t pcg32(uint64_t *s) {
  uint64_t m = 0x5851f42d4c957f2d;
  uint64_t a = 0x8b260b70b8e98891;
  uint64_t p = *s;
  uint32_t x = ((p >> 18) ^ p) >> 27;
  uint32_t r = p >> 59;
  *s = p * m + a;
  return (x >> r) | (x << (-r & 31u));
}

static unsigned long bench(uint64_t *rng) {
  unsigned long r = 0;
  uint32_t n = 1000000 + pcg32(rng) % 4000000;
  float *buf = 0;

  for (uint32_t i = 0; i < n; i++)
    buf_push(buf, pcg32(rng) / (double)UINT32_MAX);

  float threshold = pcg32(rng) / (double)UINT32_MAX;
  for (uint32_t i = 0; i < n; i++)
    r += buf[i] > threshold;

  buf_free(buf);
  return r;
}

#ifdef _WIN32
#include <windows.h>
uint64_t uepoch(void) {
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft);
  uint64_t tt = ft.dwHighDateTime;
  tt <<= 32;
  tt |= ft.dwLowDateTime;
  tt /= 10;
  tt -= UINT64_C(11644473600000000);
  return tt;
}
#else
#include <sys/time.h>
uint64_t uepoch(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return 1000000LL * tv.tv_sec + tv.tv_usec;
}
#endif

int main(int argc, char **argv) {
  test = argv[1];
  /* Benchtest? */

  if (argc > 2) {
    uint64_t rng = strtoull(argv[2], 0, 16);
    unsigned long r = 0;
    uint64_t start = uepoch();
    for (int i = 0; i < 300; i++)
      r += bench(&rng);
    double t = (uepoch() - start) / 1e6;
    printf("%.6gs : actual %lu, expect 428859598\n", t, r);
    return 0;
  }
  /* volatile due to setjmp() / longjmp() */
  volatile int count_pass = 0;
  volatile int count_fail = 0;

  /* initialization, buf_free() */
  float *a = 0;
  TEST("capacity init", buf_capacity(a) == 0);
  TEST("size init", buf_size(a) == 0);
  buf_push(a, 1.3f);
  TEST("size 1", buf_size(a) == 1);
  TEST("value", a[0] == (float)1.3f);
  buf_clear(a);
  TEST("clear", buf_size(a) == 0);
  TEST("clear not-free", a != 0);
  buf_free(a);
  TEST("free", a == 0);

  /* Clearing an NULL pointer is a no-op */
  buf_clear(a);
  TEST("clear empty", buf_size(a) == 0);
  TEST("clear no-op", a == 0);

  /* buf_push(), [] operator */
  long *ai = 0;
  for (int i = 0; i < 10000; i++)
    buf_push(ai, i);
  TEST("size 10000", buf_size(ai) == 10000);
  int match = 0;
  for (int i = 0; i < (int)(buf_size(ai)); i++)
    match += ai[i] == i;
  TEST("match 10000", match == 10000);
  buf_free(ai);

  /* buf_grow(), buf_trunc() */
  buf_grow(ai, 1000);
  TEST("grow 1000", buf_capacity(ai) == 1000);
  TEST("size 0 (grow)", buf_size(ai) == 0);
  buf_trunc(ai, 100);
  TEST("trunc 100", buf_capacity(ai) == 100);
  buf_free(ai);

  /* buf_pop() */
  buf_push(a, 1.1);
  buf_push(a, 1.2);
  buf_push(a, 1.3);
  buf_push(a, 1.4);
  TEST("size 4", buf_size(a) == 4);
  TEST("pop 3", buf_pop(a) == (float)1.4f);
  buf_trunc(a, 3);
  TEST("size 3", buf_size(a) == 3);
  TEST("pop 2", buf_pop(a) == (float)1.3f);
  buf_pop(a);
  TEST("pop 1", buf_pop(a) == (float)1.2f);
  buf_pop(a);
  TEST("pop 0", buf_pop(a) == (float)1.1f);
  buf_pop(a);
  TEST("size 0 (pop)", buf_size(a) == 0);

  buf_free(a);
}
