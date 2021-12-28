#include <stdio.h>
#include <memory.h>
#include <stdbool.h>

#include "n.h"

typedef unsigned int BIT;
typedef unsigned int VAL;
typedef unsigned int INDEX;

static VAL consec[N+1][N+1];
static INDEX lengths[N+1];
static BIT used[N+1];
static INDEX rightpos;
static INDEX leftpos;
static VAL result[2 * N + 1];
static VAL value;
static VAL previous;
static INDEX indices[2 * N + 1];
static INDEX index;
static bool found;

static int nlongest = 0;
static FILE *file;
static char fileName[100];

void 
showAll(char *where){
  printf("Where %s leftpos %d rightpos %d\n", where, leftpos, rightpos);

  printf("Used: ");
  for (int i = 0 ; i < N + 1 ; i++) {
    printf("%d:%d ", i, used[i]);
  }
  printf("\n");

  printf("Result: ");
  for (int i = leftpos ; i <= rightpos ; i++) {
    printf("%d ", result[i]);
  }
  printf("\n");

  printf("Indices: ");
  for (int i = leftpos ; i <= rightpos ; i++) {
    printf("%d ", indices[i]);
  }
  printf("\n");
}


bool
isPrime(VAL n) {
	return !((0 == n % 2) || (0 == n % 3) || (0 == n % 5) || (0 == n % 7));
}

void
gengraph() {
  for (INDEX i = 1; i <= N; i++) {
    INDEX len = 0;
    for (INDEX j = 2; j <= N; j++) {
      if (i == j) continue;
      if (j > 20 && (j > (N / 2)) && isPrime(j)) continue;
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

void printsoln(INDEX start, INDEX end) {
  fprintf(file, "%d", result[start]);
  for (int i = start + 1; i <= end; i++) {
    fprintf(file, ",%d", result[i]);
  }
  fprintf(file, "\n");
}

void forwardRight(){
bool debug = false;
  do {
    value = consec[result[rightpos - 1]][indices[rightpos - 1]];
    result[rightpos] = value;
    used[value] = 1;

if (result[N + 1] == 9) {
  debug = true;
  for (int i = N ; i <= rightpos ; i++) {
    printf("%d ", result[i]);
  }
  printf("\n");
}

    found = false;
    for (index = 0 ; index < lengths[value] ; index++) {
      if (!used[consec[value][index]]) {
        indices[rightpos++] = index;
        found = true;
        break;
      }
    }

    if (!found) {
      indices[rightpos] = lengths[value];
    }
  } while (found);
if (debug) printf("End of forwardRight\n");
}

void forwardLeft(){
  do {
    value = consec[result[leftpos + 1]][indices[leftpos]];
    result[leftpos] = value;
    used[value] = 1;

    found = false;
    for (index = 0 ; index < lengths[value] ; index++) {
      if (!used[consec[value][index]]) {
        indices[--leftpos] = index;
        found = true;
        break;
      }
    } 

  } while (found);
}

void backupLeft() {
  used[result[leftpos]] = 0;
  
  do {
    previous = result[leftpos + 1]; 
    do {
      indices[leftpos]++;
      if (indices[leftpos] >= lengths[previous]){
        break;
      }
    } while (used[consec[previous][indices[leftpos]]]);

    if (indices[leftpos] >= lengths[previous]) {
      if (N <= ++leftpos) {
        break;
      } 
      else {
        used[result[leftpos]] = 0;
        previous = result[leftpos + 1];
        do {
          indices[leftpos]++;          
        } while (used[consec[previous][indices[leftpos]]]);
      }
    }    
  } while (indices[leftpos] >= lengths[previous]);
}

void backupRight() {
  used[result[rightpos]] = 0;
  
  do {
    previous = result[rightpos - 1]; 
    do {
      indices[rightpos - 1]++;
      if (indices[rightpos - 1] >= lengths[previous]){
        break;
      }
    } while (used[consec[previous][indices[rightpos - 1]]]);

    if (indices[rightpos - 1] >= lengths[previous]) {
      if (N >= --rightpos) {
        break;
      } 
      else {
        used[result[rightpos]] = 0;
        do {
          indices[rightpos - 1]++;          
        } while (used[consec[result[rightpos - 1]][indices[rightpos - 1]]]);
      }
    }
    
  } while (indices[rightpos - 1] >= lengths[result[rightpos - 1]]);
}

void 
gensolutions() {
	result[N] = 1;
  indices[N] = 0;
	rightpos = N + 1;

  do {
// Forward right
    forwardRight();
// Complete left search

    leftpos = N - 1;
    index = 0;
    while (used[consec[1][index]]) {
      index++;
    }
    indices[N - 1] = index;

    do {
      forwardLeft();
// Forward left
// display
      if (((rightpos - leftpos) + 1) > nlongest) {
        nlongest = ((rightpos - leftpos) + 1);
        file = freopen(fileName, "w", file);
      }
      if (((rightpos - leftpos) + 1) >= nlongest) {
        printsoln(leftpos, rightpos);
      }

// back up left
      backupLeft();

    } while (leftpos < N);
// Back up right

    backupRight();
  } while (rightpos > N);
}


int
main() {
  sprintf(fileName, "hotrod/csv/maxfor%d.csv", N);
  file = fopen(fileName, "w");
  memset(used, 0, sizeof(used));
  gengraph();
  gensolutions();

  return 0;
}
