#ifndef STDIO_H
#define STDIO_H
#endif
#ifndef STDLIB_H
#define STDLIB_H
#endif

#ifndef LINK_H
#define LINK_H
#endif
#ifndef CODEOUT_H
#define CODEOUT_H
#endif
#ifndef DEBUG_H
#define DEBUG_H
#endif

extern int Debug;//声明 是否开启调试模式

void fpf(FILE *fout,int a);
FILE *pf(int a,FILE *f);
Node *Node_Cre();
int ins (Node *h,Node *node);
Leaf *Leaf_Cre(void);
int Leaf_Copy(Node *node);
int Leaf_Link(Node *node);
Leaf *Leaf_LinkAll(Node *h);
int Leaf_Fus(Node *h);
Leaf *Leaf_Xyz(Node *h);
int Leaf_Pen(Leaf *root,Leaf *leaf);
int Leaf_Syn(Leaf *root);
Leaf *Tree(Node *h);
char *Coder(int word,Leaf *root);
int decoder(Leaf *root);


void fpf(FILE *fout,int a) {//用于解码 输出原文档
	int c=0,d=0;//c 保存前8位 d 保存后8位
	if(a>255) {//若a为汉字
		d=(a|d)&0x000000ff;//取a的后8位
		c=(a|c);//取a
		c=c>>8;//位运算，右移8位
		c=c&0x000000ff;//取c的后8位，即取a的前8位
		fprintf(fout,"%c%c",c,d);//拼接c和d，写入文件

		if(Debug) {
			printf("%c%c",c,d);//----------测试用----------
		}

		return ;
	}
	fprintf(fout,"%c",a);//a不为汉字时，直接在文件中写入

	if(Debug) {
		printf("%c",a);//----------测试用----------
	}

	return ;
}

FILE *pf(int a,FILE *f) {//用于编码 生成
	int c=0,d=0;//c 保存前8位 d 保存后8位
	if(a>255) {//若a为汉字
		d=(a|d)&0x000000ff;//取a的后8位
		c=(a|c);//取a
		c=c>>8;//位运算，右移8位
		c=c&0x000000ff;//取c的后8位，即取a的前8位
		fprintf(f,"%c%c\t",c,d);//拼接c和d,写入文件

		if(Debug) {
			printf("%c%c\t",c,d);//输出中文字符----------测试用----------
		}

		return f;
	}
	fprintf(f,"%c\t",a);//a不为汉字时，直接在文件中写入

	if(Debug) {
		printf("%c\t",a);//输出非中文字符----------测试用----------
	}

	return f;
}


Node *Node_Cre() {//结点创建
	Node *node;
	node=(Node *)calloc(1,sizeof(Node));
	node->data=0;//频数 0
	node->letter=-1;//编码 -1
	node->leaf=NULL;//树结点 NULL
	node->next=NULL;//下一个结点 NULL
	return node;
}

int ins (Node *h,Node *node) {//将生成的哈夫曼子树放入链表并排序，此函数在Leaf_Fus()中被调用，而后者又被Leaf_Xyz()反复调用以生成整颗哈夫曼树
	Node *a,*b=node;
	for (a=h; a->next!=NULL; a=a->next) {//循环 h结点及其后所有结点
		if(b->data<a->next->data) {//若node结点频数小于a结点频数
			b->next=a->next;
			a->next=b;
			return 1;
		}
	}
	if (a->next==NULL) {
		a->next=b;
	}
	return 1;
}

Leaf *Leaf_Cre(void) {//创建树结点并初始化
	Leaf *leaf=(Leaf *)calloc(1,sizeof(Leaf));
	int i;
	leaf->word=-1;
	leaf->p=0;
	leaf->l=NULL;
	leaf->par=NULL;
	leaf->r=NULL;
	for(i=0; i<50; i++) {//初始化数据阈code值（2为标识符）
		leaf->code[i]=2;
	}
	return leaf;
}

int Leaf_Copy(Node *node) {//把链表结点的内容复制到对应的树的结点中
	Leaf *leaf;
	if (node==NULL) {
		return 0;
	} else if(node->leaf==NULL) {
		return 0;
	} else {
		leaf=node->leaf;
		leaf->word=node->letter;
		leaf->p=node->data;
		return 1;
	}
}

