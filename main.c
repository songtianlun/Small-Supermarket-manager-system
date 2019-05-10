#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct USER//�û���Ϣ
{
    char name[20];//�û���
    char user[20];//�˺�
    char password[20];//����
    char type[20];//�û�����
    int num;//���ݱ��/����
    struct USER *next;
};
typedef struct USER user_lnode,*user_list;

struct INVENTORY//�����Ϣ
{
    char id[20];//��׼��Ϊ13λ���˴�����20λ
    char name[30];//��Ʒ����
    char company[30];//������ҵ
    char type[10];//��Ʒ����
    char date_manufacture[20];//��������
    char date_keep[10];//������
    int quantity;//�������
    double pirce_enter;//���
    double pirce_sell;//�������ۼ�
    int num;//������Ϣ����/���
    struct INVENTORY *next;
};
typedef struct INVENTORY inventory_lnode,*inventory_list;

struct COMMODITY//������Ϣ
{
    char id[20];//��׼��Ϊ13λ���˴�����20λ
    char name[30];//��Ʒ����
    char company[30];//������ҵ
    char type[10];//��Ʒ����
    char date_manufacture[20];//��������
    char date_market[30];//��������
    char operator_name[20];//�����˴���
    double pirce_enter;//���
    double pirce_sell;//���ۼ�
    int sell_num;//������
    double pircr_profit;//����
    int num;//������Ϣ����/���
    char serial_num[12];//��λ��������ˮ��
    struct COMMODITY *next;
};
typedef struct COMMODITY commodity_lnode,*commodity_list;

void display_main();
void display_administration();
void display_common();

void user_load(user_list head); //�����û�����
void user_save(user_list head); //�����û����ݵ�����
void commodity_load(commodity_list head); //������Ʒ����
void commodity_save(commodity_list head); //������Ʒ���ݵ�����
void inventory_load(inventory_list head); //����������
void inventory_save(inventory_list head); //���������ݵ�����

int initialize(user_list user_head,commodity_list commodity_head,inventory_list inventory_head);//��ʼ��
int loading_main(user_list head,user_list mine);//�û���½������ 1�����߼����� 2������ͨ�û� -1����������� -2�����û�������
void administration_main(user_list user_head,commodity_list commodity_head,inventory_list inventory_head,user_list mine);//�߼��û�����
void common_main(user_list user_head,commodity_list commodity_head,inventory_list inventory_head,user_list mine);//��ͨ�û�����

void user_main_administration(user_list user_head,user_list mine);//�߼��û��������
void user_main_administration_ergodicity(user_list user_head,user_list mine);//�����û���Ϣ
void user_main_administration_add(user_list user_head,user_list mine);//������û�
void user_main_administration_rank(user_list user_head,user_list mine);//����޸�
void user_main_administration_delete(user_list user_head,user_list mine);//ע���û�
void user_main_administration_mine(user_list user_head,user_list mine);//�ҵ���Ϣ
void user_main_administration_revamp(user_list user_head,user_list mine);//�޸��ҵ�����
void user_main_common(user_list user_head,user_list mine);//��ͨ�û��������
void inventory_main_administration(inventory_list inventory_head,user_list mine);//�߼�������������
void inventory_main_administration_ergodicity(inventory_list inventory_head,user_list mine);//���������Ϣ
void inventory_main_administration_add(inventory_list inventory_head,user_list mine);//���
void inventory_main_administration_revamp(inventory_list inventory_head,user_list mine);//�޸���Ʒ��Ϣ
void inventory_main_administration_find(inventory_list inventory_head,user_list mine);//��Ʒ����
void inventory_main_administration_printfi(inventory_list inventory_head,int num);//���������i������Ϣ
int inventory_main_administration_find_id(inventory_list inventory_head,user_list mine);//��Ʒ����-��ʶ����
void inventory_main_administration_find_name(inventory_list inventory_head,user_list mine);//��Ʒ����-������
void inventory_main_administration_find_company(inventory_list inventory_head,user_list mine);//��Ʒ����-��������ҵ
void inventory_main_administration_find_type(inventory_list inventory_head,user_list mine);//��Ʒ����-����Ʒ����
void inventory_main_administration_find_manufacture(inventory_list inventory_head,user_list mine);//��Ʒ����-����������
void inventory_main_administration_find_quantity(inventory_list inventory_head,user_list mine);//��Ʒ����-�������
void inventory_main_administration_find_pirce(inventory_list inventory_head,user_list mine);//��Ʒ����-����������
void inventory_main_administration_adds(inventory_list inventory_head,user_list mine);//�������
void inventory_main_administration_adds_file(inventory_list inventory_head,user_list mine);//��������������
void inventory_main_administration_de_weight(inventory_list inventory_head,user_list mine);//�����Ϣ�ظ���Ϣ����
void inventory_main_common(inventory_list inventory_head,user_list mine);//��ͨ������������

void commodity_main_administration(inventory_list inventory_head,commodity_list commodity_head,user_list mine);//�߼�����������
void commodity_main_administration_find(inventory_list inventory_head,commodity_list commodity_head,user_list mine);//��ѯ������
void commodity_main_administration_sell(inventory_list inventory_head,commodity_list commodity_head,user_list mine);//���۳���
void commodity_main_administration_return(inventory_list inventory_head,commodity_list commodity_head,user_list mine);//�˻�����
void commodity_main_administration_record(commodity_list commodity_head,user_list mine);//���׼�¼��ȡ
void commodity_main_administration_record_all(commodity_list commodity_head,user_list mine);//���׼�¼����
void commodity_main_administration_record_seller(commodity_list commodity_head,user_list mine);//��ȡ����Ա���׼�¼
void commodity_main_administration_record_order(commodity_list commodity_head,user_list mine);//��ȡ�����Ž��׼�¼
void commodity_main_administration_record_year(commodity_list commodity_head,user_list mine);//���׼�¼�����ȡ
void commodity_main_administration_record_month(commodity_list commodity_head,user_list mine);//���׼�¼���µ�ȡ
void commodity_main_administration_record_day(commodity_list commodity_head,user_list mine);//���׼�¼�����ȡ
void commodity_main_administration_revamp(commodity_list commodity_head,user_list mine);//���׼�¼�޸�
void commodity_main_administration_analyse(commodity_list commodity_head,user_list mine);//�����������
void commodity_main_administration_grade();//���۱��ͷ
void transition(int num,char ch[10]);//����ת�� ��nλ��������ת��Ϊ�ַ��������ch��
int transition_ch(char ch[20]);//����ת�� �����ִ��ַ����鵼��Ϊ��������
void commodity_main_administration_printfi(commodity_list commodity_head,int num);//������۱���i������Ϣ
void commodity_main_common(inventory_list inventory_head,commodity_list commodity_head,user_list mine);//��ͨ����������

int main()
{
    user_list user_head;
    commodity_list commodity_head;
    inventory_list inventory_head;


    user_list mine;
    int i;
    int answer;
    char sel;
    int sel2;

    mine = (user_list)malloc(sizeof(user_lnode));
    user_head = (user_list)malloc(sizeof(user_lnode));
    commodity_head = (commodity_list)malloc(sizeof(commodity_lnode));
    inventory_head = (inventory_list)malloc(sizeof(inventory_lnode));

    commodity_head->next = NULL;
    inventory_head->next = NULL;
    user_head->next = NULL;

    system("mode con cols=180 lines=80");

    while(1)
    {
    system("cls");
    display_main();

    scanf("%c",&sel);
    if(sel>'9'||sel<'0')
    {
        for(i=0;i<60;i++)printf(" ");printf("����Ƿ���������ѡ��\n");
        system("pause");
        continue;
    }
        switch(sel)
    {
    case '1':
        {
            user_load(user_head);//�����û���Ϣ������user
            commodity_load(commodity_head);//������Ʒ��Ϣ������comodity
            inventory_load(inventory_head);//���ؿ����Ϣ������inventory
            answer = loading_main(user_head,mine);//1�����߼����� 2������ͨ�û� -1����������� -2�����û�������
        if(answer == 1)
            administration_main(user_head,commodity_head,inventory_head,mine);//�߼��û�����
        else if(answer == 2)
            common_main(user_head,commodity_head,inventory_head,mine);//��ͨ�û�����
        else
        {
            for(i=0;i<60;i++)printf(" ");printf("���������û�������룬�����ǣ��ɽ��г�ʼ������\n");
            system("pause");
            continue;
        }
        continue;
        }
    case '9':
        {
            for(i=0;i<60;i++)printf(" ");printf("ȷ����ʼ��ϵͳ��\n");
            for(i=0;i<50;i++)printf(" ");printf("����(����1)�������ȫ��ϵͳ���ݲ���ʼ������Ա\n");
            for(i=0;i<60;i++)printf(" ");scanf("%d",&sel2);
            getchar();
            if(sel2==1)
                {
                initialize(user_head,commodity_head,inventory_head);
                }
            continue;
        }
        default:
            return 0;
    }
    }
    return 0;
}

void display_main()
{
    int i;
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<60;i++)printf(" ");printf("           *          \n");
    for(i=0;i<60;i++)printf(" ");printf("        *     *        \n");
    for(i=0;i<60;i++)printf(" ");printf("     *           *      \n");
    for(i=0;i<60;i++)printf(" ");printf("         ��ã�       \n");
    for(i=0;i<60;i++)printf(" ");printf("           *          \n");
    for(i=0;i<60;i++)printf(" ");printf("        *     *        \n");
    for(i=0;i<60;i++)printf(" ");printf("     *           *      \n");
    for(i=0;i<60;i++)printf(" ");printf("��ӭʹ��С�ͳ��й���ϵͳ��\n\n");
    for(i=0;i<65;i++)printf(" ");printf("1.����ϵͳ\n");
    for(i=0;i<65;i++)printf(" ");printf("9.��ʼ��ϵͳ\n");
    for(i=0;i<65;i++)printf(" ");printf("all else.�˳�ϵͳ\n\n");
    for(i=0;i<55;i++)printf(" ");printf("��ܰ��ʾ:������ǵ�һ��ʹ�ø�ϵͳ�����ȶ�ϵͳ���г�ʼ��������\n\n");
    for(i=0;i<60;i++)printf(" ");printf("���������Ҫִ�еĲ������룺");
    return;
}

