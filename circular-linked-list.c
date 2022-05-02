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
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key; //data field
	struct Node* llink;
	struct Node* rlink; //link field
} listNode; //node 구조체 정의

/* 함수 리스트 */
int initialize(listNode** h); //listNode 초기화
int freeList(listNode* h); //listNode에 할당된 메모리를 free
int insertLast(listNode* h, int key); //listNode의 마지막 노드에 삽입 
int deleteLast(listNode* h); //listNode의 마지막 노드 삭제
int insertFirst(listNode* h, int key); //listNode의 첫 번째 노드에 삽입
int deleteFirst(listNode* h); //listNode의 첫 번째 노드 삭제
int invertList(listNode* h); //listNode의 순서 바꾸기

int insertNode(listNode* h, int key); //listNode에서 key 값이 매개변수 key보다 큰 노드 찾고 그 앞에 삽입한다. 
int deleteNode(listNode* h, int key); //listNode에서 매개변수 key 값에 해당하는 노드를 찾고 삭제한다.

void printList(listNode* h); //listNode의 모든 노드를 출력한다.



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	printf("[----- 김주훈 2020039027 -----]\n\n"); //이름 학번 출력

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


int initialize(listNode** h) { //listNode 초기화

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h; 
	(*h)->llink = *h; //원형 연결 리스트이므로 자기 자신을 가리킨다.
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){ //listNode에 잡혀있는 메모리를 free

	if(h->rlink == h) //listNode가 비어있을 때 
	{
		free(h);
		return 1;
	}

	listNode* p = h->rlink; //첫 노드 할당

	listNode* prev = NULL; //이전 노드를 가리키기 위한 포인터
	while(p != NULL && p != h) { //listNode의 끝까지
		prev = p; //현재의 노드 할당
		p = p->rlink; //다음 노드로 이동
		free(prev); //현재의 노드 free
	}
	free(h); //listNode의 headnode를 free
	return 0;
}



void printList(listNode* h) { //listNode의 모든 노드를 출력
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //headnode가 NULL일 때
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; //첫 노드 할당

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //다음 노드로 이동
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	//llink, headnode, rlink 출력

	i = 0;
	p = h->rlink; //첫 노드 할당
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; //다음 노드로 이동
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;
	//key값이 key인 노드 생성

	if (h->rlink == h) /* 첫 노드로 삽입 */
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
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL)
	//listNode가 비었을 때
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; //마지막 노드 할당

	/* link 정리 */
	nodetoremove->llink->rlink = h; //마지막에서 두 번째 노드가 headnode를 가리키게 함
	h->llink = nodetoremove->llink;
	//마지막 노드에 마지막에서 두 번째 노드를 할당

	free(nodetoremove);
	//마지막 노드 free

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;
	//key 값을 가진 노드 생성

	node->rlink = h->rlink;
	//첫 번째 노드를 가리키게 함
	h->rlink->llink = node;
	//첫 번째 노드의 왼쪽 노드가 되게 함
	node->llink = h;
	//왼쪽 노드가 h가 되게 함
	h->rlink = node;
	//첫 노드에 node 할당


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	//listNode가 비어있을 때

	listNode* nodetoremove = h->rlink;
	//첫 번째 노드에 대한 포인터

	/* link 정리 */
	nodetoremove->rlink->llink = h;
	//두 번째 노드의 왼쪽 노드가 headnode가 되게 함
	h->rlink = nodetoremove->rlink;
	//첫 번째 노드에 두 번째 노드 할당
	free(nodetoremove);
	//첫 번째 노드에 할당된 메모리 free

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;
	//역순으로 바꾸려면 전의 노드와 전의 전 노드에 대한 포인터가 필요하다.

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;
	//마지막 노드에 첫 번째 노드 할당

	while(n != NULL && n != h){ //listNode 끝까지 돌음
		trail = middle; //전의 값 저장
		middle = n; //현재의 값 저장
		n = n->rlink; //다음 값 이동
		middle->rlink = trail; //rlink가 전의 값을 가리키도록 함
		middle->llink = n; //llink가 다음 값을 가리키도록 함
	}

	h->rlink = middle; //rlink가 마지막 노드를 가리키게 함

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;
	//headnode가 NULL이면 삽입 못함

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;
	//key 값을 가진 노드 생성

	if (h->rlink == h) //listNode가 비어있을 때
	{
		insertFirst(h, key); //첫 번째에 삽입
		return 1;
	}

	listNode* n = h->rlink; //첫 노드 할당

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {
		if(n->key >= key) { //현재 노드의 key 값이 더 클 때까지 검사
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { //현재 노드가 첫 노드일 때
				insertFirst(h, key); //첫 노드에 삽입
			} else { /* 중간이거나 마지막인 경우 */
			//현재 노드 앞에 삽입
				node->rlink = n; //삽입하는 노드의 rlink가 현재 노드를 가리키게 함
				node->llink = n->llink; //삽입하는 노드의 llink가 현재 노드의 이전 노드를 가리키게 함
				n->llink->rlink = node; //현재 노드의 이전 노드가 삽입하는 노드를 가리키게 함
				n->llink = node; //현재 노드의 llink가 삽입하는 노드를 가리키게 함
			}
			return 0;
		}

		n = n->rlink; //다음 노드로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)
	//listNode가 비어있을 때
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; //n에 첫 노드 할당

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //첫 노드 삭제
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h); //마지막 노드 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; 
				n->rlink->llink = n->llink;
				free(n); //n에 할당된 메모리 free
			}
			return 0;
		}

		n = n->rlink; //n을 노드 오른쪽으로 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


