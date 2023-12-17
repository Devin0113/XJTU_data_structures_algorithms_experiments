#ifndef STDIO_H
#define STDIO_H
#endif
#ifndef STDLIB_H
#define STDLIB_H
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
#ifndef DEBUG_H
#define DEBUG_H
#endif

extern int Debug;//���� �Ƿ�������ģʽ

unsigned char GOU=0;//������
int  j=0;          //����λ��
FILE *fin,*fout;
Leaf *treehead;

void code(char codein[]);
int judgechs(char c);
int ReadChar();
void CreateList();
void hafuman();


void code(char codein[]) { //�����ɵĹ���������д���ļ�
	if(codein==NULL) {
		return;
	}

	int i=0;    //��λ��
	i=0;

	while(codein[i] != 2) {
		if(j!=8) {
			if(codein[i] == 0) {
				j++;
			}
			if(codein[i]==1) {
				switch(j) {
					case 0:
						GOU=GOU|0x80;
						break;
					case 1:
						GOU=GOU|0x40;
						break;
					case 2:
						GOU=GOU|0x20;
						break;
					case 3:
						GOU=GOU|0x10;
						break;
					case 4:
						GOU=GOU|0x08;
						break;
					case 5:
						GOU=GOU|0x04;
						break;
					case 6:
						GOU=GOU|0x02;
						break;
					default:
						GOU=GOU|0x01;
						break;
				}
				j++;
			}
		}
		if(j == 8) {
			fputc(GOU,fout);

			if(Debug) {
				printf("%x ",GOU);//----------������----------
			}

			GOU=0;
			j=0;
		}
		i++;
	}
}

int judgechs(char c) {//�ж��Ƿ�Ϊ�����ַ�
	if(c<0) {
		return 1;//Ϊ�����ַ�
	} else {
		return 0;//��Ϊ����
	}
}

int ReadChar() {//��ȡ�����ַ������ж��Ƿ�Ϊ�����ַ�������ȡ�����ַ�ת��Ϊint����
	int i=0,j=0;
	int *ii=&i;
	char c=0;//cΪ�ļ���
	fscanf(fin,"%c",&c);

	if(judgechs(c)) {//��Ϊ�����ַ�
		j=(int)(c);//ǿ��ת��Ϊint��
		j=j&0x000000ff;//������8λ
		j=j<<8;//λ���㣬����8λ
		i=i|j;//�����㱣��j
		j=0;
		fscanf(fin,"%c",&c);//��ȡ��һ��
		j=(int)c;
		j=j&0x000000ff;
		i=i|j;//������ ��ǰһ��j�ͺ�һ��jƴ������
	} else {//�������ַ�
		i=(int)c;//ֱ��ȡ8λint
	}
	return i;//���ض�ȡ���ĺ��ֻ�Ǻ����ַ�
}

void CreateList() {//��ȡ�ļ�����������ͳ���ַ�Ƶ�ȣ���Ƶ������
	InitList();//��ʼ������
	int t=-1;//�����ȡ���� ��ת��Ϊint���͵��ַ���ֵ
	int n=0;
	int flag=0;//��Ϊ�������������ظ��ַ��ı�ʶ
	while(t!=0) {//����δ��ȡ���ļ�β��ʱ
		t=ReadChar();//��ȡһ���ַ���Ϊ��Ԫ��
		struct Node *q=head->next;
		int i=0;
		for(i=1; i<=n; i++) {
			if(q->letter==t) {//��Ϊ����Ԫ�أ���Ƶ��+1
				q->data=q->data+1;
				flag=1;
				break;// ��Ϊ�˱����������Ԫ�أ�
			}
			q=q->next;//��Ϊ��Ԫ�أ����ƶ�����һ�����
		}
		if(flag==1) {//�ص�ǰһ�������forѭ�� ��Ϊ�˱����������Ԫ�أ�
			flag=0;
			continue;
		}

		ElemInsert(n,1,-1,t);//����Ԫ�ز��뵽q���
		n++;
	}
	ElemDel(n-1);//ɾ�����һ�����
	Node*z=FindTheLastElem();//�ҵ����һ����㣨��������ElemSort������
	ElemSort(head->next,z);//�����ַ���Ƶ����С��������
}

void hafuman() {
	int a0=1;
	int i=0,j=0;//----------������----------
	char *a1;
	fin=fopen("data/SourceDoc.txt","r+");

	while(a0!=0) {
		a0=ReadChar();//��ԭʼ�ļ��а�˳���ȡ�ַ�
		a1=Coder(a0,treehead);//ȡ���ַ���Ӧ�Ĺ���������

		if(Debug) {
			for(i=0; i<=15; i++) {//��������ַ��Ĺ���������----------������----------
				if(j>50) {
					break;
				}
				printf("%d",a1[i]);//
			}
			printf(" ");
			j++;//----------������----------
		}

		code(a1);//������������д���ļ�
	}
	printf("\n������������д���ļ���\n");
	if(Debug) {
		system("pause");
	}
	if(GOU!=0) {
		fputc(GOU,fout);
		GOU=0;
		j=0;
	}
	fclose(fin);
	system("pause");
}

