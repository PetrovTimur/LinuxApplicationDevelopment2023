#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct cell {
	int x;
	int y;
} cell;

int main(int argc, char const *argv[])
{
	int N = 6;
	char wall = '#';
	char path = '.';

	srandom(time(NULL));
	int x = random() % N;
	int y = random() % N;

	char visited[N][N];
	char maze[2 * N + 1][2 * N + 1];

	for (int i = 0; i < 2 * N + 1; i++)
		for (int j = 0; j < 2 * N + 1; j++)
			maze[i][j] = wall;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			maze[2 * i + 1][2 * j + 1] = path;
			visited[i][j] = 0;
		}


	cell stack[N * N];
	int top = -1;
	stack[++top] = (cell) { .x=x, .y=y };
	visited[x][y] = 1;

	while (top != -1) {
		cell cur = stack[top--];
		x = cur.x, y = cur.y;

		int k = 0;
		cell neighbors[4];
		for (int i = -1; i <= 1; i++) {
			for (int j = (abs(i) == 1 ? 0 : -1); j <= 1; j += 2) {
				if ((0 <= x + i) && (x + i < N) && (0 <= y + j) && (y + j < N) && (visited[x + i][y + j] == 0)) {
					neighbors[k++] = (cell) { .x = x + i, .y = y + j};
				}
			}
		}

		if (k > 0) {
			stack[++top] = cur;

			int next = random() % k;
			maze[2 * x + 1 + (neighbors[next].x - x)][2 * y + 1 + (neighbors[next].y - y)] = path;
			visited[neighbors[next].x][neighbors[next].y] = 1;
			stack[++top] = neighbors[next];
		}
	}

	for (int i = 0; i < 2 * N + 1; i++) {
		for (int j = 0; j < 2 * N + 1; j++)
			printf("%c", maze[i][j]);
		printf("\n");	
	}
	
	return 0;
}