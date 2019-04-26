#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
using namespace std;
ofstream maze("maze.maz");
void printLine(int N);
void printRow(bool rightWay[], bool downWay[], int N);
void createMaze(int currentRow, int M, int N, int previousDisjoint[]);
int main(void) {
	int m, n;
	cin >> m;
    cin >> n;
	srand((unsigned)time(NULL));
	createMaze(0, m, n, NULL);
	printLine(n);
	return 0;
}
void printLine(int N) {
	for(int i = 0; i < N; i++) {
		maze << "+-";
	}
	maze << '+' << endl;
}
void printRow(bool rightWay[], bool upWay[], int N) {
	maze << '+';
	for(int i = 0; i < N; i++) {
		maze << (upWay[i]?' ':'-') << '+';
	}

	maze << endl << '|';
	for(int i = 0; i < N; i++) {
		maze << ' ' << (rightWay[i]?' ':'|');
    }
	maze << endl;
}
void createMaze(int currentRow, int M, int N, int previousDisjoint[]) {

	int * disjoint = new int[N];	
	bool * rightWay = new bool[N];
	bool * upWay = new bool[N];	
	map<int, int> setSize;
	map<int, bool> setFlag;
    for(int i=0;i<N;i++){
        rightWay[i] = false;
        upWay[i] = false;
    }
	if(currentRow == M) {
		delete[] disjoint;
		delete[] rightWay;
		delete[] upWay;
		return;
	}
	
	if(currentRow == 0) {
		for(int i = 0; i < N; i++) {
			disjoint[i] = i*N+0;
			if(i > 0 && 1.0*rand()/RAND_MAX <= 0.6) {
				disjoint[i] = disjoint[i-1];
				rightWay[i-1] = true;
			}
		}
		printRow(rightWay, upWay, N);
		delete[] rightWay;
		delete[] upWay;
		createMaze(currentRow+1, M, N, disjoint);
	}
	else {
		for(int i = 0; i < N; i++) {
			disjoint[i] = i*N+currentRow;
			setSize[previousDisjoint[i]]++;
		}
		for(int i = 0; i < N; i++) {
			setSize[previousDisjoint[i]]--;			
			if(1.0*rand()/RAND_MAX <= 0.6 || (!setFlag[previousDisjoint[i]] && !setSize[previousDisjoint[i]])) {
				upWay[i] = true;
				setFlag[previousDisjoint[i]] = true;
				disjoint[i] = previousDisjoint[i];
			}
		}
		delete[] previousDisjoint;
		for(int i = 1; i < N; i++) {
			if(disjoint[i-1] != disjoint[i]) {
				if(1.0*rand()/RAND_MAX <= 0.6 || currentRow == M-1) {
					for(int j = 0; j < N; j++) {
						if(disjoint[j] == disjoint[i] && i != j) {
							disjoint[j] = disjoint[i-1];
						}
					}
					disjoint[i] = disjoint[i-1];
					rightWay[i-1] = true;
				}
			}
		}
		printRow(rightWay, upWay, N);

		delete[] rightWay;
		delete[] upWay;

		createMaze(currentRow+1, M, N, disjoint);
	}
}