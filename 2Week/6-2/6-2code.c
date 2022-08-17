#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING 100
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0
int EXIT_ROW; EXIT_COL;
typedef struct {
	short int vert;
	short int horiz;
}offsets;
offsets move[8]={ {-1, 0}, { -1,1 }, { 0,1 }, { 1,1 }, { 1,0 },{1, -1}, { 0,-1 }, { -1,-1 }};
typedef struct {
	short int row;
	short int col;
	short int dir;
}element;
element stack[MAX_STACK_SIZE];
int mark[100][100]={0};
int maze[50][50]={0};
int top = -1;
void init_stack() {
	top = -1;
}

int is_empty() {
	return (top == -1);
}

int is_full() {
	return (top == (MAX_STACK_SIZE - 1));
}

void push(element item) {
	if (is_full()) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else stack[++(top)] = item;
}
element pop()
{
	if (is_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return stack[top--];
}

element peek()
{
	if (is_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return stack[top];
}
void path(void)
{
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
	while (top > -1 && !found) {
		position = pop();
		row = position.row; col = position.col;
		dir = position.dir;
		while (dir < 8 && !found) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL) {
				found = TRUE;
			}
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row; position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;

			}
			else ++dir;

		}
	}
	if (found) {
		printf("The path is: \n");
		printf("row	  col\n");
		for (i = 0; i <= top; i++) {
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		}
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	else printf("The maze does not have a path\n");
}
int main() {
	FILE* fp;
	fp = fopen("input.txt", "r");
	char ch;
	int i = 1;
	int j = 1;
	fscanf(fp, "%d %d", &EXIT_ROW, &EXIT_COL);
	while (1){
		if (j == EXIT_COL+1) {
			i++;
			j = 1;
		}
		ch = fgetc(fp);
		if (ch == EOF) {
			break;
		}
		
		else if(ch == '1') {
			maze[i][j] = 1;
			j++;
		}
		else if (ch == '0') {
			maze[i][j] = 0;
			j++;
		}
	}
	for (int i = 0; i <= EXIT_ROW+1; i++) {
		for (int j = 0; j <= EXIT_COL+1; j++) {
			if (i == 0 || i == EXIT_ROW + 1) {
				maze[i][j] = 1;
			}
			else if (j == 0 || j == EXIT_COL + 1) {
				maze[i][j] = 1;
			}
		}
	}

	init_stack();
	path();
}
