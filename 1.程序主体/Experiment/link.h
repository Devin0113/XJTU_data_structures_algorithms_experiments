#ifndef STDIO_H
#define STDIO_H
#endif
#ifndef STDLIB_H
#define STDLIB_H
#endif
#ifndef MALLOC_H
#define MALLOC_H
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

extern int Debug;//���� �Ƿ�������ģʽ

typedef struct Leaf {
	int word,p; //word ��  p  Ƶ��
	char code[50];//�� 0 �� 1
	struct Leaf *par,*l,*r;
} Leaf;

typedef struct Node {
	int data,code; //data Ƶ�� code ����
	int letter; // ��
	struct Node *next;
	Leaf *leaf; //ָ����
} Node;

struct Node *head;

void InitList();
void print();
void ElemInsert(int n,int value,int codes,int letters);
void ElemDel(int n);
void DestroyList();
void my_swap(int *a,int *b);
Node *FindTheLastElem();
void ElemSort(Node *x, Node *y);


void InitList() {//��ʼ������
	head=malloc(sizeof(*head));
	head->next=NULL;
	head->leaf=NULL;
}

void print() {//�����õ�һ�����������ڱ��������㣬����ڵ�����
	struct Node *p=head->next;
	while(p!=NULL) {
		printf("%d ",p->data);
		printf("%d ",p->letter);
		printf("%d ",p->code);
		printf("%d \n",p->next);
		p=p->next;
	}
}

void ElemInsert(int n,int value,int codes,int letters) {//����һ��Ԫ�ص������ ��codes��ʱ��Ϊ-1����գ�
	struct Node *q=head,*a;
	int i;
	a=malloc(sizeof(*a));
	a->next=NULL;
	a->data=value;
	a->letter=letters;
	a->code=codes;
	a->leaf=NULL;
	for(i=0; i<n; i++) {
		q=q->next;
	}
	a->next=q->next;
	q->next=a;

}
void ElemDel(int n) {//ɾ��n֮������н��
	struct Node *q=head;
	int i;
	struct Node *a;
	for(i=0; i<n; i++) {
		q=q->next;
	}
	a=q->next;
	q->next=a->next;
	free(a);
	a=NULL;
}

void DestroyList() {//��������
	struct Node *q=head->next,*r=q->next;
	while(q!=NULL) {
		free(q);
		q=r;
		if(r!=NULL)
			r=r->next;
	}
	free(q);
	q=NULL;
	r=NULL;
	free(head);
	head=NULL;
}

void my_swap(int *a,int *b) {//������������ָ�룬����������λ�õ���ֵ
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

Node *FindTheLastElem() {//�������һ����� ������ElemSort������
	Node *q=head->next;//q ͷ������һ�����
	while(q!=NULL) {//��q��㲻Ϊ��ʱ
		q=q->next;//q q����һ�����
	}
	return q;//��qΪNULLʱ����q
}

void ElemSort(Node *x, Node *y) {//���������㷨�����ַ�Ƶ����С���������Ԫ�����򡣴˴�y��Ϊ FindTheLastElem()��������ֵq�������һ�����
	if(x==NULL) {//xΪ��ʱ����������
		return;
	}
	if(y==x) {//x=yʱ����������
		return;
	}//�����������������ִ�����´���

	Node *pslow = x;
	Node *pfast = x->next;
	Node *ptemp = x;
	while(pfast!= y) {//��x����һ����㲻Ϊ���һ��������һ�����ʱ����x��Ϊ���һ�����ʱ
		if(pfast->data < x->data) {//��x��һ������Ƶ��С�� x��Ƶ��
			ptemp = pslow;//temp����x
			pslow = pslow->next;//x�ָ�Ϊx����һ�����
			my_swap(&pslow->data , &pfast->data);
			my_swap(&pslow->letter , &pfast->letter);
		}
		pfast = pfast->next;
	}
	my_swap(&pslow->data , &x->data);
	my_swap(&pslow->letter , &x->letter);
	ElemSort(x , pslow);//�ݹ�
	ElemSort(pslow->next , y);//�ݹ�
}
