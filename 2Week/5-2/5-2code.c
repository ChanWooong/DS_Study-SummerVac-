#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING 100
#define MAX_QUEUE_SIZE 3

typedef struct {
	int id;
	char name[MAX_STRING];
}element;

typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
}QueueType;

void init_queue(QueueType* q) {
	q->rear = -1;
	q->front = -1;
}

int is_full(QueueType* q)
{
	if (q->rear == MAX_QUEUE_SIZE - 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int is_empty(QueueType* q) {
	if (q->front == q->rear) {
		return 1;
	}
	else {
		return 0;
	}
}


void enqueue(QueueType* q, element item) {
	if (is_full(q)) {
		fprintf(stderr,"queue is full, not added\n");
		return;
	}
	q->data[++(q->rear)] = item;
}

void dequeue(QueueType* q) {
	if (is_empty(q)) {
		fprintf(stderr,"quie is empty, cannot delete element.\n");
		return;
	}
	q->rear--;
	element item = q->data[++(q->front)];
	
}

void queueShift(QueueType* q) {
	q->front = -1;
	for (int i = q->front + 1; i <= q->rear; i++) {
		q->data[i] = q->data[i + 1];
	}
}
int main() {
	char* commend;
	char* id;
	FILE* fp;
	fp = fopen("input.txt", "r");
	char* commend2;
	element list;
	char tmp[50];
	char* name;
	int n = 0;
	QueueType q;

	init_queue(&q);
	printf("***********************************************\n");
	while (1) {
		fgets(tmp, 50, fp);
		commend = strtok_s(tmp, " \n", &commend2);
		//printf("%s\n", commend);

		if (strcmp(commend, "add") == 0) {
			
			id = strtok_s(commend2, " \n", &commend2);
			name = strtok_s(commend2, " \n", &commend2);
			strcpy(list.name, name);
			list.id = atoi(id);
			//printf("%d %s\n", list.id, list.name);
			enqueue(&q,list);
			n++;
		}
		else if (strcmp(commend, "delete") == 0) {
			if (is_empty(&q)) {
				break;
			}

			dequeue(&q);
			

			n--;
		}
		else if (strcmp(commend, "qprint") == 0) {
			for (int i = q.front+1; i <= q.rear; i++) {
				printf("%d %s\n", q.data[i].id, q.data[i].name);
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
	for (int i = q.front+1 ; i <= q.rear; i++) {
		printf("%d %s\n", q.data[i].id, q.data[i].name);
	}
	fclose(fp);
}
