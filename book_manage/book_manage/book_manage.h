/**
 * 创建图书链表
 * 校验是否存在该图书
 * 不存在录入
 */
void input_book(struct book *head,char *file_path,char *config_path);

/**
 * 查找图书信息
 * @param head 链表指针头
 * @param no 查找图书的id,进行文件查找不读取到内存中
 * @return int 0成功,1失败
 */
int find_book(struct book* head,char *no);

int get_book_list_size(struct book *head);

/**
 * 将图书信息写入到文件中
 * 完成创建的时候写入文件
 * @param head 头节点
 * @param file_path 文件位置
 */
void write_book(struct book *head,char *file_path);

/**
* 清空当前链表释放内存
*/
void clear_book_list(struct book *head);

/*
* 修改图书信息
* @param file_path 存储文件路径
* @param config_path 配置文件存储路径
* @param book 修改信息
*/
void change_book(char *file_path,char *config_path,struct book *change_book);
/**
* 写入配置信息
* @param type 类型
* @param size 大小
* @param config_path 存储路径
*/
void write_manage_info(int type,int size,char *config_path);

void last_manage_info(struct book_manage* last_book_manage,char *config_path);

/*
* 1、输入学生学号
* 2、校验信息是否存在
* 3、输入书编号
* 4、校验编号是否存在
* 5、校验当前是否还有书籍可借阅
* 6、书籍信息修改重新写入
* 7、添加一条借阅记录
*/
void borrow_books(char *file_path,char *config_path);

void return_the_book(char *file_path,char *config_path);

void write_borrow_books_count(char *file_path,char *config_path,struct borrowing_records *br);

void change_borrow_books(char *file_path,char *config_path,struct borrowing_records *br);