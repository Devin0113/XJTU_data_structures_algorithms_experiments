#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"link.h"
#include"leaf.h"
#include"codeout.h"
#include"kmp.h"
#include"debug.h"
#include"ew_stat.h"

Debug=0;	//�Ƿ�������ģʽ
char choicech=NULL;
int choice=0;	//������ѡ��
int IfCoded=0,IfDecoded=0,IfDeleted=0,IfRenamed=0,IfEwstated=0;	//�Ƿ��Ѿ����룬���룬ɾ������������ͳ��Ӣ�ĵ���
int IfDelete=2,IfRename=2,IfEwstat=2;	//ɾ������������ͳ��Ӣ�ĵ���ѡ��
int quit=0;	//�˳�ѡ��

int CompareFile();
int OptionForEncode();
int OptionForDelete();
int OptionForDecode();
int OptionForRename();
int OptionForEwstat();


int CompareFile() {//�ļ��Ա�
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
				printf("\n%d��\t��%d\n",finChar,foutChar);
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
	printf("�ѳɹ���ȡSourceDoc.txt��\n");
	system("pause");
	fout=fopen("data/Encode.dat","wb");
	printf("�ѳɹ�����Encode.dat��\n");
	system("pause");
	CreateList();

	if(Debug) {
		print();//������ ������ɵ�������Ԫ��
		system("pause");
	}

	treehead=Tree(head);
	hafuman();
	printf("����ɹ�����������data/Encode.dat\n");
	fclose(fout);
	IfCoded=1;
	return 0;
}

int OptionForDelete() {
	while(IfDelete!=0&&IfDelete!=1) {
		fflush(stdin);
		printf("�Ƿ�Ҫɾ��Դ�ļ���data/SourceDoc.txt������������1����������0\n");
		scanf("%d",&IfDelete);
		if(IfDelete==1) {
			if(remove("data/SourceDoc.txt")==0) {

				IfDeleted=1;
				printf("ɾ���ɹ���\n");
			} else {
				printf("ɾ��ʧ�ܣ�����ԭ��%s��\n�������Դ�ļ�����...\n",strerror(errno));
				fin=fopen("data/SourceDoc.txt","w");
				if(fin!=NULL) {
					printf("����ɹ���\n");
					fclose(fin);
					IfDeleted=1;
				} else {
					printf("���ʧ�ܣ�����ԭ��%s��\n",strerror(errno));
				}
			}
		} else if(IfDelete==0) {
			printf("�ѱ���Դ�ļ���\n");
		} else {
			printf("�������ѡ���������������룡");
		}
	}
	return 0;
}

int OptionForDecode() {
	decoder(treehead);

	printf("����ɹ�����������data/Target.txt\n");
	IfDecoded=1;
	return 0;
}

int OptionForRename() {
	while(IfRename!=1&&IfRename!=0) {
		fflush(stdin);
		printf(	"�Ƿ�Ҫ�������������ļ���data/Target.txt -> data/_SourceDoc.txt����"
		        "\n�˲����Ǳ����ظ����Դ���Ĳ��������д�����������1����������������0��"
		        "\n��������1����������0\n");
		scanf("%d",&IfRename);
		if(IfRename==1) {
			if(rename("data/Target.txt","data/_SourceDoc.txt")==0) {
				IfRenamed=1;
				printf("�������ɹ���\n");
			} else {
				printf("������ʧ�ܣ�����ԭ��%s\n",strerror(errno));
			}
		} else if(IfRename==0) {
			printf("�ѱ���������ļ���\n");
		} else {
			printf("�������ѡ���������������룡");
		}
	}
	return 0;
}

int OptionForEwstat() {
	if(Debug) {
		while(IfEwstat!=0&&IfEwstat!=1) {
			fflush(stdin);
			printf("�������ظ�ͳ��������0����֮����1\n");
			scanf("%d",&IfEwstat);
			if(IfEwstat) {
				IfEwstat=2;
				return 1;
			} else if(!IfEwstat) {
				IfEwstat=2;
				printf("��ȡ��������\n");
				return 0;
			} else {
				printf("�������ѡ���������������룡");
			}
		}
	} else {
		printf("�����ظ��´�ͳ��Ӣ�ĵ���ָ�\n");
	}
}

