#include<iostream>
#include<string>
#include<vector>
#include<string.h>
#include<sstream>
using namespace std;
string change(string str);

FILE *fp;
char s[256];
const string Zero ="_0_000000000000000000000000";
const string Max_num="255\n";
const int Im_num=24;
const int OP_place=1,RD_place=2,RS_place=3,Is_sorce_im_place=4,IM_place=5;

int main(){
	if((fp=fopen("tmp.txt","r"))==NULL){
		printf("file open error\n");
		exit(EXIT_FAILURE);
	}
	while(fgets(s,256,fp)!=NULL){
		stringstream ss;
		vector<string>code;
		string tmp;
		ss << s;
		string ret;
		while(getline(ss,tmp,'_')){
			code.push_back(tmp);
		}
		for(int i=0;i<code.size();i++){
			int len=code[i].size();
			if(i==RD_place){
				for(int j=0;j<8-len;j++){
					code[i]="0"+code[i];
				}			
			}
			if(i==RS_place){
				if(code[i][code[i].size()-1]=='\n'){
					code[i].pop_back();
					code[i]=code[i]+Zero;
				}
					
			}
			if(i==IM_place){
				if(code[i]=="16777215\n"){
					code[i]=Max_num;
				}
				code[i]=change(code[i]);
				len=code[i].size();
				for(int j=0;j<Im_num-len;j++){
					code[i]="0"+code[i];
				}
			}	
			cout<<code[i];
			if(i!=code.size()-1)
				cout<<"_";
				
		}
		cout<<endl;
	}
	fclose(fp);
	return 0;
}
string change(string str){ //二進数を十進数に
	int num=0;
	int base=1;
	for(int i=0;i<str.size()-2;i++)
		base*=10;
	for(int i=0;i<str.size();i++){
		num+=base*(str[i]-'0');
		base/=10;
	}
	string ret;
	while(num>0){
		char t=(num%2)+'0';
		ret.push_back(t);
		num/=2;
	}
	int len=ret.size();
	for(int i=0;i<len/2;i++){
		char tmp;
		tmp=ret[i];
		ret[i]=ret[len-i-1];
		ret[len-i-1]=tmp;
	}
	
	return ret;
}

