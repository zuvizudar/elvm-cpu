#include<iostream>
#include<string>
#include<vector>
#include<string.h>
#include<sstream>
using namespace std;
string change(string str);

FILE *fp;
char s[256];

int main(){
	if((fp=fopen("hoge.rom","r"))==NULL){
		printf("file open error\n");
		exit(EXIT_FAILURE);
	}
	while(fgets(s,256,fp)!=NULL){
		if(s[0]<'0'||'9'<s[0])continue;
		stringstream ss;
		vector<string>code;
		string tmp;
		ss << s;
		string ret;
		while(getline(ss,tmp,'_')){
			code.push_back(tmp);
		}
		for(int i=0;i<code.size();i++){
			cout<<code[i];			
		}
	}
	for(int i=0;i<26;i++)cout<<"1";
	cout<<endl;
	fclose(fp);
	return 0;
}

