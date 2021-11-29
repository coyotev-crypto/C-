#include "common.h"

void menu(){
	printf("===============================\n");
    printf("欢迎使用图书管理系统\n");
    printf("1、录入书籍信息\n");
	printf("2、录入学生信息\n");
	printf("3、查看录入书籍信息\n");
	printf("4、查看学生信息\n");
	printf("5、借阅书籍\n");
    printf("6、归还书籍\n");
	printf("7、借阅记录\n");
	printf("0、退出\n");
	printf("===============================\n");
}

/*
* 打印数据信息
* @param file_path 查找文件的路径
* @param config_path 配置文件路径
* @param operate_type 操作类型 0 书籍,1学生，2借阅信息
*/
int printf_file(char *file_path,char *config_path,int operate_type){
	FILE *fp;  //存储数据的文件指针
	FILE *cfp; //存储配置文件的文件指针
	int i;
	struct book_manage node;
	struct book book;
	struct student_info su_info;
	struct borrowing_records br;
	int is_first = 0;
	fp = fopen(file_path,"rb");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		printf("文件打开失败！\n");
		return 2;
	}
	printf("\n");
	printf("==============================================================\n");
	//读取配置信息
	while((fread(&node,sizeof(struct book_manage),1,cfp)) == 1){
		//书籍信息
		if(node.type == BOOK_TYPE){
			if(node.type == operate_type){
				for(i = 0;i <node.end_position;i++){
					fread(&book,sizeof(struct book),1,fp);
						  /* data */
						 //   char no[5]; //编号
						 //char book_name[128]; //书名
						 //   char author[20]; //作者
						 //   int reserve; //库存
						 //   struct book *next;
						printf("编号：%s\t书名：%s\t作者：%s\t剩余图书：%d\n",book.no,book.book_name,book.author,book.reserve);
				}
			}else{
				for(i = 0;i<node.end_position;i++)
					fseek(fp,sizeof(struct book),SEEK_CUR);
			}
			continue;
		}else if(node.type == STUDENT_TYPE){
			if(node.type == operate_type){
				for(i = 0;i <node.end_position;i++){
					fread(&su_info,sizeof(struct student_info),1,fp);
						//char id[11]; //学号
						//char name[20]; //姓名
						//char class_name[128]; //班级 
						printf("学号：%s\t姓名：%s\t班级：%s\n",su_info.id,su_info.name,su_info.class_name);
				}
			}else{
			//文件指针移动
				for(i = 0;i<node.end_position;i++)
					fseek(fp,sizeof(struct student_info),SEEK_CUR);
			}
			continue;
		}else if(node.type == BORROWING_RECORDS_TYPE){
			if(node.type == operate_type){
				for(i = 0;i <node.end_position;i++){
					fread(&br,sizeof(struct borrowing_records),1,fp);
					if(strcmp(br.no,"-1") == 0 || strcmp(br.student_id,"-1")==0){
						continue;
					}
					find_book_file(file_path,config_path,br.no,&book);
					find_student_file(file_path,config_path,br.student_id,&su_info);
					if(is_first == 0){
						printf("学号：%s\t姓名：%s\t班级：%s\n",su_info.id,su_info.name,su_info.class_name);
						printf("借阅书籍：\n");
						is_first=1;
					}
					printf("编号：%s\t书名：%s\t作者：%s\n",book.no,book.book_name,book.author);
				}
			}else{
				//文件指针移动
				for(i = 0;i<node.end_position;i++)
					fseek(fp,sizeof(struct borrowing_records),SEEK_CUR);
			}
		}
	}
	printf("==============================================================\n");
	printf("\n");
	fclose(fp);
	fclose(cfp);
	return 1;
}


