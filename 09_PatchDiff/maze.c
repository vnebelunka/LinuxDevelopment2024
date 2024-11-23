#include <stdio.h>
#include <stdlib.h>

int N;

void unfold(int v, int *i, int *j) {
  *i = v / N;
  *j = v % N;
}
int fold(int i, int j) { return i * N + j; }

int ingraph(int i, int j) { return i >= 0 && i < N && j >= 0 && j < N; }

void neighbors(int v, int res[4]) {
  int i, j;
  int count = 0;
  unfold(v, &i, &j);
  if (ingraph(i - 1, j)) {
    res[count++] = fold(i - 1, j);
  }
  if (ingraph(i + 1, j)) {
    res[count++] = fold(i + 1, j);
  }
  if (ingraph(i, j - 1)) {
    res[count++] = fold(i, j - 1);
  }
  if (ingraph(i, j + 1)) {
    res[count++] = fold(i, j + 1);
  }
  for (; count < 4; ++count) {
    res[count] = -1;
  }
}

int *visited;
int visited_count;
int *edge_vec;
int **field;

void add_edge() {
  int temp[4];
  int edge_count = 0;
  for (int i = 0; i < visited_count; ++i) {
    neighbors(visited[i], temp);
    for (int j = 0; j < 4; ++j) {
      // fprintf(stderr, "%d\n", temp[j]);
      int flag = temp[j] != -1;
      for (int k = 0; flag && k < visited_count; ++k) {
        flag &= temp[j] != visited[k];
      }
      if (flag) {
        edge_vec[edge_count++] = temp[j] * (N * N) + visited[i];
      }
    }
  }
  int rand_choice = rand() % edge_count;
  int start = edge_vec[rand_choice] % (N * N);
  int end = edge_vec[rand_choice] / (N * N);
  int i, j;
  unfold(end, &i, &j);
  int i1, j1;
  unfold(start, &i1, &j1);
  field[2 * i + 1][2 * j + 1] = 1;
  field[i + i1 + 1][j + j1 + 1] = 1;
  visited[visited_count++] = end;
}

int main(int argc, char **argv) {
  N = 6;
  int sz = N * N;
  visited = calloc(sz, sizeof(int));
  edge_vec = calloc(4 * sz, sizeof(int));
  field = calloc(2 * N + 1, sizeof(int *));
  for (int i = 0; i < 2 * N + 1; ++i) {
    field[i] = calloc(2 * N + 1, sizeof(int));
    for (int j = 0; j < 2 * N + 1; ++j) {
      field[i][j] = 0;
    }
  }
  int rand_choice = rand() % sz;
  visited[0] = rand_choice;
  int i, j;
  unfold(rand_choice, &i, &j);
  field[2 * i + 1][2 * j + 1] = 1;
  visited_count = 1;
  for (; visited_count < sz;) {
    add_edge();
  }
  for (int i = 0; i < 2 * N + 1; ++i) {
    for (int j = 0; j < 2 * N + 1; ++j) {
      if (field[i][j]) {
        printf(".");
      } else {
        printf("#");
      }
    }
    printf("\n");
  }

  free(visited);
  free(edge_vec);
  for (int i = 0; i < 2 * N + 1; ++i) {
    free(field[i]);
  }
  free(field);
}
