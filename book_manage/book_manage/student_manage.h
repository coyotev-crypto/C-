
struct student_info* init_student_info();
/**
 * ����ѧ������
 * У���Ƿ���ڸ�ѧ��
 * ������¼��
 */
void input_student(struct student_info *head,char *file_path,char *config_path);

/**
 * ����ѧ����Ϣ
 * @param head ����ָ��ͷ
 * @param no ����ͼ���id,�����ļ����Ҳ���ȡ���ڴ���
 * @return int 0�ɹ�,1ʧ��
 */
int find_student(struct student_info* head,char *no);

/**
* ���ļ��в����Ƿ���ڵ�ǰѧ��
* @param no ͼ��id
*/
int find_file_student(char *file_path,char *no);


int get_student_list_size(struct student_info *head);

/**
 * ��ѧ����Ϣд�뵽�ļ���
 * ��ɴ�����ʱ��д���ļ�
 * @param head ͷ�ڵ�
 * @param file_path �ļ�λ��
 */
void write_student(struct student_info *head,char *file_path);

/**
* ��յ�ǰ�����ͷ��ڴ�
*/
void clear_student_list(struct student_info *head);