int find_student_file(char *file_path,char *config_path,char *des,struct student_info* su_info){
	FILE *fp;  //存储数据的文件指针
	FILE *cfp; //存储配置文件的文件指针
	int i;
	struct book_manage node;
	fp = fopen(file_path,"rb");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		return 1;
	}
	//读取配置信息
	while((fread(&node,sizeof(struct book_manage),1,cfp)) == 1){
		//书籍信息
		if(node.type == BOOK_TYPE){
			for(i = 0;i<node.end_position;i++)
				fseek(fp,sizeof(struct book),SEEK_CUR);
			continue;
		}else if(node.type == STUDENT_TYPE){
			for(i = 0;i <node.end_position;i++){
					fread(su_info,sizeof(struct student_info),1,fp);
					if(strcmp(su_info->id,des) == 0){ //存在学生信息
						fclose(fp);
						fclose(cfp);
						return 0;
					}
				}
			continue;
		}else if(node.type == BORROWING_RECORDS_TYPE){
			for(i = 0;i<node.end_position;i++)
					fseek(fp,sizeof(struct borrowing_records),SEEK_CUR);
		}
	}
	fclose(fp);
	fclose(cfp);
	return 1;
}


int find_book_file(char *file_path,char *config_path,char *des,struct book* book){
	FILE *fp;  //存储数据的文件指针
	FILE *cfp; //存储配置文件的文件指针
	int i;
	struct book_manage node;
	fp = fopen(file_path,"rb");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		return 1;
	}
	//读取配置信息
	while((fread(&node,sizeof(struct book_manage),1,cfp)) == 1){
		//书籍信息
		if(node.type == BOOK_TYPE){
			for(i = 0;i <node.end_position;i++){
				fread(book,sizeof(struct book),1,fp);
				if(strcmp(book->no,des) == 0){ //存在书籍信息
					fclose(fp);
					fclose(cfp);
					return 0;
				}
			}
			continue;
		}else if(node.type == STUDENT_TYPE){
			//文件指针移动
			for(i = 0;i<node.end_position;i++)
				fseek(fp,sizeof(struct student_info),SEEK_CUR);
			continue;
		}else if(node.type == BORROWING_RECORDS_TYPE){
			for(i = 0;i<node.end_position;i++)
				fseek(fp,sizeof(struct borrowing_records),SEEK_CUR);
		}
	}
	fclose(fp);
	fclose(cfp);
	return 1;
}

int find_borrowing_records_file(char *file_path,char *config_path,struct borrowing_records *input_br,struct borrowing_records* br){
	FILE *fp;  //存储数据的文件指针
	FILE *cfp; //存储配置文件的文件指针
	int i;
	struct book_manage node;
	fp = fopen(file_path,"rb");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		return 1;
	}
	//读取配置信息
	while((fread(&node,sizeof(struct book_manage),1,cfp)) == 1){
		//书籍信息
		if(node.type == BOOK_TYPE){
			for(i = 0;i<node.end_position;i++)
				fseek(fp,sizeof(struct book),SEEK_CUR);
			continue;
		}else if(node.type == STUDENT_TYPE){
			//文件指针移动
			for(i = 0;i<node.end_position;i++)
				fseek(fp,sizeof(struct student_info),SEEK_CUR);
			continue;
		}else if(node.type == BORROWING_RECORDS_TYPE){
			for(i = 0;i <node.end_position;i++){
				fread(br,sizeof(struct borrowing_records),1,fp);
				if(strcmp(br->no,"-1") == 0 || strcmp(br->student_id,"-1") == 0){
					continue;
				}
				if(strcmp(br->no,input_br->no) == 0 && strcmp(br->student_id,input_br->student_id) == 0){ //存在借阅信息
					fclose(fp);
					fclose(cfp);
					return 0;
				}
			}
		}
	}
	fclose(fp);
	fclose(cfp);
	return 1;
}

void printf_book(char *file_path,char *config_path){
	 printf_file(file_path,config_path,BOOK_TYPE);
}


void printf_student(char *file_path,char *config_path){
	printf_file(file_path,config_path,STUDENT_TYPE);
}


void printf_borrowing_records(char *file_path,char *config_path){
	printf_file(file_path,config_path,BORROWING_RECORDS_TYPE);
}

void printf_config_info(char *config_path){
	struct book_manage book_manage;
	FILE *fp;
	fp = fopen(config_path,"ab+");
	if(!fp){
		printf("文件打开失败！\n");
		return;
	}
	while((fread(&book_manage,sizeof(struct book_manage),1,fp))==1){
		printf("类型:%d\t结束位置:%d\n",book_manage.type,book_manage.end_position);
	}
	fclose(fp);
}