#include<cstdio>
#include<cstdlib>
#include<Windows.h>

//�ð� ���� �ڵ��Դϴ�. 
#define CHECK_TIME_START QueryPerformanceFrequency((_LARGE_INTEGER*) &freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a = (float)((float) (end - start)/freq);
// a��� ���������� ���� ������� ������. �ð����� ������ �߻��մϴ�.

//SWAP�� �����ϴ� ��ũ�� �Դϴ�.
#define SWAP(a, b) {\
	swap_temp = a; a = b; b = swap_temp;\
}

//���� �̸��� ���� ��ũ�� �Դϴ�.
#define FILE_NAME "input_fewswap_2_15.bin"
//������
__int64 start, freq, end;
float resultTime;
int swap_temp;
//������!

int Validation(int *data, int left, int right);
int Insertion_Sort(int* data, int left, int right);
int main() {
	int N;
	int temp;
	int* Arr;
	FILE* fa = fopen(FILE_NAME, "rb");
	fread(&N, sizeof(int), 1, fa);

	Arr = (int*)malloc(sizeof(int) * N);
	printf("[ %d ] Numbers Of Input Data\n", N);
	for (int i = 0; i < N; i++) {
		fread(&temp, sizeof(int), 1, fa);
		Arr[i] = temp;
	}

	CHECK_TIME_START;
	if (Insertion_Sort(Arr, 0, N - 1) == 0) {
		printf("Well Done\n");
	}
	else { // Validation ����� �ùٸ��� ������ �����޽����� ����մϴ�.
		printf("Try Again\n");
	}
	CHECK_TIME_END(resultTime);//�ð����
	printf("Total Time is [ %f (ms)]\n", resultTime*1000.0f);

	/*
	for (int i = 0; i < N; i++) {
		printf("\t[%d]'s data is %d\n", i, Arr[i]);
	}*/

	fclose(fa);
	return 0;
}
int Validation(int *data, int left, int right) {
	for (int i = left; i < right - 1; i++) {
		if (data[i] > data[i + 1]) return -1;
	}
	return 0;
}
int Insertion_Sort(int* data, int left, int right) {
	if (data == NULL) {
		printf("ERROR");
		return -1;
	}
	for (int i = left + 1; i <= right; i++) {
		int tmp = data[i];
		int j = i - 1;
		while ((j > left - 1) && (data[j] > tmp)) {
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = tmp;
	}
	return Validation(data, left, right);
}