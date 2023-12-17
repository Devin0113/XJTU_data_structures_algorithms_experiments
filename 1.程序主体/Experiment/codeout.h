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

extern int Debug;//声明 是否开启调试模式

unsigned char GOU=0;//编码区
int  j=0;          //有用位数
FILE *fin,*fout;
Leaf *treehead;

void code(char codein[]);
int judgechs(char c);
int ReadChar();
void CreateList();
void hafuman();


void code(char codein[]) { //将生成的哈夫曼编码写入文件
	if(codein==NULL) {
		return;
	}

	int i=0;    //记位器
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
				printf("%x ",GOU);//----------测试用----------
			}

			GOU=0;
			j=0;
		}
		i++;
	}
}

int judgechs(char c) {//判断是否为中文字符
	if(c<0) {
		return 1;//为汉字字符
	} else {
		return 0;//不为汉字
	}
}

int ReadChar() {//读取单个字符，并判断是否为中文字符。将读取到的字符转化为int类型
	int i=0,j=0;
	int *ii=&i;
	char c=0;//c为文件名
	fscanf(fin,"%c",&c);

	if(judgechs(c)) {//若为中文字符
		j=(int)(c);//强制转化为int型
		j=j&0x000000ff;//保留后8位
		j=j<<8;//位运算，左移8位
		i=i|j;//或运算保存j
		j=0;
		fscanf(fin,"%c",&c);//读取下一个
		j=(int)c;
		j=j&0x000000ff;
		i=i|j;//或运算 将前一个j和后一个j拼接起来
	} else {//非中文字符
		i=(int)c;//直接取8位int
	}
	return i;//返回读取到的汉字或非汉字字符
}

void CreateList() {//读取文件创建链表，并统计字符频度，按频度排序
	InitList();//初始化链表
	int t=-1;//保存读取到的 已转化为int类型的字符的值
	int n=0;
	int flag=0;//作为用于跳过插入重复字符的标识
	while(t!=0) {//当还未读取到文件尾部时
		t=ReadChar();//读取一个字符作为新元素
		struct Node *q=head->next;
		int i=0;
		for(i=1; i<=n; i++) {
			if(q->letter==t) {//若为已有元素，则频度+1
				q->data=q->data+1;
				flag=1;
				break;// （为了避免插入已有元素）
			}
			q=q->next;//若为新元素，则移动到下一个结点
		}
		if(flag==1) {//回到前一个最近的for循环 （为了避免插入已有元素）
			flag=0;
			continue;
		}

		ElemInsert(n,1,-1,t);//将新元素插入到q结点
		n++;
	}
	ElemDel(n-1);//删除最后一个结点
	Node*z=FindTheLastElem();//找到最后一个结点（传参数给ElemSort函数）
	ElemSort(head->next,z);//根据字符的频数从小到大排序
}

void hafuman() {
	int a0=1;
	int i=0,j=0;//----------测试用----------
	char *a1;
	fin=fopen("data/SourceDoc.txt","r+");

	while(a0!=0) {
		a0=ReadChar();//从原始文件中按顺序读取字符
		a1=Coder(a0,treehead);//取得字符对应的哈夫曼编码

		if(Debug) {
			for(i=0; i<=15; i++) {//输出单个字符的哈夫曼编码----------测试用----------
				if(j>50) {
					break;
				}
				printf("%d",a1[i]);//
			}
			printf(" ");
			j++;//----------测试用----------
		}

		code(a1);//将哈夫曼编码写入文件
	}
	printf("\n哈夫曼编码已写入文件！\n");
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

