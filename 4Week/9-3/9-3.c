#define _CRT_SECURE_NO_WARNINGS
//#define IS_EMPTY(first) (! (first) )
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;
listPointer first = NULL;

void insert(listPointer* first, int x) {
	listPointer node = (listPointer)malloc(sizeof(listPointer));
	node->data = x;
	if (!(*first)) {
		(*first) = node;
		node->link = node;
	}
	else {
		node->link = (*first)->link;
		(*first)->link = node;
		*first = node;
	}
	printf("%d\n", node->data);
}

void delete(listPointer* first, listPointer x) {
	listPointer removed;
	if (*first == NULL) return;
	//if (x->link ==  * first) {
	//	(*first) = x;
	//}
	removed = x->link;
	x->link = removed->link;

	//free(removed);
}

void deleteOddList(listPointer first, int n) {
	listPointer p;
	p = (listPointer)malloc(sizeof(listPointer));
	p = first;
	for (int i = 0; i < n-1; i++) {
		if (p->link->link->data % 2 != 0) {
			printf("%d\n", p->link->link->data);
			delete(&first, p->link);
			i++;
		}
		if (p->link->data % 2 != 0) {
			printf("%d\n", p->link->data);
			i++;
			delete(&first, p);
		}
		p = p->link;
	}
}

void printList(listPointer first) {
	listPointer temp;
	printf("The ordered list contains :\n");
	temp = first;
	if (first) {
		do {
			printf(" (%p, %4d, %1p)\n", temp, temp->data, temp->link);
			temp = temp->link;
		} while (temp != first);
	//	printf(" (%p, %4d, %1p)", temp, temp->data, temp->link);
	}

}
int length(listPointer first) {
	listPointer temp;
	temp = first;
	int i = 0;
	if (first) {
		do {
			i++;
			temp = temp->link;
		} while (temp != first);
	}
	return i;
}
int main() {
	FILE* fp;
	int n;
	fp = fopen("input.txt", "r");
	while (!feof(fp)) {
		fscanf(fp, "%d", &n);
		insert(&first, n);
	}
	first = first->link;
	printList(first);
	//printf("%d", length(first));
	deleteOddList(first,length(first));
	printf("\n");
	//printf("%d", first->data);
	printList(first);
}
