#ifndef STDIO_H
#define STDIO_H
#endif
#ifndef STDLIB_H
#define STDLIB_H
#endif
#ifndef STRING_H
#define STRING_H
#endif

extern int Debug;
//Debug=0;//�Ƿ�������ģʽ

int debug();

int debug() {
	fflush(stdin);
	while(1) {
		printf("�Ƿ�Ҫ�Ե���ģʽ��������������1����������0\n");
		scanf("%d",&Debug);
		if(Debug==1||Debug==0) {
			if(Debug)printf("����ģʽ��������\n");
			else printf("��������......\n");
			break;
		}
		printf("�������ѡ���������������룡");
	}
	return 0;
}
