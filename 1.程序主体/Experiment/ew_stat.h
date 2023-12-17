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
#ifndef CTYPE_H
#define CTYPE_H
#endif

#ifndef DEBUG_H
#define DEBUG_H
#endif

#define EMAXL 45//最长单词长度
#define ENUM 20000//最大不重复单词个数

extern int Debug;//声明 是否开启调试模式

typedef struct Eword {
	char INDwords[EMAXL];
	int frequency;
} Eword; //存放单词及其频数

int EStatistics();
int IfAppeared(Eword *w[],char *single,int n);
void EDeposit(char *str,Eword *w[],int i,int n);
int EHandle(FILE *fp,Eword *w[]);
void ESwap(Eword *w1,Eword *w2);
void ESort(Eword *w[],int n);
void EPrint(Eword *w[],int n);
int EFPrint(Eword *w[],int n);


int EStatistics() {//单词统计主要实现函数
	int n,i;//n代表不重复单词的总数
	int c=0;//输出文件选项 
	FILE *fp;
	Eword *w[ENUM];
	fp=fopen("data/SourceDoc.txt","r");
	if(fp==NULL) {
		return 1;
	}
	n=EHandle(fp,w);
	ESort(w,n);

	while(1) {
		fflush(stdin);
		printf("是否要直接将结果输出到WordStatistics.txt中？\n是请输入1，否请输入0\n");
		scanf("%d",&c);
		if(c==1||c==0) {
			if(c) {
				printf("即将输出到WordStatistics.txt中！\n");
				system("pause");
				EFPrint(w,n);
				printf("已成功输出！\n");
			} else EPrint(w,n);
			break;
		}
		printf("您输入的选项有误，请重新输入！");
	}
	fclose(fp);
	for(i=0; i<n; i++)
		free(w[i]);
	return 0;
}

int IfAppeared(Eword *w[],char *single,int n) {//判断单词是否第一次出现，返回i代表重复单词在结构体数组中的位置，返回-1代表第一次出现
	int i;
	if(n==0)
		return -1;
	else
		for(i=0; i<n; i++)
			if(strcmp(w[i]->INDwords,single)==0)//strcmp函数用于判断两个字符串是否相等
				return i;

	return -1;
}

void EDeposit(char *str,Eword *w[],int i,int n) {//将单词存放结构体中。首次出现的单词存放进新的数组，重复出现的使对应频数+1。n代表不重复单词的总数
	int t=0;

	if(i==-1) { //不重复单词
		while(str[t]!='\0') {
			w[n]->INDwords[t]=str[t];
			t++;
		}
		w[n]->INDwords[t]='\0';
		w[n]->frequency=1;
	} else //重复单词
		w[i]->frequency++;
}

int EHandle(FILE *fp,Eword *w[]) {//将文件中的字符处理成单词，且将大写全部转换成小写。同时考虑到连接词会存在连接符的情况（“-”、“'”）
	int i=0,n=0;
	char ch;
	char bh=0;//bh用于处理单词中含有单引号的情况
	char ah=0;//用于处理首字符为-的情况
	char single[EMAXL]= {0};

	while((ch=fgetc(fp))!=EOF) {
		if(!isalpha(ch))//遇到下一个非字母字符后，重置bh
			bh=0;
		if(isalpha(ch)&&bh!=0)//当bh不为零且ch是字母时，说明当前字符处于单引号之后，跳过本次循环
			continue;
		if(!isalpha(ch)&&ch!='-')//遇到非字母字符且该字符不为连字符时跳过本次循环
			continue;
		i=0;
		while(isalpha(ch)||ch=='-') {
			if(ch=='-'&&i==0) {
				ch=fgetc(fp);
				ah=1;
				break;
			}
			if(ch>='A'&&ch<='Z')//将大写字母全部转换成小写字母
				ch+=32;
			single[i++]=ch;
			ch=fgetc(fp);
		}

		if(ah) {
			ah=0;
			continue;
		}

		if(i==1&&single[i-1]!='a') {
			continue;
		}
		if(i>0&&single[i-1]=='-') {
			if(i<=2) {
				continue;
			} else {
				single[i-1]='\0';//手动添加'\0'
			}
		}
		single[i]='\0';//手动添加'\0'

		if(ch=='\'')//处理单引号后面的字母序列
			bh=ch;
		w[n]=(Eword*)malloc(sizeof(Eword));
		if(IfAppeared(w,single,n)==-1)//IfAppeared函数用于判断single是否第一次出现
			n++;//n代表不重复的单词的总数
		EDeposit(single,w,IfAppeared(w,single,n),n-1);//EDeposit函数用于将该字符串的相关数据保存进w中
	}

	return n;
}

void ESwap(Eword *w1,Eword *w2) {//交换两个结构体的内容
	Eword w;
	strcpy(w.INDwords,w1->INDwords);
	w.frequency=w1->frequency;
	strcpy(w1->INDwords,w2->INDwords);
	w1->frequency=w2->frequency;
	strcpy(w2->INDwords,w.INDwords);
	w2->frequency=w.frequency;
}

void ESort(Eword *w[],int n) {//将单词按频数进行排序，频数相同的按字典序排序
	int i,j,f;//f作为标志

	for(i=0; i<n-1; i++) {
		f=1;
		for(j=0; j<n-1; j++) {
			if(w[j]->frequency<w[j+1]->frequency) { //比较频数
				ESwap(w[j],w[j+1]);
				f=0;
			} else if(w[j]->frequency==w[j+1]->frequency) { //频数相同则按字典序排序
				if(strcmp(w[j]->INDwords,w[j+1]->INDwords)>0)//比较字符串大小（字典序），大于0说明前者比后者大
					ESwap(w[j],w[j+1]);
				f=0;
			}
		}
		if(f==1)//f==1说明上述排序已经完成，可提前终止
			break;
	}
}

void EPrint(Eword *w[],int n) {//输出到窗体
	int i;
	for(i=0; i<n; i++) {
		printf("%d.\tINDword：%s\t\t\tFreq：%d\n",i+1,w[i]->INDwords,w[i]->frequency);
	}
}

int EFPrint(Eword *w[],int n) {//输出到文件
	FILE *fout;
	int i;
	fout=fopen("data/WordStatistics.txt","w");
	if(fout==NULL) {
		printf("创建文件失败！错误原因：%s\n",strerror(errno));
		return 1;
	}
	for(i=0; i<n; i++) {
		if(Debug) {
			printf("%d.\tINDword：%s\t\t\tFreq：%d\n",i+1,w[i]->INDwords,w[i]->frequency);//----------测试用----------
		}
		fprintf(fout,"%d.\tINDword：%s\t\t\tFreq：%d\n",i+1,w[i]->INDwords,w[i]->frequency);
	}
	fclose(fout);
	return 0;
}

