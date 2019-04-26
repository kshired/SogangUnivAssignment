#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n){
	int i, temp, j;
	for(i = 1; i < n; i++){
		temp = arr[i];
		j = i-1;
		while(j>=0&&arr[j] > temp){
			arr[j+1] = arr[j];
			j = j-1;
		}
		arr[j+1] = temp;
	}
}

int main() {
	int len,i;
	int *ary;
	clock_t st, et;
	FILE *f = NULL;
	
	

	f = fopen("lab1.data", "r");
	
	fscanf(f, "%d", &len);

	ary = (int *)malloc(sizeof(int)*len);

	for(i = 0; i < len; i++) {

		fscanf(f, "%d", &ary[i]);

	}

	printf("Input: ");

	for(i = 0; i < len-1; i++) {

		printf("%d, ", ary[i]);

	}
	printf ("%d\n", ary[len - 1]);
	st = clock ();
	insertionSort(ary, len);
	et = clock ();
	printf("Sorted: ");

	for(i = 0; i < len-1; i++) {

		printf("%d, ", ary[i]);

	}
	printf ("%d\n", ary[len - 1]);

	fclose(f);
	free(ary);



	printf("실행시간 : %f\n", (double)(et-st)/CLOCKS_PER_SEC);

}