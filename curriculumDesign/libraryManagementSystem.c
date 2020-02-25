#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <fcntl.h>

#define max 30
#define maxBook 5 //������5����

typedef struct book{
    long call;          //���
    char bookname[max]; //����
    char author[max];   //����
    int now;            //����
    int total;          //����
} book;
typedef struct student{
    long number;            //ѧ��
    char name[max];         //����
    char sex[max];          //�Ա�
    char department[max];   //Ժϵ
    long Borrowed[maxBook]; //���ĵ��鼮
} student;

//�ɱ����
void addBook(){
    book bk;    //ԭ�е��鼮
    book addbk; //�¼�����鼮
    char ch;    //��ȡ�ļ���һ���ַ����ж��ļ��Ƿ�Ϊ��
    FILE *fp;   //Դ�ļ�
    FILE *fq;   //�滻�ļ�
    int isTrue = 0; //�����Ƿ����
    int flag; //�ļ��Ƿ�Ϊ��
    if ((fp = fopen("book.txt", "a+")) == NULL){ 
        printf("���ļ�����\n");
        exit(0);
    }
    ch = fgetc(fp);
    if (ch == EOF)  //����Ϊ�գ����޸�flag
        flag = 0;
    else
        flag = 1; 
    if ((fq = fopen("ChangedBook.txt", "w+")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    printf("************������Ҫд���ͼ����Ϣ********\n");
    printf("�������룺\n        ��ţ����������ߣ�����������\n");
    //�����¼����ͼ��
    scanf("%ld %s %s %d %d", &addbk.call, addbk.bookname, addbk.author, &addbk.now, &addbk.total);
    if (flag != 0){ //���ļ���Ϊ��
        fseek(fp,0L,0);
        while (!feof(fp)){
            fscanf(fp, "%ld %s %s %d %d\n", &bk.call, bk.bookname, bk.author, &bk.now, &bk.total);
            if (addbk.call == bk.call){ //�����Ѵ��ڣ���Ӵ���������
                bk.now += addbk.now;    //��������
                bk.total += addbk.total;    //��������
                isTrue = 1; //ͼ�����
            }
            //ת�Ƶ��滻�ļ�fq��
            fprintf(fq, "%ld %s %s %d %d\n", bk.call, bk.bookname, bk.author, bk.now, bk.total);
        }
        if(isTrue == 0){    //��ͼ�鲻����
            fprintf(fq, "%ld %s %s %d %d\n", addbk.call, addbk.bookname, addbk.author, addbk.now, addbk.total);
        }
    }
    else{   //���ļ�Ϊ��,ֱ�����
        fprintf(fq, "%ld %s %s %d %d\n", addbk.call, addbk.bookname, addbk.author, addbk.now, addbk.total);      
    }
    printf("��ӳɹ�\n");
    if (fclose(fp)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
    if (fclose(fq)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
}

//���ѧ����Ϣ
void addStudent(){
    student stu;    //�¼����ѧ��
    FILE *fp;   //�洢ѧ�����ļ�
    int flag = 0; //��ʼ��Ϊδ����
    if ((fp = fopen("student.txt", "a")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    fseek(fp,0L,0);
    printf("************������Ҫд���ѧ����Ϣ********\n");
    printf("�������룺\n        ѧ�ţ��������Ա�Ժϵ\n");
    //��ȡ�¼����ѧ��
    scanf("%ld %s %s %s", &stu.number, stu.name, stu.sex, stu.department);
    //�洢�¼����ѧ��
    fprintf(fp, "%ld %s %s %s %ld %ld %ld %ld %ld\n", stu.number, stu.name, stu.sex, stu.department, flag, flag, flag, flag, flag);
    printf("��ӳɹ�\n");
    if (fclose(fp)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
}

//����Ų�ѯͼ����Ϣ
void searchBook_call(){
    book bk;    //�Ѵ洢��ͼ��
    long value; //��ѯ��ͼ�����
    FILE *fp;   //ͼ���ļ�
    int flag = 0; //�Ƿ��ҵ��飬�ҵ�Ϊ1��δ�ҵ���Ϊ0
    if ((fp = fopen("book.txt", "r")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    printf("�����ѯ��ͼ����ţ�");
    //�����ѯ��ͼ�����
    scanf("%d", &value);
    while (!feof(fp)){
        //���������Ѵ����ͼ��
        fscanf(fp, "%ld %s %s %d %d", &bk.call, bk.bookname, bk.author, &bk.now, &bk.total);
        //��ѯ����
        if (value == bk.call){   
            //���ͼ����Ϣ
            printf("�����������ţ����������ߣ�����������\n %ld %s %s %d %d\n", bk.call, bk.bookname, bk.author, bk.now, bk.total);
            flag = 1;   //���ҵ�����
            break;
        }
    }
    if (flag == 0){
        printf("δ�ҵ�����\n");
    }
    if (fclose(fp)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
}

//��������ѯͼ����Ϣ
void searchBook_bookname(){
    book bk;    //�Ѵ洢��ͼ��
    char bkname[max];   //Ҫ��ѯ��ͼ������
    FILE *fp;   //�Ѵ洢��ͼ���ļ�
    int flag = 0;   //�Ƿ��ҵ�
    if ((fp = fopen("book.txt", "r")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    printf("������Ҫ��ѯ��ͼ���������");
    //����ͼ������
    scanf("%s", bkname);
    while (!feof(fp)){
        //���������Ѵ洢��ͼ��
        fscanf(fp, "%ld %s %s %d %d", &bk.call, bk.bookname, bk.author, &bk.now, &bk.total);
        //�ҵ���
        if (strcmp(bk.bookname, bkname) == 0){
            //���ͼ����Ϣ
            printf("�����������ţ����������ߣ�����������\n %ld %s %s %d %d\n", bk.call, bk.bookname, bk.author, bk.now, bk.total);
            flag = 1;   //���ҵ�
            break;
        }
    }
    if (flag == 0){
        printf("δ�ҵ�����\n");
    }
    if (fclose(fp)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
}

//�����߲�ѯͼ����Ϣ
void searchBook_author(){
    book bk;    //�Ѵ洢��ͼ��
    char name[max]; //Ҫ���ҵ�����
    int flag = 0;   //�Ƿ��ҵ�
    FILE *fp;   //�Ѵ洢��ͼ���ļ�
    if ((fp = fopen("book.txt", "r")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    printf("������Ҫ��ѯ��ͼ������ߣ�");
    //����ͼ������
    scanf("%s", name);
    while (!feof(fp)){
        //���������Ѵ洢��ͼ��
        fscanf(fp, "%ld %s %s %d %d", &bk.call, bk.bookname, bk.author, &bk.now, &bk.total);
        //�ҵ���
        if (strcmp(bk.author, name) == 0){
            //���ͼ����Ϣ
            printf("�����������ţ����������ߣ�����������\n %ld %s %s %d %d\n", bk.call, bk.bookname, bk.author, bk.now, bk.total);
            flag = 1;   //���ҵ�
            break;
        }
    }
    if (flag == 0){
        printf("δ�ҵ�����\n");
    }
    if (fclose(fp)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
}

//��ѧ���Ľ���֤�ţ�ѧ�ţ���ʾѧ����Ϣ
void showStudent(){
    student stu;    //�Ѵ洢��ѧ��
    long value; //Ҫ���ҵ�ѧ��ѧ��
    int flag = 0;   //�Ƿ��ҵ�ѧ��
    FILE *fp;   //�Ѵ洢��ѧ����Ϣ
    if ((fp = fopen("student.txt", "r")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    printf("����ѧ������֤�ţ�");
    //����ѧ��ѧ��
    scanf("%ld", &value);
    while (!feof(fp)){
        //�����Ѵ洢��ѧ������
        fscanf(fp, "%ld %s %s %s %f %f %f %f %f", &stu.number, stu.name, stu.sex, stu.department, &stu.Borrowed[0], &stu.Borrowed[1], &stu.Borrowed[2], &stu.Borrowed[3], &stu.Borrowed[4]);
        //�ҵ���
        if (value == stu.number){
            int i;
            //���ѧ�ţ�������Ժϵ
            printf("���������ѧ�ţ��������Ա�Ժϵ�������鼮��\n%ld %s %s %s", stu.number, stu.name, stu.sex, stu.department);
            //��������鼮
            for (i = 0; (stu.Borrowed[i] != 0) && (i < 5); i++){
                printf(" %ld\n", stu.Borrowed[i]);
            }
            if (i == 0) //û�н���
                printf("\n");
            flag = 1;   //���ҵ�
            break;
        }
    }
    if (flag == 0){
        printf("δ�ҵ�����\n");
    }
    if (fclose(fp)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
}

//�����鼮
void borrowBook(){
    book bk;    //�Ѵ洢��ͼ��
    student stu;    //�Ѵ洢��ѧ��
    long number;    //Ҫ�����ѧ��ѧ��
    long booknumber;    //Ҫ���ͼ�����
    int flag = 0;   //�Ƿ����Ȿ�飬�Ƿ��д���
    FILE *fp;   //ԭͼ���ļ�
    FILE *fq;   //ԭѧ���ļ�
    FILE *fc;   //�ı����鼮�洢�ļ�
    FILE *fb;   //�ı���ѧ����Ϣ�洢�ļ�
    if ((fp = fopen("book.txt", "r+")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    if ((fq = fopen("student.txt", "r+")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    if((fc = fopen("copyBook.txt","w+")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    if((fb = fopen("copyStudent.txt","w+")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    printf("����Ҫ���ĵ��鼮��ţ�");
    scanf("%ld", &booknumber);
    printf("�������ѧ�ţ�");
    scanf("%ld", &number);
    while (!feof(fp)){
        //��������ͼ��
        fscanf(fp, "%ld %s %s %ld %ld\n", &bk.call, bk.bookname, bk.author, &bk.now, &bk.total);
        //�ҵ���
        if (booknumber == bk.call){
            bk.now--;   //ͼ���������
            flag = 1;   //���ҵ�
        }
        //ת�Ƶ��滻�ļ�fc��
        fprintf(fc,"%ld %s %s %ld %ld\n", bk.call,bk.bookname,bk.author,bk.now,bk.total);
    }
    if(flag == 0){
        printf("û���Ȿ��\n");
        return;
    }
    if (fclose(fp)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
    if (fclose(fc)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
    while (!feof(fq)){
        //��������ѧ��
        fscanf(fq, "%ld %s %s %s %ld %ld %ld %ld %ld\n", &stu.number, stu.name, stu.sex, stu.department, &stu.Borrowed[0], &stu.Borrowed[1], &stu.Borrowed[2], &stu.Borrowed[3], &stu.Borrowed[4]);
        //�ҵ���
        if (number == stu.number){
            flag = 1;   //���ҵ�
            int i = 0;
            while ((i<5) && (stu.Borrowed[i] != 0))
                i++;
            if(i>4){
                printf("���������������ֵ");
                return;
            }
            stu.Borrowed[i] = booknumber;   //�ı�����鼮
        }
        //ת�Ƶ��滻�ļ�fb��
        fprintf(fb,"%ld %s %s %s %ld %ld %ld %ld %ld\n", stu.number, stu.name, stu.sex, stu.department, stu.Borrowed[0], stu.Borrowed[1], stu.Borrowed[2], stu.Borrowed[3], stu.Borrowed[4]);
    }
    if(flag == 0){
        printf("û�������\n");
        return;
    }
    if (fclose(fq)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
    if (fclose(fb)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
    printf("����ɹ�\n");
}

//�黹�鼮
void returnBook(){
    book bk;    //�Ѵ洢��ͼ��
    student stu;    //�Ѵ洢��ѧ��
    long number;    //Ҫ�����ѧ��ѧ��
    long booknumber;    //Ҫ�����鼮���
    int flag = 0;   //�Ƿ��д���,�Ƿ���˴��飬�Ƿ��д���
    FILE *fp;   //ԭͼ���ļ�
    FILE *fq;   //ԭѧ���ļ�
    FILE *fc;   //�滻��ͼ���ļ�
    FILE *fb;   //�滻��ѧ���ļ�
    if ((fp = fopen("book.txt", "r+")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    if ((fq = fopen("student.txt", "r+")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    if ((fc = fopen("copyBook.txt", "w+")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    if ((fb = fopen("copyStudent.txt", "w+")) == NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    printf("����Ҫ�黹���鼮��ţ�");
    scanf("%ld", &booknumber);
    printf("�������ѧ�ţ�");
    scanf("%ld", &number);
    while (!feof(fp)){
        //��������ͼ��
        fscanf(fp, "%ld %s %s %ld %ld\n", &bk.call, bk.bookname, bk.author, &bk.now, &bk.total);
        //�ҵ���
        if (booknumber == bk.call){
            bk.now++;   //�鼮��������
            flag = 1 ;  //���ҵ�
        }
        //ת�Ƶ��滻�ļ�fc��
        fprintf(fc, "%ld %s %s %ld %ld\n", bk.call, bk.bookname, bk.author, bk.now, bk.total);
    }
    if(flag == 0){
        printf("û���Ȿ��\n");
        return;
    }
    if (fclose(fp)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
    if (fclose(fc)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
    while (!feof(fq)){
        //��������ѧ��
        fscanf(fq, "%ld %s %s %s %ld %ld %ld %ld %ld\n", &stu.number, stu.name, stu.sex, stu.department, &stu.Borrowed[0], &stu.Borrowed[1], &stu.Borrowed[2], &stu.Borrowed[3], &stu.Borrowed[4]);
        //�ҵ���
        if (number == stu.number){
            flag = 1;   //���ҵ�
            int i = 0;
            while ((i<5) && (stu.Borrowed[i] != booknumber))   //���������鲻��ͬ
                i++;
            if(i>4){
                printf("��û�н��Ȿ��\n");
                return;
            }
            stu.Borrowed[i] = 0;    //�����ѽ��鼮
        }
        //ת�Ƶ��滻�ļ�fb��
        fprintf(fb, "%ld %s %s %s %ld %ld %ld %ld %ld\n", stu.number, stu.name, stu.sex, stu.department, stu.Borrowed[0], stu.Borrowed[1], stu.Borrowed[2], stu.Borrowed[3], stu.Borrowed[4]);
    }
    if(flag == 0){
        printf("��û�н��Ȿ��\n");
        return;
    }
    if (fclose(fq)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
    if (fclose(fb)){
        printf("�ر��ļ�ʧ��\n");
        exit(0);
    }
    printf("����ɹ�\n");
}

int main(){
    int code1, code2;   //code1Ϊ�ܲ�����code2Ϊ��ѯ����
    printf("    ***************************************\n");
    printf("                ͼ�����ϵͳ              *\n");
    printf("                                          *\n");
    printf("    *                                     *\n");
    printf("    *                                     *\n");
    printf("    *                                     *\n");
    printf("        *        ��Ȩ����    ����������������   *\n");
    printf("        *                    ����������������   *\n");
    printf("        *                    ����������������   *\n");
    printf("        *                    ���������������� *\n");
    printf("        *                    ������������������ *\n");
    printf("        ***********************************\n");
    printf("����1������鼮 ����2�����ѧ����Ϣ ����3:��ѯ�鼮\n");
    printf("����4����ʾѧ����Ϣ ����5�������鼮 ����6���黹�鼮\n");
    printf("����7���˳�\n");
    scanf("%d", &code1);
    while (code1 != 7){
        switch (code1){
        case 1:{
            int flag;   //�Ƿ����������ͬ��
            do{
                addBook();
                remove("book.txt");
                rename("ChangedBook.txt","book.txt");
                printf("����Ҫ��������鼮�����ǣ������0�������ǣ�����0\n");
                scanf("%d",&flag);
            }while(flag!=0);
            break;
        }
        case 2:{
            int flag;
            do{
                addStudent();
                printf("����Ҫ�������ѧ����Ϣ�����ǣ������0�������ǣ�����0\n");
                scanf("%d",&flag);
            }while(flag!=0);
            break;
        }
        case 3:{
            int flag;
            do{
                printf("�������ѯ��ʽ��\n");
                printf("����1������Ų�ѯ������2����������ѯ������3�������߲�ѯ\n");
                scanf("%d", &code2);
                if (code2 == 1){
                    searchBook_call();
                }
                else if (code2 == 2){
                    searchBook_bookname();
                }
                else
                    searchBook_author();
                printf("����Ҫ������ѯ�鼮�����ǣ������0�������ǣ�����0\n");
                scanf("%d", &flag);
            } while (flag != 0);
            break;
        }
        case 4:{
            int flag;
            do{
                showStudent();
                printf("����Ҫ������ʾѧ����Ϣ�����ǣ������0�������ǣ�����0\n");
                scanf("%d", &flag);
            } while (flag != 0);
            break;
        }
        case 5:{
            int flag;
            do{
                borrowBook();
                remove("book.txt");
                rename("copyBook.txt","book.txt");
                remove("student.txt");
                rename("copyStudent.txt","student.txt");
                printf("����Ҫ�������������ǣ������0�������ǣ�����0\n");
                scanf("%d", &flag);
            } while (flag != 0);
            break;
        }
        case 6:{
            int flag;
            do{
                returnBook();
                remove("book.txt");
                rename("copyBook.txt","book.txt");
                remove("student.txt");
                rename("copyStudent.txt","student.txt");
                printf("����Ҫ�������������ǣ������0�������ǣ�����0\n");
                scanf("%d",&flag);
            } while (flag != 0);
            break;
        }
        default:
            break;
        }
        printf("��Ҫ������������ѡ��\n");
        printf("����1������鼮 ����2�����ѧ����Ϣ ����3:��ѯ�鼮\n");
        printf("����4����ʾѧ����Ϣ ����5�������鼮 ����6���黹�鼮\n");
        printf("����7���˳�\n");
        scanf("%d", &code1);
    }
    return 0;
}