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

extern int Debug;//声明 是否开启调试模式

typedef struct Leaf {
	int word,p; //word 字  p  频数
	char code[50];//左 0 右 1
	struct Leaf *par,*l,*r;
} Leaf;

typedef struct Node {
	int data,code; //data 频数 code 编码
	int letter; // 字
	struct Node *next;
	Leaf *leaf; //指向树
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


void InitList() {//初始化链表
	head=malloc(sizeof(*head));
	head->next=NULL;
	head->leaf=NULL;
}

void print() {//测试用的一个函数，用于遍历链表结点，输出节点内容
	struct Node *p=head->next;
	while(p!=NULL) {
		printf("%d ",p->data);
		printf("%d ",p->letter);
		printf("%d ",p->code);
		printf("%d \n",p->next);
		p=p->next;
	}
}

void ElemInsert(int n,int value,int codes,int letters) {//插入一个元素到结点中 （codes暂时置为-1代表空）
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
void ElemDel(int n) {//删除n之后的所有结点
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

void DestroyList() {//销毁链表
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

void my_swap(int *a,int *b) {//传入两个整型指针，调换这两个位置的数值
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

Node *FindTheLastElem() {//返回最后一个结点 （传给ElemSort函数）
	Node *q=head->next;//q 头结点的下一个结点
	while(q!=NULL) {//当q结点不为空时
		q=q->next;//q q的下一个结点
	}
	return q;//当q为NULL时返回q
}

void ElemSort(Node *x, Node *y) {//快速排序算法，按字符频度由小到大给链表元素排序。此处y即为 FindTheLastElem()函数返回值q，即最后一个结点
	if(x==NULL) {//x为空时，结束函数
		return;
	}
	if(y==x) {//x=y时，结束函数
		return;
	}//除了以上两种情况，执行以下代码

	Node *pslow = x;
	Node *pfast = x->next;
	Node *ptemp = x;
	while(pfast!= y) {//当x的下一个结点不为最后一个结点的下一个结点时，即x不为最后一个结点时
		if(pfast->data < x->data) {//若x下一个结点的频数小于 x的频数
			ptemp = pslow;//temp保存x
			pslow = pslow->next;//x又赋为x的下一个结点
			my_swap(&pslow->data , &pfast->data);
			my_swap(&pslow->letter , &pfast->letter);
		}
		pfast = pfast->next;
	}
	my_swap(&pslow->data , &x->data);
	my_swap(&pslow->letter , &x->letter);
	ElemSort(x , pslow);//递归
	ElemSort(pslow->next , y);//递归
}
