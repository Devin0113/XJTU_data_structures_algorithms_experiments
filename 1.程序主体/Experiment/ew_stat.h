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

#define EMAXL 45//����ʳ���
#define ENUM 20000//����ظ����ʸ���

extern int Debug;//���� �Ƿ�������ģʽ

typedef struct Eword {
	char INDwords[EMAXL];
	int frequency;
} Eword; //��ŵ��ʼ���Ƶ��

int EStatistics();
int IfAppeared(Eword *w[],char *single,int n);
void EDeposit(char *str,Eword *w[],int i,int n);
int EHandle(FILE *fp,Eword *w[]);
void ESwap(Eword *w1,Eword *w2);
void ESort(Eword *w[],int n);
void EPrint(Eword *w[],int n);
int EFPrint(Eword *w[],int n);


int EStatistics() {//����ͳ����Ҫʵ�ֺ���
	int n,i;//n�����ظ����ʵ�����
	int c=0;//����ļ�ѡ�� 
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
		printf("�Ƿ�Ҫֱ�ӽ���������WordStatistics.txt�У�\n��������1����������0\n");
		scanf("%d",&c);
		if(c==1||c==0) {
			if(c) {
				printf("���������WordStatistics.txt�У�\n");
				system("pause");
				EFPrint(w,n);
				printf("�ѳɹ������\n");
			} else EPrint(w,n);
			break;
		}
		printf("�������ѡ���������������룡");
	}
	fclose(fp);
	for(i=0; i<n; i++)
		free(w[i]);
	return 0;
}

int IfAppeared(Eword *w[],char *single,int n) {//�жϵ����Ƿ��һ�γ��֣�����i�����ظ������ڽṹ�������е�λ�ã�����-1�����һ�γ���
	int i;
	if(n==0)
		return -1;
	else
		for(i=0; i<n; i++)
			if(strcmp(w[i]->INDwords,single)==0)//strcmp���������ж������ַ����Ƿ����
				return i;

	return -1;
}

void EDeposit(char *str,Eword *w[],int i,int n) {//�����ʴ�Žṹ���С��״γ��ֵĵ��ʴ�Ž��µ����飬�ظ����ֵ�ʹ��ӦƵ��+1��n�����ظ����ʵ�����
	int t=0;

	if(i==-1) { //���ظ�����
		while(str[t]!='\0') {
			w[n]->INDwords[t]=str[t];
			t++;
		}
		w[n]->INDwords[t]='\0';
		w[n]->frequency=1;
	} else //�ظ�����
		w[i]->frequency++;
}

int EHandle(FILE *fp,Eword *w[]) {//���ļ��е��ַ�����ɵ��ʣ��ҽ���дȫ��ת����Сд��ͬʱ���ǵ����Ӵʻ�������ӷ����������-������'����
	int i=0,n=0;
	char ch;
	char bh=0;//bh���ڴ������к��е����ŵ����
	char ah=0;//���ڴ������ַ�Ϊ-�����
	char single[EMAXL]= {0};

	while((ch=fgetc(fp))!=EOF) {
		if(!isalpha(ch))//������һ������ĸ�ַ�������bh
			bh=0;
		if(isalpha(ch)&&bh!=0)//��bh��Ϊ����ch����ĸʱ��˵����ǰ�ַ����ڵ�����֮����������ѭ��
			continue;
		if(!isalpha(ch)&&ch!='-')//��������ĸ�ַ��Ҹ��ַ���Ϊ���ַ�ʱ��������ѭ��
			continue;
		i=0;
		while(isalpha(ch)||ch=='-') {
			if(ch=='-'&&i==0) {
				ch=fgetc(fp);
				ah=1;
				break;
			}
			if(ch>='A'&&ch<='Z')//����д��ĸȫ��ת����Сд��ĸ
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
				single[i-1]='\0';//�ֶ����'\0'
			}
		}
		single[i]='\0';//�ֶ����'\0'

		if(ch=='\'')//�������ź������ĸ����
			bh=ch;
		w[n]=(Eword*)malloc(sizeof(Eword));
		if(IfAppeared(w,single,n)==-1)//IfAppeared���������ж�single�Ƿ��һ�γ���
			n++;//n�����ظ��ĵ��ʵ�����
		EDeposit(single,w,IfAppeared(w,single,n),n-1);//EDeposit�������ڽ����ַ�����������ݱ����w��
	}

	return n;
}

void ESwap(Eword *w1,Eword *w2) {//���������ṹ�������
	Eword w;
	strcpy(w.INDwords,w1->INDwords);
	w.frequency=w1->frequency;
	strcpy(w1->INDwords,w2->INDwords);
	w1->frequency=w2->frequency;
	strcpy(w2->INDwords,w.INDwords);
	w2->frequency=w.frequency;
}

void ESort(Eword *w[],int n) {//�����ʰ�Ƶ����������Ƶ����ͬ�İ��ֵ�������
	int i,j,f;//f��Ϊ��־

	for(i=0; i<n-1; i++) {
		f=1;
		for(j=0; j<n-1; j++) {
			if(w[j]->frequency<w[j+1]->frequency) { //�Ƚ�Ƶ��
				ESwap(w[j],w[j+1]);
				f=0;
			} else if(w[j]->frequency==w[j+1]->frequency) { //Ƶ����ͬ���ֵ�������
				if(strcmp(w[j]->INDwords,w[j+1]->INDwords)>0)//�Ƚ��ַ�����С���ֵ��򣩣�����0˵��ǰ�߱Ⱥ��ߴ�
					ESwap(w[j],w[j+1]);
				f=0;
			}
		}
		if(f==1)//f==1˵�����������Ѿ���ɣ�����ǰ��ֹ
			break;
	}
}

void EPrint(Eword *w[],int n) {//���������
	int i;
	for(i=0; i<n; i++) {
		printf("%d.\tINDword��%s\t\t\tFreq��%d\n",i+1,w[i]->INDwords,w[i]->frequency);
	}
}

int EFPrint(Eword *w[],int n) {//������ļ�
	FILE *fout;
	int i;
	fout=fopen("data/WordStatistics.txt","w");
	if(fout==NULL) {
		printf("�����ļ�ʧ�ܣ�����ԭ��%s\n",strerror(errno));
		return 1;
	}
	for(i=0; i<n; i++) {
		if(Debug) {
			printf("%d.\tINDword��%s\t\t\tFreq��%d\n",i+1,w[i]->INDwords,w[i]->frequency);//----------������----------
		}
		fprintf(fout,"%d.\tINDword��%s\t\t\tFreq��%d\n",i+1,w[i]->INDwords,w[i]->frequency);
	}
	fclose(fout);
	return 0;
}

