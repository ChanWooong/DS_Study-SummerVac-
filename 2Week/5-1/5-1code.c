#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 5
#define MAX_STRING 100

typedef struct {
	int id;
	char name[100];
}element;

element stack[MAX_STACK_SIZE];
int top = -1;

int is_empty()
{
	return (top == -1);
}

int is_full()
{
	return (top == (MAX_STACK_SIZE - 1));
}

void push(element item)
{
	if (is_full()) {
		printf("stack is full, cannot add element\n");
		return;
	}
	else stack[++top] = item;

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

int main() {
	char *commend;
	char *id;
	FILE* fp;
	fp = fopen("input.txt", "r");
	char* commend2;
	element list;
	char tmp[50];
	char* name;
	int n = 0;
	printf("***********************************************\n");
	while (1) {
		fgets(tmp, 50,fp);
		commend = strtok_s(tmp, " \n", &commend2);
		//printf("%s\n", commend);

		if (strcmp(commend, "push") == 0) {
			if (is_full()) {
				break;
			}
			id = strtok_s(commend2, " \n", &commend2);
			name = strtok_s(commend2, " \n", &commend2);
			strcpy(list.name, name);
			list.id = atoi(id);
		//	printf("%d %s\n", list.id, list.name);
			push(list);
			n++;
		}
		else if (strcmp(commend, "pop") == 0) {
			if (is_empty()) {
				break;
			}
			pop(&stack);
			n--;
		}
		else if (strcmp(commend, "sprint") == 0) {
			for (int i = n-1; i >=0; i--) {
				printf("%d %s\n", stack[i].id, stack[i].name);
			}
			printf("\n");
		}
		else if (strcmp(commend, "quit") == 0) {
			break;
		}
		else {
			printf("wrong message!\n");
		}

	}
	printf("currentstack elements : \n");
	for (int i = n - 1; i >= 0; i--) {
		printf("%d %s\n", stack[i].id, stack[i].name);
	}
	fclose(fp);
}	
