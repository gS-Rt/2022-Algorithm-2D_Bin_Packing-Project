#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct item {
	int width;
	int height;
	int id;
	int value; // 가치
	double gastarrain; // 단위당 가치
}item; //각 아이템은 고유의 가로와 세로의 크기를 가짐

typedef struct node {
	item thing;
	struct node* next;
}node;

void partition(node* L, node** L1, node** L2, int n) {
	node* tmp = L;
	*L1 = L;
	for (int i = 0; i < (n / 2) - 1; i++) {
		tmp = tmp->next;
	}
	*L2 = tmp->next;
	tmp->next = NULL;
}

node* merge(node** L1, node** L2) {
	node* p, * L;
	node* A = *L1;
	node* B = *L2;
	//정렬은 단위 크기당 가치가 높은 순, 높이가 높은 순, 너비가 좁은 순, id순으로 정렬됨.
	if (A->thing.gastarrain > B->thing.gastarrain) {
		L = A;
		A = A->next;
		p = L;
	}
	else if (A->thing.gastarrain < B->thing.gastarrain) {
		L = B;
		B = B->next;
		p = L;
	}
	else {
		if (A->thing.height > B->thing.height) {
			L = A;
			A = A->next;
			p = L;
		}
		else if (A->thing.height < B->thing.height) {
			L = B;
			B = B->next;
			p = L;
		}
		else {
			if (A->thing.width < B->thing.width) {
				L = A;
				A = A->next;
				p = L;
			}
			else if (A->thing.width > B->thing.width) {
				L = B;
				B = B->next;
				p = L;
			}
			else {
				if (A->thing.id < B->thing.id) {
					L = A;
					A = A->next;
					p = L;
				}
				else {
					L = B;
					B = B->next;
					p = L;
				}
			}
		}
	}

	while ((A != NULL) && (B != NULL)) {
		if (A->thing.gastarrain > B->thing.gastarrain) {
			p->next = A;
			A = A->next;
			p = p->next;
		}
		else if (A->thing.gastarrain < B->thing.gastarrain) {
			p->next = B;
			B = B->next;
			p = p->next;
		}
		else {
			if (A->thing.height > B->thing.height) {
				p->next = A;
				A = A->next;
				p = p->next;
			}
			else if (A->thing.height < B->thing.height) {
				p->next = B;
				B = B->next;
				p = p->next;
			}
			else {
				if (A->thing.width < B->thing.width) {
					p->next = A;
					A = A->next;
					p = p->next;
				}
				else if (A->thing.width > B->thing.width) {
					p->next = B;
					B = B->next;
					p = p->next;
				}
				else {
					if (A->thing.id < B->thing.id) {
						p->next = A;
						A = A->next;
						p = p->next;
					}
					else {
						p->next = B;
						B = B->next;
						p = p->next;
					}
				}
			}
		}
	}

	while (A != NULL) {
		p->next = A;
		p = A;
		A = A->next;
	}

	while (B != NULL) {
		p->next = B;
		p = B;
		B = B->next;
	}

	return L;
}

void mergeSort(node** L, int n) {
	node* L1, * L2, * p = *L;
	if (n > 1) {
		partition(p, &L1, &L2, n);
		if ((n % 2) == 0) {
			mergeSort(&L1, n / 2);
			mergeSort(&L2, n / 2);
		}
		else {
			mergeSort(&L1, n / 2);
			mergeSort(&L2, (n / 2) + 1);
		}
		*L = merge(&L1, &L2);
	}
}

void addList(node** L, int width, int height, int id, int value) {
	node* tmp = *L;
	node* newnode = (node*)malloc(sizeof(node));
	newnode->thing.width = width;
	newnode->thing.height = height;
	newnode->thing.id = id;
	newnode->thing.value = value;
	newnode->thing.gastarrain = (double)value / (double)(width * height);
	newnode->next = NULL;
	if (*L == NULL) {
		*L = newnode;
	}
	else {
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = newnode;
	}
}

node* deleteHead(node* L) {
	node* removed;
	if (L == NULL) {
		return NULL;
	}
	removed = L;
	L = removed->next;
	free(removed);
	return L;
}

node* deleteNode(node* L, node* pre) {
	node* removed;
	removed = pre->next;
	pre->next = removed->next;
	free(removed);
	return L;
}

void deleteList(node* L) {
	node* tmp = L;
	while (tmp != NULL) {
		L = L->next;
		free(tmp);
		tmp = L;
	}
}

void main() {
	int n, gaRo, seRo;
	int width, height, value;
	int sum = 0;
	node* things = NULL;

	printf("배낭의 가로와 세로를 입력해주세요");
	scanf("%d %d", &gaRo, &seRo);

	int** inven = (int**)malloc(sizeof(int*) * seRo); //배낭은 int 2차원 배열로 동적할당해 사용
	for (int i = 0; i < seRo; i++) {
		inven[i] = (int*)malloc(sizeof(int) * gaRo);
	}

	for (int i = 0; i < seRo; i++) {
		for (int j = 0; j < gaRo; j++) {
			inven[i][j] = 0;
		}
	}

	printf("물건의 수 입력");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("%d번의 너비, 높이, 가치 입력", i + 1);
		scanf("%d %d %d", &width, &height, &value);
		addList(&things, width, height, i + 1, value);
	}

	mergeSort(&things, n); //단위크기당 가치 순으로 정렬

	for (node* tmp = things; tmp != NULL; tmp = tmp->next) {
		printf("%d %d %d %d\n", tmp->thing.id, tmp->thing.width, tmp->thing.height, tmp->thing.value);
	}

	int w = 0, h = 0; //현재 검사 중인 x좌표와 y좌표
	int isSame = 1; // 인벤토리의 변화를 판단할 변수

	do {
		isSame = 1;
		int longest = 0; //넣은 물건 중 가장 긴 세로, 다음 가로줄의 시작 좌표 판단용
		w = 0;
		node* prt;
		node* tmp;
		for (prt = things, tmp = things; prt != NULL;) {
			if (prt->thing.width > gaRo - w || prt->thing.height > seRo - h) { //넣을 수 없는 물건이면
				tmp = prt;
				prt = tmp->next;
				continue; //다음 물건 확인
			}
			else { //넣을 수 있다면
				isSame = 0;
				sum += prt->thing.value;
				for (int i = h; i < h + prt->thing.height; i++) {
					for (int j = w; j < w + prt->thing.width; j++) {
						inven[i][j] = prt->thing.id; //가방에 넣기
					}
				}
				if (longest < prt->thing.height)
					longest = prt->thing.height; //가장 긴 물건인지 확인
				w += prt->thing.width; //x좌표 변경
				if (prt == things) {
					things = deleteHead(things);
					prt = things;
					tmp = things;
				}
				else {
					things = deleteNode(things, tmp);
					prt = tmp->next;
				}
			}
		}
		h += longest;
	} while (!isSame);

	printf("\n\n<%d 가치의 배낭>\n", sum);
	for (int i = 0; i < seRo; i++) {
		for (int j = 0; j < gaRo; j++) {
			printf("%3d", inven[i][j]);
		}
		printf("\n");
	}

	//동작할당 받은 것들 삭제
	deleteList(things);

	for (int i = 0; i < seRo; i++) {
		free(inven[i]);
	}
	free(inven);
}