int main() {//������
	debug();

	printf("�뽫Ҫ������ļ�������ΪSourceDoc.txt������ڸ�Ŀ¼�µ�data�ļ����С�\n");
	system("pause");

	while(!quit) {

		fflush(stdin);
		if(Debug) {
			printf(	"��ѡ������Ҫ���еĲ������������뵥�����֣���"
			        "\n\t1......����\t\t\t\t2......����\n\t3......���ң���ȷ��ģ����\t\t4......�Ա��ļ�����"
			        "\n\t5......����\t\t\t\t6......ͳ��Ӣ�ĵ���\n\t7......�رյ���\t\t\t\t8......�˳�\n");
		} else {
			printf(	"��ѡ������Ҫ���еĲ������������뵥�����֣���"
			        "\n\t1......����\t\t\t\t2......����\n\t3......���ң���ȷ��ģ����\t\t4......�Ա��ļ�����"
			        "\n\t5......����\t\t\t\t6......ͳ��Ӣ�ĵ���\n\t7......��������\t\t\t\t8......�˳�\n");
		}
		scanf("%s",&choicech);
		if(choicech>=48||choice<=57) {
			choice=(int)(choicech)-48;
		} else choice=0;
		fflush(stdin);

		switch(choice) {
			case 1://����
				if(IfCoded) {
					printf("�ļ��ѱ��룬�����ظ��´����ָ�\n���������룡");
				} else {
					fin=fopen("data/SourceDoc.txt","r");
					if(fin==NULL) {
						printf("δ�ҵ�SourceDoc.txt������ȷ�����ļ�������������\n");
						fclose(fin);
						system("pause");
						return 0;
					}
					if(fgetc(fin)==EOF) {
						printf("SourceDoc.txtΪ�գ��뵼����ȷ���ļ�������������\n");
						fclose(fin);
						system("pause");
						return 0;
					}

					OptionForEncode();//���벿�ֺ���

					fclose(fin);

					OptionForDelete();//ɾ��Դ�ļ����ֺ���

					system("pause");
				}
				break;
			case 2://����
				if(IfCoded) {
					if(!IfDecoded) {

						OptionForDecode();//���벿�ֺ���

						if(IfDeleted) {

							OptionForRename();//�����������ļ�����

						}
						system("pause");
					} else {
						printf("�ļ��ѽ��룬�����ظ��´����ָ�\n���������룡");
					}
				} else {
					printf("�ļ���δ���룬���������룡");
				}
				break;
			case 3://����
				if(IfCoded) {
					if(IfDeleted) {
						printf("Դ�ļ���ɾ����������޷��������ݲ��ң����������룡");
					} else {

						kmp2();//���Ҳ��ֺ���

						system("pause");
					}
				} else {
					printf("�ļ���δ���룬���������룡");
				}
				break;
			case 4://�ȶ�
				if(IfCoded) {
					if(!IfDeleted) {
						if(!IfDecoded) {
							printf("�ļ���δ���룬���������룡");
						} else {
							if(CompareFile()==-1) {
								printf("�������ļ���Target.txt����Դ�ļ���SourceDoc.txt������һ�£�\n");
							} else {
								printf("�������ļ���Target.txt����Դ�ļ���SourceDoc.txt�����ݲ�һ�£�"
								       "\n����λ�ã���%d���ַ���\n",CompareFile());
							}
						}
					} else {
						printf("Դ�ļ���ɾ����������޷��������ݱȶԣ����������룡");
					}
				} else {
					printf("�ļ���δ���룬���������룡");
				}
				break;
			case 5://����
				system("cls");
				break;
			case 6:
				if(IfEwstated) {
					printf("�Ѿ����ͳ�ƣ�");
					if(!OptionForEwstat()) {
						break;
					}
				}
				if(EStatistics()) {
					printf("δ�ܳɹ�����SourceDoc.txt������ԭ��%s\n",strerror(errno));
				} else {
					IfEwstated=1;
				}
				system("pause");
				break;
			case 7:
				Debug=!Debug;
				if(Debug) {
					printf("����ģʽ�ѿ�����");
				} else {
					printf("����ģʽ�ѹرգ�");
				}
				break;
			case 8://�˳�
				quit=1;
				break;
			default:
				printf("�������ѡ���������������룡");
				break;
		}
	}
	printf("���˳��˵�ҳ����������˳�����\n");
	system("pause");

	return 0;
}
