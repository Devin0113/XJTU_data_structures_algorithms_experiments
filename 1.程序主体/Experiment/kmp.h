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

//extern int Debug;//���� �Ƿ�������ģʽ

int NextArray[100] = {0};

int NumOccur(char *str,char *substr);
int kmp2();
void GetNext(char substr[], int size);
char *KMPstrstr(char *str, char *substr);
char *ApproxStr(char *str, char *substr);


void GetNext(char substr[], int size) {//kmp�㷨���ģ��ó�next������ȥ������Ҫ��ƥ�� 
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

char *KMPstrstr(char *str, char *substr) {//kmp�㷨���庯���������Ӵ��ڴ��г���λ��ָ�� 
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

char *ApproxStr(char *str, char *substr) {//ģ��ƥ�� 
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

int NumOccur(char *str,char *substr) {//kmpƥ�䣬ͳ���Ӵ��ڸ��Ӵ��г��ִ�����
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

int kmp2() {//kmp��ȫƥ���ģ��ƥ������ַ��� 
	char find_str[100];
	int line=0;
	int i=0,j=0;
	char file_str[32768];
	fin= fopen("data/SourceDoc.txt","r");//��ֻ����ʽ���ļ�
	if (fin==NULL) {
		printf("open file for read error\n");
		return -1;
	}
	printf("������Ҫ���ҵ��ַ���: ");
	fflush(stdin);
	gets(find_str);
	while(fgets(file_str,sizeof(file_str),fin)) {
		line++;
		if(KMPstrstr(file_str,find_str)) {
			i++;
			j=NumOccur(file_str,find_str);
			if(j<=1) {
				printf("��%d�� %s �ڵ� %d �У�\n%s\n",i,find_str,line,file_str);
			} else {
				printf("��%d - %d�� %s �ڵ� %d �У�\n%s\n",i,i+j-1,find_str,line,file_str);
				i=i+j-1;
				j=0;
			}
		}
	}
	if(i==0) {
		printf("δѰ�ҵ���ȫƥ����ַ�����%s\n",find_str);
		int c=0;//ģ��ƥ��ѡ��
		while (1) {
			fflush(stdin);
			printf("�Ƿ�Ҫ����ģ��ƥ�䣨˳��ģ��������������1����������0\n");
			scanf("%d",&c);
			if(c==1||c==0) {
				if(c) {
					line=0,i=0,j=0;//��ʼ��
					rewind(fin);//��ʼ��
					while(fgets(file_str,sizeof(file_str),fin)) {
						line++;
						if(ApproxStr(file_str,find_str)) {
							i++;
							j=NumOccur(file_str,find_str);
							if(j<=1) {
								printf("��%d�� %s �ڵ� %d �У�\n%s\n",i,find_str,line,file_str);
							} else {
								printf("��%d - %d�� %s �ڵ� %d �У�\n%s\n",i,i+j-1,find_str,line,file_str);
								i=i+j-1;
								j=0;
							}
						}
					}
					break;
				} else {
					printf("��ȡ��ģ��������\n");
					break;
				}
			} else printf("�������ѡ���������������룡");
		}
	}
	fclose(fin);
	if(i==0) {
		fclose(fin);
		printf("δѰ�ҵ�Ҫ���ҵ��ַ�����%s\n",find_str);
		return -1;
	} else {
		printf("������ϣ�\n");
		return 0;
	}
}









