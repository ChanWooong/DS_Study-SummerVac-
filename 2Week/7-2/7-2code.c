#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "error\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "error\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "error\n");
		exit(1);
	}
	else return s->data[s->top];
}

int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}

void infix_to_postfix(char exp[]) {

	int i = 0;
	char ch, top_op;
	char tmp[100]={0};
	int len = strlen(exp);
	FILE* fp2;
	fp2 = fopen("output.txt", "w");
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/':
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				tmp[i] = pop(&s);
				printf("%c", tmp[i]);
			fprintf(fp2, "%c", tmp[i]);
			push(&s, ch);
			break;
		case '(':
			push(&s, ch);
			break;
		case ')':
			top_op = pop(&s);
			while (top_op != '(') {
				tmp[i] = top_op;
				printf("%c", tmp[i]);
				fprintf(fp2, "%c", tmp[i]);
				top_op = pop(&s);
			}
			break;
		default:
			printf("%c", ch);
			fprintf(fp2, "%c", ch);
			break;
		}
	}
	while (!is_empty(&s)) {
		tmp[i] = pop(&s);
		printf("%c", tmp[i]);
		fprintf(fp2, "%c", tmp[i]);
	}
	fclose(fp2);
}
int main() {
	
	char str[50];
	char result[50];
	FILE* fp;


	fp = fopen("input.txt", "r");

	fgets(str, 50, fp);
	printf("postfix expression : %s\n", str);
	infix_to_postfix(str);
	
	
	fclose(fp);

}