void display_administration()
{
    int i;
    for(i=0;i<60;i++)printf(" ");printf("           *           \n");
    for(i=0;i<60;i++)printf(" ");printf("        *     *        \n");
    for(i=0;i<60;i++)printf(" ");printf("     *           *     \n");
    for(i=0;i<60;i++)printf(" ");printf("    ^^   ��ã� ^^    \n");
    for(i=0;i<60;i++)printf(" ");printf("     *           *     \n");
    for(i=0;i<60;i++)printf(" ");printf("        *     *        \n");
    for(i=0;i<60;i++)printf(" ");printf("           *           \n");
    for(i=0;i<60;i++)printf(" ");printf("��ӭ�߼�����Ա����С�ͳ��й���ϵͳ��\n\n");
    for(i=0;i<60;i++)printf(" ");printf("��1.�߼��û��������\n\n");

    for(i=0;i<60;i++)printf(" ");printf("��2.�߼����������\n\n");

    for(i=0;i<60;i++)printf(" ");printf("��3.�߼����۹������\n\n");

    for(i=0;i<60;i++)printf(" ");printf("��0.�˳�ϵͳ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("�������������ִ�еĲ������룺");
    return;
}
void display_common()
{
    int i;
    for(i=0;i<60;i++)printf(" ");printf("           *           \n");
    for(i=0;i<60;i++)printf(" ");printf("        *     *        \n");
    for(i=0;i<60;i++)printf(" ");printf("     *           *     \n");
    for(i=0;i<60;i++)printf(" ");printf("    ^^   ��ã� ^^    \n");
    for(i=0;i<60;i++)printf(" ");printf("     *           *     \n");
    for(i=0;i<60;i++)printf(" ");printf("        *     *        \n");
    for(i=0;i<60;i++)printf(" ");printf("           *           \n");
    for(i=0;i<60;i++)printf(" ");printf("��ӭʹ��С�ͳ��й���ϵͳ��\n\n");
    for(i=0;i<60;i++)printf(" ");printf("��1.��ͨ�û��������\n\n");

    for(i=0;i<60;i++)printf(" ");printf("��2.��ͨ���������\n\n");

    for(i=0;i<60;i++)printf(" ");printf("��3.��ͨ���۹������\n\n");

    for(i=0;i<60;i++)printf(" ");printf("��4.�˳�ϵͳ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("\n�������������ִ�еĲ������룺");
    return;
}

int initialize(user_list user_head,commodity_list commodity_head,inventory_list inventory_head)//��ʼ��
{
    int i;
    user_list user_guide,user_first;
    commodity_list commodity_guide;
    inventory_list inventory_guide;
    for(i=0;i<60;i++)printf(" ");printf("���ڳ�ʼ������\n");

    user_guide = (user_list)malloc(sizeof(user_lnode));
    commodity_guide = (commodity_list)malloc(sizeof(commodity_lnode));
    inventory_guide = (inventory_list)malloc(sizeof(inventory_lnode));

    user_first = (user_list)malloc(sizeof(user_lnode));

    strcpy(user_first->name,"admin");
    strcpy(user_first->user,"admin");
    strcpy(user_first->password,"admin");
    strcpy(user_first->type,"administration");
    user_first->num = 1;//��һ���û��ı��

    strcpy(user_guide->name,"�û���");
    strcpy(user_guide->user,"�˺�");
    strcpy(user_guide->password,"����");
    strcpy(user_guide->type,"����");
    user_guide->num = 1;//�û�����

    strcpy(commodity_guide->id,"ʶ����");
    strcpy(commodity_guide->name,"��Ʒ����");
    strcpy(commodity_guide->company,"������ҵ");
    strcpy(commodity_guide->type,"��Ʒ����");
    strcpy(commodity_guide->date_manufacture,"��������");
    strcpy(commodity_guide->date_market,"��������");
    strcpy(commodity_guide->operator_name,"����Ա");
    strcpy(commodity_guide->serial_num,"������ˮ��");
    //strcpy(commodity_guide->sell_num,"����Ա");
    //strcpy(commodity_guide->pirce_enter,"����");
    //strcpy(commodity_guide->pirce_sell,"���ۼ�");
    //strcpy(commodity_guide->pircr_profit,"����");
    commodity_guide->num = 0;//��������

    strcpy(inventory_guide->id,"ʶ����");
    strcpy(inventory_guide->name,"��Ʒ����");
    strcpy(inventory_guide->company,"������ҵ");
    strcpy(inventory_guide->type,"��Ʒ����");
    strcpy(inventory_guide->date_manufacture,"��������");
    strcpy(inventory_guide->date_keep,"������");
    //strcpy(inventory_guide->quantity,"�������");
    //strcpy(inventory_guide->pirce_enter,"����");
    //strcpy(inventory_guide->pirce_sell,"�����ۼ�");
    inventory_guide->num = 0;//��������

    user_head->next = user_guide;
    commodity_head->next = commodity_guide;
    inventory_head->next = inventory_guide;

    user_guide->next = user_first;
    commodity_guide = NULL;
    inventory_guide = NULL;

    user_first->next = NULL;

    user_save(user_head);
    commodity_save(commodity_head);
    inventory_save(inventory_head);

    for(i=0;i<60;i++)printf(" ");printf("���μ����ĳ�ʼ����Ա�û���������\n");
    for(i=0;i<60;i++)printf(" ");printf("�û�����admin\n");
    for(i=0;i<60;i++)printf(" ");printf("���룺admin\n");
    system("pause");
    return -1;
}

void user_load(user_list head) //�����û�����
{
    user_list rear = head,p;
    FILE *fp;
    int i=0,sum;
    fp = fopen("User information.dat","rb");
    if(fp == NULL)
    {
        return;
    }
    p = (user_list)malloc(sizeof(user_lnode));
    fread(p,sizeof(user_lnode),1,fp);i++;
    sum = p->num;
    rear->next = p;
    rear = p;
    while(i<=sum)
    {
        p = (user_list)malloc(sizeof(user_lnode));
        if(fread(p,sizeof(user_lnode),1,fp)==0)
        break;
        rear->next = p;
        rear = p;
        i++;
    }
    rear->next = NULL;
    fclose(fp);
    return;
}
void user_save(user_list head)//�����û����ݵ�����
{
    user_list rear = head->next;
    FILE *fp;
    int sum,i=1;
    sum = rear->num+1;
    fp = fopen("User information.dat","wb");
    while(i<=sum)
    {
        fwrite(rear,sizeof(user_lnode),1,fp);
        rear = rear->next;
        i++;
    }
    fclose(fp);
    return;
}

void commodity_load(commodity_list head) //������Ʒ����
{
    commodity_list p,rear = head;
    FILE *fp;
    int i=0,sum;

    fp = fopen("Commodity information.dat","rb");
    if(fp == NULL)
    {
        return;
    }
    p = (commodity_list)malloc(sizeof(commodity_lnode));
    fread(p,sizeof(commodity_lnode),1,fp);i++;
    sum = p->num;
    rear->next = p;
    rear = p;
    while(i<=sum)
    {
        p = (commodity_list)malloc(sizeof(commodity_lnode));
        if(fread(p,sizeof(commodity_lnode),1,fp)==0)
            break;
        rear->next = p;
        rear = p;
        i++;
    }
    rear->next = NULL;
    fclose(fp);
    return;
}
void commodity_save(commodity_list head) //������Ʒ���ݵ�����
{
    commodity_list rear = head->next;
    FILE *fp;
    int sum,i=1;
    sum = rear->num+1;
    fp = fopen("Commodity information.dat","wb");
    while(i<=sum)
        {
            fwrite(rear,sizeof(commodity_lnode),1,fp);
            rear = rear->next;
            i++;
        }
    fclose(fp);
    return;
}
void inventory_load(inventory_list head) //����������
{
    inventory_list p,rear = head;
    FILE *fp;
    int i=0,sum;

    fp = fopen("Inventory information.dat","rb");
    if(fp == NULL)
    {
        return;
    }
    p = (inventory_list)malloc(sizeof(inventory_lnode));
    fread(p,sizeof(inventory_lnode),1,fp);
    sum = p->num;
    rear->next = p;
    p->next = NULL;
    rear = rear->next;
    while(i<sum)
    {
        p = (inventory_list)malloc(sizeof(inventory_lnode));
        if(fread(p,sizeof(inventory_lnode),1,fp)==0)
            break;
        rear->next = p;
        rear=rear->next;
        i++;
    }
    rear->next = NULL;
    fclose(fp);
    return;
}
void inventory_save(inventory_list head) //���������ݵ�����
{
    inventory_list rear = head->next;
    FILE *fp;
    int sum,i=1;
    sum = rear->num+1;
    fp = fopen("Inventory information.dat","wb");
    while(i<=sum&&rear)
    {
        fwrite(rear,sizeof(inventory_lnode),1,fp);
        rear = rear->next;
        i++;
    }
    fclose(fp);
    return;
}

int loading_main(user_list head,user_list mine)//�û����ʶ�������� 1�����߼����� 2������ͨ�û� -1����������� -2�����û�������
{
    user_list p = head->next;
    char printuser[20],printpassword[20];
    int i=1,n;
    n = p->num;
    system("cls");
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<60;i++)printf(" ");printf("��ӭʹ��С�ͳ��й���ϵͳ\n\n\n");
    for(i=0;i<60;i++)printf(" ");printf("��ʹ�������û������������ϵͳ��\n\n");
    for(i=0;i<60;i++)printf(" ");printf("�û�����");scanf("%s",printuser);
    for(i=0;i<60;i++)printf(" ");printf("��  �룺");scanf("%s",printpassword);
    printf("\n");
    p = p->next;
    i = 1;
    while(i<=n&&p)//�����˻���Ϣ
    {
        if(strcmp(p->user,printuser)==0)
        {
            if(strcmp(p->password,printpassword)==0)
            {
                printf("�ɹ���¼������ʶ�����\n");
                strcpy(mine->name,p->name);
                strcpy(mine->user,p->user);
                strcpy(mine->password,p->password);
                strcpy(mine->type,p->type);
                mine->num = i;
                if(strcmp(p->type,"administration")==0)
                    {
                        return 1;
                    }
                else
                    {
                        return 2;
                    }
            }
            else
                {
                printf("�����������������\n");
                printf("��  �룺");
                scanf("%s",printpassword);

                if(strcmp(p->password,printpassword)==0)
                    {
                        printf("�ɹ���¼������ʶ�����\n");
                        strcpy(p->name,mine->name);
                        strcpy(p->user,mine->user);
                        strcpy(p->password,mine->password);
                        strcpy(p->type,mine->type);
                        mine->num = i;
                        if(strcmp(p->type,"administration")==0)
                            {
                                printf("�𾴵ĸ߼�����Ա����ӭ����С�ͳ��и߼�����ϵͳ��\n");
                                return 1;
                            }
                        else
                            {
                                printf("�𾴵�����Ա����ӭ����С�ͳ�������ϵͳ��\n");
                                return 2;
                            }
                    }
                    else
                    {
                        printf("�ܽӵ�¼��\n");
                        getchar();
                        return -1;
                    }
                }

        }
        i++;
        p = p->next;
    }
        printf("\n�û������ڣ��ܾ����룡\n\n\n");
        getchar();
        return -2;
}

void administration_main(user_list user_head,commodity_list commodity_head,inventory_list inventory_head,user_list mine)//�߼��û�����
{
    char sel;
    int i;
    while(1)
    {
    system("cls");
    getchar();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<80;i++)printf(" ");printf("��ǰ�û�Ϊ��%20s\n\n",mine->name);
    display_administration();

    scanf("%c",&sel);
    if(sel>'9'||sel<'0')
    {
        printf("����Ƿ���������ѡ��\n");
        system("pause");
    }
    else
    switch(sel)
    {
        case '1':
            user_main_administration(user_head,mine);
            continue;
        case '2':
            inventory_main_administration(inventory_head,mine);
            continue;
        case '3':
            commodity_main_administration(inventory_head,commodity_head,mine);
            continue;
        default:
            getchar();
            return;
    }
    }
    return;
}

