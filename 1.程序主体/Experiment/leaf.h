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

extern int Debug;//���� �Ƿ�������ģʽ

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


void fpf(FILE *fout,int a) {//���ڽ��� ���ԭ�ĵ�
	int c=0,d=0;//c ����ǰ8λ d �����8λ
	if(a>255) {//��aΪ����
		d=(a|d)&0x000000ff;//ȡa�ĺ�8λ
		c=(a|c);//ȡa
		c=c>>8;//λ���㣬����8λ
		c=c&0x000000ff;//ȡc�ĺ�8λ����ȡa��ǰ8λ
		fprintf(fout,"%c%c",c,d);//ƴ��c��d��д���ļ�

		if(Debug) {
			printf("%c%c",c,d);//----------������----------
		}

		return ;
	}
	fprintf(fout,"%c",a);//a��Ϊ����ʱ��ֱ�����ļ���д��

	if(Debug) {
		printf("%c",a);//----------������----------
	}

	return ;
}

FILE *pf(int a,FILE *f) {//���ڱ��� ����
	int c=0,d=0;//c ����ǰ8λ d �����8λ
	if(a>255) {//��aΪ����
		d=(a|d)&0x000000ff;//ȡa�ĺ�8λ
		c=(a|c);//ȡa
		c=c>>8;//λ���㣬����8λ
		c=c&0x000000ff;//ȡc�ĺ�8λ����ȡa��ǰ8λ
		fprintf(f,"%c%c\t",c,d);//ƴ��c��d,д���ļ�

		if(Debug) {
			printf("%c%c\t",c,d);//��������ַ�----------������----------
		}

		return f;
	}
	fprintf(f,"%c\t",a);//a��Ϊ����ʱ��ֱ�����ļ���д��

	if(Debug) {
		printf("%c\t",a);//����������ַ�----------������----------
	}

	return f;
}


Node *Node_Cre() {//��㴴��
	Node *node;
	node=(Node *)calloc(1,sizeof(Node));
	node->data=0;//Ƶ�� 0
	node->letter=-1;//���� -1
	node->leaf=NULL;//����� NULL
	node->next=NULL;//��һ����� NULL
	return node;
}

