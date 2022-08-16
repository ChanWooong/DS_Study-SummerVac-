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

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init_queue(QueueType* q) {
	q->rear = q->front = 0;
}

int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(QueueType* q) {

	return (q->front == q->rear);

}
void queue_print(QueueType* q) {
	printf("QUEUE(front=%d , rear=%d)", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear) {
				break;
			}
		} while (i != q->front);
	}
	printf("\n");
}
void enqueue(QueueType* q, element item) {
	if (is_full(q)) {
		fprintf(stderr, "queue is full, not added\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
void dequeue(QueueType* q) {
	int i = 0;
	if (is_empty(q)) {
		fprintf(stderr, "empty");
	}
	//q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	q->front = 0;
	for (i = q->front+1; i <= q->rear; i++) {
		q->data[i] = q->data[i + 1];
	}
	q->rear--;

	
}
element peek(QueueType* q) {
	if (is_empty(q)) {
		error("empty!");
		return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
	}
}

int main() {
	element garbage;
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
		//printf("%d %d\n", q.front, q.rear);
		fgets(tmp, 50, fp);
		commend = strtok_s(tmp, " \n", &commend2);
		//printf("%s\n", commend);

		if (strcmp(commend, "add") == 0) {

			id = strtok_s(commend2, " \n", &commend2);
			name = strtok_s(commend2, " \n", &commend2);
			strcpy(list.name, name);
			list.id = atoi(id);
			//printf("%d %s\n", list.id, list.name);
			enqueue(&q, list);
			n++;
		}
		else if (strcmp(commend, "delete") == 0) {
			if (is_empty(&q)) {
				printf("queue is empty!");
				break;
			}

			dequeue(&q);

			n--;
		}
		else if (strcmp(commend, "qprint") == 0) {
			//printf("%d %d\n", q.front, q.rear);
			for (int i = q.front + 1; i <= q.rear; i++) {
				printf("%d, %s\n", q.data[i].id, q.data[i].name);
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
	
	fclose(fp);
}
