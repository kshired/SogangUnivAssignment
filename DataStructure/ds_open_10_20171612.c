#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 30

//한 정점을 시작점으로 깊이우선 탐색했을 때 각 정점을 방문하는 순서
short int dfn[MAX_VERTICES];
//u의 후손들과 많아야 하나의 백 간선으로 된 경로를 이용하여 u로부터 도달할 수 있는 가장 적은 dfn번호
short int low[MAX_VERTICES];

//이하 그래프
typedef struct node *node_pointer;
typedef struct node {
	int vertex;
	node_pointer link;
}node;
void init();
void bicon(int u, int v);
int insert_graph(node_pointer *headnode, int vertex1, int vertex2);
node_pointer graph[MAX_VERTICES];
int vertices;
int num;


//이하 스택
typedef struct stack *stack_pointer;
typedef struct stack {
	int vertex1;
	int vertex2;
	stack_pointer link;
}stack;
stack_pointer top;
void push(stack_pointer *top, int v1, int v2);
void pop(stack_pointer *top, int *v1, int *v2);


int main() {
	int a[30][30];
	FILE *f = fopen("input.txt", "r");
	int i=0;
	int repetition;
	int vertex, vertex1, vertex2;
	int maxedge;
	int k = 0;
	int count = 0;
	char tmp1[30][50];
	int temp, temp2;
	fscanf(f, "%d", &vertices);
	fgetc(f);
	maxedge = vertices *(vertices-1)/2;
	//각 줄 받아와서 한 줄씩 처리.
	for(int j =0; j<vertices; j++)
		fgets(&tmp1[j][0], 49, f);
	for(int j=0; j<vertices; j++) {
		sscanf(&tmp1[j][k], "%d ", &vertex1);
		k+=2;
		while(1) {
			if(sscanf(&tmp1[j][k], "%d ", &vertex2)==EOF) //한줄이 끝나면 break
				break;
			else {
				vertex = vertex1;
				i=0;
				repetition=0;
				while((i++ < 2)&& !repetition) {
					if((repetition = insert_graph(&graph[vertex], vertex, vertex2)))
						count -= 1;
					vertex = vertex2;
					vertex2 = vertex1;
				}
				k+=2;
			}
		}
		k = 0;
	}
	init();
	bicon(3, -1);
	fclose(f);
}
// 인접리스트 저장
int insert_graph(node_pointer *headnode, int vertex1, int vertex2) {
	int repetition = 0;
	node_pointer element, trail, lists;
	if(!(*headnode)) {
		lists = (node_pointer)malloc(sizeof(node));
		lists->vertex = vertex2;
		lists->link = NULL;
		*headnode = lists;
	}
	else {
		for(trail = *headnode; trail; trail = trail->link) {
			element = trail;
			if(trail->vertex == vertex2) {
				repetition = 1;
				break;
			}
		}
		if(!repetition) {
			lists = (node_pointer)malloc (sizeof(node));
			lists->vertex = vertex2;
			lists->link = NULL;
			element->link = lists;
		}
		else
			return repetition;
	}
	return repetition;
}
//dfn ,low 초기화
void init() {
	int i;
	for(i=0; i<MAX_VERTICES; i++)
		dfn[i] = low[i] = -1;
	num = 0;
}
//이중결합요소 구하기 [최대 이중결합 부분그래프(maximal biconnected subgraph)]
void bicon(int u, int v) {
	node_pointer ptr;
	int w, x, y;
	dfn[u] = low[u] = num++;
	for(ptr = graph[u]; ptr; ptr = ptr->link) {
		w = ptr->vertex;
		if(v!= w && dfn[w] < dfn[u])
			push(&top, u, w);
		if(dfn[w]<0) {
			bicon(w, u);
			low[u] = low[u] < low[w] ? low[u] : low[w];
			if(low[w] >= dfn[u]) {
				printf("Biconnected component : ");
				do {
					pop(&top, &x, &y);
					printf("[ %d, %d ] ", x, y);
				} while(!((x == u) && (y == w)));
				printf("\n");
			}
		}
		else if(w!=v)
			low[u] = low[u] < dfn[w] ? low[u] : dfn[w];
	}
}
//스택 푸시
void push(stack_pointer *top, int v1, int v2) {
	stack_pointer temp = (stack_pointer)malloc(sizeof(stack));
	temp->vertex1 = v1;
	temp->vertex2 = v2;
	temp->link = *top;
	*top = temp;
}
//스택 팝
void pop(stack_pointer *top, int *v1, int *v2) {
	stack_pointer temp = *top;
	*v1 = temp->vertex1;
	*v2 = temp->vertex2;
	*top = temp->link;
	free(temp);
}
