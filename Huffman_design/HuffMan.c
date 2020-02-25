#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

#define MAXCHAR 10000   //文件可容纳最多字符数
#define CHARNUM 256 //最多256种字符
#define MAXNUM 6000
#define TRUE 1
typedef struct{
    char ch;    //存储的字符
    int weight; //权值，这个字符出现的频率
    int parent; //父节点
    int left;   //左子节点
    int right;  //右子节点
}HuffNode;

typedef struct{
    char code[MAXNUM];  //Huffman编码
    int start;
}HuffCode;

HuffNode ht[MAXNUM*2]; //存放哈夫曼树

HuffCode hcd[MAXNUM];  //存放ht数组中对应的字符的编码

int n;                 //字符的个数

//计算字符的权值
void count(){
    char file[MAXCHAR]; //存储字符
    int statistic[CHARNUM]; //存储权值
    int i;
    char c; //记录读到的字符
    FILE *fp,*fq;   
    for(i=0;i<CHARNUM;i++){
        statistic[i] = 0;
    }
    if((fp = fopen("file.txt","r")) == NULL)
    {
        printf("打开文件失败\n");
        exit(0);
    }
    if((fq = fopen("character.txt","w+")) == NULL)
    {
        printf("打开文件失败\n");
        exit(0);
    }
    while((c = getc(fp)) != EOF){   //记录权值
        statistic[(unsigned int)c]++;
    }
    if(fclose(fp)){
        printf("关闭文件1失败");
        exit(0);
    }
    for(i=0;i<CHARNUM;i++){
        if(statistic[i] != 0){   //若字符出现过，则加入
            file[i] = (char)i;
            fprintf(fq,"%c%d\n",file[i],statistic[i]);
        }
    }
    if(fclose(fq)){
        printf("关闭文件失败");
        exit(0);
    }
    printf("已将file.txt的字符及权值写入character.txt\n");
}

//初始化哈夫曼树ht
void initHt(){
    FILE * fp;  //存储编码字符和权值的文件
    char ch;    //文件中字符
    int i = 0;
    int j;
    //character.txt中读出要编码的字符和权值
    if((fp = fopen("character.txt","r")) == NULL){
        printf("打开文件失败\n");
        exit(0);
    }
    //初始化根结点
    ht[i].left = ht[i].right = ht[i].parent=-1;
    //遍历读取编码文件
    while((ch = fgetc(fp))!=EOF){
        if(ch == '\n'){   //初始化下一个结点
            i++;
            ht[i].left = ht[i].right = ht[i].parent=-1;     
        }
        //结点的权值赋值
        else if(ch>='0'&&ch<='9')
            ht[i].weight = ht[i].weight*10 + ch-'0';
        //结点的字符赋值
        else 
            ht[i].ch = ch;
    }
    n = i+1;    //计算字符个数
    //初始化后n-1个结点
    for(j=n;j<2*n-1;j++){
        ht[j].parent = ht[j].left = ht[j].right = -1;
        ht[j].weight = -1;
    }
    if(fclose(fp)){
        printf("关闭文件错误");
        exit(0);
    }
    printf("已将character.txt字符权值写入哈夫曼结点中\n");
}

//构造哈夫曼树,看成有n棵树，选择权值最小的两棵树合并
void createHuffTree(){
    int i,j,m1,m2;  //m1为最小权值，m2为次小权值
    int minI,minJ;  //minI为权值最小结点，minJ为权值次小结点
    minI = minJ = -1; //minI<minJ
    for(i=0;i<n-1;i++){
        m1 = m2 = MAXNUM;
        minI = minJ = -1;
        for(j=0;j<n+i;j++){ //找两个最小权的无父节点的结点
            if(ht[j].weight < m1 && ht[j].parent == -1){
                m2 = m1;
                minJ = minI;
                m1 = ht[j].weight;
                minI = j;
            }
            else if(ht[j].weight < m2 && ht[j].parent == -1){
                m2  = ht[j].weight;
                minJ = j;
            }
        }
        ht[minI].parent = ht[minJ].parent = n+i;
        ht[n+i].weight = m1+m2;
        ht[n+i].left = minI;
        ht[n+i].right = minJ;
    }
    ht[2*n-2].parent  = -1;
    printf("已创建哈夫曼树\n");
}

//将一个字符串反转
void reverse(char *str){
    int i,j;
    char ch;
    for(i=0,j = strlen(str)-1;i<j;i++,j--){
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
    }
}

