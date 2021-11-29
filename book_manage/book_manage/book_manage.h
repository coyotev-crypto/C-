/**
 * ����ͼ������
 * У���Ƿ���ڸ�ͼ��
 * ������¼��
 */
void input_book(struct book *head,char *file_path,char *config_path);

/**
 * ����ͼ����Ϣ
 * @param head ����ָ��ͷ
 * @param no ����ͼ���id,�����ļ����Ҳ���ȡ���ڴ���
 * @return int 0�ɹ�,1ʧ��
 */
int find_book(struct book* head,char *no);

int get_book_list_size(struct book *head);

/**
 * ��ͼ����Ϣд�뵽�ļ���
 * ��ɴ�����ʱ��д���ļ�
 * @param head ͷ�ڵ�
 * @param file_path �ļ�λ��
 */
void write_book(struct book *head,char *file_path);

/**
* ��յ�ǰ�����ͷ��ڴ�
*/
void clear_book_list(struct book *head);

/*
* �޸�ͼ����Ϣ
* @param file_path �洢�ļ�·��
* @param config_path �����ļ��洢·��
* @param book �޸���Ϣ
*/
void change_book(char *file_path,char *config_path,struct book *change_book);
/**
* д��������Ϣ
* @param type ����
* @param size ��С
* @param config_path �洢·��
*/
void write_manage_info(int type,int size,char *config_path);

void last_manage_info(struct book_manage* last_book_manage,char *config_path);

/*
* 1������ѧ��ѧ��
* 2��У����Ϣ�Ƿ����
* 3����������
* 4��У�����Ƿ����
* 5��У�鵱ǰ�Ƿ����鼮�ɽ���
* 6���鼮��Ϣ�޸�����д��
* 7�����һ�����ļ�¼
*/
void borrow_books(char *file_path,char *config_path);

void return_the_book(char *file_path,char *config_path);

void write_borrow_books_count(char *file_path,char *config_path,struct borrowing_records *br);

void change_borrow_books(char *file_path,char *config_path,struct borrowing_records *br);