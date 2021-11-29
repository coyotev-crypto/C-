#include "book_manage.h"
#include "common.h"


/**
创建图书信息
*/
void input_book(struct book *head,char *file_path,char *config_path){
	struct book *new_book;
	struct book fb;
	new_book = (struct book*)malloc(sizeof(struct book));
	printf("请输入图书编号：");
	scanf("%s",new_book->no);
	//已经存在
	if(find_book(head,new_book->no) == 0 || find_book_file(file_path,config_path,new_book->no,&fb) == 0){
		free(new_book);
		printf("图书已经录入！\n");
		return;
	}
	printf("请输入书名：");
	scanf("%s",new_book->book_name);
	printf("请输入作者：");
	scanf("%s",new_book->author);
	printf("请输入库存：");
	scanf("%d",&new_book->reserve);
	new_book->next = head->next;
	head->next = new_book;
}


/**
 * 查找图书信息
 * @param no 查找图书的id,进行文件查找不读取到内存中
 * @return int 1成功,0失败
 */
int find_book(struct book* head,char *no){
	//1、先从链表中读取信息
	struct book* p;
	p = head->next;
	while(p!=NULL){
		if(strcmp(p->no,no) == 0){
			return 0;
		}
		p = p->next;
	}
	return 1;
}

/**
 * 将图书信息写入到文件中
 * 完成创建的时候写入文件
 */
void write_book(struct book *head,char *file_path){
	struct book *p;
	FILE *fp;
	p = head->next;
	fp = fopen(file_path,"ab+");
	if(!fp){
		printf("文件打开失败！\n");
		return;
	}
	while(p != NULL){
		fwrite(p,sizeof(struct book),1,fp);
		p = p->next;
	}
	fclose(fp);
}

/**
* 清空当前链表释放内存
*/
void clear_book_list(struct book *head){
	struct book *p;
	struct book *del;
	p = head->next;
	while(p!=NULL){
		del = p;
		p = del->next;
		free(del);
	}
	head->next = NULL;
}

int get_book_list_size(struct book *head){
	struct book *p;
	int lenght = 0;
	p = head->next;
	if(p == NULL){
		return 0;
	}
	while(p != NULL){
		lenght++;
		p = p->next;
	}
	return lenght;
}

/*
* 写入配置文件
*/
void write_manage_info(int type,int size,char *config_path){
	struct book_manage *node;
	struct book_manage *last_book_manage;
	long book_manage_sizeof;
	FILE *fp;
	book_manage_sizeof = sizeof(struct book_manage);
	node = (struct book_manage*)malloc(book_manage_sizeof);
	last_book_manage = (struct book_manage*)malloc(sizeof(struct book_manage));
	fp = fopen(config_path,"ab+");
	if(!fp){
		printf("文件打开失败！\n");
		return;
	}
    last_manage_info(last_book_manage,config_path);
	//第一次创建文件
	if(last_book_manage == NULL){
		node -> type = type;
		node->end_position=size;
		fwrite(node,book_manage_sizeof,1,fp);
	}else if(last_book_manage->type == type){ //校验数据类型是否相同
		fclose(fp);
		fp = fopen(config_path,"rb+");
		//修改数据
		last_book_manage->end_position += size;
		//printf("修改数据：%d\t%d\t%d\t%d\n",type,last_book_manage->type,last_book_manage->start_position,last_book_manage->end_position);
		//覆盖原先的结构体数据
		//1、定位到最后一个结构体
		fseek(fp,0,SEEK_END);
		fseek(fp,-book_manage_sizeof,SEEK_CUR);
		//2、修改
		fwrite(last_book_manage,book_manage_sizeof,1,fp);
	}else{
		//不同类型的链表数据
		node -> type = type;
		node->end_position=size;	
		fwrite(node,book_manage_sizeof,1,fp);
	}
	fclose(fp);
}


void last_manage_info(struct book_manage* last_book_manage,char *config_path){
	FILE *fp;
	long offset = 0;
	long book_manage_sizeof;
	book_manage_sizeof = sizeof(struct book_manage);
	fp = fopen(config_path,"rb");
	if(!fp){
		printf("文件打开失败！\n");
		return;
	}
	//定位到文件末尾
	fseek(fp,0,SEEK_END);
	offset = ftell(fp);
	//printf("当前位置：%d",offset);
	if(offset > 0){
		//计算出最后一个文件的指针位置
		fseek(fp,-book_manage_sizeof,SEEK_CUR);
		fread(last_book_manage,book_manage_sizeof,1,fp);
		//printf("图书类型:%d\t开始位置:%d\t结束位置:%d\n",last_book_manage->type,last_book_manage->start_position,last_book_manage->end_position);
	}
	fclose(fp);
}

