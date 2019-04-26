#include <iostream>
#include <algorithm>
#include <stack>
#include <cstdio>
#define INFILE "input.txt"
#define OUTFILE "output.txt"
int s, f, p;
int n1,n2;
char X[1000];
char Y[1000];
int dp[10000][10000];
using namespace std;

int getVal(char a,char b){
	if(a==b) return s;
	return -f;
}
int h3_1(int i, int j) {
	int &ret = dp[i][j];
	if(!i) return ret = j*p*(-1);
	if(!j) return ret = i*p*(-1);
	if(ret != -1) return ret;
	return ret = max(h3_1(i-1, j-1) + getVal(X[i],Y[j]), max(h3_1(i, j-1)-p, h3_1(i-1, j)-p));
}
void init(){
	for(int i=0;i<=n1;i++){
		for(int j=0;j<=n2;j++){
			dp[i][j] = -1;
		}
	}
}
int main() {
	stack<int> st1,st2;
	char tmpS[1000];
	int i,j,cnt,cnt1,cnt2;
	FILE* tmp = fopen(INFILE,"r");
	FILE* ofp = fopen(OUTFILE,"w");
	FILE* ifp;
	fscanf(tmp,"%s",tmpS);
	fscanf(tmp,"%d %d %d",&s,&f,&p);
	ifp = fopen(tmpS,"r");
	fread(&n1,4,1,ifp);
	i = n1;
	fread(&n2,4,1,ifp);
	j = n2;
	fread(X+1,n1,1,ifp);
	fread(Y+1,n2,1,ifp);
	X[0] = '0';
	Y[0] = '0';

	init();
	h3_1(n1,n2);
	
	cnt = cnt1 = cnt2 = 0;
	while (i != 0 || j != 0) {
		if (dp[i][j] + p == dp[i][j - 1]){
			st1.push(j);
            j--;
            cnt++;
            cnt1++;
		}
		else if(dp[i][j] + p == dp[i-1][j]){
			st2.push(i);
            i--;
            cnt++;
            cnt2++;
		}
		else{
            i--;
            j--;
        }
	}
	
	fprintf(ofp,"%d\n",dp[n1][n2]);
	fprintf(ofp,"%d\n",n1 + cnt1);
	fprintf(ofp,"%d\n",cnt1);
	while (!st1.empty()) {
		fprintf(ofp,"%d\n",st1.top());
		st1.pop();
	}
    fprintf(ofp,"%d\n",cnt2);
	while (!st2.empty()) {
		fprintf(ofp,"%d\n",st2.top());
		st2.pop();
	}
	
	
	fclose(tmp);
	fclose(ifp);
	fclose(ofp);
	return 0;
}
