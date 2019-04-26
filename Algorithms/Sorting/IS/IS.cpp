#include<cstdio>
#include<cstdlib>
#include<Windows.h>

//시간 측정 코드입니다. 
#define CHECK_TIME_START QueryPerformanceFrequency((_LARGE_INTEGER*) &freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a = (float)((float) (end - start)/freq);
// a라는 전역변수를 절대 사용하지 마세요. 시간측정 오류가 발생합니다.

//SWAP을 진행하는 매크로 입니다.
#define SWAP(a, b) {\
	swap_temp = a; a = b; b = swap_temp;\
}

//파일 이름에 대한 매크로 입니다.
#define FILE_NAME "input_fewswap_2_15.bin"
//지우지
__int64 start, freq, end;
float resultTime;
int swap_temp;
//마세요!

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
	else { // Validation 결과가 올바르지 않으면 에러메시지를 출력합니다.
		printf("Try Again\n");
	}
	CHECK_TIME_END(resultTime);//시간출력
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