#include <stdlib.h>
#include <string.h>
#include <stdio.h>
void failure(char* pattern, int* f);
int kmp(char* t, char* p);
int* init_array(int size);

int main(void) {
	FILE *f;
	f = fopen("kmp.txt","r");
	int match;
	char s1[100];
	char s2[100];
	fgets(s1, 40, f);
	fgets(s2, 10, f);

	fclose(f);
	match = kmp(s1, s2);
	printf("%d\n", match);

	return 0;
}
int* init_array(int size) {
	int* arr = (int*)malloc(size * sizeof(int));
	int i;
	for(i = 0; i < size; i++) {
		arr[i] = 0;
	}

	return arr;
}
int kmp(char* t, char* p) {
	int m = strlen(p);
	int n = strlen(t);
	int* f = init_array(m);
	int i = 0;
	int j = 0;

	while(i < n) {
		if(t[i] == p[j]) {
			if(j == m - 1) {
				return i - j;
			}
			else {
				i += 1;
				j += 1;
			}
		}
		else {
			if(j > 0) {
				j = f[j-1];
			}
			else {
				i += 1;
			}
		}
	}

	return -1;
}
void failure(char* p, int* f) {
	//F[q] = MAX{ k: k<q 이면서, P[0~k]가 P[0~q]의 접미어가 되는 k }
		
	f[0] = 0;
	int i = 1;
	int j = 0;

	int m = strlen(p);

	while(i < m) {
		if(p[i] == p[j]) {
			f[i] = j + 1;
			i += 1;
			j += 1;
		}
		else if(j > 0) {
			j = f[j - 1];
		}
		else {
			f[i] = 0;
			i += 1;
		}
	}
}
