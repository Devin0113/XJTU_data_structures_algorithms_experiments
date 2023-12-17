#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"link.h"
#include"leaf.h"
#include"codeout.h"
#include"kmp.h"
#include"debug.h"
#include"ew_stat.h"

Debug=0;	//是否开启调试模式
char choicech=NULL;
int choice=0;	//主函数选项
int IfCoded=0,IfDecoded=0,IfDeleted=0,IfRenamed=0,IfEwstated=0;	//是否已经编码，解码，删除，重命名，统计英文单词
int IfDelete=2,IfRename=2,IfEwstat=2;	//删除，重命名，统计英文单词选项
int quit=0;	//退出选项

int CompareFile();
int OptionForEncode();
int OptionForDelete();
int OptionForDecode();
int OptionForRename();
int OptionForEwstat();


int CompareFile() {//文件对比
	int finChar=NULL,foutChar=NULL;
	int i=0;
	fin=fopen("data/SourceDoc.txt","r");
	fout=fopen("data/Target.txt","r");
	do {
		finChar=(int)(fgetc(fin));
		foutChar=(int)(fgetc(fout));
		if(finChar==foutChar) {
			if(Debug) {
				printf("%d\t%d\n",finChar,foutChar);
			}
			i++;
		} else {
			if(Debug) {
				printf("\n%d？\t？%d\n",finChar,foutChar);
			}
			fclose(fin);
			fclose(fout);
			return i;
		}
	} while(EOF!=finChar||EOF!=foutChar);
	fclose(fin);
	fclose(fout);
	return -1;
}

int OptionForEncode() {
	printf("已成功读取SourceDoc.txt！\n");
	system("pause");
	fout=fopen("data/Encode.dat","wb");
	printf("已成功创建Encode.dat！\n");
	system("pause");
	CreateList();

	if(Debug) {
		print();//测试用 输出生成的链表内元素
		system("pause");
	}

	treehead=Tree(head);
	hafuman();
	printf("编码成功，结果输出于data/Encode.dat\n");
	fclose(fout);
	IfCoded=1;
	return 0;
}

int OptionForDelete() {
	while(IfDelete!=0&&IfDelete!=1) {
		fflush(stdin);
		printf("是否要删除源文件（data/SourceDoc.txt）？是请输入1，否请输入0\n");
		scanf("%d",&IfDelete);
		if(IfDelete==1) {
			if(remove("data/SourceDoc.txt")==0) {

				IfDeleted=1;
				printf("删除成功！\n");
			} else {
				printf("删除失败！错误原因：%s。\n尝试清除源文件内容...\n",strerror(errno));
				fin=fopen("data/SourceDoc.txt","w");
				if(fin!=NULL) {
					printf("清除成功！\n");
					fclose(fin);
					IfDeleted=1;
				} else {
					printf("清除失败！错误原因：%s。\n",strerror(errno));
				}
			}
		} else if(IfDelete==0) {
			printf("已保留源文件。\n");
		} else {
			printf("您输入的选项有误，请重新输入！");
		}
	}
	return 0;
}

int OptionForDecode() {
	decoder(treehead);

	printf("解码成功，结果输出于data/Target.txt\n");
	IfDecoded=1;
	return 0;
}

int OptionForRename() {
	while(IfRename!=1&&IfRename!=0) {
		fflush(stdin);
		printf(	"是否要重命名解码后的文件（data/Target.txt -> data/_SourceDoc.txt）？"
		        "\n此步骤是便于重复测试代码的操作，若有此需求请输入1，若无需求请输入0。"
		        "\n是请输入1，否请输入0\n");
		scanf("%d",&IfRename);
		if(IfRename==1) {
			if(rename("data/Target.txt","data/_SourceDoc.txt")==0) {
				IfRenamed=1;
				printf("重命名成功！\n");
			} else {
				printf("重命名失败！错误原因：%s\n",strerror(errno));
			}
		} else if(IfRename==0) {
			printf("已保留解码后文件。\n");
		} else {
			printf("您输入的选项有误，请重新输入！");
		}
	}
	return 0;
}

