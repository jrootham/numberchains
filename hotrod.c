#include <stdio.h>
#include <memory.h>
#include <stdbool.h>

#include "n.h"

static int consec[N+1][N+1];
static int lengths[N+1];
typedef int BIT;
static BIT used[N+1];
typedef int VAL;
static int rightpos;
static int leftpos;
static VAL result[2 * N + 1];
/* static int index[N+1]; */

bool
isPrime(unsigned int n) {
	return !((0 == n % 2) || (0 == n % 3) || (0 == n % 5) || (0 == n % 7));
}

void
gengraph() {
  for (int i = 1; i <= N; i++) {
    int len = 0;
    for (int j = 2; j <= N; j++) {
      if (i == j) continue;
      if (j > (N / 2) && isPrime(j)) continue;
      if (j % i == 0 || i % j == 0) {
        consec[i][len++] = j;
      }
    }
    lengths[i] = len;
#if 1
    printf("%d: %d -- ", i, len);
    for (int k = 0; k < len; k++) {
      printf(" %d", consec[i][k]);
    }
    printf("\n");
#endif
  }
}

void 
gensolutions() {
	used[1] = 1;
	result[N] = 1;
	leftpos = N;
	rightpos = N;


}


int
main() {
  memset(used, 0, sizeof(used));
  gengraph();
  gensolutions();

  return 0;
}
