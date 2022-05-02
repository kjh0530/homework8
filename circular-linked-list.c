/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key; //data field
	struct Node* llink;
	struct Node* rlink; //link field
} listNode; //node ����ü ����

/* �Լ� ����Ʈ */
int initialize(listNode** h); //listNode �ʱ�ȭ
int freeList(listNode* h); //listNode�� �Ҵ�� �޸𸮸� free
int insertLast(listNode* h, int key); //listNode�� ������ ��忡 ���� 
int deleteLast(listNode* h); //listNode�� ������ ��� ����
int insertFirst(listNode* h, int key); //listNode�� ù ��° ��忡 ����
int deleteFirst(listNode* h); //listNode�� ù ��° ��� ����
int invertList(listNode* h); //listNode�� ���� �ٲٱ�

int insertNode(listNode* h, int key); //listNode���� key ���� �Ű����� key���� ū ��� ã�� �� �տ� �����Ѵ�. 
int deleteNode(listNode* h, int key); //listNode���� �Ű����� key ���� �ش��ϴ� ��带 ã�� �����Ѵ�.

void printList(listNode* h); //listNode�� ��� ��带 ����Ѵ�.



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	printf("[----- ������ 2020039027 -----]\n\n"); //�̸� �й� ���

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) { //listNode �ʱ�ȭ

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h; 
	(*h)->llink = *h; //���� ���� ����Ʈ�̹Ƿ� �ڱ� �ڽ��� ����Ų��.
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){ //listNode�� �����ִ� �޸𸮸� free

	if(h->rlink == h) //listNode�� ������� �� 
	{
		free(h);
		return 1;
	}

	listNode* p = h->rlink; //ù ��� �Ҵ�

	listNode* prev = NULL; //���� ��带 ����Ű�� ���� ������
	while(p != NULL && p != h) { //listNode�� ������
		prev = p; //������ ��� �Ҵ�
		p = p->rlink; //���� ���� �̵�
		free(prev); //������ ��� free
	}
	free(h); //listNode�� headnode�� free
	return 0;
}



void printList(listNode* h) { //listNode�� ��� ��带 ���
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //headnode�� NULL�� ��
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; //ù ��� �Ҵ�

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //���� ���� �̵�
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	//llink, headnode, rlink ���

	i = 0;
	p = h->rlink; //ù ��� �Ҵ�
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; //���� ���� �̵�
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;
	//key���� key�� ��� ����

	if (h->rlink == h) /* ù ���� ���� */
	{
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} else {
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL)
	//listNode�� ����� ��
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; //������ ��� �Ҵ�

	/* link ���� */
	nodetoremove->llink->rlink = h; //���������� �� ��° ��尡 headnode�� ����Ű�� ��
	h->llink = nodetoremove->llink;
	//������ ��忡 ���������� �� ��° ��带 �Ҵ�

	free(nodetoremove);
	//������ ��� free

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;
	//key ���� ���� ��� ����

	node->rlink = h->rlink;
	//ù ��° ��带 ����Ű�� ��
	h->rlink->llink = node;
	//ù ��° ����� ���� ��尡 �ǰ� ��
	node->llink = h;
	//���� ��尡 h�� �ǰ� ��
	h->rlink = node;
	//ù ��忡 node �Ҵ�


	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	//listNode�� ������� ��

	listNode* nodetoremove = h->rlink;
	//ù ��° ��忡 ���� ������

	/* link ���� */
	nodetoremove->rlink->llink = h;
	//�� ��° ����� ���� ��尡 headnode�� �ǰ� ��
	h->rlink = nodetoremove->rlink;
	//ù ��° ��忡 �� ��° ��� �Ҵ�
	free(nodetoremove);
	//ù ��° ��忡 �Ҵ�� �޸� free

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;
	//�������� �ٲٷ��� ���� ���� ���� �� ��忡 ���� �����Ͱ� �ʿ��ϴ�.

	/* ���� �ٲ� ��ũ ���� */
	h->llink = h->rlink;
	//������ ��忡 ù ��° ��� �Ҵ�

	while(n != NULL && n != h){ //listNode ������ ����
		trail = middle; //���� �� ����
		middle = n; //������ �� ����
		n = n->rlink; //���� �� �̵�
		middle->rlink = trail; //rlink�� ���� ���� ����Ű���� ��
		middle->llink = n; //llink�� ���� ���� ����Ű���� ��
	}

	h->rlink = middle; //rlink�� ������ ��带 ����Ű�� ��

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;
	//headnode�� NULL�̸� ���� ����

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;
	//key ���� ���� ��� ����

	if (h->rlink == h) //listNode�� ������� ��
	{
		insertFirst(h, key); //ù ��°�� ����
		return 1;
	}

	listNode* n = h->rlink; //ù ��� �Ҵ�

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL && n != h) {
		if(n->key >= key) { //���� ����� key ���� �� Ŭ ������ �˻�
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->rlink) { //���� ��尡 ù ����� ��
				insertFirst(h, key); //ù ��忡 ����
			} else { /* �߰��̰ų� �������� ��� */
			//���� ��� �տ� ����
				node->rlink = n; //�����ϴ� ����� rlink�� ���� ��带 ����Ű�� ��
				node->llink = n->llink; //�����ϴ� ����� llink�� ���� ����� ���� ��带 ����Ű�� ��
				n->llink->rlink = node; //���� ����� ���� ��尡 �����ϴ� ��带 ����Ű�� ��
				n->llink = node; //���� ����� llink�� �����ϴ� ��带 ����Ű�� ��
			}
			return 0;
		}

		n = n->rlink; //���� ���� �̵�
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)
	//listNode�� ������� ��
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; //n�� ù ��� �Ҵ�

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h); //ù ��� ����
			} else if (n->rlink == h){ /* ������ ����� ��� */
				deleteLast(h); //������ ��� ����
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink; 
				n->rlink->llink = n->llink;
				free(n); //n�� �Ҵ�� �޸� free
			}
			return 0;
		}

		n = n->rlink; //n�� ��� ���������� �̵�
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


