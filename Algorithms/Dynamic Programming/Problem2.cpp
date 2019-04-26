#include <iostream>
#include <stack>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int str1[1010];
int str2[1010];
int str3[1010];
int str3_2[1010];
int str4[1010];
int str4_2[1010];
int LCS1[1010][1010];
int LCS2[1010][1010];
int LCS3[1010][1010];
int LCS4[1010][1010];
int main(){
    int n;
    int flag1,flag2;
    flag1 = 0;
    flag2 = 0;
    int i,j;
    int s1,s2,s3,s4;
    FILE* inf = fopen("input.txt","r");
    FILE* outf = fopen("output.txt","w");
    fscanf(inf,"%d",&n);
    str1[0] = 0;
    for(i=1;i<=n;i++){
        fscanf(inf,"%d",&str1[i]);
    }
    s1 = n+1;
    fscanf(inf,"%d",&n);
    str2[0] = 0;
    for(i=1;i<=n;i++){
        fscanf(inf,"%d",&str2[i]);
    }
    s2 = n+1;
    fscanf(inf,"%d",&n);
    str3[0] = 0;
    str3_2[0] = 0;
    for(i=1;i<=n;i++){
        fscanf(inf,"%d",&str3[i]);
        str3_2[i] = str3[i];
    }
    s3 = n+1;
    fscanf(inf,"%d",&n);
    str4[0] = 0;
    str4_2[0] = 0;
    for(i=1;i<=n;i++){
        fscanf(inf,"%d",&str4[i]);
        str4_2[i] = str4[i];
    }
    s4 = n+1;
    for (i = 0; i < s3; i++) {
        for (j = 0; j < s1; j++) {
            if(i==0 || j==0){
                LCS1[i][j] = 0;
                continue;
            }
            if (str3[i] == str1[j]){
                LCS1[i][j] = LCS1[i - 1][j - 1] + 1;
			}
			else
                LCS1[i][j] = max(LCS1[i - 1][j], LCS1[i][j - 1]);
        }
    }
    if(LCS1[s3-1][s1-1]==(s1-1)){
        i = s3-1;
        j = s1-1;
        stack<int> st;
        while (LCS1[i][j] != 0){
            if (LCS1[i][j] == LCS1[i][j - 1])
                j--;
            else if (LCS1[i][j] == LCS1[i - 1][j])
                i--;
            else if (LCS1[i][j] - 1 == LCS1[i - 1][j - 1]){
                st.push(i);
                i--;
                j--;
            }
        }
        while (!st.empty()){

            str3[st.top()] = -1;
            st.pop();
        }
        for (i = 0; i < s3; i++) {
            for (j = 0; j < s2; j++) {
                if(i==0 || j==0){
                    LCS2[i][j] = 0;
                    continue;
                }
                if (str3[i] == str2[j]){
                    LCS2[i][j] = LCS2[i - 1][j - 1] + 1;
                }
                else
                    LCS2[i][j] = max(LCS2[i - 1][j], LCS2[i][j - 1]);
            }
        }
        if(LCS2[s3-1][s2-1]==(s2-1)){
            flag1++;
        }
    }
    for (i = 0; i < s3; i++) {
        for (j = 0; j < s2; j++) {
            if(i==0 || j==0){
                LCS1[i][j] = 0;
                continue;
            }
            if (str3_2[i] == str2[j]){
                LCS1[i][j] = LCS1[i - 1][j - 1] + 1;
			}
			else
                LCS1[i][j] = max(LCS1[i - 1][j], LCS1[i][j - 1]);
        }
    }
    if(LCS1[s3-1][s2-1]==(s2-1)){
        i = s3-1;
        j = s2-1;
        stack<int> st;
        while (LCS1[i][j] != 0){
            if (LCS1[i][j] == LCS1[i][j - 1])
                j--;
            else if (LCS1[i][j] == LCS1[i - 1][j])
                i--;
            else if (LCS1[i][j] - 1 == LCS1[i - 1][j - 1]){
                st.push(i);
                i--;
                j--;
            }
        }
        
        while (!st.empty()){

            str3_2[st.top()] = -1;
            st.pop();
        }
        for (i = 0; i < s3; i++) {
            for (j = 0; j < s1; j++) {
                if(i==0 || j==0){
                    LCS2[i][j] = 0;
                    continue;
                }
                if (str3_2[i] == str1[j]){
                    LCS2[i][j] = LCS2[i - 1][j - 1] + 1;
                }
                else
                    LCS2[i][j] = max(LCS2[i - 1][j], LCS2[i][j - 1]);
            }
        }
        if(LCS2[s3-1][s1-1]==(s1-1)){
            flag1++;
        }
    }
    if(flag1>=1){
        fprintf(outf,"1");
    }
    else{
        fprintf(outf,"0");
    }
    for (i = 0; i < s4; i++) {
        for (j = 0; j < s1; j++) {
            if(i==0 || j==0){
                LCS3[i][j] = 0;
                continue;
            }
            if (str4[i] == str1[j]){
                LCS3[i][j] = LCS3[i - 1][j - 1] + 1;
			}
			else
                LCS3[i][j] = max(LCS3[i - 1][j], LCS3[i][j - 1]);
        }
    }
    if(LCS3[s4-1][s1-1]==(s1-1)){
        i = s4-1;
        j = s1-1;
        stack<int> st;
        while (LCS3[i][j] != 0){
            if (LCS3[i][j] == LCS3[i][j - 1])
                j--;
            else if (LCS3[i][j] == LCS3[i - 1][j])
                i--;
            else if (LCS3[i][j] - 1 == LCS3[i - 1][j - 1]){
                st.push(i);
                i--;
                j--;
            }
        }
        while (!st.empty()){
            str4[st.top()] = -1;
            st.pop();
        }
        for (i = 0; i < s4; i++) {
            for (j = 0; j < s2; j++) {
                if(i==0 || j==0){
                    LCS4[i][j] = 0;
                    continue;
                }
                if (str4[i] == str2[j]){
                    LCS4[i][j] = LCS4[i - 1][j - 1] + 1;
                }
                else
                    LCS4[i][j] = max(LCS4[i - 1][j], LCS4[i][j - 1]);
            }
        }
        if(LCS4[s4-1][s2-1]==(s2-1)){
            flag2++;
        }
    }
    for (i = 0; i < s4; i++) {
        for (j = 0; j < s2; j++) {
            if(i==0 || j==0){
                LCS3[i][j] = 0;
                continue;
            }
            if (str4_2[i] == str2[j]){
                LCS3[i][j] = LCS3[i - 1][j - 1] + 1;
			}
			else
                LCS3[i][j] = max(LCS3[i - 1][j], LCS3[i][j - 1]);
        }
    }
    if(LCS3[s4-1][s2-1]==(s2-1)){
        i = s4-1;
        j = s2-1;
        stack<int> st;
        while (LCS3[i][j] != 0){
            if (LCS3[i][j] == LCS3[i][j - 1])
                j--;
            else if (LCS3[i][j] == LCS3[i - 1][j])
                i--;
            else if (LCS3[i][j] - 1 == LCS3[i - 1][j - 1]){
                st.push(i);
                i--;
                j--;
            }
        }
        while (!st.empty()){

            str4_2[st.top()] = -1;
            st.pop();
        }
        for (i = 0; i < s4; i++) {
            for (j = 0; j < s1; j++) {
                if(i==0 || j==0){
                    LCS4[i][j] = 0;
                    continue;
                }
                if (str4_2[i] == str1[j]){
                    LCS4[i][j] = LCS4[i - 1][j - 1] + 1;
                }
                else
                    LCS4[i][j] = max(LCS4[i - 1][j], LCS4[i][j - 1]);
            }
        }
        if(LCS4[s4-1][s1-1]==(s1-1)){
            flag2++;
        }
    }
    if(flag2>=1){
        fprintf(outf,"1\n");
    }
    else{
        fprintf(outf,"0\n");
    }
    fclose(inf);
    fclose(outf);
    return 0;
}
