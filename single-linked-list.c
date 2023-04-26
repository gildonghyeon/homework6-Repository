#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;



headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[------길동현 2022041025------\n]");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //command값을 입력받는다.

		switch(command) { //z나Z를 입력받았을때 headnode에 initialize(headnode)값을 대입한다.
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P': //p나 P를 입력받았을때 printList(headnode)를 실행한다.
			printList(headnode);
			break;
		case 'i': case 'I': //i나 I를 입력받았을때 key값을 스캔하고 insertNode 함수를 실행한다.
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D': //d나 D값을 입력받았을때 key값을 스캔하고 deleteNode함수를 실행한다.
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': //n이나 N값을 입력받았을때 key값을 스캔하고 insertLast 함수를 실행한다.
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': //e나E값을 입력받았을때 deleteLast 함수를 실행한다.
			deleteLast(headnode);
			break;
		case 'f': case 'F': //f나 F값을 입력받았을때 key값을 스캔하고 insertFirst 함수를 실행한다.
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': //t나 T값을 입력받았을때 deleteFirst함수를 실행한다.
			deleteFirst(headnode);
			break; 
		case 'r': case 'R': //r이나 R값을 입력받았을떄 inverList함수를 실행한다.
			invertList(headnode);
			break;
		case 'q': case 'Q': //q나 Q값을 입력받았을때 freeList함수를 실행한다.
			freeList(headnode);
			break;
		default: //다른 입력값을 받았을떄 경고를 띄운다.
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //입력값이 q나 Q가 아닐때 계속 실행한다.

	return 1;
}

headNode* initialize(headNode* h) {

	if(h != NULL)
		freeList(h);

	headNode* temp = (headNode*)malloc(sizeof(headNode)); //temp값을 동적할당한다.
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node값을 동적할당한다.
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;


	while(n != NULL) {
		if(n->key >= key) {
			if(n == h->first) {
				h->first = node;
				node->link = n;
			} else { 
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}


	trail->link = node;
	return 0;
}

int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node값을 동적할당한다.
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {
		n = n->link;
	}
	n->link = node;
	return 0;
}

int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node값을 동적할당한다.
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;


	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) {
				h->first = n->link;
			} else { 
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}


	printf("cannot find the node for key = %d\n", key);
	return 0;

}


int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;


	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}


	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}


	trail->link = NULL;
	free(n);

	return 0;
}

int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;
	free(n);

	return 0;
}

int invertList(headNode* h) {


	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
