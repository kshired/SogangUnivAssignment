#include <iostream>
#include<cstring>
#include "Str.h"

Str::Str(int leng){
	if(leng<=0){
		std::cout<<"Size Must Be Positive\n";
	}
	else{
		this->len = leng;
		this->str = new char[this->len];
	}
}
Str::Str(const char *neyong){
	int i;
	for(i=0;;i++){
		if(neyong[i]=='\0') break;
	}
	this->len = i;
	this->str = new char[this->len+1];
	for(int j=0;j<=i;j++){
		(this->str)[j] = neyong[j];
	}
}
Str::~Str(){
	delete [] this->str;
}
int Str::length(void){
	return this->len;
}
char* Str::contents(void){
	static char* tmp = NULL;
	if(this->str==NULL){
		std::cout<<"Not have Contents!\n";
		return tmp;
	}else{
		return this->str;
	}
}
int Str::compare(class Str& a){
	return strcmp(this->str,a.contents());
}
int Str::compare(const char *a){
	return strcmp(this->str,a);
}
void Str::operator=(const char *a){
	if(this->len < strlen(a)){
		delete [] this->str;
		this->str=new char[strlen(a)+1];
	}
	strcpy(this->str,a);
	this->len=strlen(a);
}
void Str::operator=(class Str& a){
	if(this->len < a.length()){
		delete [] this->str;
		this->str=new char[a.length()+1];
	}
	strcpy(this->str,a.contents());
	this->len=a.length();
}