//哈夫曼编码，通过父节点从下往上找
void createHuffCode(){
    int i,j,length;
    FILE * fp;  //存放哈夫曼编码的文件
    for(i=0;i<n;i++){
        length = 0;
        j = i;
        //给每个字符进行编码
        while(ht[j].parent != -1){
            //若j为左子结点，则编码0
            if(ht[ht[j].parent].left == j){
                hcd[i].code[length++] = 0+'0';
            }
            //若j为右子结点，则编码1
            else{
                hcd[i].code[length++] = 1+'0';
            }
            j = ht[j].parent;   //不断向上
        }
        hcd[i].start = hcd[i].code[length-1]-'0'; //记录开始位置
        hcd[i].code[length] = '\0';   //最后为结束符
        reverse(hcd[i].code);   //反转来完成编码
    }
    if((fp=fopen("code.txt","w+"))==NULL){
        printf("打开文件错误\n");
        exit(0);
    }
    //把hcd字符编码写入文件code.txt中
    for(i=0;i<n;i++){
        fputc(ht[i].ch,fp);
        fputs("    ",fp);
        fputs(hcd[i].code,fp);
        fputc('\n',fp);
    }
    if(fclose(fp)){
        printf("can not close the file character.txt");
        exit(0);
    }
    printf("已创建哈夫曼编码，保存在code.txt中\n");
}

//哈夫曼译码，每次都从根节点开始搜索1
int releaseHuffCode(char *str,char* code){
    int root = 2*n-2;
    int length = 0,i = 0;
    //遍历解码
    while(code[i]){
        //编码为0则为左子树
        if(code[i] == '0')
            root = ht[root].left;
        //编码为1则为右子树
        else if(code[i] == '1')
            root = ht[root].right;
        //解码失败
        else
            return 0;
        //若为树叶
        if(ht[root].left == -1 && ht[root].right == -1){
            str[length++] = ht[root].ch;    //赋值
            root = 2*n-2;   //重新从根节点往下
        }
        i++;
    }
    str[length]='\0';
    //解码成功
    if(root==2*n-2)
        return 1;
    return 0;
}

//用户输入字符
void encode(){
    int i = 0,j;
    char str[500];   //存储字符
    char code[5000]={'\0'};  //存储编码
    printf("\n请输入要编码的字符串(length<50)\n");
    gets(str);
    while(str[i]){
        //遍历寻找字符
        for(j=0;j<n;j++){
            //找到了字符
            if(str[i] == ht[j].ch){
                strcat(code,hcd[j].code);   //连接编码
                break;
            }
        }
        i++;
    }
        printf("输入字符串的编码为:     ");
        puts(code); //输出编码
}

//用户输入解码字串
void  decode(){
    char str[500];   //存储字符
    char code[5000]; //存储编码
    printf("\n请输入要译码的字串(用0和1表示)\n");
    scanf("%s",code);   
    //若解码成功
    if(releaseHuffCode(str,code)){
        printf("输入的编码的译码为：");
        puts(str);
    }else
        printf("你输入的字串错误！\n");
}

//计算压缩比
float compressRate(){
	double up=0.0,down=0.0; //up为压缩后文件大小，down为压缩前原文件大小
	for(int i=0;i<n;i++)
		up += ht[i].weight*(n-hcd[i].start + 1);
	int x = ceil(log2(n));    //未压缩前每个字符的大小
	down = n*x;
	if(down!=0) return up/down;
}

int main(){
    int choice;
    int i;
    count();    //计算字符出现频率
    initHt();   //初始化哈夫曼树
    createHuffTree();   //构建哈夫曼树
    createHuffCode();   //哈夫曼编码
    float rate = compressRate();
    printf("/****************哈夫曼编码与解码*********************/\n");
    printf("                                                    *\n");
    printf("    *                                               *\n");
    printf("    *                                               *\n");
    printf("    *                                               *\n");
    printf("        *                   版权所有    ——————瞿晟   *\n");
    printf("        *                              ——————王鑫   *\n");
    printf("        *                              ——————夏洋   *\n");
    printf("        *                              ——————向景荣 *\n");
    printf("        *                              ——————刘雅婷 *\n");
    printf("                  ***********************************\n");
    printf(" 在character.txt 文件中存放着各个字母的权值\n");
    printf(" 程序从中读出各个字母的权值构造哈夫曼树并进行编码\n");
    printf(" 各个字符的编码存在code.txt文件中\n");
    printf("哈夫曼编码的压缩比为：%2.1f%%\n",rate);
    printf("/*****************************************************/\n");
    do{
        printf("\n请输入你的选择：1 ---- 编码  2 ---- 译码  0 ---- 退出\n");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1: 
                encode();
                break;
            case 2: 
                decode();
                break;
            case 0: 
                printf("谢谢使用！\n");
                return 0;
            default:
                printf("你的输入错误！请重新输入！\n");
                break;
        }
        printf("还要继续操作吗？\n");
    }while(TRUE);
    return 0;
}