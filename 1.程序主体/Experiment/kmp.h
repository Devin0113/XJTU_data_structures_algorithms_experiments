#ifndef STDIO_H
#define STDIO_H
#endif
#ifndef STDLIB_H
#define STDLIB_H
#endif
#ifndef MALLOC_H
#define MALLOC_H
#endif
#ifndef STRING_H
#define STRING_H
#endif

#ifndef LINK_H
#define LINK_H
#endif
#ifndef LEAF_H
#define LEAF_H
#endif
#ifndef CODEOUT_H
#define CODEOUT_H
#endif
#ifndef DEBUG_H
#define DEBUG_H
#endif

//extern int Debug;//声明 是否开启调试模式

int NextArray[100] = {0};

int NumOccur(char *str,char *substr);
int kmp2();
void GetNext(char substr[], int size);
char *KMPstrstr(char *str, char *substr);
char *ApproxStr(char *str, char *substr);


void GetNext(char substr[], int size) {//kmp算法核心，得出next数组以去除不必要的匹配 
	NextArray[0] = 0;
	NextArray[1] = 0;
	int i = 1, j = 0;
	for(; i<size-1; i++) {
		j = NextArray[i];
		if(substr[i] == substr[j]) {
			NextArray[i+1] = j + 1;
		} else {
			j = NextArray[j];
			while((substr[i] != substr[j]) && (j != 0) ) {
				j = NextArray[j];
			}
			NextArray[i+1] = j;
		}
	}
}

char *KMPstrstr(char *str, char *substr) {//kmp算法整体函数，返回子串在串中出现位置指针 
	int sn = strlen(str);
	int pn = strlen(substr);
	if(pn == 0)
		return str;
	GetNext(substr, pn);

	int i=0,j=0;
	while(j < sn) {
		if(substr[i] == str[j]) {
			i++;
			j++;
		} else if( i == 0)
			j++;
		else
			i = NextArray[i];

		if(i == pn)
			return str + j - i;
	}
	return NULL;
}

char *ApproxStr(char *str, char *substr) {//模糊匹配 
	int sn = strlen(str);
	int pn = strlen(substr);
	if(pn == 0)
		return str;

	int j=0,i=0;
	int a=0;
	while(j < sn) {
		if(substr[i] == str[j]) {
			i++;
			j++;
		} else j++;

		if(i == pn)
			return str+a;
	}
	return NULL;
}

int NumOccur(char *str,char *substr) {//kmp匹配，统计子串在副子串中出现次数。
	int count = 0;
	while(*str) {
		char *str1 = str, *str2 = substr;
		if (*str1 == *str2) {
			while(*str2) {
				if (*str1 != *str2) {
					break;
				}
				str1++;
				str2++;
			}
			if (*str2 == '\0') {
				count++;
			}
		}
		str++;
	}
	return count;
}

int kmp2() {//kmp完全匹配和模糊匹配查找字符串 
	char find_str[100];
	int line=0;
	int i=0,j=0;
	char file_str[32768];
	fin= fopen("data/SourceDoc.txt","r");//以只读方式打开文件
	if (fin==NULL) {
		printf("open file for read error\n");
		return -1;
	}
	printf("请输入要查找的字符串: ");
	fflush(stdin);
	gets(find_str);
	while(fgets(file_str,sizeof(file_str),fin)) {
		line++;
		if(KMPstrstr(file_str,find_str)) {
			i++;
			j=NumOccur(file_str,find_str);
			if(j<=1) {
				printf("第%d处 %s 在第 %d 行：\n%s\n",i,find_str,line,file_str);
			} else {
				printf("第%d - %d处 %s 在第 %d 行：\n%s\n",i,i+j-1,find_str,line,file_str);
				i=i+j-1;
				j=0;
			}
		}
	}
	if(i==0) {
		printf("未寻找到完全匹配的字符串：%s\n",find_str);
		int c=0;//模糊匹配选项
		while (1) {
			fflush(stdin);
			printf("是否要进行模糊匹配（顺序模糊）？是请输入1，否请输入0\n");
			scanf("%d",&c);
			if(c==1||c==0) {
				if(c) {
					line=0,i=0,j=0;//初始化
					rewind(fin);//初始化
					while(fgets(file_str,sizeof(file_str),fin)) {
						line++;
						if(ApproxStr(file_str,find_str)) {
							i++;
							j=NumOccur(file_str,find_str);
							if(j<=1) {
								printf("第%d处 %s 在第 %d 行：\n%s\n",i,find_str,line,file_str);
							} else {
								printf("第%d - %d处 %s 在第 %d 行：\n%s\n",i,i+j-1,find_str,line,file_str);
								i=i+j-1;
								j=0;
							}
						}
					}
					break;
				} else {
					printf("已取消模糊搜索！\n");
					break;
				}
			} else printf("您输入的选项有误，请重新输入！");
		}
	}
	fclose(fin);
	if(i==0) {
		fclose(fin);
		printf("未寻找到要查找的字符串：%s\n",find_str);
		return -1;
	} else {
		printf("搜索完毕！\n");
		return 0;
	}
}









