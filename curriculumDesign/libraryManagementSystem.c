#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <fcntl.h>

#define max 30
#define maxBook 5 //最多借阅5本书

typedef struct book{
    long call;          //书号
    char bookname[max]; //书名
    char author[max];   //作者
    int now;            //存量
    int total;          //总量
} book;
typedef struct student{
    long number;            //学号
    char name[max];         //姓名
    char sex[max];          //性别
    char department[max];   //院系
    long Borrowed[maxBook]; //借阅的书籍
} student;

//采编入库
void addBook(){
    book bk;    //原有的书籍
    book addbk; //新加入的书籍
    char ch;    //读取文件第一个字符，判断文件是否为空
    FILE *fp;   //源文件
    FILE *fq;   //替换文件
    int isTrue = 0; //此书是否存在
    int flag; //文件是否为空
    if ((fp = fopen("book.txt", "a+")) == NULL){ 
        printf("打开文件错误\n");
        exit(0);
    }
    ch = fgetc(fp);
    if (ch == EOF)  //若不为空，则修改flag
        flag = 0;
    else
        flag = 1; 
    if ((fq = fopen("ChangedBook.txt", "w+")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    printf("************输入你要写入的图书信息********\n");
    printf("依次输入：\n        书号，书名，作者，存量，总量\n");
    //输入新加入的图书
    scanf("%ld %s %s %d %d", &addbk.call, addbk.bookname, addbk.author, &addbk.now, &addbk.total);
    if (flag != 0){ //若文件不为空
        fseek(fp,0L,0);
        while (!feof(fp)){
            fscanf(fp, "%ld %s %s %d %d\n", &bk.call, bk.bookname, bk.author, &bk.now, &bk.total);
            if (addbk.call == bk.call){ //若书已存在，则加存量与总量
                bk.now += addbk.now;    //存量增加
                bk.total += addbk.total;    //总量增加
                isTrue = 1; //图书存在
            }
            //转移到替换文件fq中
            fprintf(fq, "%ld %s %s %d %d\n", bk.call, bk.bookname, bk.author, bk.now, bk.total);
        }
        if(isTrue == 0){    //若图书不存在
            fprintf(fq, "%ld %s %s %d %d\n", addbk.call, addbk.bookname, addbk.author, addbk.now, addbk.total);
        }
    }
    else{   //若文件为空,直接添加
        fprintf(fq, "%ld %s %s %d %d\n", addbk.call, addbk.bookname, addbk.author, addbk.now, addbk.total);      
    }
    printf("添加成功\n");
    if (fclose(fp)){
        printf("关闭文件失败\n");
        exit(0);
    }
    if (fclose(fq)){
        printf("关闭文件失败\n");
        exit(0);
    }
}

//添加学生信息
void addStudent(){
    student stu;    //新加入的学生
    FILE *fp;   //存储学生的文件
    int flag = 0; //初始化为未借书
    if ((fp = fopen("student.txt", "a")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    fseek(fp,0L,0);
    printf("************输入你要写入的学生信息********\n");
    printf("依次输入：\n        学号，姓名，性别，院系\n");
    //读取新加入的学生
    scanf("%ld %s %s %s", &stu.number, stu.name, stu.sex, stu.department);
    //存储新加入的学生
    fprintf(fp, "%ld %s %s %s %ld %ld %ld %ld %ld\n", stu.number, stu.name, stu.sex, stu.department, flag, flag, flag, flag, flag);
    printf("添加成功\n");
    if (fclose(fp)){
        printf("关闭文件失败\n");
        exit(0);
    }
}

//按书号查询图书信息
void searchBook_call(){
    book bk;    //已存储的图书
    long value; //查询的图书书号
    FILE *fp;   //图书文件
    int flag = 0; //是否找到书，找到为1，未找到则为0
    if ((fp = fopen("book.txt", "r")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    printf("输入查询的图书书号：");
    //输入查询的图书书号
    scanf("%d", &value);
    while (!feof(fp)){
        //遍历输入已储存的图书
        fscanf(fp, "%ld %s %s %d %d", &bk.call, bk.bookname, bk.author, &bk.now, &bk.total);
        //查询到了
        if (value == bk.call){   
            //输出图书信息
            printf("依次输出：书号，书名，作者，存量，总量\n %ld %s %s %d %d\n", bk.call, bk.bookname, bk.author, bk.now, bk.total);
            flag = 1;   //已找到此书
            break;
        }
    }
    if (flag == 0){
        printf("未找到此书\n");
    }
    if (fclose(fp)){
        printf("关闭文件失败\n");
        exit(0);
    }
}

//按书名查询图书信息
void searchBook_bookname(){
    book bk;    //已存储的图书
    char bkname[max];   //要查询的图书书名
    FILE *fp;   //已存储的图书文件
    int flag = 0;   //是否找到
    if ((fp = fopen("book.txt", "r")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    printf("输入你要查询的图书的书名：");
    //输入图书书名
    scanf("%s", bkname);
    while (!feof(fp)){
        //遍历查找已存储的图书
        fscanf(fp, "%ld %s %s %d %d", &bk.call, bk.bookname, bk.author, &bk.now, &bk.total);
        //找到了
        if (strcmp(bk.bookname, bkname) == 0){
            //输出图书信息
            printf("依次输出：书号，书名，作者，存量，总量\n %ld %s %s %d %d\n", bk.call, bk.bookname, bk.author, bk.now, bk.total);
            flag = 1;   //已找到
            break;
        }
    }
    if (flag == 0){
        printf("未找到此书\n");
    }
    if (fclose(fp)){
        printf("关闭文件失败\n");
        exit(0);
    }
}

//按作者查询图书信息
void searchBook_author(){
    book bk;    //已存储的图书
    char name[max]; //要查找的作者
    int flag = 0;   //是否找到
    FILE *fp;   //已存储的图书文件
    if ((fp = fopen("book.txt", "r")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    printf("输入你要查询的图书的作者：");
    //输入图书作者
    scanf("%s", name);
    while (!feof(fp)){
        //遍历查找已存储的图书
        fscanf(fp, "%ld %s %s %d %d", &bk.call, bk.bookname, bk.author, &bk.now, &bk.total);
        //找到了
        if (strcmp(bk.author, name) == 0){
            //输出图书信息
            printf("依次输出：书号，书名，作者，存量，总量\n %ld %s %s %d %d\n", bk.call, bk.bookname, bk.author, bk.now, bk.total);
            flag = 1;   //已找到
            break;
        }
    }
    if (flag == 0){
        printf("未找到此书\n");
    }
    if (fclose(fp)){
        printf("关闭文件失败\n");
        exit(0);
    }
}

//用学生的借书证号（学号）显示学生信息
void showStudent(){
    student stu;    //已存储的学生
    long value; //要查找的学生学号
    int flag = 0;   //是否找到学生
    FILE *fp;   //已存储的学生信息
    if ((fp = fopen("student.txt", "r")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    printf("输入学生借书证号：");
    //输入学生学号
    scanf("%ld", &value);
    while (!feof(fp)){
        //遍历已存储的学生查找
        fscanf(fp, "%ld %s %s %s %f %f %f %f %f", &stu.number, stu.name, stu.sex, stu.department, &stu.Borrowed[0], &stu.Borrowed[1], &stu.Borrowed[2], &stu.Borrowed[3], &stu.Borrowed[4]);
        //找到了
        if (value == stu.number){
            int i;
            //输出学号，姓名，院系
            printf("依次输出：学号，姓名，性别，院系，借阅书籍：\n%ld %s %s %s", stu.number, stu.name, stu.sex, stu.department);
            //输出借阅书籍
            for (i = 0; (stu.Borrowed[i] != 0) && (i < 5); i++){
                printf(" %ld\n", stu.Borrowed[i]);
            }
            if (i == 0) //没有借书
                printf("\n");
            flag = 1;   //已找到
            break;
        }
    }
    if (flag == 0){
        printf("未找到此人\n");
    }
    if (fclose(fp)){
        printf("关闭文件失败\n");
        exit(0);
    }
}

//借阅书籍
void borrowBook(){
    book bk;    //已存储的图书
    student stu;    //已存储的学生
    long number;    //要借书的学生学号
    long booknumber;    //要借的图书书号
    int flag = 0;   //是否有这本书，是否有此人
    FILE *fp;   //原图书文件
    FILE *fq;   //原学生文件
    FILE *fc;   //改变后的书籍存储文件
    FILE *fb;   //改变后的学生信息存储文件
    if ((fp = fopen("book.txt", "r+")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    if ((fq = fopen("student.txt", "r+")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    if((fc = fopen("copyBook.txt","w+")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    if((fb = fopen("copyStudent.txt","w+")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    printf("输入要借阅的书籍书号：");
    scanf("%ld", &booknumber);
    printf("输入你的学号：");
    scanf("%ld", &number);
    while (!feof(fp)){
        //遍历查找图书
        fscanf(fp, "%ld %s %s %ld %ld\n", &bk.call, bk.bookname, bk.author, &bk.now, &bk.total);
        //找到了
        if (booknumber == bk.call){
            bk.now--;   //图书存量减少
            flag = 1;   //已找到
        }
        //转移到替换文件fc中
        fprintf(fc,"%ld %s %s %ld %ld\n", bk.call,bk.bookname,bk.author,bk.now,bk.total);
    }
    if(flag == 0){
        printf("没有这本书\n");
        return;
    }
    if (fclose(fp)){
        printf("关闭文件失败\n");
        exit(0);
    }
    if (fclose(fc)){
        printf("关闭文件失败\n");
        exit(0);
    }
    while (!feof(fq)){
        //遍历查找学生
        fscanf(fq, "%ld %s %s %s %ld %ld %ld %ld %ld\n", &stu.number, stu.name, stu.sex, stu.department, &stu.Borrowed[0], &stu.Borrowed[1], &stu.Borrowed[2], &stu.Borrowed[3], &stu.Borrowed[4]);
        //找到了
        if (number == stu.number){
            flag = 1;   //已找到
            int i = 0;
            while ((i<5) && (stu.Borrowed[i] != 0))
                i++;
            if(i>4){
                printf("借书数量超过最大值");
                return;
            }
            stu.Borrowed[i] = booknumber;   //改变借阅书籍
        }
        //转移到替换文件fb中
        fprintf(fb,"%ld %s %s %s %ld %ld %ld %ld %ld\n", stu.number, stu.name, stu.sex, stu.department, stu.Borrowed[0], stu.Borrowed[1], stu.Borrowed[2], stu.Borrowed[3], stu.Borrowed[4]);
    }
    if(flag == 0){
        printf("没有这个人\n");
        return;
    }
    if (fclose(fq)){
        printf("关闭文件失败\n");
        exit(0);
    }
    if (fclose(fb)){
        printf("关闭文件失败\n");
        exit(0);
    }
    printf("借书成功\n");
}

//归还书籍
void returnBook(){
    book bk;    //已存储的图书
    student stu;    //已存储的学生
    long number;    //要还书的学生学号
    long booknumber;    //要还的书籍书号
    int flag = 0;   //是否有此书,是否借了此书，是否有此人
    FILE *fp;   //原图书文件
    FILE *fq;   //原学生文件
    FILE *fc;   //替换的图书文件
    FILE *fb;   //替换的学生文件
    if ((fp = fopen("book.txt", "r+")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    if ((fq = fopen("student.txt", "r+")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    if ((fc = fopen("copyBook.txt", "w+")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    if ((fb = fopen("copyStudent.txt", "w+")) == NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    printf("输入要归还的书籍书号：");
    scanf("%ld", &booknumber);
    printf("输入你的学号：");
    scanf("%ld", &number);
    while (!feof(fp)){
        //遍历查找图书
        fscanf(fp, "%ld %s %s %ld %ld\n", &bk.call, bk.bookname, bk.author, &bk.now, &bk.total);
        //找到了
        if (booknumber == bk.call){
            bk.now++;   //书籍存量增加
            flag = 1 ;  //已找到
        }
        //转移到替换文件fc中
        fprintf(fc, "%ld %s %s %ld %ld\n", bk.call, bk.bookname, bk.author, bk.now, bk.total);
    }
    if(flag == 0){
        printf("没有这本书\n");
        return;
    }
    if (fclose(fp)){
        printf("关闭文件失败\n");
        exit(0);
    }
    if (fclose(fc)){
        printf("关闭文件失败\n");
        exit(0);
    }
    while (!feof(fq)){
        //遍历查找学生
        fscanf(fq, "%ld %s %s %s %ld %ld %ld %ld %ld\n", &stu.number, stu.name, stu.sex, stu.department, &stu.Borrowed[0], &stu.Borrowed[1], &stu.Borrowed[2], &stu.Borrowed[3], &stu.Borrowed[4]);
        //找到了
        if (number == stu.number){
            flag = 1;   //已找到
            int i = 0;
            while ((i<5) && (stu.Borrowed[i] != booknumber))   //借的书与此书不相同
                i++;
            if(i>4){
                printf("你没有借这本书\n");
                return;
            }
            stu.Borrowed[i] = 0;    //重置已借书籍
        }
        //转移到替换文件fb中
        fprintf(fb, "%ld %s %s %s %ld %ld %ld %ld %ld\n", stu.number, stu.name, stu.sex, stu.department, stu.Borrowed[0], stu.Borrowed[1], stu.Borrowed[2], stu.Borrowed[3], stu.Borrowed[4]);
    }
    if(flag == 0){
        printf("你没有借这本书\n");
        return;
    }
    if (fclose(fq)){
        printf("关闭文件失败\n");
        exit(0);
    }
    if (fclose(fb)){
        printf("关闭文件失败\n");
        exit(0);
    }
    printf("还书成功\n");
}

int main(){
    int code1, code2;   //code1为总操作，code2为查询操作
    printf("    ***************************************\n");
    printf("                图书管理系统              *\n");
    printf("                                          *\n");
    printf("    *                                     *\n");
    printf("    *                                     *\n");
    printf("    *                                     *\n");
    printf("        *        版权所有    ——————瞿晟   *\n");
    printf("        *                    ——————王鑫   *\n");
    printf("        *                    ——————夏洋   *\n");
    printf("        *                    ——————向景荣 *\n");
    printf("        *                    ——————刘雅婷 *\n");
    printf("        ***********************************\n");
    printf("输入1：添加书籍 输入2：添加学生信息 输入3:查询书籍\n");
    printf("输入4：显示学生信息 输入5：借阅书籍 输入6：归还书籍\n");
    printf("输入7来退出\n");
    scanf("%d", &code1);
    while (code1 != 7){
        switch (code1){
        case 1:{
            int flag;   //是否继续操作，同下
            do{
                addBook();
                remove("book.txt");
                rename("ChangedBook.txt","book.txt");
                printf("还需要继续添加书籍吗？若是，输入非0，若不是，输入0\n");
                scanf("%d",&flag);
            }while(flag!=0);
            break;
        }
        case 2:{
            int flag;
            do{
                addStudent();
                printf("还需要继续添加学生信息吗？若是，输入非0，若不是，输入0\n");
                scanf("%d",&flag);
            }while(flag!=0);
            break;
        }
        case 3:{
            int flag;
            do{
                printf("请输入查询方式：\n");
                printf("输入1：以书号查询，输入2：以书名查询，输入3：以作者查询\n");
                scanf("%d", &code2);
                if (code2 == 1){
                    searchBook_call();
                }
                else if (code2 == 2){
                    searchBook_bookname();
                }
                else
                    searchBook_author();
                printf("还需要继续查询书籍吗？若是，输入非0，若不是，输入0\n");
                scanf("%d", &flag);
            } while (flag != 0);
            break;
        }
        case 4:{
            int flag;
            do{
                showStudent();
                printf("还需要继续显示学生信息吗，若是，输入非0，若不是，输入0\n");
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
                printf("还需要继续借书吗？若是，输入非0，若不是，输入0\n");
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
                printf("还需要继续还书吗？若是，输入非0，若不是，输入0\n");
                scanf("%d",&flag);
            } while (flag != 0);
            break;
        }
        default:
            break;
        }
        printf("还要继续操作吗？请选择：\n");
        printf("输入1：添加书籍 输入2：添加学生信息 输入3:查询书籍\n");
        printf("输入4：显示学生信息 输入5：借阅书籍 输入6：归还书籍\n");
        printf("输入7来退出\n");
        scanf("%d", &code1);
    }
    return 0;
}