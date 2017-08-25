#include <stdio.h>
#include <memory.h>

#include "n.h"

static int consec[N+1][N+1];
static int lengths[N+1];

void
gengraph() {
  for (int i = 1; i <= N; i++) {
    int len = 0;
    for (int j = 1; j <= N; j++) {
      if (i == j) continue;
      if (j % i == 0 || i % j == 0) {
        consec[i][len++] = j;
      }
    }
    lengths[i] = len;
#if 0
    printf("%d: %d -- ", i, len);
    for (int k = 0; k < len; k++) {
      printf(" %d", consec[i][k]);
    }
    printf("\n");
#endif
  }
}

typedef unsigned char BIT;
static BIT used[N+1];

typedef unsigned char VAL;
/* static int curpos; */
static VAL result[N+1];
/* static int index[N+1]; */

static FILE* file;
static char fileName[100];

void printsoln(int len) {
  fprintf(file, "%d", result[0]);
  for (int i = 1; i < len; i++) {
    fprintf(file, ",%d", result[i]);
  }
  fprintf(file, "\n");
}

static int nlongest = 0;

void
iterate(int pos) {
  int val = result[pos];
  for (int i = 0; i < lengths[val]; i++) {
    int nextval = consec[val][i];
    if (used[nextval]) continue;
    result[pos + 1] = nextval;
    used[nextval] = 1;
    iterate(pos + 1);
    used[nextval] = 0;
  }
  if (pos > nlongest) {
    nlongest = pos;
    freopen(fileName, "w", file);
  }
  if (pos >= nlongest) {
    printsoln(pos + 1);
  }
}


void
gensolutions() {
  for (int i = 1; i <= N; i++) {
    used[i] = 1;
    result[0] = i;
    iterate(0);
    used[i] = 0;
  }
}


int
main() {
  sprintf(fileName, "search/csv/maxfor%d.csv", N);
  file = fopen(fileName, "w");
  memset(used, 0, sizeof(used));
  gengraph();
  gensolutions();
  fclose(file);
  return 0;
}
