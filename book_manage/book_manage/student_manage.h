
struct student_info* init_student_info();
/**
 * 创建学生链表
 * 校验是否存在该学生
 * 不存在录入
 */
void input_student(struct student_info *head,char *file_path,char *config_path);

/**
 * 查找学生信息
 * @param head 链表指针头
 * @param no 查找图书的id,进行文件查找不读取到内存中
 * @return int 0成功,1失败
 */
int find_student(struct student_info* head,char *no);

/**
* 从文件中查找是否存在当前学生
* @param no 图书id
*/
int find_file_student(char *file_path,char *no);


int get_student_list_size(struct student_info *head);

/**
 * 将学生信息写入到文件中
 * 完成创建的时候写入文件
 * @param head 头节点
 * @param file_path 文件位置
 */
void write_student(struct student_info *head,char *file_path);

/**
* 清空当前链表释放内存
*/
void clear_student_list(struct student_info *head);