int OptionForEwstat() {
	if(Debug) {
		while(IfEwstat!=0&&IfEwstat!=1) {
			fflush(stdin);
			printf("若无需重复统计请输入0，反之输入1\n");
			scanf("%d",&IfEwstat);
			if(IfEwstat) {
				IfEwstat=2;
				return 1;
			} else if(!IfEwstat) {
				IfEwstat=2;
				printf("已取消操作！\n");
				return 0;
			} else {
				printf("您输入的选项有误，请重新输入！");
			}
		}
	} else {
		printf("请勿重复下达统计英文单词指令！\n");
	}
}

int main() {//主函数
	debug();

	printf("请将要编码的文件重命名为SourceDoc.txt并存放于根目录下的data文件夹中。\n");
	system("pause");

	while(!quit) {

		fflush(stdin);
		if(Debug) {
			printf(	"请选择您将要进行的操作（仅需输入单个数字）："
			        "\n\t1......编码\t\t\t\t2......解码\n\t3......查找（精确和模糊）\t\t4......对比文件内容"
			        "\n\t5......清屏\t\t\t\t6......统计英文单词\n\t7......关闭调试\t\t\t\t8......退出\n");
		} else {
			printf(	"请选择您将要进行的操作（仅需输入单个数字）："
			        "\n\t1......编码\t\t\t\t2......解码\n\t3......查找（精确和模糊）\t\t4......对比文件内容"
			        "\n\t5......清屏\t\t\t\t6......统计英文单词\n\t7......开启调试\t\t\t\t8......退出\n");
		}
		scanf("%s",&choicech);
		if(choicech>=48||choice<=57) {
			choice=(int)(choicech)-48;
		} else choice=0;
		fflush(stdin);

		switch(choice) {
			case 1://编码
				if(IfCoded) {
					printf("文件已编码，请勿重复下达编码指令！\n请重新输入！");
				} else {
					fin=fopen("data/SourceDoc.txt","r");
					if(fin==NULL) {
						printf("未找到SourceDoc.txt，请正确导入文件后再启动程序！\n");
						fclose(fin);
						system("pause");
						return 0;
					}
					if(fgetc(fin)==EOF) {
						printf("SourceDoc.txt为空！请导入正确的文件后再启动程序！\n");
						fclose(fin);
						system("pause");
						return 0;
					}

					OptionForEncode();//编码部分函数

					fclose(fin);

					OptionForDelete();//删除源文件部分函数

					system("pause");
				}
				break;
			case 2://解码
				if(IfCoded) {
					if(!IfDecoded) {

						OptionForDecode();//解码部分函数

						if(IfDeleted) {

							OptionForRename();//重命名解码文件函数

						}
						system("pause");
					} else {
						printf("文件已解码，请勿重复下达解码指令！\n请重新输入！");
					}
				} else {
					printf("文件还未编码，请重新输入！");
				}
				break;
			case 3://查找
				if(IfCoded) {
					if(IfDeleted) {
						printf("源文件已删除或清除，无法进行内容查找！请重新输入！");
					} else {

						kmp2();//查找部分函数

						system("pause");
					}
				} else {
					printf("文件还未编码，请重新输入！");
				}
				break;
			case 4://比对
				if(IfCoded) {
					if(!IfDeleted) {
						if(!IfDecoded) {
							printf("文件还未解码，请重新输入！");
						} else {
							if(CompareFile()==-1) {
								printf("解码后的文件（Target.txt）与源文件（SourceDoc.txt）内容一致！\n");
							} else {
								printf("解码后的文件（Target.txt）与源文件（SourceDoc.txt）内容不一致！"
								       "\n出错位置：第%d个字符。\n",CompareFile());
							}
						}
					} else {
						printf("源文件已删除或清除，无法进行内容比对！请重新输入！");
					}
				} else {
					printf("文件还未编码，请重新输入！");
				}
				break;
			case 5://清屏
				system("cls");
				break;
			case 6:
				if(IfEwstated) {
					printf("已经完成统计！");
					if(!OptionForEwstat()) {
						break;
					}
				}
				if(EStatistics()) {
					printf("未能成功导入SourceDoc.txt！错误原因：%s\n",strerror(errno));
				} else {
					IfEwstated=1;
				}
				system("pause");
				break;
			case 7:
				Debug=!Debug;
				if(Debug) {
					printf("调试模式已开启！");
				} else {
					printf("调试模式已关闭！");
				}
				break;
			case 8://退出
				quit=1;
				break;
			default:
				printf("您输入的选项有误，请重新输入！");
				break;
		}
	}
	printf("已退出菜单页，按任意键退出程序。\n");
	system("pause");

	return 0;
}