int Leaf_Link(Node *node) {//使叶子节点与链表结点对应：对链表中的单个结点：若为空则返回0；若不为空，且无对应树结点，则创建一个树结点，并将链表结点内容赋值进去（并返回1）。
	Leaf *leaf;
	if(node==NULL) {
		return 0;
	} else if(node->leaf==NULL) {
		leaf=Leaf_Cre();
		node->leaf=leaf;
	}
	Leaf_Copy(node);//把链表结点的内容复制到对应的树的结点中
	return 1;
}

Leaf *Leaf_LinkAll(Node *h) { //相当于将链表元素（记原先为h（即1）到2，3，...，n的顺序），倒序连接在root（树根）上，每个结点右子树指向原先链表的上一个结点，左子树为下一个（或root根）（右边是上一个 ，即从右向左）
	Node *a,*b;
	Leaf *root,*leaf,*t;
	int k;
	a=h;
	for (a=h; a->next!=NULL; a=a->next) {//（此处a初始值为链表头结点）a不为链表最后一个结点时
		b=a->next;//a的下一个结点
		k=Leaf_Link(a);//创建a对应的树结点
		k=Leaf_Link(b);//创建a下一个结点对应的树结点
		t=a->leaf;
		t->r=b->leaf;//a对应的树结点的右儿子为b结点（a的下一个结点）对应的树结点
		b->leaf->l=a->leaf;//b对应的树结点的左儿子为a结点对应的树结点
	}
	root=Leaf_Cre();//创建了一个根结点
	a->leaf->r=root;//a此时为最后一个结点
	root->l=a->leaf;
	a=h;
	leaf=a->leaf;
	free(leaf);
	a=h->next;
	a->leaf->l=NULL;
	return root;//返回root树根
}

int Leaf_Fus(Node *h) {//h 链表的头结点 构建哈夫曼树的过程
	Node *a=h->next,*b,*c;
	int k;
	if(a==NULL) {
		return 0;
	} else if(a->next==NULL) {
		return 0;
	} else {
		b=a->next;
		c=Node_Cre();
		k=Leaf_Link(c);
		c->leaf->r=a->leaf;
		c->leaf->l=b->leaf;
		c->data=a->data+b->data;
		c->leaf->p=c->data;
		a->leaf->par=c->leaf;
		b->leaf->par=c->leaf;
		h->next=b->next;
		k=ins(h,c);
		free(a);
		free(b);
		return 1;
	}
}

Leaf *Leaf_Xyz(Node *h) { //0-1. 左子树解密  右子树加密
	Leaf *root,*t;
	Node *a=h,*b;
	root=Leaf_Cre();//0-1-1.创建树结点并初始化
	t=Leaf_LinkAll(h);//0-1-2.链表向树转化（仍然是类似链表的结构）
	root->r=t;
	for (b=a->next; b->next!=NULL; b=a->next) {
		Leaf_Fus(a);//0-1-3.生成哈夫曼树
	}
	root->l=b->leaf;
	b->leaf->par=root;
	free(a);
	free(b);
	return root;
}

int Leaf_Pen(Leaf *root,Leaf *leaf) { //生成二叉排序树  左小右大
	Leaf *roo=root,*lea=leaf;
	int a=1;
	lea->r=NULL;
	lea->l=NULL;
	while(lea->word!=roo->word) {
		if(lea->word>roo->word) {
			if(roo->r==NULL) {
				roo->r=lea;
				return 1;
			}
			roo=roo->r;
		} else {
			if(roo->l==NULL) {
				roo->l=lea;
				return 1;
			}
			roo=roo->l;
		}
	}
	return 0;
}

