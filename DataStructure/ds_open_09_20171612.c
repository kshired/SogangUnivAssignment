#include <stdio.h>

#include <stdlib.h>



#define MAX_TERMS 100



typedef struct treeNode* treePtr;

typedef struct treeNode {

	treePtr lchild;

	int data;

	treePtr rchild;

}treeNode;



/* You have to implement the functions below */

void inorder(treePtr node);

void preorder(treePtr node);

void insert(treePtr* node, int num);

treePtr modifiedSearch(treePtr tree, int key);

/*

3 9 8 2 5 10 7 1 4 6   입력

*/

int main(){

	int n, A[MAX_TERMS];

	treePtr tree = NULL;

	FILE* fp = fopen("input.txt", "r");

	fscanf(fp, "%d", &n);

	for(int i = 0; i < n; i++){
		fscanf(fp, "%d", &A[i]);
	}

	/* Open a data input file and

	store the size of input into 'n' and then

	store the integers to be inserted into 'A' array */



	for(int i = 0; i < n; i++){
		insert(&tree, A[i]);
	}

	printf("In-order:");
	inorder(tree);
	printf("\nPre-order:");
	preorder(tree);


	/* By using 'inorder' and 'preorder',

	check whether tree was constructed correctly or not. */


	return 0;

}



void inorder (treePtr tree){

	if(tree) {

		inorder (tree->lchild);
		printf (" %d", tree->data);
		inorder (tree->rchild);

	}

}



void preorder (treePtr tree)



{

	if(tree)

	{

		printf (" %d", tree->data);

		preorder (tree->lchild);

		preorder (tree->rchild);

	}

}



void insert(treePtr* tree, int num){

	treePtr ptr;
	treePtr temp = modifiedSearch(*tree, num);

	if(temp || !(*tree)){
		ptr = (treePtr)malloc(sizeof(treeNode));
		ptr->data = num;
		ptr->lchild = ptr->rchild = NULL;
		if(*tree){
			if(num < temp->data){
				temp->lchild = ptr;
			}
			else
				temp->rchild = ptr;
		}
		else *tree = ptr;           //tree가 존재하지 않을때(즉 트리에 0개의 데이터가 들어가있을때)
	}

}

treePtr modifiedSearch(treePtr tree, int key) {
	treePtr tmp = NULL;
	if(!tree)
		return NULL;

	while(tree){
		if(key == tree->data)
			return NULL;
		if(key < tree->data){
			tmp = tree;
			tree = tree->lchild;
		}
		else{
			tmp = tree;
			tree = tree->rchild;
		}
	}
	return tmp;
}