int ins (Node *h,Node *node) {//�����ɵĹ��������������������򣬴˺�����Leaf_Fus()�б����ã��������ֱ�Leaf_Xyz()�����������������Ź�������
	Node *a,*b=node;
	for (a=h; a->next!=NULL; a=a->next) {//ѭ�� h��㼰������н��
		if(b->data<a->next->data) {//��node���Ƶ��С��a���Ƶ��
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

Leaf *Leaf_Cre(void) {//��������㲢��ʼ��
	Leaf *leaf=(Leaf *)calloc(1,sizeof(Leaf));
	int i;
	leaf->word=-1;
	leaf->p=0;
	leaf->l=NULL;
	leaf->par=NULL;
	leaf->r=NULL;
	for(i=0; i<50; i++) {//��ʼ��������codeֵ��2Ϊ��ʶ����
		leaf->code[i]=2;
	}
	return leaf;
}

int Leaf_Copy(Node *node) {//������������ݸ��Ƶ���Ӧ�����Ľ����
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

int Leaf_Link(Node *node) {//ʹҶ�ӽڵ����������Ӧ���������еĵ�����㣺��Ϊ���򷵻�0������Ϊ�գ����޶�Ӧ����㣬�򴴽�һ������㣬�������������ݸ�ֵ��ȥ��������1����
	Leaf *leaf;
	if(node==NULL) {
		return 0;
	} else if(node->leaf==NULL) {
		leaf=Leaf_Cre();
		node->leaf=leaf;
	}
	Leaf_Copy(node);//������������ݸ��Ƶ���Ӧ�����Ľ����
	return 1;
}

Leaf *Leaf_LinkAll(Node *h) { //�൱�ڽ�����Ԫ�أ���ԭ��Ϊh����1����2��3��...��n��˳�򣩣�����������root���������ϣ�ÿ�����������ָ��ԭ���������һ����㣬������Ϊ��һ������root�������ұ�����һ�� ������������
	Node *a,*b;
	Leaf *root,*leaf,*t;
	int k;
	a=h;
	for (a=h; a->next!=NULL; a=a->next) {//���˴�a��ʼֵΪ����ͷ��㣩a��Ϊ�������һ�����ʱ
		b=a->next;//a����һ�����
		k=Leaf_Link(a);//����a��Ӧ�������
		k=Leaf_Link(b);//����a��һ������Ӧ�������
		t=a->leaf;
		t->r=b->leaf;//a��Ӧ���������Ҷ���Ϊb��㣨a����һ����㣩��Ӧ�������
		b->leaf->l=a->leaf;//b��Ӧ�������������Ϊa����Ӧ�������
	}
	root=Leaf_Cre();//������һ�������
	a->leaf->r=root;//a��ʱΪ���һ�����
	root->l=a->leaf;
	a=h;
	leaf=a->leaf;
	free(leaf);
	a=h->next;
	a->leaf->l=NULL;
	return root;//����root����
}

int Leaf_Fus(Node *h) {//h �����ͷ��� �������������Ĺ���
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

Leaf *Leaf_Xyz(Node *h) { //0-1. ����������  ����������
	Leaf *root,*t;
	Node *a=h,*b;
	root=Leaf_Cre();//0-1-1.��������㲢��ʼ��
	t=Leaf_LinkAll(h);//0-1-2.��������ת������Ȼ����������Ľṹ��
	root->r=t;
	for (b=a->next; b->next!=NULL; b=a->next) {
		Leaf_Fus(a);//0-1-3.���ɹ�������
	}
	root->l=b->leaf;
	b->leaf->par=root;
	free(a);
	free(b);
	return root;
}

int Leaf_Pen(Leaf *root,Leaf *leaf) { //���ɶ���������  ��С�Ҵ�
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

int Leaf_Syn(Leaf *root) {//��Ҷ�ӽ�����ϲ��ң����ɹ��������벢д���뱾�ļ��������ɶ������������ڱ��� 
	Leaf *a=root->r,*b1,*b2,*r=root->r;
	char c[50];
	FILE *f=fopen("data/Statistic.txt","w+");
	int i,j,n,k;
	for (i=0; i<50; i++) {//��ʼ��
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
				printf("Enter\t");//----------������----------
			}

		} else if(a->word==32) {
			fprintf(f,"Space\t");

			if(Debug) {
				printf("Space\t");//----------������----------
			}

		} else if(a->word==9) {
			fprintf(f,"Tab\t");

			if(Debug) {
				printf("Tab\t");//----------������----------
			}

		} else if(a->word==41377) {
			fprintf(f,"C-Space\t");

			if(Debug) {
				printf("C-Space\t");//----------������----------
			}

		} else {
			f=pf(a->word,f);

			if(Debug) {
				printf("%d\t",a->word);//----------������----------
			}

		}
		fprintf(f,"freq=%d\t\tHFMcode:",a->p);

		if(Debug) {
			printf("freq=%d\t\tHFMcode:",a->p);//----------������----------
		}

		for(j=0; j<n; j++) {
			a->code[j]=c[i];
			fprintf(f,"%d",c[i]);

			if(Debug) {
				printf("%d",c[i]);//----------������----------
			}

			i--;
		}
		fprintf(f,"\n");

		if(Debug) {
			printf("\n");//----------������----------
		}

		b1=a;
		a=a->l;
		Leaf_Pen(r,b1);//���ɶ���������
	}
	fclose(f);
	printf("Statistic.txt���뱾��������\n");
	system("pause");
	return 1;
}

Leaf *Tree(Node *h) {//0.���������ؽ��õ����ĸ��ڵ�
	Leaf *root;
	root=Leaf_Xyz(h);//0-1.���ɹ������� 
	Leaf_Syn(root);//0-2.�����뱾�����ɶ��������� 
	return root;
}

char *Coder(int word,Leaf *root) {//ĳ���ַ����ѱ�ת�����͵��ַ��� ���������ĸ��ڵ�  ���ܣ����ز��ҵ��ַ���Ӧ�Ĺ���������
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

int decoder(Leaf *root) {//����
	unsigned char c=1,t,j;
	FILE *fou,*fi;
	Leaf *leaf=root->l;
	int ii = 0;
	fi=fopen("data/Encode.dat","rb");//rb��ʾ��ȡ�������ļ�
	fou=fopen("data/Target.txt","w+");
	while (1) {
		ii++;
		c=0;
		fscanf(fi,"%c",&c);//��ÿ8λ����ȡEncode.dat�ļ�����ֵ��c
		if(feof(fi)) {//��ʾ�ļ���ȡ��ϣ���end of file��
			break;
		}
		t=1<<7;//t=10000000(B)
		while (t!=0) {
			j=((t&c)!=0);
			if (j) {
				leaf=leaf->r;//����ȡ����λֵΪ1ʱ��������
			} else {
				leaf=leaf->l;//����ȡ����λֵΪ0ʱ��������
			}
			if(leaf->word!=-1) {//���˽������ַ�ʱ�����˽ڵ�Ϊ��Ҷʱ
				fpf(fou,leaf->word);//���ַ�д��DecodeDoc.txt�ļ�
				leaf=root->l;//�ص����������һ��Ѱ���ַ�
			}
			t=t>>1;//��t����һλ����1000 0000��Ϊ0100 0000
		}
	}
	printf("�ĵ�ѹ����ɺ�ռ���ֽ���Ϊ%d\n",ii);
	fclose(fi);
	fclose(fou);
	return 1;
}
