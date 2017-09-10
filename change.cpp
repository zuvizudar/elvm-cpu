#include<iostream>
#include<string>
#include<vector>
#include<string.h>

using namespace std;
void split(void);
void char_to_int(vector<char> str);
void decimal_to_binary(int num);

FILE *fp;
char s[256];
const char *zero ="_0_000000000000000000000000\n";

int main(){
	if((fp=fopen("hello3.ecpu","r"))==NULL){
		printf("file open error\n");
		exit(EXIT_FAILURE);
	}
	while(fgets(s,256,fp)!=NULL){
			if(s[15]=='\n'){
				s[15]='\0';
				strcat(s,zero);
				printf("%s",s);
			}	
			else {
					//printf("%c",im[i]);
				for(int i=0;i<18;i++)
					cout<<s[i];
				split();
				}
			//	printf("\n");
	}
	fclose(fp);
	return 0;
}

void decimal_to_binary(int num){
	vector<char>ret;
	while(num>0){
		char t=(num%2)+'0';
		ret.push_back(t);
		num/=2;
	}
	int len=ret.size();
	for(int i=0;i<24-len;i++)
		cout<<"0";
	for(int i=0;i<len/2;i++){
		char tmp;
		tmp=ret[i];
		ret[i]=ret[len-i-1];
		ret[len-i-1]=tmp;
	}
	
	for(int i=0;i<ret.size();i++)
		cout<<ret[i];
	cout<<endl;
	return;
}

void char_to_int(vector<char> str){
	//cout<<str.size()<<endl;
	int ret=0;
	int base=1;
	for(int i=0;i<str.size()-1;i++)
		base*=10;
	for(int i=0;i<str.size();i++){
		ret+=base*(str[i]-'0');
		base/=10;
	}
	decimal_to_binary(ret);
	//cout<<ret<<endl;
	return;
}
void split(void){
	vector<char> im;
	for(int i=0;i<25;i++){
		if(s[18+i]=='\n')
		break;
		im.push_back(s[18+i]);
	}
  /*	for(int i=0;i<im.size();i++)
		cout<<im[i];
	cout<<endl;
	*/
	char_to_int(im);
	return;
}