void common_main(user_list user_head,commodity_list commodity_head,inventory_list inventory_head,user_list mine)//��ͨ�û�����
{
    char sel;
    int i;
    while(1)
    {
    system("cls");
    getchar();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<80;i++)printf(" ");printf("��ǰ�û�Ϊ��%s\n",mine->name);
    display_common();

    scanf("%c",&sel);
    if(sel>'9'||sel<'0')
    {
        printf("����Ƿ���������ѡ��\n");
        system("pause");
        continue;
    }
    else
        switch(sel)
    {
    case '1':
        user_main_common(user_head,mine);
        break;
    case '2':
        inventory_main_common(inventory_head,mine);
    case '3':
        commodity_main_common(inventory_head,commodity_head,mine);
    default:
        getchar();
        return;
    }
    }
    return;
}
void user_main_administration(user_list user_head,user_list mine)//�߼��û��������
{
    int sel,i;
    while(1)
    {
    system("cls");
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("��ǰ�û�Ϊ��%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("��ӭ������߼��û���Ϣ�������\n\n");

    for(i=0;i<60;i++)printf(" ");printf("1.���ȫ���û���Ϣ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.������û�/����Ա\n\n");
    for(i=0;i<60;i++)printf(" ");printf("3.����û����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("4.ע���û�\n\n");
    for(i=0;i<60;i++)printf(" ");printf("5.����ҵ��˻���Ϣ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("6.�޸�����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.�˳��û���Ϣ�������\n\n");
    for(i=0;i<60;i++)printf(" ");printf("����������ִ�еĲ������룺");
    scanf("%d",&sel);
    switch(sel)
    {
    case 1:
        user_main_administration_ergodicity(user_head,mine);
        continue;
    case 2:
        user_main_administration_add(user_head,mine);
        continue;
    case 3:
        user_main_administration_rank(user_head,mine);
        continue;
    case 4:
        user_main_administration_delete(user_head,mine);
        continue;
    case 5:
        user_main_administration_mine(user_head,mine);
        continue;
    case 6:
        user_main_administration_revamp(user_head,mine);
        continue;
    case 0:
        return;
    }
    }
    return;
}

void user_main_administration_ergodicity(user_list user_head,user_list mine)//�����û�
{
    user_list p;
    int i;
    p = user_head->next;
    system("cls");
    for(i=0;i<30;i++)printf(" ");printf("�û��嵥\n");
    printf("%4s%20s%20s%20s\n\n","���",p->name,p->user,p->type);
    p = p->next;
    while(p)
    {
        printf("%4d%20s%20s",p->num,p->name,p->user);
        if(strcmp(p->type,"administration")==0)
            printf("%20s\n\n","����Ա");
        else
            printf("%20s\n\n","��ͨ�û�");

        p = p->next;
    }
    for(i=0;i<120;i++)printf(" ");printf("\n��ǰ�û�Ϊ��%s\n",mine->name);
    system("pause");
    return;
}

void user_main_administration_add(user_list user_head,user_list mine)//������û�
{
    int sel;
    user_list p,rear=user_head->next;
    while(rear->next)
        rear = rear->next;
    p = (user_list)malloc(sizeof(user_lnode));
    printf("�������������û���Ϣ\n");
    printf("������");
    scanf("%s",p->name);
    printf("�˺ţ�");
    scanf("%s",p->user);
    printf("���룺");
    scanf("%s",p->password);
    printf("��ָ�����û���ʼ���(1.����Ա 2.��ͨ�û�):");
    scanf("%d",&sel);
    if(sel == 1)
        strcpy(p->type,"administration");
    else
        strcpy(p->type,"common");
    p->num = rear->num+1;

    rear->next = p;
    p->next = NULL;
    user_head->next->num = user_head->next->num+1;
    printf("��ϲ�������Ǳ�ϵͳ�ĵ�%dλ�û���\n",p->num);
    printf("������˺���ϢΪ��\n");
    printf("%4s%20s%20s%20s%20s\n","���","�û���","�˺�","����","�û�����");
    printf("%10d%20s%20s%20s",p->num,p->name,p->user,p->password);
    if(strcmp(p->type,"administration")==0)
        printf("%20s\n","����Ա");
    else
        printf("%20s\n","��ͨ�û�");
    user_save(user_head);
    system("pause");
    return;
}
void user_main_administration_rank(user_list user_head,user_list mine)//����޸�
{
    int sel,sum;
    user_list p = user_head->next;
    sum = p->num;
    printf("��ǰȫ���û���Ϣ���£�\n");
    user_main_administration_ergodicity(user_head,mine);
    printf("\n����������������˺ŵı�ţ�");
    scanf("%d",&sel);
    if(sel>sum)
    {
        printf("�Բ������������Ч��\n");
        return;
    }
    if(sel==mine->num)
    {
        printf("�Բ��𣡱�ϵͳ������ǰ�û��޸ĵ�ǰ�û���ݣ�\n");
        system("pause");
        return;
    }
    while(sel--)
        p = p->next;

    printf("��ǰ�û����Ϊ:  ");
    if(strcmp(p->type,"administration")==0)
        printf("%s\n","����Ա");
    else
        printf("%s\n","��ͨ�û�");
    printf("\n�Ƿ�ȷ���޸�(1.ȷ�� 2.ȡ���޸�)���û�Ϊ��");
    if(strcmp(p->type,"common")==0)
        printf("%s\n","����Ա");
    else
        printf("%s\n","��ͨ�û�");
        scanf("%d",&sel);
        if(sel == 1)
                if(strcmp(p->type,"administration")==0)
                    strcpy(p->type,"common");
                else
                    strcpy(p->type,"administration");
        else
        {
            printf("������ȡ����\n");
            system("pause");
            return;
        }
            printf("��ݱ���ɹ���\n");
            system("pause");
        return;

}
void user_main_administration_delete(user_list user_head,user_list mine)//ע���û�
{
    int sel,sum,sel2,i=0;
    user_list prior,p = user_head->next;
    sum = p->num;
    prior = p;
    printf("��ǰȫ���û���Ϣ���£�\n");
    user_main_administration_ergodicity(user_head,mine);
    printf("\n����������ע���˺ŵı�ţ�");
    scanf("%d",&sel);
    if(sel>sum)
    {
        printf("�Բ������������Ч��\n");
        system("pause");
        return;
    }
    if(sel==mine->num)
    {
        printf("�Բ��𣡱�ϵͳ������ǰ�û�ע����ǰ�û���\n");
        system("pause");
        return;
    }
    while(i<sel)
        {
            prior = p;
            p = p->next;
            i++;
        }
    printf("Ԥ��ע���û�����ϢΪ��\n");
    printf("%4s%20s%20s%20s%20s\n","���","�û���","�˺�","����","�û�����");
    printf("%10d%20s%20s%20s",p->num,p->name,p->user,p->password);
    if(strcmp(p->type,"administration")==0)
        printf("%20s\n","����Ա");
    else
        printf("%20s\n","��ͨ�û�");
    printf("ȷ��ע���𣿣�1.ȷ�� 2.ȡ����: ");
    scanf("%d",&sel2);
    if(sel2 == 1)
    {
        prior->next = p->next;
        free(p);
        user_head->next->num = user_head->next->num-1;
    }
    else
        return;

    p = p->next;
    while(p)
        {
            p->num = p->num - 1;
            p = p->next;
        }

    user_save(user_head);
    printf("ע�����˺ųɹ���\n");
    system("pause");
    return;
}
void user_main_administration_mine(user_list user_head,user_list mine)//�ҵ���Ϣ
{
    printf("�ҵı�ţ�%4d\n�ҵ�������%20s\n�ҵ��˺ţ�%20s\n�ҵ���ݣ�",mine->num,mine->name,mine->user);
    if(strcmp(mine->type,"administration")==0)
        printf("%20s\n","����Ա");
    else
        printf("%20s\n","��ͨ�û�");
    system("pause");
    return;
}
void user_main_administration_revamp(user_list user_head,user_list mine)//�޸��ҵ�����
{
    user_list p = user_head->next->next;//����ǰ��
    char pass[20];
    int i,n,sel;
    n = mine->num;
    i = 1;
    while(i<n)
    {
        p = p->next;
        i++;
    }
    printf("����������ǰ�����룺");
    scanf("%s",pass);
    if(strcmp(pass,mine->password)==0)
    {
        printf("���������������룺");
        scanf("%s",mine->password);
        if(strcmp(mine->password,p->password)==0)
        {
            system("cls");
            printf("�������������һ�£��޸�ʧ�ܣ�\n");
            return;
        }
        printf("����������Ϊ��%s\n",mine->password);
        printf("ȷ���޸ģ�1.ȷ�� 2.ȡ������");
        scanf("%d",&sel);
        if(sel == 1)
            strcpy(p->password,mine->password);
        else
            return;
        system("pause");
        system("cls");
        printf("���μ����������룡\n");
        system("pause");
        user_save(user_head);
        return;
    }
    else
    {
        printf("�������������޸�����ʧ�ܣ�\n");
        system("pause");
    }
    return;
}

void user_main_common(user_list user_head,user_list mine)//��ͨ�û��������
{
    int sel,i;
    while(1)
    {
    system("cls");
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("��ǰ�û�Ϊ��%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("��ӭ�������û���Ϣ�������\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.����ҵ��˻���Ϣ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.�޸�����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.�˳��û���Ϣ�������\n\n");
    for(i=0;i<60;i++)printf(" ");printf("����������ִ�еĲ������룺");
    scanf("%d",&sel);
    switch(sel)
    {
    case 1:
        user_main_administration_mine(user_head,mine);
        continue;
    case 2:
        user_main_administration_revamp(user_head,mine);
        continue;
    case 0:
        return;
    }
    }
    return;
}

void inventory_main_administration(inventory_list inventory_head,user_list mine)//�߼�������������
{
    int sel,i;
    while(1)
    {
    system("cls");
    inventory_main_administration_de_weight(inventory_head,mine);
    inventory_save(inventory_head);
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("��ǰ�û�Ϊ��%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("��ӭ������߼��������������\n\n");

    for(i=0;i<60;i++)printf(" ");printf("1.���ȫ�������Ʒ��Ϣ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.�������Ǽ�\n\n");
    for(i=0;i<60;i++)printf(" ");printf("3.�޸Ļ�Ʒ��Ϣ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("4.�����Ʒ��Ϣ����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("5.��������\n\n");
    for(i=0;i<60;i++)printf(" ");printf("6.�ⲿ��������Ϣ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.�˳������Ϣ�������\n\n");
    for(i=0;i<60;i++)printf(" ");printf("����������ִ�еĲ������룺");
    scanf("%d",&sel);
    switch(sel)
    {
    case 1:
        inventory_main_administration_ergodicity(inventory_head,mine);
        continue;
    case 2:
        inventory_main_administration_add(inventory_head,mine);
        continue;
    case 3:
        inventory_main_administration_revamp(inventory_head,mine);
        continue;
    case 4:
        inventory_main_administration_find(inventory_head,mine);
        continue;
    case 5:
        inventory_main_administration_adds(inventory_head,mine);
        continue;
    case 6:
        inventory_main_administration_adds_file(inventory_head,mine);
        continue;
    case 0:
        return;
    }
    inventory_save(inventory_head);
    }
    return;
}

void inventory_main_administration_ergodicity(inventory_list inventory_head,user_list mine)//���������Ϣ
{
    inventory_list p;
    int sum,i=0;
    system("cls");
    p = inventory_head->next;
    sum = p->num;
    if(sum<=0)
    {
        for(i=0;i<15;i++)printf("\n");
        printf("\n������ݿ��ڵ�ǰû�п����Ϣ��������������¼�����ݣ�\n");
        system("pause");
        return;
    }
    for(i=0;i<80;i++)printf(" ");printf("����嵥\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",p->id,p->name,p->company,p->type,p->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
    p = p->next;
    while(p)
    {
        printf("%-6d%-15s%-30s%-30s%-10s%-20s%-12s%-15d%-15.2lf%-30.2lf\n",p->num,p->id,p->name,p->company,p->type,p->date_manufacture,p->date_keep,p->quantity,p->pirce_enter,p->pirce_sell);
        p = p->next;
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
    system("pause");
    return;
}

void inventory_main_administration_printfi(inventory_list inventory_head,int num)//���������i������Ϣ
{
    inventory_list p = inventory_head->next;//����ǰ��
    while(num--)
    {
        p = p->next;
    }
        printf("%-6d%-15s%-30s%-30s%-10s%-20s%-12s%-15d%-15.2lf%-30.2lf\n",p->num,p->id,p->name,p->company,p->type,p->date_manufacture,p->date_keep,p->quantity,p->pirce_enter,p->pirce_sell);
    return;
}
void inventory_main_administration_add(inventory_list inventory_head,user_list mine)//���
{
    char ch[30];
    int quanlity;
    double price;
    char y[5],m[3],d[3];
    inventory_list p,rear;
    rear = inventory_head->next;
    while(rear->next)
        rear=rear->next;

    while(1)
    {
    p = (inventory_list)malloc(sizeof(inventory_lnode));
    printf("��������-1ʱֹͣ��⣡\n");
    printf("�����������Ʒ��13λʶ���룺");
    scanf("%s",ch);
    if(strcmp(ch,"-1")==0) return;
    if(strlen(ch)>13&&strlen(ch)<13)
    {
        printf("�����ʽ�Ƿ������������룡");
        printf("���ٴ����������Ʒ��13λʶ���룺");
        scanf("%s",ch);
        if(strlen(ch)>13&&strlen(ch)<13)
        {
            printf("�Բ������ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    strcpy(p->id,ch);

    printf("��������Ʒ������������15λ���ֻ�30λӢ�ģ���");
    scanf("%s",ch);
    if(strlen(ch)>30&&strlen(ch)<1)
    {
        printf("�����ʽ�Ƿ������������룡");
        printf("���ٴ�������Ʒ������������15λ���ֻ�30λӢ�ģ���");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<1)
        {
            printf("�Բ������ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    strcpy(p->name,ch);

    printf("��������Ʒ������ҵ����������15λ���ֻ�30λӢ�ģ���");
    scanf("%s",ch);
    if(strlen(ch)>30&&strlen(ch)<1)
    {
        printf("�����ʽ�Ƿ������������룡");
        printf("���ٴ�������Ʒ������ҵ����������15λ���ֻ�30λӢ�ģ���");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<1)
        {
            printf("�Բ������ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    strcpy(p->company,ch);

    printf("��������Ʒ���ࣨ������5λ���ֻ�10λӢ�ģ���");
    scanf("%s",ch);
    if(strlen(ch)>10&&strlen(ch)<1)
    {
        printf("�����ʽ�Ƿ������������룡");
        printf("���ٴ�������Ʒ��Ʒ���ࣨ������15λ���ֻ�30λӢ�ģ���");
        scanf("%s",ch);
        if(strlen(ch)>10&&strlen(ch)<1)
        {
            printf("�Բ������ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    strcpy(p->type,ch);

    printf("��������Ʒ�������ڣ���ʽ��xxxx.xx.xx����");
    scanf("%s",ch);
    sscanf(ch,"%4s%*1s%2s%*1s%2s",y,m,d);
    if(strcmp(y,"2050")>0||strcmp(y,"1970")<0||strcmp(m,"01")<0||strcmp(m,"12")>0||strcmp(d,"01")<0||strcmp(d,"31")>0)
    {
        printf("����Ƿ������������룡\n");
        printf("���ٴ�������Ʒ�������ڣ���ʽ��xxxx.xx.xx����");
        scanf("%s",ch);
        sscanf(ch,"%4s%*1s%2s%*1s%2s",y,m,d);
        if(strcmp(y,"2050")>0||strcmp(y,"1970")<0||strcmp(m,"01")<0||strcmp(m,"12")>0||strcmp(d,"01")<0||strcmp(d,"31")>0)
        {
            printf("�Բ�������Ƿ������ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    strcat(p->date_manufacture,y);
    strcat(p->date_manufacture,".");
    strcat(p->date_manufacture,m);
    strcat(p->date_manufacture,".");
    strcat(p->date_manufacture,d);
    strcat(p->date_manufacture,".");

    printf("��������Ʒ�����ڣ���ʽ������or xx�£���");
    scanf("%s",ch);
    if(strcmp(ch,"0")<=0)
    {
        printf("����Ƿ������������룡\n");
        printf("��������Ʒ�����ڣ���ʽ������or xx�£���");
        scanf("%s",ch);
        if(strcmp(ch,"0")<=0)
        {
            printf("�����쳣�����ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    strcpy(p->date_keep,ch);

    printf("��������Ʒ���������λ��������");
    scanf("%d",&quanlity);
    if(quanlity<0)
    {
        printf("����Ƿ������������룡\n");
        printf("��������Ʒ���������λ��������");
        scanf("%d",&quanlity);
        if(quanlity<0)
        {
            printf("�����쳣�����ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    p->quantity = quanlity;

    printf("��������Ʒ���ۣ���ʽ��xx��ͳһ����Ҳ��ԡ�Ԫ��Ϊ������λ������");
    scanf("%lf",&price);
    if(price<0)
    {
        printf("����Ƿ������������룡\n");
        printf("��������Ʒ���ۣ���ʽ��xx��ͳһ����Ҳ��ԡ�Ԫ��Ϊ������λ������");
        scanf("%lf",&price);
        if(price<0)
        {
            printf("�����쳣�����ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    p->pirce_enter = price;

    printf("��������Ʒ�������ۼۣ���ʽ��xx��ͳһ����Ҳ��ԡ�Ԫ��Ϊ������λ������");
    scanf("%lf",&price);
    if(price<0)
    {
        printf("����Ƿ������������룡\n");
        printf("��������Ʒ�������ۼۣ���ʽ��xx��ͳһ����Ҳ��ԡ�Ԫ��Ϊ������λ������");
        scanf("%lf",&price);
        if(price<0)
        {
            printf("�����쳣�����ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    if(price < p->pirce_enter||price<0)
    {
        printf("����Ƿ����ۼ�С�ڽ��ۣ����������룡\n");
        printf("��������Ʒ�������ۼۣ���ʽ��xx��ͳһ����Ҳ��ԡ�Ԫ��Ϊ������λ������");
        scanf("%lf",&price);
        if(price < p->pirce_enter||price<0)
        {
            printf("�����쳣�����ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    p->pirce_sell = price;

    p->num = inventory_head->next->num+1;
    rear->next = p;
    p->next = NULL;

    inventory_head->next->num = inventory_head->next->num+1;
    inventory_save(inventory_head);
    }
}
void inventory_main_administration_revamp(inventory_list inventory_head,user_list mine)//�޸���Ʒ��Ϣ
{
    inventory_list p,b,guide;
    double ch_double;
    int sel,num,i,sum,ch_int;
    char ch[30],y[5],m[4],d[4];
    while(1)
    {
    guide = inventory_head->next;//ǰ��
    p = inventory_head->next;
    b = inventory_head;
    sum = p->num;
    system("cls");
    printf("����������Ҫ�޸ĵ���Ʒ��ţ���ͨ�����ҹ���ȷ����Ʒ��ţ�����-1�˳�����");
    scanf("%d",&num);
    if(num>sum&&num<0)
    {
        printf("���������޸�ʧ�ܣ�\n");
        system("pause");
        return;
    }
    if(num == -1) return;
    while(1)
    {
    printf("�����ָ�����Ʒ��Ϣ���£�\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
    inventory_main_administration_printfi(inventory_head,num);//���i������Ϣ
    printf("��ʼ�޸ģ���1.ȷ�� 2.ȡ����");
    scanf("%d",&sel);
    if(sel==2)return;
    i = num;
    p = inventory_head->next;
    b = inventory_head;
    while(i--)
    {
        b = p;
        p = p->next;
    }
    for(i=0;i<5;i++)printf("\n");
        for(i=0;i<50;i++)printf(" ");printf("�����嵥��\n\n");
        for(i=0;i<60;i++)printf(" ");printf("1.�޸���Ʒ��\n\n");
        for(i=0;i<60;i++)printf(" ");printf("2.�޸�������ҵ��\n\n");
        for(i=0;i<60;i++)printf(" ");printf("3.�޸���Ʒ����\n\n");
        for(i=0;i<60;i++)printf(" ");printf("4.�޸���������\n\n");
        for(i=0;i<60;i++)printf(" ");printf("5.�޸ı�����\n\n");
        for(i=0;i<60;i++)printf(" ");printf("6.�޸Ŀ����\n\n");
        for(i=0;i<60;i++)printf(" ");printf("7.�޸���Ʒ����\n\n");
        for(i=0;i<60;i++)printf(" ");printf("8.�޸���Ʒ�������ۼ�\n\n");
        for(i=0;i<60;i++)printf(" ");printf("9.ɾ����ǰ��Ʒ�����Ϣ\n\n");
        for(i=0;i<60;i++)printf(" ");printf("0.�˳��ò�������\n\n");
        for(i=0;i<60;i++)printf(" ");printf("����������Ҫִ�в����Ĵ��룺");
        scanf("%d",&sel);
    switch(sel)
    {
    case 1:
        printf("��ǰ��Ʒ����Ϊ��%s\n",p->name);
        printf("�������޸ĺ����Ʒ��������-1ȡ����������");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)
            continue;
        strcpy(p->name,ch);
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
        inventory_main_administration_printfi(inventory_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        inventory_save(inventory_head);
        system("pause");
        continue;
    case 2:
        printf("��ǰ��Ʒ������ҵ����Ϊ��%s\n",p->company);
        printf("�������޸ĺ����Ʒ��������-1ȡ����������");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;

        if(strlen(ch)>30&&strlen(ch)<3)
        {
        printf("�����ַ����������������룡");
        printf("���ٴ������޸ĺ����Ʒ���ƣ����ݿ�����1~15�֣���");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<3)
        {
            printf("�Բ����޸�ʧ�ܣ�\n");
            system("pause");
            return;
        }
        }
        strcpy(p->company,ch);
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
        inventory_main_administration_printfi(inventory_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        inventory_save(inventory_head);
        system("pause");
        continue;
    case 3:
        printf("��ǰ��Ʒ����Ϊ��%s\n",p->type);
        printf("�������޸ĺ����Ʒ���ࣨ����-1ȡ����������");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;
        if(strlen(ch)>30&&strlen(ch)<1)
        {
        printf("�����ʽ�Ƿ������������룡");
        printf("���ٴ�������Ʒ������ҵ����������15λ���ֻ�30λӢ�ģ���");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<1)
        {
            printf("�Բ����޸�ʧ�ܣ�\n");
            system("pause");
            return;
        }
        }
        strcpy(p->type,ch);
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
        inventory_main_administration_printfi(inventory_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        inventory_save(inventory_head);
        system("pause");
        continue;
    case 4:
        printf("��ǰ��Ʒ��������Ϊ��%s\n",p->date_manufacture);
        printf("�������޸ĺ����Ʒ�������ڣ���ʽ��xxxx.xx.xx;����-1ȡ����������");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;
        sscanf(ch,"%4s%*1s%2s%*1s%2s",y,m,d);
    if(strcmp(y,"2050")>0||strcmp(y,"1970")<0||strcmp(m,"01")<0||strcmp(m,"12")>0||strcmp(d,"01")<0||strcmp(d,"31")>0)
    {
        printf("����Ƿ������������룡\n");
        printf("���ٴ�������Ʒ�������ڣ���ʽ��xxxx.xx.xx����");
        scanf("%s",ch);
        sscanf(ch,"%4s%*1s%2s%*1s%2s",y,m,d);
        if(strcmp(y,"2050")>0||strcmp(y,"1970")<0||strcmp(m,"01")<0||strcmp(m,"12")>0||strcmp(d,"01")<0||strcmp(d,"31")>0)
        {
            printf("�Բ�������Ƿ�������ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    strcat(p->date_manufacture,y);
    strcat(p->date_manufacture,"��");
    strcat(p->date_manufacture,m);
    strcat(p->date_manufacture,"��");
    strcat(p->date_manufacture,d);
    strcat(p->date_manufacture,"��");
        strcpy(p->date_manufacture,ch);
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
        inventory_main_administration_printfi(inventory_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        inventory_save(inventory_head);
        system("pause");
        continue;
    case 5:
        printf("��ǰ��Ʒ������Ϊ��%s\n",p->date_keep);
        printf("�������޸ĺ����Ʒ�����ڣ���ʽ������or xx��;����-1ȡ����������");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;
        if(strcmp(ch,"0")<=0)
        {
        printf("����Ƿ������������룡\n");
        printf("��������Ʒ�����ڣ���ʽ������or xx�£���");
        scanf("%s",ch);
        if(strcmp(ch,"0")<=0)
        {
            printf("�����쳣������ʧ�ܣ�\n");
            return;
        }
        }
        strcpy(p->date_keep,ch);
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
        inventory_main_administration_printfi(inventory_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        inventory_save(inventory_head);
        system("pause");
        continue;
    case 6:
        printf("��ǰ��Ʒ�����Ϊ��%d\n",p->quantity);
        printf("�������޸ĺ����Ʒ�����������-1ȡ����������");
        scanf("%d",&ch_int);
        if(ch_int==-1)continue;
        if(ch_int<0)
        {
        printf("����Ƿ������������룡\n");
        printf("��������Ʒ���������λ��������");
        scanf("%d",&ch_int);
        if(ch_int<0)
        {
            printf("�����쳣������ʧ�ܣ�\n");
            system("pause");
            return;
        }
        }
        p->quantity = ch_int;
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
        inventory_main_administration_printfi(inventory_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        inventory_save(inventory_head);
        system("pause");
        continue;
    case 7:
        printf("��ǰ��Ʒ����Ϊ��%.2lf\n",p->pirce_enter);
        printf("�������޸ĺ�Ľ��ۣ�����-1ȡ����������");
        scanf("%lf",&ch_double);
        if(ch_double==-1)continue;
        if(ch_double<0)
        {
        printf("����Ƿ������������룡\n");
        printf("��������Ʒ����:");
        scanf("%lf",&ch_double);
        if(ch_double<0)
        {
            printf("�����쳣������ʧ�ܣ�\n");
            system("pause");
            return;
        }
        }
        p->pirce_enter = ch_double;
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
        inventory_main_administration_printfi(inventory_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        inventory_save(inventory_head);
        system("pause");
        continue;
    case 8:
        printf("��ǰ��Ʒ�����ۼۣ�%.2lf\n",p->pirce_sell);
        printf("�������޸ĺ����Ʒ�����ۼۣ�����-1ȡ����������");
        scanf("%lf",&ch_double);
        if(ch_double==-1)continue;

        if(ch_double<0)
    {
        printf("����Ƿ������������룡\n");
        printf("��������Ʒ�������ۼۣ�");
        scanf("%lf",&ch_double);
        if(ch_double<0)
        {
            printf("�����쳣������ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    if(ch_double < p->pirce_enter||ch_double<0)
    {
        printf("����Ƿ����ۼ�С�ڽ��ۣ����������룡\n");
        printf("��������Ʒ�������ۼۣ�");
        scanf("%lf",&ch_double);
        if(ch_double < p->pirce_enter||ch_double<0)
        {
            printf("�����쳣������ʧ�ܣ�\n");
            return;
        }
    }
    p->pirce_sell = ch_double;
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
        inventory_main_administration_printfi(inventory_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        inventory_save(inventory_head);
        system("pause");
        continue;
    case 9:
        printf("ȷ��ɾ������1.ȷ�� 2.ȡ����");
        scanf("%d",&sel);
        if(sel==2)return;
        b->next = p->next;
        free(p);
        p = b->next;
        while(p)
        {
            p->num = p->num-1;
            p = p->next;
        }
        guide->num = guide->num-1;
        printf("ɾ���ɹ���\n");
        inventory_save(inventory_head);
        system("pause");
            continue;
    case 0:
        return;
    }
    }
    }
}
void inventory_main_administration_find(inventory_list inventory_head,user_list mine)//��Ʒ����
{
    inventory_list p;
    int sel,i,answer;
    while(1)
    {
    p = inventory_head->next;
    system("cls");
    for(i=0;i<50;i++)printf(" ");printf("��Ʒ�������룺\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.ʶ����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.��Ʒ����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("3.������ҵ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("4.��Ʒ����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("5.������������\n\n");
    for(i=0;i<60;i++)printf(" ");printf("6.����С�����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("7.����ͽ���\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.�˳����ҳ���\n\n");
    for(i=0;i<40;i++)printf(" ");printf("������������ҵ���Ʒ�������룺");
    scanf("%d",&sel);
        switch(sel)
    {
    case 1:
        answer = inventory_main_administration_find_id(inventory_head,mine);
        if(answer == 0)
            {
            printf("�Բ���δ�ҵ�����Ʒ��\n");
            continue;
            }
        printf("��������ָ�����Ʒ��Ϣ���£�\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",p->id,p->name,p->company,p->type,p->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
        inventory_main_administration_printfi(inventory_head,answer);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        system("pause");
        continue;
    case 2:
        inventory_main_administration_find_name(inventory_head,mine);
        continue;
    case 3:
        inventory_main_administration_find_company(inventory_head,mine);
        continue;
    case 4:
        inventory_main_administration_find_type(inventory_head,mine);
        continue;
    case 5:
        inventory_main_administration_find_manufacture(inventory_head,mine);
        continue;
    case 6:
        inventory_main_administration_find_quantity(inventory_head,mine);
        continue;
    case 7:
        inventory_main_administration_find_pirce(inventory_head,mine);
        continue;
    case 0:
        return;
    }
    }
    return;
}
int inventory_main_administration_find_id(inventory_list inventory_head,user_list mine)//��Ʒ����-��ʶ����
{
    char ch[20];
    inventory_list p = inventory_head->next->next;//����ǰ��
    printf("������������ҵ���Ʒ��13λ�����룺");
    scanf("%s",ch);
    if(strlen(ch)>13&&strlen(ch)<13)
    {
        printf("�����ʽ�Ƿ������������룡");
        printf("���ٴ�����������ҵ���Ʒ��13λʶ���룺");
        scanf("%s",ch);
        if(strlen(ch)>13&&strlen(ch)<13)
        {
            printf("�Բ��𣡲���ʧ�ܣ�\n");
            system("pause");
            return 0;
        }
    }
    while(p)
    {
        if(strcmp(ch,p->id)==0)
            return p->num;
        p = p->next;
    }
    return 0;
}
void inventory_main_administration_find_name(inventory_list inventory_head,user_list mine)//��Ʒ����-������
{
    int like,i,j,len,len2,answer;
    char ch[30];
    inventory_list p;
    p = inventory_head->next;
    answer = 0;
    printf("����������������Ʒ���ƣ���������������3~15�֣���");
    scanf("%s",ch);
    if(strlen(ch)>30&&strlen(ch)<3)
    {
        printf("�����ַ����������������룡");
        printf("���ٴ���������������Ʒ���ƣ���������������3~15�֣���");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<3)
        {
            printf("�Բ��𣡲���Ԫ��ָ��ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    len = strlen(ch);
    printf("Ϊ���ҵ�������Ʒ��\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",p->id,p->name,p->company,p->type,p->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
    p = p->next;//����ǰ��
    while(p)
    {
        like = 0;
        len2 = strlen(p->name);
        for(i=0;i<len2;i++)
        {
            for(j=0;j<len;j++)
            {
                if(p->name[i]==ch[j])
                    like = like+1;
            }
        }
        if(like>len/2)
            {
                inventory_main_administration_printfi(inventory_head,p->num);
                answer = answer+1;
            }
        p = p->next;
    }
    if(answer==0)
        {
            system("cls");
            printf("�Բ���û���ҵ�������Ҫ�����Ʒ��\n");
        }
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        system("pause");
    return;
}
void inventory_main_administration_find_company(inventory_list inventory_head,user_list mine)//��Ʒ����-��������ҵ
{
    int like,i,j,len,len2,answer;
    char ch[30];
    inventory_list p;
    p = inventory_head->next;
    answer = 0;
    printf("��������������Ʒ��������ҵ���ƣ���������������3~15�֣���");
    scanf("%s",ch);
    if(strlen(ch)>30&&strlen(ch)<3)
    {
        printf("�����ַ����������������룡");
        printf("���ٴ�������������Ʒ��������ҵ���ƣ���������������3~15�֣���");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<3)
        {
            printf("�Բ��𣡲���Ԫ��ָ��ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    len = strlen(ch);
    printf("Ϊ���ҵ�������Ʒ��\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",p->id,p->name,p->company,p->type,p->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
    p = p->next;//����ǰ��
    while(p)
    {
        like = 0;
        len2 = strlen(p->company);
        for(i=0;i<len2;i++)
        {
            for(j=0;j<len;j++)
            {
                if(p->company[i]==ch[j])
                    like = like+1;
            }
        }
        if(like>len/2)
            {
                inventory_main_administration_printfi(inventory_head,p->num);
                answer = answer+1;
            }
        p = p->next;
    }
    if(answer==0)
        {
            system("cls");
            printf("�Բ���û���ҵ�������Ҫ�����Ʒ��\n");
        }
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        system("pause");
    return;
}
void inventory_main_administration_find_type(inventory_list inventory_head,user_list mine)//��Ʒ����-����Ʒ����
{
    int like,i,j,len,len2,answer;
    char ch[30];
    inventory_list p;
    p = inventory_head->next;
    answer = 0;
    printf("��������������Ʒ�����ͣ���������������2~8�֣���");
    scanf("%s",ch);
    if(strlen(ch)>16&&strlen(ch)<3)
    {
        printf("�����ַ����������������룡");
        printf("���ٴ�������������Ʒ�����ͣ���������������2~8�֣���");
        scanf("%s",ch);
        if(strlen(ch)>16&&strlen(ch)<3)
        {
            printf("�Բ��𣡲���Ԫ��ָ��ʧ�ܣ�\n");
            system("pause");
            return;
        }
    }
    len = strlen(ch);
    printf("Ϊ���ҵ�������Ʒ��\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",p->id,p->name,p->company,p->type,p->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
    p = p->next;//����ǰ��
    while(p)
    {
        like = 0;
        len2 = strlen(p->type);
        for(i=0;i<len2;i++)
        {
            for(j=0;j<len;j++)
            {
                if(p->type[i]==ch[j])
                    like = like + 1;
            }
        }
        if(like>1)
            {
                inventory_main_administration_printfi(inventory_head,p->num);
                answer = answer+1;
            }
        p = p->next;
    }
    if(answer==0)
        {
            system("cls");
            printf("�Բ���û���ҵ�������Ҫ�����Ʒ��\n");
        }
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        system("pause");
    return;
}
void inventory_main_administration_find_manufacture(inventory_list inventory_head,user_list mine)//��Ʒ����-����������
{
    inventory_list p;
    p = inventory_head->next;
    int answer,i;
    char y1[5],y2[5],m1[5],m2[5],d1[5],d2[5],y[5],m[5],d[5];
    printf("������������ҵ���Ʒ�����������䣨�޶�Ϊ1970��1��1�����񣩣�\n");
    printf("ʼ��    �꣺\b\b\b\b\b\b\b\b");scanf("%s",y1);
    printf("  �£�\b\b\b\b\b\b");scanf("%s",m1);
    printf("  �գ�\b\b\b\b\b\b");scanf("%s",d1);
    printf("����    �꣺\b\b\b\b\b\b\b\b");scanf("%s",y2);
    printf("  �£�\b\b\b\b\b\b");scanf("%s",m2);
    printf("  �գ�\b\b\b\b\b\b");scanf("%s",d2);
    printf("Ϊ���ҵ�������Ʒ��\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",p->id,p->name,p->company,p->type,p->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
    p = p->next;//����ǰ��
    while(p)
    {
        sscanf(p->date_manufacture,"%4s%*1s%2s%*1s%2s",y,m,d);
        if(strcmp(y1,y)<0&&strcmp(y2,y)>0)
        {
            inventory_main_administration_printfi(inventory_head,p->num);
            answer = answer+1;
            p = p->next;
            continue;
        }
        if(strcmp(y1,y)==0)
        {
            if(strcmp(m1,m)<0&&strcmp(m2,m)>0)
            {
                inventory_main_administration_printfi(inventory_head,p->num);
                answer = answer+1;
                p = p->next;
                continue;
            }
            else if(strcmp(m1,m)==0)
            {
                if(strcmp(d1,d)<=0&&strcmp(d2,d)>=0)
                {
                    inventory_main_administration_printfi(inventory_head,p->num);
                    answer = answer+1;
                    p = p->next;
                    continue;
                }
            }
        }
        if(strcmp(y2,y)==0)
        {
            if(strcmp(m1,m)<0&&strcmp(m2,m)>0)
            {
                inventory_main_administration_printfi(inventory_head,p->num);
                answer = answer+1;
                p = p->next;
                continue;
            }
            else if(strcmp(m1,m)==0)
            {
                if(strcmp(d1,d)<=0&&strcmp(d2,d)>=0)
                {
                    inventory_main_administration_printfi(inventory_head,p->num);
                    answer = answer+1;
                    p = p->next;
                    continue;
                }
            }
        }
        p = p->next;
    }
    if(answer==0)
    {
        system("pause");
        printf("�Բ���û���ҵ�������Ҫ�����Ʒ��\n");
        return;
    }
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        system("pause");
    return;
}
void inventory_main_administration_find_quantity(inventory_list inventory_head,user_list mine)//��Ʒ����-�������
{
    inventory_list p;
    int i,sel,answer = 0;
    p = inventory_head->next;
    printf("������������ҵ���Ʒ�Ŀ����Сֵ��");
    scanf("%d",&sel);
    printf("Ϊ���ҵ�������Ʒ��\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",p->id,p->name,p->company,p->type,p->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
    p = p->next;//����ǰ��
    while(p)
    {
        if(p->quantity>=sel)
        {
            inventory_main_administration_printfi(inventory_head,p->num);
            answer = answer+1;
        }
        p = p->next;
    }
    if(answer==0)
    {
        system("pause");
        printf("�Բ���û���ҵ�������Ҫ�����Ʒ��\n");
        return;
    }
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        system("pause");
    return;
}
void inventory_main_administration_find_pirce(inventory_list inventory_head,user_list mine)//��Ʒ����-����������
{
    inventory_list p;
    int i,sel,answer = 0;
    p = inventory_head->next;
    printf("������������ҵ���Ʒ�Ľ�����Сֵ��");
    scanf("%d",&sel);
    printf("Ϊ���ҵ�������Ʒ��\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",p->id,p->name,p->company,p->type,p->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
    p = p->next;//����ǰ��
    while(p)
    {
        if(p->pirce_enter>=sel)
        {
            inventory_main_administration_printfi(inventory_head,p->num);
            answer = answer+1;
        }
        p = p->next;
    }
    if(answer==0)
    {
        system("pause");
        printf("�Բ���û���ҵ�������Ҫ�����Ʒ��\n");
        return;
    }
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        system("pause");
    return;
}

void inventory_main_administration_adds(inventory_list inventory_head,user_list mine)//�������
{
    inventory_list p,rear;
    char ch[30];
    int sum;
    sum = inventory_head->next->num;
    rear = inventory_head;
    while(rear->next)
        rear = rear->next;
    printf("�����ϸ������¸�ʽҪ���������ݣ�����-1������\n");
    printf("%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-10s\n","13λʶ����","15λ����","15λ������","5λ����","XXXX.xx.xx","������","������","����","�����ۼ�");
    while(scanf("%s",ch),strcmp(ch,"-1")!=0)
    {
        p = (inventory_list)malloc(sizeof(inventory_lnode));
        strcpy(p->id,ch);
        scanf("%s%s%s%s%s%d%lf%lf",p->name,p->company,p->type,p->date_manufacture,p->date_keep,&p->quantity,&p->pirce_enter,&p->pirce_sell);
        p->num = sum+1;sum = sum+1;
        inventory_head->next->num = inventory_head->next->num+1;
        rear->next = p;
        rear = p;
    }
    rear->next = NULL;
    inventory_save(inventory_head);
    printf("�������ɹ�������Ϊ����Ŀ����Ϣ��\n");
    inventory_main_administration_ergodicity(inventory_head,mine);

}
void inventory_main_administration_de_weight(inventory_list inventory_head,user_list mine)//����ظ���Ϣ����
{
    inventory_list a,b,c,d;
    if(inventory_head->next->next!=NULL)
    a = inventory_head->next->next;//ָ���׸�������Ϣ������
    else
        return;
    if(inventory_head->next->next->next!=NULL)
    b = inventory_head->next->next->next;//ָ��ڶ���������Ϣ������
    else
        return;
    c = a;
    while(a)
    {
        while(b)
        {
            if(strcmp(a->id,b->id)==0)
            {
                a->quantity = a->quantity+b->quantity;
                inventory_head->next->num = inventory_head->next->num-1;
                d = b->next;
                while(d)
                {
                    d->num = d->num - 1;
                    d = d->next;
                }
                c->next = b->next;
                free(b);
                b = c;
            }
            c = b;
            b = b->next;
        }
        if(a->next == NULL)
            return;
        a = a->next;
        if(a->next == NULL)
            return;
        b = a->next;
    }
    return;
}

void inventory_main_administration_adds_file(inventory_list inventory_head,user_list mine)//��������������
{
    inventory_list p,rear;
    FILE *fp;
    rear = inventory_head;
    while(rear->next)
        rear = rear->next;
    printf("��ʹ�����׿�����ϵͳָ����ʽ������Ҫ��������ļ�������ΪADD Inventory information.dat,���������ļ����ڳ���ԴĿ¼��\n");
    printf("���ȫ�������������\n");
    system("pause");
    fp = fopen("ADD Inventory information.dat","r");
    if(fp == NULL)
    {
        return;
    }
    while(1)
    {
        p = (inventory_list)malloc(sizeof(inventory_lnode));
        fread(p,sizeof(inventory_lnode),1,fp);
        if(strcmp(p->id,"-1")==0)
        {
            break;
            free(p);
        }
        p->num = inventory_head->next->num + 1;
        inventory_head->next->num = inventory_head->next->num + 1;
        rear->next = p;
        rear = p;
    }
    rear->next=NULL;
    inventory_save(inventory_head);
    printf("�������������ݳɹ���\n");
    inventory_main_administration_ergodicity(inventory_head,mine);
    return;
}
void inventory_main_common(inventory_list inventory_head,user_list mine)//��ͨ������������
{
        int sel,i;
    while(1)
    {
    system("cls");
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("��ǰ�û�Ϊ��%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("��ӭ�������������ѯ����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.���ȫ�������Ʒ��Ϣ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.�����Ʒ��Ϣ����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.�˳������Ϣ�������\n\n");
    for(i=0;i<60;i++)printf(" ");printf("����������ִ�еĲ������룺");

    scanf("%d",&sel);
    switch(sel)
    {
    case 1:
        inventory_main_administration_ergodicity(inventory_head,mine);
        continue;
    case 2:
        inventory_main_administration_find(inventory_head,mine);
        continue;
    case 0:
        getchar();
        return;
    }
    return;
}
}


void commodity_main_administration(inventory_list inventory_head,commodity_list commodity_head,user_list mine)//�߼�����������
{
    int sel,i;
    while(1)
    {
    system("cls");
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("��ǰ�û�Ϊ��%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("��ӭ������߼���Ʒ����ϵͳ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.��ѯ��Ʒ&����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.��Ʒ���۳���\n\n");
    for(i=0;i<60;i++)printf(" ");printf("3.�û��˻�����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("4.���ۼ�¼��ȡ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("5.���ۼ�¼�޸�\n\n");
    for(i=0;i<60;i++)printf(" ");printf("6.���ۼ�¼����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.�˳������Ϣ�������\n\n");
    for(i=0;i<60;i++)printf(" ");printf("�������������ִ�еĲ������룺");

    scanf("%d",&sel);
    switch(sel)
    {
    case 1:
        commodity_main_administration_find(inventory_head,commodity_head,mine);
        commodity_save(commodity_head);
        inventory_save(inventory_head);
        continue;
    case 2:
        commodity_main_administration_sell(inventory_head,commodity_head,mine);
        commodity_save(commodity_head);
        inventory_save(inventory_head);
        continue;
    case 3:
        commodity_main_administration_return(inventory_head,commodity_head,mine);
        commodity_save(commodity_head);
        inventory_save(inventory_head);
        continue;
    case 4:
        commodity_main_administration_record(commodity_head,mine);
        commodity_save(commodity_head);
        inventory_save(inventory_head);
        continue;
    case 5:
        commodity_main_administration_revamp(commodity_head,mine);
        commodity_save(commodity_head);
        inventory_save(inventory_head);
        continue;
    case 6:
        commodity_main_administration_analyse(commodity_head,mine);
        commodity_save(commodity_head);
        inventory_save(inventory_head);
        continue;
    case 0:
        return;
    }
    commodity_save(commodity_head);
    inventory_save(inventory_head);
    }
    return;
}

void commodity_main_administration_find(inventory_list inventory_head,commodity_list commodity_head,user_list mine)//��ѯ������
{
    int sel,i;
    while(1)
    {
    system("cls");
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("��ǰ�û�Ϊ��%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("��ӭ����������ϵͳ��ѯ���۽���\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.������\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.����ѯ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("3.��Ʒ����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.�˳���Ʒ��ѯ����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("�������������ִ�еĲ������룺");

    scanf("%d",&sel);
    switch(sel)
    {
    case 1:
        inventory_main_administration_ergodicity(inventory_head,mine);
        continue;
    case 2:
        inventory_main_administration_find(inventory_head,mine);
        continue;
    case 3:
        commodity_main_administration_sell(inventory_head,commodity_head,mine);
        continue;
    case 0:
        return;
    }
    }
    return;
}
void commodity_main_administration_sell(inventory_list inventory_head,commodity_list commodity_head,user_list mine)//���۳���
{
    time_t rawtime;
    struct tm *timeinfo;
    commodity_list commodity,p;
    inventory_list inventory,guide;
    char ch[20],serial[12],ni[30];
    int find,sel,num,len,i,j,a,fa,answer,gi=0;//fa-���ҽ�� �ҵ�ֵ��Ϊ1 gi������ͷ�������
    double price;
    char op[20];
    guide = inventory_head->next;//��¼�����Ϣǰ��
    commodity = commodity_head->next;//����ǰ��
    while(commodity->next)
        commodity = commodity->next;

    while(1)
    {
    system("cls");
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("��ǰ�û�Ϊ��%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("��ӭ����������ϵͳ���۽���\n\n");
    for(i=0;i<60;i++)printf(" ");printf("����������ִ�еĲ������루1.���� 2.�˳�����");
    scanf("%d",&sel);
    if(sel == 2)
        break;
    else
    {
    gi = 0;

    if(commodity_head->next->num == 0)
        strcpy(serial,"000000000");
    else
    {
        strcpy(serial,commodity->serial_num);
        serial[8] = serial[8]+1;
        for(i=8;i<=0;i--)
        {
            if(serial[i]==9)
            {
                serial[i] = '0';
                serial[i-1] = serial[i-1] + 1;
            }
        }
    }
    while(1)
    {
        len = 0;
        inventory = inventory_head->next->next;//����ǰ��
        p = (commodity_list)malloc(sizeof(commodity_lnode));
        fa = 0;
        for(i=0;i<60;i++)printf(" ");printf("������������Ʒ�Ŀ��������13λʶ���루����-1������Ʒѡ������");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)
            break;
        len = strlen(ch);
        if(len == 13)
        {
            while(inventory)
            {
            if(strcmp(ch,inventory->id)==0)
            {
                if(gi==0)
                {
                    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
                    gi++;
                }
                fa = 1;
                inventory_main_administration_printfi(inventory_head,inventory->num);
                break;
            }
            inventory = inventory->next;
            }
        }
        else
        {
            transition(inventory_head->next->num,ni);
            if(strlen(ch)<strlen(ni))
            {
                a = strlen(ni) - strlen(ch);
                for(i = a,j=0;i<strlen(ni);i++,j++)
                    op[i] = ch[j];
                for(i = a-1;i>=0;i--)
                    op[i] = '0';
                op[strlen(ni)] = '\0';
                strcpy(ch,op);
            }
            if(strcmp(ni,ch)<0)
            {
                printf("%s %s\n",ni,ch);
                printf("�����������������룡\n");
                system("pause");
                continue;
            }
            //���Ǳ��������������

            if(gi==0)
                {
                    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","���",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"�����ڣ��£�","��棨����","���ۣ�Ԫ��","�����ۼۣ�Ԫ��");
                    gi++;
                }
                fa = 1;
                find = transition_ch(ch);
                while(--find)
                    inventory = inventory->next;
                inventory_main_administration_printfi(inventory_head,inventory->num);
        }
        if(fa==0)
        {
            printf("�Բ���û�в�ѯ�������Ʒ��Ϣ�����������룡\n\n");
            printf("������������Ʒ�Ŀ��������13λʶ���루����-1������Ʒѡ������");
            continue;
        }
        printf("�����빺��������");
        scanf("%d",&num);
        if(num > inventory->quantity)
        {
            printf("�����������ڿ��������������Ч��\n\n");
            printf("�Ƿ����۽�����Ʒȫ���۳�����1.ȫ���۳� 2.ȡ��������");
            scanf("%d",&sel);
            if(sel==1)
                num = inventory->quantity;
            else
                break;
        }
        printf("��������Ʒ�۳����ۣ�");
        scanf("%lf",&price);

        inventory->quantity = inventory->quantity-num;
        strcpy(p->id,inventory->id);
        strcpy(p->name,inventory->name);
        strcpy(p->company,inventory->company);
        strcpy(p->type,inventory->type);
        strcpy(p->date_manufacture,inventory->date_manufacture);
        strcpy(p->operator_name,mine->name);
        p->pirce_enter = inventory->pirce_enter;
        p->pirce_sell = price;
        p->sell_num = num;
        p->pircr_profit = (price-inventory->pirce_enter)*num;
        p->num = commodity_head->next->num+1;
        rawtime = time(&rawtime);
        timeinfo = localtime( &rawtime );
        transition((timeinfo->tm_year+1900),ch);//���ת��
        strcpy(p->date_market,ch);
        strcat(p->date_market,".");//��
        transition((timeinfo->tm_mon+1),ch);//�·�ת��
        strcat(p->date_market,ch);
        strcat(p->date_market,".");//��
        transition((timeinfo->tm_mday),ch);//����ת��
        strcat(p->date_market,ch);
        strcat(p->date_market,".");//��
        strcat(p->date_market," ");//����
        transition((timeinfo->tm_hour),ch);//Сʱת��
        strcat(p->date_market,ch);//ʱ
        strcat(p->date_market,"��");
        transition((timeinfo->tm_min),ch);//����ת��
        strcat(p->date_market,ch);//��
        strcat(p->date_market,"��");
        transition((timeinfo->tm_sec),ch);//����ת��
        strcat(p->date_market,ch);//��
        strcpy(p->serial_num,serial);//��ˮ��
        commodity_head->next->num = commodity_head->next->num+1;
        commodity->next = p;
        commodity = p;
    }
    commodity->next = NULL;
    commodity_save(commodity_head);
    inventory_save(inventory_head);

    system("cls");
    for(i=0;i<80;i++)printf(" ");printf("���ν��׼�¼\n");
    p = commodity_head->next->next;
    answer = 0;
    while(p)
    {
        if(strcmp(p->serial_num,serial)==0)
        {
            if(answer==0)
                commodity_main_administration_grade();
            answer ++;
            commodity_main_administration_printfi(commodity_head,p->num);
        }
        p = p->next;
    }
    if(answer == 0)
    {
        system("cls");
        printf("��ӭ�����´ι��٣�\n");
        system("pause");
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
    printf("���ι��������ף���������⣬������죡\n");
    system("pause");
    }
    }
    return;
}
void commodity_main_administration_return(inventory_list inventory_head,commodity_list commodity_head,user_list mine)//�˻�����
{
    time_t rawtime;
    struct tm *timeinfo;
    char serial[15],ch[20];
    commodity_list commodity,a,p;
    inventory_list inventory;
    int sel,num,i,b;
    system("cls");
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("��ǰ�û�Ϊ��%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("��ӭ�������û��˻�����\n");
    printf("��ͨ�����ۼ�¼��ѯϵͳ��ѯ����Ҫ�˻���Ʒ���۳���Ų����룺");
    scanf("%d",&sel);
    if(sel>commodity_head->next->num)
    {
        printf("���������˻�ʧ�ܣ�\n");
        system("pause");
        return;
    }
    printf("������Ϣ��\n");
    commodity_main_administration_grade();
    commodity_main_administration_printfi(commodity_head,sel);
    i = sel;
    commodity = commodity_head->next;
    while(i)
    {
        commodity = commodity->next;
        i--;
    }
    if(commodity->sell_num<0)
    {
        printf("�Բ�����ѡ���������Ϣ����Ϊ�˻���Ʒ����ֹ����˻���\n");
        system("pause");
        return;
    }
    printf("�����������˻���������-1ȡ����������");
    scanf("%d",&num);
    if(num == -1)
        return;
    if(num>commodity->sell_num)
    {
        printf("�Բ����˻��������ۻ������Ƿ�ȫ���˻�����1.ȫ���˻� 2.ȡ����\n");
        scanf("%d",&b);
        if(b == 1)
            num = commodity->sell_num;
        else
            return;
    }
    printf("��ȷ����Ʒ�Ƿ���ã�ȷ��������1����ȷ��������-1ȡ��������");
    scanf("%d",&b);
    if(b == -1)
        return;
    else
    {
        a = commodity_head->next;
        while(a->next)
            a = a->next;
        inventory = inventory_head->next;
        while(inventory)
        {
            if(strcmp(inventory->id,commodity->id)==0)
                break;
            inventory = inventory->next;
        }

        p = (commodity_list)malloc(sizeof(commodity_lnode));
        strcpy(serial,commodity->serial_num);
        inventory->quantity = inventory->quantity+num;
        strcpy(p->id,inventory->id);
        strcpy(p->name,inventory->name);
        strcpy(p->company,inventory->company);
        strcpy(p->type,inventory->type);
        strcpy(p->date_manufacture,inventory->date_manufacture);
        strcpy(p->operator_name,mine->name);
        p->pirce_enter = inventory->pirce_enter;
        p->pirce_sell = commodity->pirce_sell;
        p->sell_num = 0 - num;
        p->pircr_profit = (commodity->pirce_sell-inventory->pirce_enter) * num * (-1);
        p->num = commodity_head->next->num+1;
        rawtime = time(&rawtime);
        timeinfo = localtime( &rawtime );
        transition((timeinfo->tm_year+1900),ch);//���ת��
        strcpy(p->date_market,ch);
        strcat(p->date_market,".");//��
        transition((timeinfo->tm_mon+1),ch);//�·�ת��
        strcat(p->date_market,ch);
        strcat(p->date_market,".");//��
        transition((timeinfo->tm_mday),ch);//����ת��
        strcat(p->date_market,ch);
        strcat(p->date_market,".");//��
        strcat(p->date_market," ");//����
        transition((timeinfo->tm_hour),ch);//Сʱת��
        strcat(p->date_market,ch);//ʱ
        strcat(p->date_market,"��");
        transition((timeinfo->tm_min),ch);//����ת��
        strcat(p->date_market,ch);//��
        strcat(p->date_market,"��");
        transition((timeinfo->tm_sec),ch);//����ת��
        strcat(p->date_market,ch);//��
        strcpy(p->serial_num,serial);//��ˮ��
        commodity_head->next->num = commodity_head->next->num + 1;
        a->next = p;
        a = p;
        inventory->quantity = inventory->quantity + num;
        a->next = NULL;
    }
    printf("�˻��ɹ���\n");
    system("pause");
    return;
}
void commodity_main_administration_record(commodity_list commodity_head,user_list mine)//���׼�¼��ȡ
{
    int sel,i;
    while(1)
    {
    system("cls");
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("��ǰ�û�Ϊ��%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("��ӭ�����뽻�������ѯ����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.���ȫ�����׼�¼\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.�����ȡ���׼�¼\n\n");
    for(i=0;i<60;i++)printf(" ");printf("3.���µ�ȡ���׼�¼\n\n");
    for(i=0;i<60;i++)printf(" ");printf("4.�����ȡ���׼�¼\n\n");
    for(i=0;i<60;i++)printf(" ");printf("5.��ȡ����Ա���׼�¼\n\n");
    for(i=0;i<60;i++)printf(" ");printf("6.��ȡ�������׼�¼\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.�˳����������ѯ����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("�������������ִ�еĲ������룺");

    scanf("%d",&sel);
    switch(sel)
    {
    case 1:
        commodity_main_administration_record_all(commodity_head,mine);
        continue;
    case 2:
        commodity_main_administration_record_year(commodity_head,mine);
        continue;
    case 3:
        commodity_main_administration_record_month(commodity_head,mine);
        continue;
    case 4:
        commodity_main_administration_record_day(commodity_head,mine);
        continue;
    case 5:
        commodity_main_administration_record_seller(commodity_head,mine);
        continue;
    case 6:
        commodity_main_administration_record_order(commodity_head,mine);
        continue;
    case 0:
        return;
    }
    }
    return;
}
void commodity_main_administration_record_all(commodity_list commodity_head,user_list mine)//���׼�¼����
{
    int sum,i;
    commodity_list p;
    p = commodity_head->next;
        system("cls");
    sum = p->num;
    if(sum<=0)
    {
        for(i=0;i<15;i++)printf("\n");
        for(i=0;i<60;i++)printf(" ");printf("\n��ǰϵͳ���׼�¼����Ϊ�գ�\n");
        system("pause");
        return;
    }
    //��ͷ
    for(i=0;i<80;i++)printf(" ");printf("���׼�¼\n");
    commodity_main_administration_grade();
    p = p->next;
    while(p)
    {
        printf("%-6d%-12s%-15s%-30s%-10s%-27s%-15.2lf%-15.2lf%-15d%-15.2lf%-30s\n",p->num,p->serial_num,p->id,p->name,p->type,p->date_market,p->pirce_enter,p->pirce_sell,p->sell_num,p->pircr_profit,p->operator_name);
        p = p->next;
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
    system("pause");
    return;
}
void commodity_main_administration_record_year(commodity_list commodity_head,user_list mine)//���׼�¼�����ȡ
{
    int i,answer = 0;
    char ch[30],year[10];
    commodity_list p;
    p = commodity_head->next->next;
    printf("�����������ȡ��¼����ݣ�");
    scanf("%s",ch);
    while(p)
    {
        sscanf(p->date_market,"%4s%*s",year);
        if(strcmp(year,ch)==0)
        {
            if(answer==0)
                commodity_main_administration_grade();
            answer ++;
            commodity_main_administration_printfi(commodity_head,p->num);
        }
        p = p->next;
    }
    if(answer == 0)
    {
        system("cls");
        printf("�Բ���û���ҵ�������ݣ�\n");
        system("pause");
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
    system("pause");
    return;
}
void commodity_main_administration_record_month(commodity_list commodity_head,user_list mine)
{
    int i,answer = 0;
    char ch[30],month[12];
    commodity_list p;
    p = commodity_head->next->next;
    printf("�����������ȡ��¼�����£�****.**����");
    scanf("%s",ch);
    while(p)
    {
        sscanf(p->date_market,"%7s%*s",month);
        if(strcmp(ch,month)==0)
        {
            if(answer==0)
                commodity_main_administration_grade();
            answer ++;
            commodity_main_administration_printfi(commodity_head,p->num);
        }
        p = p->next;
    }
    if(answer == 0)
    {
        system("cls");
        printf("�Բ���û���ҵ�������ݣ�\n");
        system("pause");
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
    system("pause");
    return;
}
void commodity_main_administration_record_day(commodity_list commodity_head,user_list mine)//���׼�¼���յ�ȡ
{
    int i,answer = 0;
    char ch[30],day[15];
    commodity_list p;
    p = commodity_head->next->next;
    printf("�����������ȡ��¼�������գ�****.**.**����");
    scanf("%s",ch);
    while(p)
    {
        sscanf(p->date_market,"%10s%*s",day);
        if(strcmp(day,ch)==0)
        {
            if(answer==0)
                commodity_main_administration_grade();
            answer ++;
            commodity_main_administration_printfi(commodity_head,p->num);
        }
        p = p->next;
    }
    if(answer == 0)
    {
        system("cls");
        printf("�Բ���û���ҵ�������ݣ�\n");
        system("pause");
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
    system("pause");
    return;
}
void commodity_main_administration_record_seller(commodity_list commodity_head,user_list mine)//��ȡ����Ա���׼�¼
{
    int i,answer = 0;
    char ch[30];
    commodity_list p;
    p = commodity_head->next->next;
    printf("�����������ȡ����Ա���ۼ�¼���û�����");
    scanf("%s",ch);
    while(p)
    {
        if(strcmp(p->operator_name,ch)==0)
        {
            if(answer==0)
                commodity_main_administration_grade();
            answer ++;
            commodity_main_administration_printfi(commodity_head,p->num);
        }
        p = p->next;
    }
    if(answer == 0)
    {
        system("cls");
        printf("�Բ���û���ҵ�������ݣ�\n");
        system("pause");
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
    system("pause");
    return;
}
void commodity_main_administration_record_order(commodity_list commodity_head,user_list mine)//��ȡ�����Ž��׼�¼
{
    int i,answer = 0;
    char ch[30];
    commodity_list p;
    p = commodity_head->next->next;
    printf("�����������ȡ���ۼ�¼�Ķ����ţ�");
    scanf("%s",ch);
    while(p)
    {
        if(strcmp(p->serial_num,ch)==0)
        {
            if(answer==0)
                commodity_main_administration_grade();
            answer ++;
            commodity_main_administration_printfi(commodity_head,p->num);
        }
        p = p->next;
    }
    if(answer == 0)
    {
        system("cls");
        printf("�Բ���û���ҵ�������ݣ�\n");
        system("pause");
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
    system("pause");
    return;
}
void commodity_main_administration_revamp(commodity_list commodity_head,user_list mine)//�޸Ľ��׼�¼
{
    commodity_list p,b;
    double ch_double;
    int sel,num,i,sum,ch_int;
    char ch[30];
    while(1)
    {
    p = commodity_head->next;
    b = commodity_head;
    sum = p->num;
    system("cls");
    printf("����������Ҫ�޸ĵ�������Ʒ��ţ���ͨ�����ҹ���ȷ����ţ�����-1�˳�����");
    scanf("%d",&num);
    if(num>sum||num<0)
    {
        printf("���������޸�ʧ�ܣ�\n");
        system("pause");
        return;
    }
    if(num == -1) return;
    while(1)
    {
    printf("�����ָ�����Ʒ��Ϣ���£�\n");
    commodity_main_administration_grade();
    commodity_main_administration_printfi(commodity_head,num);//���i������Ϣ
    printf("ȷ���޸ģ���1.ȷ�� 2.ȡ����");
    scanf("%d",&sel);
    if(sel==2)return;
    i = num;
    while(i--)
    {
        b = p;
        p = p->next;
    }
        for(i=0;i<5;i++)printf("\n");
        for(i=0;i<50;i++)printf(" ");printf("�����嵥��\n\n");
        for(i=0;i<60;i++)printf(" ");printf("1.�޸���Ʒ��\n\n");
        for(i=0;i<60;i++)printf(" ");printf("2.�޸���Ʒ������ҵ��\n\n");
        for(i=0;i<60;i++)printf(" ");printf("3.�޸���Ʒ����\n\n");
        for(i=0;i<60;i++)printf(" ");printf("4.�޸���Ʒ����ʱ��\n\n");//
        for(i=0;i<60;i++)printf(" ");printf("5.�޸���Ʒ����\n\n");//
        for(i=0;i<60;i++)printf(" ");printf("6.�޸���Ʒ������\n\n");//
        for(i=0;i<60;i++)printf(" ");printf("7.�޸���Ʒ����\n\n");//
        for(i=0;i<60;i++)printf(" ");printf("8.ɾ����ǰ��Ʒ������Ϣ\n\n");//
        for(i=0;i<60;i++)printf(" ");printf("0.�˳��ò�������\n\n");
        for(i=0;i<60;i++)printf(" ");printf("����������Ҫִ�в����Ĵ��룺");
        scanf("%d",&sel);
    switch(sel)
    {
    case 1:
        printf("��ǰ��Ʒ����Ϊ��%s\n",p->name);
        printf("�������޸ĺ����Ʒ��������-1ȡ����������");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)
            continue;
        strcpy(p->name,ch);
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        commodity_save(commodity_head);
        system("pause");
        return;
    case 2:
        printf("��ǰ��Ʒ������ҵ����Ϊ��%s\n",p->company);
        printf("�������޸ĺ����Ʒ��������-1ȡ����������");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;
        if(strlen(ch)>30&&strlen(ch)<3)
        {
        printf("�����ַ����������������룡");
        printf("���ٴ������޸ĺ����Ʒ���ƣ����ݿ�����1~15�֣���");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<3)
        {
            printf("�Բ����޸�ʧ�ܣ�\n");
            system("pause");
            break;
        }
        }
        strcpy(p->company,ch);
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        commodity_save(commodity_head);
        system("pause");
        return;
    case 3:
        printf("��ǰ��Ʒ����Ϊ��%s\n",p->type);
        printf("�������޸ĺ����Ʒ���ࣨ����-1ȡ����������");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;
        if(strlen(ch)>30&&strlen(ch)<1)
        {
        printf("�����ʽ�Ƿ������������룡");
        printf("���ٴ�������Ʒ������ҵ����������15λ���ֻ�30λӢ�ģ���");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<1)
        {
            printf("�Բ����޸�ʧ�ܣ�\n");
            system("pause");
            break;
        }
        }
        strcpy(p->type,ch);
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        commodity_save(commodity_head);
        system("pause");
        return;
    case 4:
        printf("��ǰ��Ʒ��������Ϊ��%s\n",p->date_market);
        printf("�������޸ĺ����Ʒ�������ڣ���ʽ��xxxx.xx.xx xx:xx:xx;����-1ȡ����������");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;
        strcpy(p->date_market,ch);
        scanf("%s",ch);
        strcat(p->date_market," ");
        strcat(p->date_market,ch);
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        commodity_save(commodity_head);
        system("pause");
        return;
    case 5://����
        printf("��ǰ��Ʒ����Ϊ��%.2lf\n",p->pirce_enter);
        printf("�������޸ĺ����Ʒ���ۣ�����-1ȡ����������");
        scanf("%lf",&ch_double);
        if(ch_double==-1)continue;
        p->pirce_enter = ch_double;
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        commodity_save(commodity_head);
        system("pause");
        return;
    case 6://����
        printf("��ǰ��Ʒ������Ϊ��%d\n",p->sell_num);
        printf("�������޸ĺ����Ʒ������������-1ȡ����������");
        scanf("%d",&ch_int);
        if(ch_int==-1)continue;

        p->sell_num = ch_int;
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        commodity_save(commodity_head);
        system("pause");
        return;
    case 7://����
        printf("��ǰ��Ʒ����Ϊ��%.2lf\n",p->pircr_profit);
        printf("�������޸ĺ�Ľ��ۣ�����-1ȡ����������");
        scanf("%lf",&ch_double);
        if(ch_double==-1)continue;

        p->pircr_profit = ch_double;
        printf("�޸ĺ����Ʒ��ϢΪ��\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//���i������Ϣ
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        commodity_save(commodity_head);
        system("pause");
        return;
    case 8:
        printf("ȷ��ɾ������1.ȷ�� 2.ȡ����");
        scanf("%d",&sel);
        if(sel==2)return;
        b->next = p->next;
        free(p);
        p = b->next;
        while(p)
        {
            p->num = p->num-1;
            p = p->next;
        }
        commodity_head->next->num = commodity_head->next->num-1;
        printf("ɾ���ɹ���\n");
        commodity_save(commodity_head);
        system("pause");
        return;
    case 0:
        return;
    }
    }
    }
}
void commodity_main_administration_analyse(commodity_list commodity_head,user_list mine)//�����������
{
    commodity_list p;
    int i,sel;
    double sum_sell,sum_enter,sum_return,sum_loss;
    char ch[20],info[20];
    while(1)
    {
        system("cls");
        for(i=0;i<5;i++)printf("\n");
        for(i=0;i<50;i++)printf(" ");printf("�����嵥��\n\n");
        for(i=0;i<60;i++)printf(" ");printf("1.����������ͳ��\n\n");
        for(i=0;i<60;i++)printf(" ");printf("2.�¶��������ͳ��\n\n");
        for(i=0;i<60;i++)printf(" ");printf("3.һ���������ͳ��\n\n");
        for(i=0;i<60;i++)printf(" ");printf("0.�˳��ò�������\n\n");
        for(i=0;i<60;i++)printf(" ");printf("����������Ҫִ�в����Ĵ��룺");
        scanf("%d",&sel);
        p = commodity_head->next->next;//����ǰ��
        sum_sell = 0;
        sum_enter = 0;
        sum_return = 0;
        sum_loss = 0;
    switch(sel)
    {
    case 1:
        for(i=0;i<60;i++)printf(" ");printf("����������ͳ����������������ȣ�");
        scanf("%s",ch);
        while(p)
        {
            sscanf(p->date_market,"%4s%*s",info);
            if(strcmp(ch,info)==0)
            {
                if(p->sell_num>=0)
                {
                    sum_sell += p->pirce_sell;
                    sum_enter += p->pirce_enter;
                    if(p->pirce_sell<p->pirce_enter)
                        sum_loss += p->pirce_sell;
                }
                else
                {
                sum_return += p->pirce_sell;
                }
            }
            p = p->next;
        }
        for(i=0;i<5;i++)printf("\n");
        if(sum_enter==0)
        {
            for(i=0;i<50;i++)printf(" ");printf("û����֮��ص����ۼ�¼����Ч������\n");
            system("pause");
            continue;
        }
        for(i=0;i<50;i++)printf(" ");printf("%s������������ͳ�ƣ�\n\n",ch);
        for(i=0;i<50;i++)printf(" ");printf("����ȹ����۶%.2lf\n\n",sum_sell);
        for(i=0;i<50;i++)printf(" ");printf("����������ʣ������˻�����%.2f\n\n",(sum_sell-sum_enter)/sum_enter);
        for(i=0;i<50;i++)printf(" ");printf("����ȿ���%.2lf\n\n",sum_loss);
        for(i=0;i<50;i++)printf(" ");printf("������˻���%.2lf\n\n",sum_return);
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        system("pause");
        return;
    case 2:
        for(i=0;i<60;i++)printf(" ");printf("����������ͳ���¶�����������¶ȣ�xxxx.xx����");
        scanf("%s",ch);
        while(p)
        {
            sscanf(p->date_market,"%7s%*s",info);
            if(strcmp(ch,info)==0)
            {
                if(p->sell_num>=0)
                {
                    sum_sell += p->pirce_sell;
                    sum_enter += p->pirce_enter;
                    if(p->pirce_sell<p->pirce_enter)
                        sum_loss += p->pirce_sell;
                }
                else
                {
                sum_return += p->pirce_sell;
                }
            }
            p = p->next;
        }
        for(i=0;i<5;i++)printf("\n");
        if(sum_enter==0)
        {
            for(i=0;i<50;i++)printf(" ");printf("û����֮��ص����ۼ�¼����Ч������\n");
            system("pause");
            continue;
        }
        for(i=0;i<50;i++)printf(" ");printf("%s���¶��������ͳ�ƣ�\n\n",ch);
        for(i=0;i<50;i++)printf(" ");printf("���¶ȹ����۶%.2lf\n\n",sum_sell);
        for(i=0;i<50;i++)printf(" ");printf("���¶������ʣ������˻�����%.2f\n\n",(sum_sell-sum_enter)/sum_enter);
        for(i=0;i<50;i++)printf(" ");printf("���¶ȿ���%.2lf\n\n",sum_loss);
        for(i=0;i<50;i++)printf(" ");printf("���¶��˻���%.2lf\n\n",sum_return);
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        system("pause");
        return;
    case 3:
        for(i=0;i<60;i++)printf(" ");printf("����������ͳ��һ��������������ڣ�xxxx.xx.xx����");
        scanf("%s",ch);
        while(p)
        {
            sscanf(p->date_market,"%10s%*s",info);
            if(strcmp(ch,info)==0)
            {
                if(p->sell_num>=0)
                {
                    sum_sell += p->pirce_sell;
                    sum_enter += p->pirce_enter;
                    if(p->pirce_sell<p->pirce_enter)
                        sum_loss += p->pirce_sell;
                }
                else
                {
                sum_return += p->pirce_sell;
                }
            }
            p = p->next;
        }
        for(i=0;i<5;i++)printf("\n");
        if(sum_enter==0)
        {
            for(i=0;i<50;i++)printf(" ");printf("û����֮��ص����ۼ�¼����Ч������\n");
            system("pause");
            continue;
        }
        for(i=0;i<50;i++)printf(" ");printf("%s��һ���������ͳ�ƣ�\n\n",ch);
        for(i=0;i<50;i++)printf(" ");printf("���չ����۶%.2lf\n\n",sum_sell);
        for(i=0;i<50;i++)printf(" ");printf("���������ʣ������˻�����%.2f\n\n",(sum_sell-sum_enter)/sum_enter);
        for(i=0;i<50;i++)printf(" ");printf("���տ���%.2lf\n\n",sum_loss);
        for(i=0;i<50;i++)printf(" ");printf("�����˻���%.2lf\n\n",sum_return);
        for(i=0;i<120;i++)printf(" ");printf("�����ˣ�%s\n",mine->name);
        system("pause");
        return;
    case 0:
        return;
    }
    }
}
void commodity_main_administration_printfi(commodity_list commodity_head,int num)//������۱���i������Ϣ
{
    commodity_list p = commodity_head->next;//����ǰ��
    while(num--)
    {
        p = p->next;
    }
        printf("%-6d%-12s%-15s%-30s%-10s%-27s%-15.2lf%-15.2lf%-15d%-15.2lf%-30s\n",p->num,p->serial_num,p->id,p->name,p->type,p->date_market,p->pirce_enter,p->pirce_sell,p->sell_num,p->pircr_profit,p->operator_name);
    return;
}
void commodity_main_administration_grade()//���۱��ͷ
{
    printf("%-6s%-12s%-15s%-30s%-10s%-27s%-15s%-15s%-15s%-15s%-30s\n","���","������","ʶ����","��Ʒ����","��Ʒ����","��������","���","�ۼ�","������","����","������");
    return;
}
void transition(int num,char ch[10])
{
    int i,c,n;
    n = num;
    i = 0;
    while(n>0)
    {
        n = n/10;
        i++;
    }
    if(i==1)
        {
            ch[0] = '0';
            ch[1] = '0' + num;
            ch[2] = '\0';
            return;
        }
    ch[i] = '\0';
    i--;
    n = num;
    while(n>0)
    {
        c = n%10;
        n = n/10;
        ch[i] = '0' + c;
        i--;
    }
    return;
}
int transition_ch(char ch[20])//����ת�� �����ִ��ַ����鵼��Ϊ��������
{
    int num,i;
    num = 0;
    for(i=0;ch[i]!='\0';i++)
    {
        num = num * 10 + ch[i] - '0';
    }
    return num;
}
void commodity_main_common(inventory_list inventory_head,commodity_list commodity_head,user_list mine)//��ͨ����������
{
    int sel,i;
    while(1)
    {
    system("cls");
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("��ǰ�û�Ϊ��%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("��ӭ��������Ʒ����ϵͳ\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.��ѯ��Ʒ&����\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.��Ʒ���۳���\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.�˳������Ϣ�������\n\n");
    for(i=0;i<60;i++)printf(" ");printf("�������������ִ�еĲ������룺");
    scanf("%d",&sel);
    switch(sel)
    {
    case 1:
        commodity_main_administration_find(inventory_head,commodity_head,mine);
        commodity_save(commodity_head);
        inventory_save(inventory_head);
        continue;
    case 2:
        commodity_main_administration_sell(inventory_head,commodity_head,mine);
        commodity_save(commodity_head);
        inventory_save(inventory_head);
        continue;
    case 0:
        return;
    }
    commodity_save(commodity_head);
    inventory_save(inventory_head);
    }
    return;
}
