#define _CRT_SECURE_NO_WARNINGS
//#define IS_EMPTY(first) (! (first) )
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode* listPointer;
typedef struct element {
	char name[30];
	char school[30];
	char gender[30];
}element;
typedef struct listNode {
	element data;
	listPointer link;
}listNode;
listPointer first = NULL;
listPointer man = NULL;
listPointer woman = NULL;

void insert(listPointer* first, element data) {
	listPointer temp, p, m, w;
	p = (listPointer*)malloc(sizeof(*p));
	p = *first;
	temp = (listPointer*)malloc(sizeof(*temp));
	temp->data = data;

	if (*first == NULL) {
		temp->link = *first;
		*first = temp;
	}

	else {
		while (p->link != NULL) {
			p = p->link;
		}
		temp->link = p->link;
		p->link = temp;
	}

}
void search(listPointer* first, char gender[], listPointer* cmp) {
	listPointer p = first;
	while (p != NULL) {
		if (strcmp(p->data.gender, gender) == 0) {
			(* cmp)->link = p;
		}
		p = p->link;
	}
}
void delete(listPointer* first, listPointer x) {
	listPointer removed;
	if (*first == NULL) return;

	removed = x->link;
	x->link = removed->link;

	free(removed);

}
void printList(listPointer first) {
//	printf("The ordered list contains :\n");
	for (;first;first = first->link) {
		printf(" (%p, %2s %2s %2s %1p)\n",first->data, first->data.name, first->data.school, first->data.gender, first->link);
	}
}
int main() {
	FILE* fp;
	element data;
	int count = 0;
	fp = fopen("input.txt", "r");
	while (!feof(fp)) {
		fscanf(fp, "%s %s %s", data.name, data.school, data.gender);
		insert(&first, data);
		count++;
	}
	
	printList(first);
	listPointer m_pre = NULL;
	listPointer w_pre = NULL;
	listPointer p = first;
	listPointer m = NULL;
	listPointer w = NULL;

	while (1) {
		if (p == NULL) {
			break;
		}
		if (strcmp(p->data.gender, "남자")== 0) {

			if (m != NULL) {
				m_pre->link = p;
			}
			else {
				m = p;
			}
			m_pre = p;
		}
		else {
			if (w != NULL) {
				w_pre->link = p;
			}
			else {
				w = p;
			}
			w_pre = p;
		}

		p = p->link;
	
	}
	m_pre->link = NULL;
	w_pre->link = NULL;

	printf("남자 리스트 \n");
	printList(m);
	printf("\n여자 리스트 \n");
	printList(w);
}
