#include <stdio.h>
#include <memory.h>

#define N 35

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

typedef int BIT;
static BIT used[N+1];

typedef int VAL;
/* static int curpos; */
static VAL result[N+1];
/* static int index[N+1]; */

void printsoln(len) {
  printf("[%d]", len);
  for (int i = 0; i < len; i++) {
    printf(" %d", result[i]);
  }
  printf("\n");
}

static int nlongest = 0;

void
iterate(pos) {
  int havelegal = 0;
  int val = result[pos];
  for (int i = 0; i < lengths[val]; i++) {
    int nextval = consec[val][i];
    if (used[nextval]) continue;
    havelegal = 1;
    result[pos + 1] = nextval;
    used[nextval] = 1;
    iterate(pos + 1);
    used[nextval] = 0;
  }
  /* if (!havelegal && pos + 1 == 9) { */
  if (pos >= nlongest) {
    nlongest = pos;
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
  memset(used, 0, sizeof(used));
  gengraph();
  gensolutions();

  return 0;
}


#if 0
void iterate() {
  int val = result[curpos];

  // step forward
  int nextval = consec[val][index[curpos]];
  if (!used[nextval]) {
    result[curpos + 1] = nextval;
    index[curpos + 1] = i;
    used[nextval] = 1;
  }
  index[curpos]++;

  // step back
  while (index[curpos] == len[val]) {
    used[val] = 0;
    curpos--;
    val = result[curpos];
  }
}
#endif
