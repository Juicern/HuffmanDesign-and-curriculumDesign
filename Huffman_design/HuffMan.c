#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

#define MAXCHAR 10000   //�ļ�����������ַ���
#define CHARNUM 256 //���256���ַ�
#define MAXNUM 6000
#define TRUE 1
typedef struct{
    char ch;    //�洢���ַ�
    int weight; //Ȩֵ������ַ����ֵ�Ƶ��
    int parent; //���ڵ�
    int left;   //���ӽڵ�
    int right;  //���ӽڵ�
}HuffNode;

typedef struct{
    char code[MAXNUM];  //Huffman����
    int start;
}HuffCode;

HuffNode ht[MAXNUM*2]; //��Ź�������

HuffCode hcd[MAXNUM];  //���ht�����ж�Ӧ���ַ��ı���

int n;                 //�ַ��ĸ���

//�����ַ���Ȩֵ
void count(){
    char file[MAXCHAR]; //�洢�ַ�
    int statistic[CHARNUM]; //�洢Ȩֵ
    int i;
    char c; //��¼�������ַ�
    FILE *fp,*fq;   
    for(i=0;i<CHARNUM;i++){
        statistic[i] = 0;
    }
    if((fp = fopen("file.txt","r")) == NULL)
    {
        printf("���ļ�ʧ��\n");
        exit(0);
    }
    if((fq = fopen("character.txt","w+")) == NULL)
    {
        printf("���ļ�ʧ��\n");
        exit(0);
    }
    while((c = getc(fp)) != EOF){   //��¼Ȩֵ
        statistic[(unsigned int)c]++;
    }
    if(fclose(fp)){
        printf("�ر��ļ�1ʧ��");
        exit(0);
    }
    for(i=0;i<CHARNUM;i++){
        if(statistic[i] != 0){   //���ַ����ֹ��������
            file[i] = (char)i;
            fprintf(fq,"%c%d\n",file[i],statistic[i]);
        }
    }
    if(fclose(fq)){
        printf("�ر��ļ�ʧ��");
        exit(0);
    }
    printf("�ѽ�file.txt���ַ���Ȩֵд��character.txt\n");
}

//��ʼ����������ht
void initHt(){
    FILE * fp;  //�洢�����ַ���Ȩֵ���ļ�
    char ch;    //�ļ����ַ�
    int i = 0;
    int j;
    //character.txt�ж���Ҫ������ַ���Ȩֵ
    if((fp = fopen("character.txt","r")) == NULL){
        printf("���ļ�ʧ��\n");
        exit(0);
    }
    //��ʼ�������
    ht[i].left = ht[i].right = ht[i].parent=-1;
    //������ȡ�����ļ�
    while((ch = fgetc(fp))!=EOF){
        if(ch == '\n'){   //��ʼ����һ�����
            i++;
            ht[i].left = ht[i].right = ht[i].parent=-1;     
        }
        //����Ȩֵ��ֵ
        else if(ch>='0'&&ch<='9')
            ht[i].weight = ht[i].weight*10 + ch-'0';
        //�����ַ���ֵ
        else 
            ht[i].ch = ch;
    }
    n = i+1;    //�����ַ�����
    //��ʼ����n-1�����
    for(j=n;j<2*n-1;j++){
        ht[j].parent = ht[j].left = ht[j].right = -1;
        ht[j].weight = -1;
    }
    if(fclose(fp)){
        printf("�ر��ļ�����");
        exit(0);
    }
    printf("�ѽ�character.txt�ַ�Ȩֵд������������\n");
}

