#include "header.h"
int num_of_page[10];
int main(){
    int T;
    scanf("%d",&T);
    for(int i=0;i<T;i++){
        int tmp;
        scanf("%d",&tmp);
        find_num(num_of_page,tmp);
        print_num(num_of_page);
    }
}