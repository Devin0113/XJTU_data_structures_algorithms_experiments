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
//Debug=0;//是否开启调试模式

int debug();

int debug() {
	fflush(stdin);
	while(1) {
		printf("是否要以调试模式启动？是请输入1，否请输入0\n");
		scanf("%d",&Debug);
		if(Debug==1||Debug==0) {
			if(Debug)printf("调试模式已启动！\n");
			else printf("正常运行......\n");
			break;
		}
		printf("您输入的选项有误，请重新输入！");
	}
	return 0;
}
