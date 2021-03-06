```
// CSE591-Assignment1.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include "map"
#define new_node (struct node*)malloc(sizeof(struct node))
#define new_element (struct element*)malloc(sizeof(struct element))
#define new_elenode (struct elenode*)malloc(sizeof(struct elenode))
#define MAXN 501
#define MAXM 1000

typedef struct {
	int ver1;
	int ver2;
}E_NODE;

struct node
{
	int vertex;
	struct node *next;
};

typedef node L_NODE;

struct element
{
	int key;
	node* dom_e;
	bool isInR = false;
	bool isInT = false;
};

struct elenode
{
	element* evalue;
	struct elenode* next;
};

bool isExistInList(int v, elenode* targetList);
void create_adj_list(L_NODE *head[], int n, E_NODE e[], int m);
elenode* ReachableVertices(node* sList, L_NODE *head[]);
elenode* Init(E_NODE e[], int m, L_NODE *head[]);
void insert(elenode** p_head, int v, L_NODE* dmoe, bool isinR, bool isinT);

bool isExistInList(int v, elenode* targetList)
{
	if (targetList == NULL) return false;
	for (elenode* p = targetList; p!= NULL; p = p->next) {
		if (p->evalue->key == v) {
			return true;
		}
	}

	return false;
}

void deleteFromList(int v, elenode** p_head)
{
	elenode *p, *q;
	q = *p_head;
	if (q == NULL) return;
	if (q->evalue->key == v) {
		*p_head = q->next;
		free(q);
		return;
	}

	while(q->evalue->key != v && q->next != NULL) {
		p = q;
		q = q->next;
	}
    if(q->evalue->key == v){
		p->next = q->next;
		free(q);
	}
}

elenode* ReachableVertices(node* sList, L_NODE *head[])
{
	elenode* w = NULL;
	elenode* t = NULL;
	elenode* r = NULL;

	for (node *x = sList; x != NULL; x = x->next) {
		node* eList = head[x->vertex];
		for (node* y = eList; y != NULL; y = y->next) {
			if (!isExistInList(y->vertex, t)) {
				if (!isExistInList(y->vertex, r)) {
					insert(&w, y->vertex, eList, false, false);
				}

				insert(&t, y->vertex, eList, false, true);
			}
		}

		if (isExistInList(x->vertex, t)) {
			deleteFromList(x->vertex, &w);
		}

		insert(&r, x->vertex, eList, true, false);
	}

	while (w != NULL) {
		int insertnode = w->evalue->key;
		node* eList = head[w->evalue->key];
		for (node* y = eList; y!= NULL; y = y->next) {
			if (!isExistInList(y->vertex, t)) {
				if (!isExistInList(y->vertex, r)) {
					insert(&w, y->vertex, eList, false, false);
				}

				insert(&t, y->vertex, eList, false, true);
			}
		}

		if (isExistInList(w->evalue->key, t)) {
			insertnode = w->evalue->key;
			deleteFromList(w->evalue->key, &w);
		}

		insert(&r, insertnode, eList, true, false);
	}

	return r;
}

void create_adj_list(L_NODE *head[], int n, E_NODE e[], int m)
{
	L_NODE* p;
	for (int i = 0; i <= n; i++) {
		head[i] = NULL;
	}

	for (int i = 0; i < m; i++) {
		int u = e[i].ver1;
		int v = e[i].ver2;
		p = (L_NODE*)malloc(sizeof(L_NODE));
		p->vertex = v;
		p->next = head[u];
		head[u] = p;
		//p = (L_NODE*)malloc(sizeof(L_NODE));
		//p->vertex = u;
		//p->next = head[v];
		//head[v] = p;
	}
}

 void insert(elenode** p_head, int v, L_NODE* dmoe, bool isinR, bool isinT)
 {
	 elenode* p, *q;
	 q = new_elenode;
	 q->evalue = new_element;
	 q->evalue->key = v;
	 q->evalue->dom_e = dmoe;
	 q->evalue->isInR = isinR;
     q->evalue->isInT = isinT;
	 q->next = NULL;
	 if (*p_head == NULL)
		 *p_head = q;
	 else
	 {
		 p = *p_head;
		 while (p->next != NULL)
			 p = p->next;
		 q->next = p->next;
		 p->next = q;
	 }
 }

 elenode* Init(E_NODE e[], int m, L_NODE *head[])
 {
	 elenode* h = NULL;
	 for (int i = 0; i < m; i++) {
		 if (!isExistInList(e[i].ver1, h)) {
			 insert(&h, e[i].ver1, head[e[i].ver1], false, false);
		 }

		 if (!isExistInList(e[i].ver2, h)) {
			 insert(&h, e[i].ver2, head[e[i].ver2], false, false);
		 }
	 }

	 return h;
 }

 void readinfile(E_NODE e[])
 {
	 FILE *file = fopen("C:\\Users\\SPY\\Desktop\\reach1000in.txt", "r");
	 if (file == NULL)
	 {
		 printf("the file is opeaned error!\n");
	 }

	 int i = 0;
	 int num1, num2;
	 char ch = fgetc(file);
	 bool nextisnum = false;
	 while (ch != EOF) {
		 ch = fgetc(file);
		 if (ch == '(') {
			 fscanf(file, "%d", &num1);
			 e[i].ver1 = num1;

			 char nextch1 = fgetc(file);
			 char nextch2 = fgetc(file);
			 fscanf(file, "%d", &num2);
			 e[i].ver2 = num2;
			 i++;
		 }
	 }
	 fclose(file);
 }

 int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int main()
{
	L_NODE *head[MAXN];
	E_NODE e[MAXM];
	readinfile(e);

	//e[0].ver1 = 0;
	//e[0].ver2 = 1;
	//e[1].ver1 = 1;
	//e[1].ver2 = 2;
	//e[2].ver1 = 1;
	//e[2].ver2 = 5;
	//e[3].ver1 = 2;
	//e[3].ver2 = 5;
	////e[4].ver1 = 6;
	////e[4].ver2 = 7;
	////e[5].ver1 = 2;
	////e[5].ver2 = 6;
	////e[6].ver1 = 6;
	////e[6].ver2 = 6;


	create_adj_list(head, MAXN - 1, e, MAXM);
	elenode* h = Init(e, MAXM, head);

	node* sList = new_node;
	sList->vertex = 144;
	sList->next = NULL;
	elenode* result = ReachableVertices(sList, head);

	int re[1000] = { 0 };
	int i = 0;
	for (elenode* p = result; p != NULL; p = p->next)
	{
		re[i] = p->evalue->key;
		i++;
	}

	qsort(re, i - 1, sizeof(int), cmp);
	int cor[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 16, 17, 18, 20, 21, 22, 23, 25, 26, 27, 28, 30, 31, 32, 33, 34, 36, 38, 40, 41, 42, 43, 44, 45, 46, 48, 49, 51, 52, 53, 54, 57, 58, 59, 60, 61, 62, 63, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 83, 87, 88, 89, 90, 91, 92, 94, 95, 96, 97, 101, 102, 103, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 119, 120, 121, 123, 124, 125, 127, 128, 130, 131, 132, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 165, 166, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 180, 181, 182, 183, 184, 186, 187, 188, 189, 191, 192, 193, 195, 196, 197, 199, 200, 202, 203, 204, 206, 207, 208, 209, 210, 212, 213, 214, 215, 216, 217, 219, 220, 221, 222, 223, 225, 227, 228, 229, 230, 231, 233, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 248, 249, 250, 251, 252, 256, 257, 258, 261, 264, 265, 266, 268, 269, 270, 271, 272, 275, 276, 278, 280, 281, 282, 283, 284, 285, 286, 287, 288, 290, 291, 292, 294, 295, 296, 297, 298, 299, 300, 301, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 314, 315, 316, 318, 319, 321, 322, 323, 324, 325, 326, 328, 329, 333, 334, 335, 336, 337, 338, 341, 343, 344, 345, 346, 347, 348, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 363, 365, 366, 367, 368, 369, 371, 372, 373, 376, 378, 379, 380, 382, 384, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 397, 398, 399, 400, 401, 402, 404, 405, 406, 407, 408, 409, 411, 412, 414, 416, 417, 418, 419, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 433, 434, 435, 436, 438, 439, 440, 441, 442, 443, 445, 446, 447, 449, 450, 451, 452, 453, 454, 456, 458, 459, 460, 461, 462, 464, 465, 467, 469, 471, 472, 473, 474, 475, 476, 477, 479, 480, 482, 484, 486, 487, 488, 489, 490, 492, 493, 494, 495, 496, 497, 498, 499 };

	FILE *file = fopen("C:\\Users\\SPY\\Desktop\\output.txt", "wt+");
	if (file == NULL)
	{
		printf("the file is opeaned error!\n");
	}

	fputc('{', file);
	int n = 0;
	for (; n < i - 2; n++)
	{
		////if (re[n] != cor[n]) {
		////	printf("%d is not equal\n", re[n]);
		////}

		fprintf(file, "%d, ", re[n]);
	}

	fprintf(file, "%d", re[n]);
	fputc('}', file);
	fclose(file);

    return 0;
}

```