//�����������,������n������ѡ��Ȩֵ��С���������ϲ�
void createHuffTree(){
    int i,j,m1,m2;  //m1Ϊ��СȨֵ��m2Ϊ��СȨֵ
    int minI,minJ;  //minIΪȨֵ��С��㣬minJΪȨֵ��С���
    minI = minJ = -1; //minI<minJ
    for(i=0;i<n-1;i++){
        m1 = m2 = MAXNUM;
        minI = minJ = -1;
        for(j=0;j<n+i;j++){ //��������СȨ���޸��ڵ�Ľ��
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
    printf("�Ѵ�����������\n");
}

//��һ���ַ�����ת
void reverse(char *str){
    int i,j;
    char ch;
    for(i=0,j = strlen(str)-1;i<j;i++,j--){
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
    }
}

//���������룬ͨ�����ڵ����������
void createHuffCode(){
    int i,j,length;
    FILE * fp;  //��Ź�����������ļ�
    for(i=0;i<n;i++){
        length = 0;
        j = i;
        //��ÿ���ַ����б���
        while(ht[j].parent != -1){
            //��jΪ���ӽ�㣬�����0
            if(ht[ht[j].parent].left == j){
                hcd[i].code[length++] = 0+'0';
            }
            //��jΪ���ӽ�㣬�����1
            else{
                hcd[i].code[length++] = 1+'0';
            }
            j = ht[j].parent;   //��������
        }
        hcd[i].start = hcd[i].code[length-1]-'0'; //��¼��ʼλ��
        hcd[i].code[length] = '\0';   //���Ϊ������
        reverse(hcd[i].code);   //��ת����ɱ���
    }
    if((fp=fopen("code.txt","w+"))==NULL){
        printf("���ļ�����\n");
        exit(0);
    }
    //��hcd�ַ�����д���ļ�code.txt��
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
    printf("�Ѵ������������룬������code.txt��\n");
}

//���������룬ÿ�ζ��Ӹ��ڵ㿪ʼ����1
int releaseHuffCode(char *str,char* code){
    int root = 2*n-2;
    int length = 0,i = 0;
    //��������
    while(code[i]){
        //����Ϊ0��Ϊ������
        if(code[i] == '0')
            root = ht[root].left;
        //����Ϊ1��Ϊ������
        else if(code[i] == '1')
            root = ht[root].right;
        //����ʧ��
        else
            return 0;
        //��Ϊ��Ҷ
        if(ht[root].left == -1 && ht[root].right == -1){
            str[length++] = ht[root].ch;    //��ֵ
            root = 2*n-2;   //���´Ӹ��ڵ�����
        }
        i++;
    }
    str[length]='\0';
    //����ɹ�
    if(root==2*n-2)
        return 1;
    return 0;
}

//�û������ַ�
void encode(){
    int i = 0,j;
    char str[500];   //�洢�ַ�
    char code[5000]={'\0'};  //�洢����
    printf("\n������Ҫ������ַ���(length<50)\n");
    gets(str);
    while(str[i]){
        //����Ѱ���ַ�
        for(j=0;j<n;j++){
            //�ҵ����ַ�
            if(str[i] == ht[j].ch){
                strcat(code,hcd[j].code);   //���ӱ���
                break;
            }
        }
        i++;
    }
        printf("�����ַ����ı���Ϊ:     ");
        puts(code); //�������
}

//�û���������ִ�
void  decode(){
    char str[500];   //�洢�ַ�
    char code[5000]; //�洢����
    printf("\n������Ҫ������ִ�(��0��1��ʾ)\n");
    scanf("%s",code);   
    //������ɹ�
    if(releaseHuffCode(str,code)){
        printf("����ı��������Ϊ��");
        puts(str);
    }else
        printf("��������ִ�����\n");
}

//����ѹ����
float compressRate(){
	double up=0.0,down=0.0; //upΪѹ�����ļ���С��downΪѹ��ǰԭ�ļ���С
	for(int i=0;i<n;i++)
		up += ht[i].weight*(n-hcd[i].start + 1);
	int x = ceil(log2(n));    //δѹ��ǰÿ���ַ��Ĵ�С
	down = n*x;
	if(down!=0) return up/down;
}

int main(){
    int choice;
    int i;
    count();    //�����ַ�����Ƶ��
    initHt();   //��ʼ����������
    createHuffTree();   //������������
    createHuffCode();   //����������
    float rate = compressRate();
    printf("/****************���������������*********************/\n");
    printf("                                                    *\n");
    printf("    *                                               *\n");
    printf("    *                                               *\n");
    printf("    *                                               *\n");
    printf("        *                   ��Ȩ����    ����������������   *\n");
    printf("        *                              ����������������   *\n");
    printf("        *                              ����������������   *\n");
    printf("        *                              ���������������� *\n");
    printf("        *                              ������������������ *\n");
    printf("                  ***********************************\n");
    printf(" ��character.txt �ļ��д���Ÿ�����ĸ��Ȩֵ\n");
    printf(" ������ж���������ĸ��Ȩֵ����������������б���\n");
    printf(" �����ַ��ı������code.txt�ļ���\n");
    printf("�����������ѹ����Ϊ��%2.1f%%\n",rate);
    printf("/*****************************************************/\n");
    do{
        printf("\n���������ѡ��1 ---- ����  2 ---- ����  0 ---- �˳�\n");
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
                printf("ллʹ�ã�\n");
                return 0;
            default:
                printf("�������������������룡\n");
                break;
        }
        printf("��Ҫ����������\n");
    }while(TRUE);
    return 0;
}