/*
* 1、输入学生学号
* 2、校验信息是否存在
* 3、输入书编号
* 4、校验编号是否存在
* 5、校验当前是否还有书籍可借阅
* 6、书籍信息修改重新写入
* 7、添加一条借阅记录
*/
void borrow_books(char *file_path,char *config_path){
	struct book find_book;
	struct borrowing_records *br;
	struct student_info su_info;
	br = (struct borrowing_records*) malloc(sizeof(struct borrowing_records));
	printf("请输入学生学号：");
	scanf("%s",br->student_id);
	if(find_student_file(file_path,config_path,br->student_id,&su_info) != 0){
		printf("学生信息不存在\n");
		return;
	}
	printf("请输入借阅书籍编号：");
	scanf("%s",br->no);
	if(find_book_file(file_path,config_path,br->no,&find_book) != 0){
		printf("书籍信息不存在\n");
		return;
	}
	if(find_book.reserve == 0){
		printf("没有图书可借阅，请过段时间再来\n");
		return;
	}
	//写入借阅记录
	write_borrow_books_count(file_path,config_path,br);
	write_manage_info(BORROWING_RECORDS_TYPE,1,config_path);
	//修改图书信息
	find_book.reserve--;
	change_book(file_path,config_path,&find_book);
	printf("借阅成功！\n");
}

void change_book(char *file_path,char *config_path,struct book *change_book){
	//1、查找到当前book文件位置
	FILE *fp;  //存储数据的文件指针
	FILE *cfp; //存储配置文件的文件指针
	int i;
	struct book_manage node;
	struct book book;
	long book_size;
	book_size = sizeof(struct book);
	fp = fopen(file_path,"rb+");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		printf("文件打开失败！\n");
	}
	//读取配置信息
	while((fread(&node,sizeof(struct book_manage),1,cfp)) == 1){
		//书籍信息
		if(node.type == BOOK_TYPE){
			for(i = 0;i <node.end_position;i++){
				fread(&book,book_size,1,fp);
				if(strcmp(book.no,change_book->no) == 0){ //存在书籍信息
					fseek(fp,-book_size,SEEK_CUR);
					fwrite(change_book,book_size,1,fp);
					fclose(fp);
					fclose(cfp);
					return;
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
}

void write_borrow_books_count(char *file_path,char *config_path,struct borrowing_records *br){
	FILE *fp;  //存储数据的文件指针
	FILE *cfp; //存储配置文件的文件指针
	int i;
	int br_size;
	struct book_manage node;
	br_size = sizeof(struct borrowing_records);
	fp = fopen(file_path,"rb+");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		return;
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
				fread(br,br_size,1,fp);
				if(strcmp(br->no,"-1") == 0 || strcmp(br->student_id,"-1") == 0){
					fseek(fp,-br_size,SEEK_CUR);
					fwrite(br,br_size,1,fp);
					fclose(fp);
					fclose(cfp);
					return;
				}
			}
		}
	}
	fwrite(br,br_size,1,fp);
	fclose(fp);
	fclose(cfp);
}
/*
* 归还书籍信息
* 1、查找学生信息
* 2、输入归还图书编号
* 3、查找借阅记录
* 4、借阅记录修改
* 5、图书信息修改
*/
void return_the_book(char *file_path,char *config_path){
	struct book find_book;
	struct borrowing_records *br;
	struct borrowing_records find_br;
	struct student_info su_info;
	br = (struct borrowing_records*) malloc(sizeof(struct borrowing_records));
	printf("请输入学生学号：");
	scanf("%s",br->student_id);
	if(find_student_file(file_path,config_path,br->student_id,&su_info) != 0){
		printf("学生信息不存在\n");
		return;
	}
	printf("请输入归还书籍编号：");
	scanf("%s",br->no);
	if(find_book_file(file_path,config_path,br->no,&find_book) != 0){
		printf("书籍信息不存在\n");
		return;
	}
	//查找借阅记录
	if(find_borrowing_records_file(file_path,config_path,br,&find_br) != 0){
		printf("不存在借阅记录\n");
		return;
	}
	//修改借阅记录
	change_borrow_books(file_path,config_path,&find_br);
	//修改图书信息
	find_book.reserve++;
	change_book(file_path,config_path,&find_book);
	printf("归还成功\n");
}


void change_borrow_books(char *file_path,char *config_path,struct borrowing_records *br){
	//1、查找到当前借阅记录文件位置
	FILE *fp;  //存储数据的文件指针
	FILE *cfp; //存储配置文件的文件指针
	int i;
	struct book_manage node;
	struct borrowing_records borrowing_record;
	long br_size;
	br_size = sizeof(struct borrowing_records);
	fp = fopen(file_path,"rb+");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		printf("文件打开失败！\n");
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
				fread(&borrowing_record,br_size,1,fp);
				if(strcmp(borrowing_record.no,"-1") == 0 || strcmp(borrowing_record.student_id,"-1") == 0){
					continue;
				}
				if(strcmp(br->no,borrowing_record.no) == 0 && strcmp(br->student_id,borrowing_record.student_id) == 0){ //存在借阅信息
					fseek(fp,-br_size,SEEK_CUR);
					//清空文件，后面复用
					strcpy(br->no,"-1");
					strcpy(br->student_id,"-1");
					fwrite(br,br_size,1,fp);
					fclose(fp);
					fclose(cfp);
					return;
				}
			}
		}
	}
	fclose(fp);
	fclose(cfp);
}