int Leaf_Syn(Leaf *root) {//由叶子结点向上查找，生成哈夫曼编码并写入码本文件，再生成二叉排序树用于编码 
	Leaf *a=root->r,*b1,*b2,*r=root->r;
	char c[50];
	FILE *f=fopen("data/Statistic.txt","w+");
	int i,j,n,k;
	for (i=0; i<50; i++) {//初始化
		c[i]=2;
	}
	a=a->l;
	r->l=NULL;
	r->word=0;
	while(a!=NULL) {
		b1=a;
		b2=b1->par;
		i=0;
		k=0;
		while (b2!=root) {
			if(b1!=b2->r) {
				c[i]=0;
			} else {
				c[i]=1;
			}
			i++;
			b1=b2;
			b2=b2->par;
		}
		n=i;
		i--;
		if(a->word==10) {
			fprintf(f,"Enter\t");

			if(Debug) {
				printf("Enter\t");//----------测试用----------
			}

		} else if(a->word==32) {
			fprintf(f,"Space\t");

			if(Debug) {
				printf("Space\t");//----------测试用----------
			}

		} else if(a->word==9) {
			fprintf(f,"Tab\t");

			if(Debug) {
				printf("Tab\t");//----------测试用----------
			}

		} else if(a->word==41377) {
			fprintf(f,"C-Space\t");

			if(Debug) {
				printf("C-Space\t");//----------测试用----------
			}

		} else {
			f=pf(a->word,f);

			if(Debug) {
				printf("%d\t",a->word);//----------测试用----------
			}

		}
		fprintf(f,"freq=%d\t\tHFMcode:",a->p);

		if(Debug) {
			printf("freq=%d\t\tHFMcode:",a->p);//----------测试用----------
		}

		for(j=0; j<n; j++) {
			a->code[j]=c[i];
			fprintf(f,"%d",c[i]);

			if(Debug) {
				printf("%d",c[i]);//----------测试用----------
			}

			i--;
		}
		fprintf(f,"\n");

		if(Debug) {
			printf("\n");//----------测试用----------
		}

		b1=a;
		a=a->l;
		Leaf_Pen(r,b1);//生成二叉排序树
	}
	fclose(f);
	printf("Statistic.txt（码本）已生成\n");
	system("pause");
	return 1;
}

Leaf *Tree(Node *h) {//0.建树，返回建好的树的根节点
	Leaf *root;
	root=Leaf_Xyz(h);//0-1.生成哈夫曼树 
	Leaf_Syn(root);//0-2.生成码本，生成二叉排序树 
	return root;
}

char *Coder(int word,Leaf *root) {//某个字符（已被转成整型的字符） 哈夫曼树的根节点  功能：返回查找到字符对应的哈夫曼编码
	int w=word;
	char *c;
	Leaf *leaf=root->r;
	if(w==0) {
		return NULL;
	}
	while(leaf!=NULL) {
		if(w==leaf->word) {
			c=leaf->code;
			return c;
		} else if(w>leaf->word) {
			leaf=leaf->r;
		} else {
			leaf=leaf->l;
		}
	}
	if(leaf==NULL) {
		return NULL;
	}
}

int decoder(Leaf *root) {//解码
	unsigned char c=1,t,j;
	FILE *fou,*fi;
	Leaf *leaf=root->l;
	int ii = 0;
	fi=fopen("data/Encode.dat","rb");//rb表示读取二进制文件
	fou=fopen("data/Target.txt","w+");
	while (1) {
		ii++;
		c=0;
		fscanf(fi,"%c",&c);//（每8位）读取Encode.dat文件并赋值给c
		if(feof(fi)) {//表示文件读取完毕，（end of file）
			break;
		}
		t=1<<7;//t=10000000(B)
		while (t!=0) {
			j=((t&c)!=0);
			if (j) {
				leaf=leaf->r;//即读取到的位值为1时，右子树
			} else {
				leaf=leaf->l;//即读取到的位值为0时，左子树
			}
			if(leaf->word!=-1) {//当此结点存在字符时，即此节点为树叶时
				fpf(fou,leaf->word);//将字符写入DecodeDoc.txt文件
				leaf=root->l;//回到起点用于下一次寻找字符
			}
			t=t>>1;//将t右移一位，如1000 0000变为0100 0000
		}
	}
	printf("文档压缩完成后占总字节数为%d\n",ii);
	fclose(fi);
	fclose(fou);
	return 1;
}
