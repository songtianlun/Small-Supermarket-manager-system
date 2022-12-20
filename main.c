#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct USER//用户信息
{
    char name[20];//用户名
    char user[20];//账号
    char password[20];//密码
    char type[20];//用户类型
    int num;//数据编号/总量
    struct USER *next;
};
typedef struct USER user_lnode,*user_list;

struct INVENTORY//库存信息
{
    char id[20];//标准码为13位，此处定义20位
    char name[30];//商品名称
    char company[30];//生产企业
    char type[10];//商品分类
    char date_manufacture[20];//生产日期
    char date_keep[10];//保质期
    int quantity;//库存数量
    double pirce_enter;//标价
    double pirce_sell;//建议销售价
    int num;//数据信息总量/编号
    struct INVENTORY *next;
};
typedef struct INVENTORY inventory_lnode,*inventory_list;

struct COMMODITY//销售信息
{
    char id[20];//标准码为13位，此处定义20位
    char name[30];//商品名称
    char company[30];//生产企业
    char type[10];//商品分类
    char date_manufacture[20];//生产日期
    char date_market[30];//销售日期
    char operator_name[20];//操作人代码
    double pirce_enter;//标价
    double pirce_sell;//销售价
    int sell_num;//销售量
    double pircr_profit;//利润
    int num;//数据信息总量/编号
    char serial_num[12];//九位数购物流水号
    struct COMMODITY *next;
};
typedef struct COMMODITY commodity_lnode,*commodity_list;

void resize_window(int cols, int lines);
void clear_display();
void display_main();
void display_administration();
void display_common();

void user_load(user_list head); //载入用户数据
void user_save(user_list head); //存入用户数据到磁盘
void commodity_load(commodity_list head); //载入商品数据
void commodity_save(commodity_list head); //存入商品数据到磁盘
void inventory_load(inventory_list head); //载入库存数据
void inventory_save(inventory_list head); //存入库存数据到磁盘

int initialize(user_list user_head,commodity_list commodity_head,inventory_list inventory_head);//初始化
int loading_main(user_list head,user_list mine);//用户登陆主函数 1——高级管理 2——普通用户 -1——密码错误 -2——用户不存在
void administration_main(user_list user_head,commodity_list commodity_head,inventory_list inventory_head,user_list mine);//高级用户界面
void common_main(user_list user_head,commodity_list commodity_head,inventory_list inventory_head,user_list mine);//普通用户界面

void user_main_administration(user_list user_head,user_list mine);//高级用户界管理面
void user_main_administration_ergodicity(user_list user_head,user_list mine);//遍历用户信息
void user_main_administration_add(user_list user_head,user_list mine);//添加新用户
void user_main_administration_rank(user_list user_head,user_list mine);//身份修改
void user_main_administration_delete(user_list user_head,user_list mine);//注销用户
void user_main_administration_mine(user_list user_head,user_list mine);//我的信息
void user_main_administration_revamp(user_list user_head,user_list mine);//修改我的密码
void user_main_common(user_list user_head,user_list mine);//普通用户管理界面
void inventory_main_administration(inventory_list inventory_head,user_list mine);//高级库存情况主函数
void inventory_main_administration_ergodicity(inventory_list inventory_head,user_list mine);//遍历库存信息
void inventory_main_administration_add(inventory_list inventory_head,user_list mine);//入库
void inventory_main_administration_revamp(inventory_list inventory_head,user_list mine);//修改商品信息
void inventory_main_administration_find(inventory_list inventory_head,user_list mine);//商品查找
void inventory_main_administration_printfi(inventory_list inventory_head,int num);//输出库存表中i处的信息
int inventory_main_administration_find_id(inventory_list inventory_head,user_list mine);//商品查找-按识别码
void inventory_main_administration_find_name(inventory_list inventory_head,user_list mine);//商品查找-按名称
void inventory_main_administration_find_company(inventory_list inventory_head,user_list mine);//商品查找-按生产企业
void inventory_main_administration_find_type(inventory_list inventory_head,user_list mine);//商品查找-按商品分类
void inventory_main_administration_find_manufacture(inventory_list inventory_head,user_list mine);//商品查找-按生产日期
void inventory_main_administration_find_quantity(inventory_list inventory_head,user_list mine);//商品查找-按库存量
void inventory_main_administration_find_pirce(inventory_list inventory_head,user_list mine);//商品查找-按进价区间
void inventory_main_administration_adds(inventory_list inventory_head,user_list mine);//批量入库
void inventory_main_administration_adds_file(inventory_list inventory_head,user_list mine);//批量导入库存数据
void inventory_main_administration_de_weight(inventory_list inventory_head,user_list mine);//库存信息重复信息处理
void inventory_main_common(inventory_list inventory_head,user_list mine);//普通库存情况主函数

void commodity_main_administration(inventory_list inventory_head,commodity_list commodity_head,user_list mine);//高级销售主函数
void commodity_main_administration_find(inventory_list inventory_head,commodity_list commodity_head,user_list mine);//查询与销售
void commodity_main_administration_sell(inventory_list inventory_head,commodity_list commodity_head,user_list mine);//销售程序
void commodity_main_administration_return(inventory_list inventory_head,commodity_list commodity_head,user_list mine);//退货流程
void commodity_main_administration_record(commodity_list commodity_head,user_list mine);//交易记录调取
void commodity_main_administration_record_all(commodity_list commodity_head,user_list mine);//交易记录遍历
void commodity_main_administration_record_seller(commodity_list commodity_head,user_list mine);//调取销售员交易记录
void commodity_main_administration_record_order(commodity_list commodity_head,user_list mine);//调取订单号交易记录
void commodity_main_administration_record_year(commodity_list commodity_head,user_list mine);//交易记录按年调取
void commodity_main_administration_record_month(commodity_list commodity_head,user_list mine);//交易记录按月调取
void commodity_main_administration_record_day(commodity_list commodity_head,user_list mine);//交易记录按天调取
void commodity_main_administration_revamp(commodity_list commodity_head,user_list mine);//交易记录修改
void commodity_main_administration_analyse(commodity_list commodity_head,user_list mine);//交易情况分析
void commodity_main_administration_grade();//销售表表头
void transition(int num,char ch[10]);//类型转换 讲n位整形数字转换为字符数组放在ch中
int transition_ch(char ch[20]);//类型转换 将数字串字符数组导出为整形数字
void commodity_main_administration_printfi(commodity_list commodity_head,int num);//输出销售表中i处的信息
void commodity_main_common(inventory_list inventory_head,commodity_list commodity_head,user_list mine);//普通销售主函数

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

    resize_window(180, 80);

    while(1)
    {
    clear_display();
    display_main();

    scanf("%c",&sel);
    if(sel>'9'||sel<'0')
    {
        for(i=0;i<60;i++)printf(" ");printf("输入非法，请重新选择！\n");
        getchar();
        continue;
    }
        switch(sel)
    {
    case '1':
        {
            user_load(user_head);//加载用户信息到链表user
            commodity_load(commodity_head);//加载商品信息到链表comodity
            inventory_load(inventory_head);//加载库存信息到链表inventory
            answer = loading_main(user_head,mine);//1——高级管理 2——普通用户 -1——密码错误 -2——用户不存在
        if(answer == 1)
            administration_main(user_head,commodity_head,inventory_head,mine);//高级用户界面
        else if(answer == 2)
            common_main(user_head,commodity_head,inventory_head,mine);//普通用户界面
        else
        {
            for(i=0;i<60;i++)printf(" ");printf("请检查您的用户民和密码，若忘记，可进行初始化操作\n");
            getchar();
            continue;
        }
        continue;
        }
    case '9':
        {
            for(i=0;i<60;i++)printf(" ");printf("确定初始化系统吗？\n");
            for(i=0;i<50;i++)printf(" ");printf("继续(输入1)，将清空全部系统数据并初始化管理员\n");
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
    for(i=0;i<60;i++)printf(" ");printf("         你好！       \n");
    for(i=0;i<60;i++)printf(" ");printf("           *          \n");
    for(i=0;i<60;i++)printf(" ");printf("        *     *        \n");
    for(i=0;i<60;i++)printf(" ");printf("     *           *      \n");
    for(i=0;i<60;i++)printf(" ");printf("欢迎使用小型超市管理系统！\n\n");
    for(i=0;i<65;i++)printf(" ");printf("1.进入系统\n");
    for(i=0;i<65;i++)printf(" ");printf("9.初始化系统\n");
    for(i=0;i<65;i++)printf(" ");printf("all else.退出系统\n\n");
    for(i=0;i<55;i++)printf(" ");printf("温馨提示:如果您是第一次使用该系统，请先对系统进行初始化操作！\n\n");
    for(i=0;i<60;i++)printf(" ");printf("请键入您想要执行的操作代码：");
    return;
}

void display_administration()
{
    int i;
    for(i=0;i<60;i++)printf(" ");printf("           *           \n");
    for(i=0;i<60;i++)printf(" ");printf("        *     *        \n");
    for(i=0;i<60;i++)printf(" ");printf("     *           *     \n");
    for(i=0;i<60;i++)printf(" ");printf("    ^^   你好！ ^^    \n");
    for(i=0;i<60;i++)printf(" ");printf("     *           *     \n");
    for(i=0;i<60;i++)printf(" ");printf("        *     *        \n");
    for(i=0;i<60;i++)printf(" ");printf("           *           \n");
    for(i=0;i<60;i++)printf(" ");printf("欢迎高级管理员进入小型超市管理系统！\n\n");
    for(i=0;i<60;i++)printf(" ");printf("→1.高级用户管理界面\n\n");

    for(i=0;i<60;i++)printf(" ");printf("→2.高级库存管理界面\n\n");

    for(i=0;i<60;i++)printf(" ");printf("→3.高级销售管理界面\n\n");

    for(i=0;i<60;i++)printf(" ");printf("→0.退出系统\n\n");
    for(i=0;i<60;i++)printf(" ");printf("请输入您想程序执行的操作代码：");
    return;
}
void display_common()
{
    int i;
    for(i=0;i<60;i++)printf(" ");printf("           *           \n");
    for(i=0;i<60;i++)printf(" ");printf("        *     *        \n");
    for(i=0;i<60;i++)printf(" ");printf("     *           *     \n");
    for(i=0;i<60;i++)printf(" ");printf("    ^^   你好！ ^^    \n");
    for(i=0;i<60;i++)printf(" ");printf("     *           *     \n");
    for(i=0;i<60;i++)printf(" ");printf("        *     *        \n");
    for(i=0;i<60;i++)printf(" ");printf("           *           \n");
    for(i=0;i<60;i++)printf(" ");printf("欢迎使用小型超市管理系统！\n\n");
    for(i=0;i<60;i++)printf(" ");printf("→1.普通用户管理界面\n\n");

    for(i=0;i<60;i++)printf(" ");printf("→2.普通库存管理界面\n\n");

    for(i=0;i<60;i++)printf(" ");printf("→3.普通销售管理界面\n\n");

    for(i=0;i<60;i++)printf(" ");printf("→4.退出系统\n\n");
    for(i=0;i<60;i++)printf(" ");printf("\n请输入您想程序执行的操作代码：");
    return;
}

int initialize(user_list user_head,commodity_list commodity_head,inventory_list inventory_head)//初始化
{
    int i;
    user_list user_guide,user_first;
    commodity_list commodity_guide;
    inventory_list inventory_guide;
    for(i=0;i<60;i++)printf(" ");printf("正在初始化程序\n");

    user_guide = (user_list)malloc(sizeof(user_lnode));
    commodity_guide = (commodity_list)malloc(sizeof(commodity_lnode));
    inventory_guide = (inventory_list)malloc(sizeof(inventory_lnode));

    user_first = (user_list)malloc(sizeof(user_lnode));

    strcpy(user_first->name,"admin");
    strcpy(user_first->user,"admin");
    strcpy(user_first->password,"admin");
    strcpy(user_first->type,"administration");
    user_first->num = 1;//第一个用户的编号

    strcpy(user_guide->name,"用户名");
    strcpy(user_guide->user,"账号");
    strcpy(user_guide->password,"密码");
    strcpy(user_guide->type,"类型");
    user_guide->num = 1;//用户总量

    strcpy(commodity_guide->id,"识别码");
    strcpy(commodity_guide->name,"商品名称");
    strcpy(commodity_guide->company,"生产企业");
    strcpy(commodity_guide->type,"商品分类");
    strcpy(commodity_guide->date_manufacture,"生产日期");
    strcpy(commodity_guide->date_market,"销售日期");
    strcpy(commodity_guide->operator_name,"操作员");
    strcpy(commodity_guide->serial_num,"交易流水号");
    //strcpy(commodity_guide->sell_num,"操作员");
    //strcpy(commodity_guide->pirce_enter,"进价");
    //strcpy(commodity_guide->pirce_sell,"销售价");
    //strcpy(commodity_guide->pircr_profit,"利润");
    commodity_guide->num = 0;//数据总量

    strcpy(inventory_guide->id,"识别码");
    strcpy(inventory_guide->name,"商品名称");
    strcpy(inventory_guide->company,"生产企业");
    strcpy(inventory_guide->type,"商品分类");
    strcpy(inventory_guide->date_manufacture,"生产日期");
    strcpy(inventory_guide->date_keep,"保质期");
    //strcpy(inventory_guide->quantity,"库存数量");
    //strcpy(inventory_guide->pirce_enter,"进价");
    //strcpy(inventory_guide->pirce_sell,"建议售价");
    inventory_guide->num = 0;//数据总量

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

    for(i=0;i<60;i++)printf(" ");printf("请牢记您的初始管理员用户名及密码\n");
    for(i=0;i<60;i++)printf(" ");printf("用户名：admin\n");
    for(i=0;i<60;i++)printf(" ");printf("密码：admin\n");
    getchar();
    return -1;
}

void user_load(user_list head) //载入用户数据
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
void user_save(user_list head)//存入用户数据到磁盘
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

void commodity_load(commodity_list head) //载入商品数据
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
void commodity_save(commodity_list head) //存入商品数据到磁盘
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
void inventory_load(inventory_list head) //载入库存数据
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
void inventory_save(inventory_list head) //存入库存数据到磁盘
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

int loading_main(user_list head,user_list mine)//用户身份识别主函数 1——高级管理 2——普通用户 -1——密码错误 -2——用户不存在
{
    user_list p = head->next;
    char printuser[20],printpassword[20];
    int i=1,n;
    n = p->num;
    clear_display();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<60;i++)printf(" ");printf("欢迎使用小型超市管理系统\n\n\n");
    for(i=0;i<60;i++)printf(" ");printf("请使用您的用户名和密码登入系统！\n\n");
    for(i=0;i<60;i++)printf(" ");printf("用户名：");scanf("%s",printuser);
    for(i=0;i<60;i++)printf(" ");printf("密  码：");scanf("%s",printpassword);
    printf("\n");
    p = p->next;
    i = 1;
    while(i<=n&&p)//查找账户信息
    {
        if(strcmp(p->user,printuser)==0)
        {
            if(strcmp(p->password,printpassword)==0)
            {
                printf("成功登录，正在识别身份\n");
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
                printf("密码错误，请重新输入\n");
                printf("密  码：");
                scanf("%s",printpassword);

                if(strcmp(p->password,printpassword)==0)
                    {
                        printf("成功登录，正在识别身份\n");
                        strcpy(p->name,mine->name);
                        strcpy(p->user,mine->user);
                        strcpy(p->password,mine->password);
                        strcpy(p->type,mine->type);
                        mine->num = i;
                        if(strcmp(p->type,"administration")==0)
                            {
                                printf("尊敬的高级管理员，欢迎进入小型超市高级管理系统！\n");
                                return 1;
                            }
                        else
                            {
                                printf("尊敬的销售员，欢迎进入小型超市销售系统！\n");
                                return 2;
                            }
                    }
                    else
                    {
                        printf("拒接登录！\n");
                        getchar();
                        return -1;
                    }
                }

        }
        i++;
        p = p->next;
    }
        printf("\n用户不存在，拒绝登入！\n\n\n");
        getchar();
        return -2;
}

void administration_main(user_list user_head,commodity_list commodity_head,inventory_list inventory_head,user_list mine)//高级用户界面
{
    char sel;
    int i;
    while(1)
    {
    clear_display();
    getchar();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<80;i++)printf(" ");printf("当前用户为：%20s\n\n",mine->name);
    display_administration();

    scanf("%c",&sel);
    if(sel>'9'||sel<'0')
    {
        printf("输入非法，请重新选择！\n");
        getchar();
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

void common_main(user_list user_head,commodity_list commodity_head,inventory_list inventory_head,user_list mine)//普通用户界面
{
    char sel;
    int i;
    while(1)
    {
    clear_display();
    getchar();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<80;i++)printf(" ");printf("当前用户为：%s\n",mine->name);
    display_common();

    scanf("%c",&sel);
    if(sel>'9'||sel<'0')
    {
        printf("输入非法，请重新选择！\n");
        getchar();
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
void user_main_administration(user_list user_head,user_list mine)//高级用户界管理面
{
    int sel,i;
    while(1)
    {
    clear_display();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("当前用户为：%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("欢迎您进入高级用户信息管理程序\n\n");

    for(i=0;i<60;i++)printf(" ");printf("1.输出全部用户信息\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.添加新用户/管理员\n\n");
    for(i=0;i<60;i++)printf(" ");printf("3.变更用户身份\n\n");
    for(i=0;i<60;i++)printf(" ");printf("4.注销用户\n\n");
    for(i=0;i<60;i++)printf(" ");printf("5.输出我的账户信息\n\n");
    for(i=0;i<60;i++)printf(" ");printf("6.修改密码\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.退出用户信息管理程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("请输入您想执行的操作代码：");
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

void user_main_administration_ergodicity(user_list user_head,user_list mine)//遍历用户
{
    user_list p;
    int i;
    p = user_head->next;
    clear_display();
    for(i=0;i<30;i++)printf(" ");printf("用户清单\n");
    printf("%4s%20s%20s%20s\n\n","序号",p->name,p->user,p->type);
    p = p->next;
    while(p)
    {
        printf("%4d%20s%20s",p->num,p->name,p->user);
        if(strcmp(p->type,"administration")==0)
            printf("%20s\n\n","管理员");
        else
            printf("%20s\n\n","普通用户");

        p = p->next;
    }
    for(i=0;i<120;i++)printf(" ");printf("\n当前用户为：%s\n",mine->name);
    getchar();
    return;
}

void user_main_administration_add(user_list user_head,user_list mine)//添加新用户
{
    int sel;
    user_list p,rear=user_head->next;
    while(rear->next)
        rear = rear->next;
    p = (user_list)malloc(sizeof(user_lnode));
    printf("请输入您的新用户信息\n");
    printf("姓名：");
    scanf("%s",p->name);
    printf("账号：");
    scanf("%s",p->user);
    printf("密码：");
    scanf("%s",p->password);
    printf("请指定新用户初始身份(1.管理员 2.普通用户):");
    scanf("%d",&sel);
    if(sel == 1)
        strcpy(p->type,"administration");
    else
        strcpy(p->type,"common");
    p->num = rear->num+1;

    rear->next = p;
    p->next = NULL;
    user_head->next->num = user_head->next->num+1;
    printf("恭喜您！你是本系统的第%d位用户！\n",p->num);
    printf("你的新账号信息为：\n");
    printf("%4s%20s%20s%20s%20s\n","编号","用户名","账号","密码","用户类型");
    printf("%10d%20s%20s%20s",p->num,p->name,p->user,p->password);
    if(strcmp(p->type,"administration")==0)
        printf("%20s\n","管理员");
    else
        printf("%20s\n","普通用户");
    user_save(user_head);
    getchar();
    return;
}
void user_main_administration_rank(user_list user_head,user_list mine)//身份修改
{
    int sel,sum;
    user_list p = user_head->next;
    sum = p->num;
    printf("当前全部用户信息如下：\n");
    user_main_administration_ergodicity(user_head,mine);
    printf("\n请输入您想变更身份账号的编号：");
    scanf("%d",&sel);
    if(sel>sum)
    {
        printf("对不起！输入序号无效！\n");
        return;
    }
    if(sel==mine->num)
    {
        printf("对不起！本系统不允许当前用户修改当前用户身份！\n");
        getchar();
        return;
    }
    while(sel--)
        p = p->next;

    printf("当前用户身份为:  ");
    if(strcmp(p->type,"administration")==0)
        printf("%s\n","管理员");
    else
        printf("%s\n","普通用户");
    printf("\n是否确认修改(1.确认 2.取消修改)该用户为：");
    if(strcmp(p->type,"common")==0)
        printf("%s\n","管理员");
    else
        printf("%s\n","普通用户");
        scanf("%d",&sel);
        if(sel == 1)
                if(strcmp(p->type,"administration")==0)
                    strcpy(p->type,"common");
                else
                    strcpy(p->type,"administration");
        else
        {
            printf("操作已取消！\n");
            getchar();
            return;
        }
            printf("身份变更成功！\n");
            getchar();
        return;

}
void user_main_administration_delete(user_list user_head,user_list mine)//注销用户
{
    int sel,sum,sel2,i=0;
    user_list prior,p = user_head->next;
    sum = p->num;
    prior = p;
    printf("当前全部用户信息如下：\n");
    user_main_administration_ergodicity(user_head,mine);
    printf("\n请输入您想注销账号的编号：");
    scanf("%d",&sel);
    if(sel>sum)
    {
        printf("对不起！输入序号无效！\n");
        getchar();
        return;
    }
    if(sel==mine->num)
    {
        printf("对不起！本系统不允许当前用户注销当前用户！\n");
        getchar();
        return;
    }
    while(i<sel)
        {
            prior = p;
            p = p->next;
            i++;
        }
    printf("预备注销用户的信息为：\n");
    printf("%4s%20s%20s%20s%20s\n","编号","用户名","账号","密码","用户类型");
    printf("%10d%20s%20s%20s",p->num,p->name,p->user,p->password);
    if(strcmp(p->type,"administration")==0)
        printf("%20s\n","管理员");
    else
        printf("%20s\n","普通用户");
    printf("确认注销吗？（1.确认 2.取消）: ");
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
    printf("注销该账号成功！\n");
    getchar();
    return;
}
void user_main_administration_mine(user_list user_head,user_list mine)//我的信息
{
    printf("我的编号：%4d\n我的姓名：%20s\n我的账号：%20s\n我的身份：",mine->num,mine->name,mine->user);
    if(strcmp(mine->type,"administration")==0)
        printf("%20s\n","管理员");
    else
        printf("%20s\n","普通用户");
    getchar();
    return;
}
void user_main_administration_revamp(user_list user_head,user_list mine)//修改我的密码
{
    user_list p = user_head->next->next;//跳过前导
    char pass[20];
    int i,n,sel;
    n = mine->num;
    i = 1;
    while(i<n)
    {
        p = p->next;
        i++;
    }
    printf("请输入您当前的密码：");
    scanf("%s",pass);
    if(strcmp(pass,mine->password)==0)
    {
        printf("请输入您的新密码：");
        scanf("%s",mine->password);
        if(strcmp(mine->password,p->password)==0)
        {
            clear_display();
            printf("新密码与旧密码一致，修改失败！\n");
            return;
        }
        printf("您的新密码为：%s\n",mine->password);
        printf("确认修改（1.确认 2.取消）？");
        scanf("%d",&sel);
        if(sel == 1)
            strcpy(p->password,mine->password);
        else
            return;
        getchar();
        clear_display();
        printf("请牢记您的新密码！\n");
        getchar();
        user_save(user_head);
        return;
    }
    else
    {
        printf("您的输入有误！修改密码失败！\n");
        getchar();
    }
    return;
}

void user_main_common(user_list user_head,user_list mine)//普通用户管理界面
{
    int sel,i;
    while(1)
    {
    clear_display();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("当前用户为：%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("欢迎您进入用户信息管理程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.输出我的账户信息\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.修改密码\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.退出用户信息管理程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("请输入您想执行的操作代码：");
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

void inventory_main_administration(inventory_list inventory_head,user_list mine)//高级库存情况主函数
{
    int sel,i;
    while(1)
    {
    clear_display();
    inventory_main_administration_de_weight(inventory_head,mine);
    inventory_save(inventory_head);
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("当前用户为：%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("欢迎您进入高级库存情况管理程序\n\n");

    for(i=0;i<60;i++)printf(" ");printf("1.输出全部库存商品信息\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.库存进货登记\n\n");
    for(i=0;i<60;i++)printf(" ");printf("3.修改货品信息\n\n");
    for(i=0;i<60;i++)printf(" ");printf("4.库存商品信息查找\n\n");
    for(i=0;i<60;i++)printf(" ");printf("5.批量进货\n\n");
    for(i=0;i<60;i++)printf(" ");printf("6.外部导入库存信息\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.退出库存信息管理程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("请输入您想执行的操作代码：");
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

void inventory_main_administration_ergodicity(inventory_list inventory_head,user_list mine)//遍历库存信息
{
    inventory_list p;
    int sum,i=0;
    clear_display();
    p = inventory_head->next;
    sum = p->num;
    if(sum<=0)
    {
        for(i=0;i<15;i++)printf("\n");
        printf("\n库存数据库内当前没有库存信息，请您进货或者录入数据！\n");
        getchar();
        return;
    }
    for(i=0;i<80;i++)printf(" ");printf("库存清单\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",p->id,p->name,p->company,p->type,p->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
    p = p->next;
    while(p)
    {
        printf("%-6d%-15s%-30s%-30s%-10s%-20s%-12s%-15d%-15.2lf%-30.2lf\n",p->num,p->id,p->name,p->company,p->type,p->date_manufacture,p->date_keep,p->quantity,p->pirce_enter,p->pirce_sell);
        p = p->next;
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
    getchar();
    return;
}

void inventory_main_administration_printfi(inventory_list inventory_head,int num)//输出库存表中i处的信息
{
    inventory_list p = inventory_head->next;//跳过前导
    while(num--)
    {
        p = p->next;
    }
        printf("%-6d%-15s%-30s%-30s%-10s%-20s%-12s%-15d%-15.2lf%-30.2lf\n",p->num,p->id,p->name,p->company,p->type,p->date_manufacture,p->date_keep,p->quantity,p->pirce_enter,p->pirce_sell);
    return;
}
void inventory_main_administration_add(inventory_list inventory_head,user_list mine)//入库
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
    printf("当您输入-1时停止入库！\n");
    printf("请输入入库商品的13位识别码：");
    scanf("%s",ch);
    if(strcmp(ch,"-1")==0) return;
    if(strlen(ch)>13&&strlen(ch)<13)
    {
        printf("输入格式非法，请重新输入！");
        printf("请再次输入入库商品的13位识别码：");
        scanf("%s",ch);
        if(strlen(ch)>13&&strlen(ch)<13)
        {
            printf("对不起！入库失败！\n");
            getchar();
            return;
        }
    }
    strcpy(p->id,ch);

    printf("请输入商品姓名（控制在15位汉字或30位英文）：");
    scanf("%s",ch);
    if(strlen(ch)>30&&strlen(ch)<1)
    {
        printf("输入格式非法，请重新输入！");
        printf("请再次输入商品姓名（控制在15位汉字或30位英文）：");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<1)
        {
            printf("对不起！入库失败！\n");
            getchar();
            return;
        }
    }
    strcpy(p->name,ch);

    printf("请输入商品生产企业名（控制在15位汉字或30位英文）：");
    scanf("%s",ch);
    if(strlen(ch)>30&&strlen(ch)<1)
    {
        printf("输入格式非法，请重新输入！");
        printf("请再次输入商品生产企业名（控制在15位汉字或30位英文）：");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<1)
        {
            printf("对不起！入库失败！\n");
            getchar();
            return;
        }
    }
    strcpy(p->company,ch);

    printf("请输入商品分类（控制在5位汉字或10位英文）：");
    scanf("%s",ch);
    if(strlen(ch)>10&&strlen(ch)<1)
    {
        printf("输入格式非法，请重新输入！");
        printf("请再次输入商品商品分类（控制在15位汉字或30位英文）：");
        scanf("%s",ch);
        if(strlen(ch)>10&&strlen(ch)<1)
        {
            printf("对不起！入库失败！\n");
            getchar();
            return;
        }
    }
    strcpy(p->type,ch);

    printf("请输入商品生产日期（格式：xxxx.xx.xx）：");
    scanf("%s",ch);
    sscanf(ch,"%4s%*1s%2s%*1s%2s",y,m,d);
    if(strcmp(y,"2050")>0||strcmp(y,"1970")<0||strcmp(m,"01")<0||strcmp(m,"12")>0||strcmp(d,"01")<0||strcmp(d,"31")>0)
    {
        printf("输入非法，请重新输入！\n");
        printf("请再次输入商品生产日期（格式：xxxx.xx.xx）：");
        scanf("%s",ch);
        sscanf(ch,"%4s%*1s%2s%*1s%2s",y,m,d);
        if(strcmp(y,"2050")>0||strcmp(y,"1970")<0||strcmp(m,"01")<0||strcmp(m,"12")>0||strcmp(d,"01")<0||strcmp(d,"31")>0)
        {
            printf("对不起！输入非法！入库失败！\n");
            getchar();
            return;
        }
    }
    strcat(p->date_manufacture,y);
    strcat(p->date_manufacture,".");
    strcat(p->date_manufacture,m);
    strcat(p->date_manufacture,".");
    strcat(p->date_manufacture,d);
    strcat(p->date_manufacture,".");

    printf("请输入商品保质期（格式：永久or xx月）：");
    scanf("%s",ch);
    if(strcmp(ch,"0")<=0)
    {
        printf("输入非法！请重新输入！\n");
        printf("请输入商品保质期（格式：永久or xx月）：");
        scanf("%s",ch);
        if(strcmp(ch,"0")<=0)
        {
            printf("数据异常！入库失败！\n");
            getchar();
            return;
        }
    }
    strcpy(p->date_keep,ch);

    printf("请输入商品入库量（单位：件）：");
    scanf("%d",&quanlity);
    if(quanlity<0)
    {
        printf("输入非法！请重新输入！\n");
        printf("请输入商品入库量（单位：件）：");
        scanf("%d",&quanlity);
        if(quanlity<0)
        {
            printf("数据异常！入库失败！\n");
            getchar();
            return;
        }
    }
    p->quantity = quanlity;

    printf("请输入商品进价（格式：xx（统一人民币并以“元”为计量单位））：");
    scanf("%lf",&price);
    if(price<0)
    {
        printf("输入非法！请重新输入！\n");
        printf("请输入商品进价（格式：xx（统一人民币并以“元”为计量单位））：");
        scanf("%lf",&price);
        if(price<0)
        {
            printf("数据异常！入库失败！\n");
            getchar();
            return;
        }
    }
    p->pirce_enter = price;

    printf("请输入商品建议零售价（格式：xx（统一人民币并以“元”为计量单位））：");
    scanf("%lf",&price);
    if(price<0)
    {
        printf("输入非法！请重新输入！\n");
        printf("请输入商品建议零售价（格式：xx（统一人民币并以“元”为计量单位））：");
        scanf("%lf",&price);
        if(price<0)
        {
            printf("数据异常！入库失败！\n");
            getchar();
            return;
        }
    }
    if(price < p->pirce_enter||price<0)
    {
        printf("输入非法！售价小于进价！请重新输入！\n");
        printf("请输入商品建议零售价（格式：xx（统一人民币并以“元”为计量单位））：");
        scanf("%lf",&price);
        if(price < p->pirce_enter||price<0)
        {
            printf("数据异常！入库失败！\n");
            getchar();
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
void inventory_main_administration_revamp(inventory_list inventory_head,user_list mine)//修改商品信息
{
    inventory_list p,b,guide;
    double ch_double;
    int sel,num,i,sum,ch_int;
    char ch[30],y[5],m[4],d[4];
    while(1)
    {
    guide = inventory_head->next;//前导
    p = inventory_head->next;
    b = inventory_head;
    sum = p->num;
    clear_display();
    printf("请输入您想要修改的商品编号（可通过查找功能确定商品编号：输入-1退出）：");
    scanf("%d",&num);
    if(num>sum&&num<0)
    {
        printf("输入有误，修改失败！\n");
        getchar();
        return;
    }
    if(num == -1) return;
    while(1)
    {
    printf("该序号指向的商品信息如下：\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
    inventory_main_administration_printfi(inventory_head,num);//输出i处的信息
    printf("开始修改？（1.确认 2.取消）");
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
        for(i=0;i<50;i++)printf(" ");printf("操作清单：\n\n");
        for(i=0;i<60;i++)printf(" ");printf("1.修改商品名\n\n");
        for(i=0;i<60;i++)printf(" ");printf("2.修改生产企业名\n\n");
        for(i=0;i<60;i++)printf(" ");printf("3.修改商品分类\n\n");
        for(i=0;i<60;i++)printf(" ");printf("4.修改生产日期\n\n");
        for(i=0;i<60;i++)printf(" ");printf("5.修改保质期\n\n");
        for(i=0;i<60;i++)printf(" ");printf("6.修改库存量\n\n");
        for(i=0;i<60;i++)printf(" ");printf("7.修改商品进价\n\n");
        for(i=0;i<60;i++)printf(" ");printf("8.修改商品建议零售价\n\n");
        for(i=0;i<60;i++)printf(" ");printf("9.删除当前商品库存信息\n\n");
        for(i=0;i<60;i++)printf(" ");printf("0.退出该操作程序\n\n");
        for(i=0;i<60;i++)printf(" ");printf("请输入您想要执行操作的代码：");
        scanf("%d",&sel);
    switch(sel)
    {
    case 1:
        printf("当前商品名称为：%s\n",p->name);
        printf("请输入修改后的商品名（输入-1取消操作）：");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)
            continue;
        strcpy(p->name,ch);
        printf("修改后的商品信息为：\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
        inventory_main_administration_printfi(inventory_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        inventory_save(inventory_head);
        getchar();
        continue;
    case 2:
        printf("当前商品生产企业名称为：%s\n",p->company);
        printf("请输入修改后的商品名（输入-1取消操作）：");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;

        if(strlen(ch)>30&&strlen(ch)<3)
        {
        printf("输入字符过长，请重新输入！");
        printf("请再次输入修改后的商品名称（内容控制在1~15字）：");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<3)
        {
            printf("对不起！修改失败！\n");
            getchar();
            return;
        }
        }
        strcpy(p->company,ch);
        printf("修改后的商品信息为：\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
        inventory_main_administration_printfi(inventory_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        inventory_save(inventory_head);
        getchar();
        continue;
    case 3:
        printf("当前商品分类为：%s\n",p->type);
        printf("请输入修改后的商品分类（输入-1取消操作）：");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;
        if(strlen(ch)>30&&strlen(ch)<1)
        {
        printf("输入格式非法，请重新输入！");
        printf("请再次输入商品生产企业名（控制在15位汉字或30位英文）：");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<1)
        {
            printf("对不起！修改失败！\n");
            getchar();
            return;
        }
        }
        strcpy(p->type,ch);
        printf("修改后的商品信息为：\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
        inventory_main_administration_printfi(inventory_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        inventory_save(inventory_head);
        getchar();
        continue;
    case 4:
        printf("当前商品生产日期为：%s\n",p->date_manufacture);
        printf("请输入修改后的商品生产日期（格式：xxxx.xx.xx;输入-1取消操作）：");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;
        sscanf(ch,"%4s%*1s%2s%*1s%2s",y,m,d);
    if(strcmp(y,"2050")>0||strcmp(y,"1970")<0||strcmp(m,"01")<0||strcmp(m,"12")>0||strcmp(d,"01")<0||strcmp(d,"31")>0)
    {
        printf("输入非法，请重新输入！\n");
        printf("请再次输入商品生产日期（格式：xxxx.xx.xx）：");
        scanf("%s",ch);
        sscanf(ch,"%4s%*1s%2s%*1s%2s",y,m,d);
        if(strcmp(y,"2050")>0||strcmp(y,"1970")<0||strcmp(m,"01")<0||strcmp(m,"12")>0||strcmp(d,"01")<0||strcmp(d,"31")>0)
        {
            printf("对不起！输入非法！操作失败！\n");
            getchar();
            return;
        }
    }
    strcat(p->date_manufacture,y);
    strcat(p->date_manufacture,"年");
    strcat(p->date_manufacture,m);
    strcat(p->date_manufacture,"月");
    strcat(p->date_manufacture,d);
    strcat(p->date_manufacture,"日");
        strcpy(p->date_manufacture,ch);
        printf("修改后的商品信息为：\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
        inventory_main_administration_printfi(inventory_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        inventory_save(inventory_head);
        getchar();
        continue;
    case 5:
        printf("当前商品保质期为：%s\n",p->date_keep);
        printf("请输入修改后的商品保质期（格式：永久or xx月;输入-1取消操作）：");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;
        if(strcmp(ch,"0")<=0)
        {
        printf("输入非法！请重新输入！\n");
        printf("请输入商品保质期（格式：永久or xx月）：");
        scanf("%s",ch);
        if(strcmp(ch,"0")<=0)
        {
            printf("数据异常！操作失败！\n");
            return;
        }
        }
        strcpy(p->date_keep,ch);
        printf("修改后的商品信息为：\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
        inventory_main_administration_printfi(inventory_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        inventory_save(inventory_head);
        getchar();
        continue;
    case 6:
        printf("当前商品库存量为：%d\n",p->quantity);
        printf("请输入修改后的商品库存量（输入-1取消操作）：");
        scanf("%d",&ch_int);
        if(ch_int==-1)continue;
        if(ch_int<0)
        {
        printf("输入非法！请重新输入！\n");
        printf("请输入商品库存量（单位：件）：");
        scanf("%d",&ch_int);
        if(ch_int<0)
        {
            printf("数据异常！操作失败！\n");
            getchar();
            return;
        }
        }
        p->quantity = ch_int;
        printf("修改后的商品信息为：\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
        inventory_main_administration_printfi(inventory_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        inventory_save(inventory_head);
        getchar();
        continue;
    case 7:
        printf("当前商品进价为：%.2lf\n",p->pirce_enter);
        printf("请输入修改后的进价（输入-1取消操作）：");
        scanf("%lf",&ch_double);
        if(ch_double==-1)continue;
        if(ch_double<0)
        {
        printf("输入非法！请重新输入！\n");
        printf("请输入商品进价:");
        scanf("%lf",&ch_double);
        if(ch_double<0)
        {
            printf("数据异常！操作失败！\n");
            getchar();
            return;
        }
        }
        p->pirce_enter = ch_double;
        printf("修改后的商品信息为：\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
        inventory_main_administration_printfi(inventory_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        inventory_save(inventory_head);
        getchar();
        continue;
    case 8:
        printf("当前商品建议售价：%.2lf\n",p->pirce_sell);
        printf("请输入修改后的商品建议售价（输入-1取消操作）：");
        scanf("%lf",&ch_double);
        if(ch_double==-1)continue;

        if(ch_double<0)
    {
        printf("输入非法！请重新输入！\n");
        printf("请输入商品建议零售价：");
        scanf("%lf",&ch_double);
        if(ch_double<0)
        {
            printf("数据异常！操作失败！\n");
            getchar();
            return;
        }
    }
    if(ch_double < p->pirce_enter||ch_double<0)
    {
        printf("输入非法！售价小于进价！请重新输入！\n");
        printf("请输入商品建议零售价：");
        scanf("%lf",&ch_double);
        if(ch_double < p->pirce_enter||ch_double<0)
        {
            printf("数据异常！操作失败！\n");
            return;
        }
    }
    p->pirce_sell = ch_double;
        printf("修改后的商品信息为：\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
        inventory_main_administration_printfi(inventory_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        inventory_save(inventory_head);
        getchar();
        continue;
    case 9:
        printf("确认删除？（1.确认 2.取消）");
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
        printf("删除成功！\n");
        inventory_save(inventory_head);
        getchar();
            continue;
    case 0:
        return;
    }
    }
    }
}
void inventory_main_administration_find(inventory_list inventory_head,user_list mine)//商品查找
{
    inventory_list p;
    int sel,i,answer;
    while(1)
    {
    p = inventory_head->next;
    clear_display();
    for(i=0;i<50;i++)printf(" ");printf("商品特征代码：\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.识别码\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.商品名称\n\n");
    for(i=0;i<60;i++)printf(" ");printf("3.生产企业\n\n");
    for(i=0;i<60;i++)printf(" ");printf("4.商品分类\n\n");
    for(i=0;i<60;i++)printf(" ");printf("5.生产日期区间\n\n");
    for(i=0;i<60;i++)printf(" ");printf("6.按最小库存量\n\n");
    for(i=0;i<60;i++)printf(" ");printf("7.按最低进价\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.退出查找程序\n\n");
    for(i=0;i<40;i++)printf(" ");printf("请输入您想查找的商品特征代码：");
    scanf("%d",&sel);
        switch(sel)
    {
    case 1:
        answer = inventory_main_administration_find_id(inventory_head,mine);
        if(answer == 0)
            {
            printf("对不起，未找到此商品！\n");
            continue;
            }
        printf("该特征码指向的商品信息如下：\n");
        printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",p->id,p->name,p->company,p->type,p->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
        inventory_main_administration_printfi(inventory_head,answer);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        getchar();
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
int inventory_main_administration_find_id(inventory_list inventory_head,user_list mine)//商品查找-按识别码
{
    char ch[20];
    inventory_list p = inventory_head->next->next;//跳过前导
    printf("请输入您想查找的商品的13位特征码：");
    scanf("%s",ch);
    if(strlen(ch)>13&&strlen(ch)<13)
    {
        printf("输入格式非法，请重新输入！");
        printf("请再次输入您想查找的商品的13位识别码：");
        scanf("%s",ch);
        if(strlen(ch)>13&&strlen(ch)<13)
        {
            printf("对不起！查找失败！\n");
            getchar();
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
void inventory_main_administration_find_name(inventory_list inventory_head,user_list mine)//商品查找-按名称
{
    int like,i,j,len,len2,answer;
    char ch[30];
    inventory_list p;
    p = inventory_head->next;
    answer = 0;
    printf("请输入欲搜索的商品名称（控制搜索内容在3~15字）：");
    scanf("%s",ch);
    if(strlen(ch)>30&&strlen(ch)<3)
    {
        printf("输入字符过长，请重新输入！");
        printf("请再次输入欲搜索的商品名称（控制搜索内容在3~15字）：");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<3)
        {
            printf("对不起！查找元素指定失败！\n");
            getchar();
            return;
        }
    }
    len = strlen(ch);
    printf("为您找到如下商品：\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",p->id,p->name,p->company,p->type,p->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
    p = p->next;//跳过前导
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
            clear_display();
            printf("对不起，没有找到符合您要求的商品！\n");
        }
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        getchar();
    return;
}
void inventory_main_administration_find_company(inventory_list inventory_head,user_list mine)//商品查找-按生产企业
{
    int like,i,j,len,len2,answer;
    char ch[30];
    inventory_list p;
    p = inventory_head->next;
    answer = 0;
    printf("请输入欲搜索商品的生产企业名称（控制搜索内容在3~15字）：");
    scanf("%s",ch);
    if(strlen(ch)>30&&strlen(ch)<3)
    {
        printf("输入字符过长，请重新输入！");
        printf("请再次输入欲搜索商品的生产企业名称（控制搜索内容在3~15字）：");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<3)
        {
            printf("对不起！查找元素指定失败！\n");
            getchar();
            return;
        }
    }
    len = strlen(ch);
    printf("为您找到如下商品：\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",p->id,p->name,p->company,p->type,p->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
    p = p->next;//跳过前导
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
            clear_display();
            printf("对不起，没有找到符合您要求的商品！\n");
        }
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        getchar();
    return;
}
void inventory_main_administration_find_type(inventory_list inventory_head,user_list mine)//商品查找-按商品分类
{
    int like,i,j,len,len2,answer;
    char ch[30];
    inventory_list p;
    p = inventory_head->next;
    answer = 0;
    printf("请输入欲搜索商品的类型（控制搜索内容在2~8字）：");
    scanf("%s",ch);
    if(strlen(ch)>16&&strlen(ch)<3)
    {
        printf("输入字符过长，请重新输入！");
        printf("请再次输入欲搜索商品的类型（控制搜索内容在2~8字）：");
        scanf("%s",ch);
        if(strlen(ch)>16&&strlen(ch)<3)
        {
            printf("对不起！查找元素指定失败！\n");
            getchar();
            return;
        }
    }
    len = strlen(ch);
    printf("为您找到如下商品：\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",p->id,p->name,p->company,p->type,p->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
    p = p->next;//跳过前导
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
            clear_display();
            printf("对不起，没有找到符合您要求的商品！\n");
        }
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        getchar();
    return;
}
void inventory_main_administration_find_manufacture(inventory_list inventory_head,user_list mine)//商品查找-按生产日期
{
    inventory_list p;
    p = inventory_head->next;
    int answer,i;
    char y1[5],y2[5],m1[5],m2[5],d1[5],d2[5],y[5],m[5],d[5];
    printf("请输入您想查找的商品生产日期区间（限度为1970年1月1日至今）：\n");
    printf("始于    年：\b\b\b\b\b\b\b\b");scanf("%s",y1);
    printf("  月：\b\b\b\b\b\b");scanf("%s",m1);
    printf("  日：\b\b\b\b\b\b");scanf("%s",d1);
    printf("终于    年：\b\b\b\b\b\b\b\b");scanf("%s",y2);
    printf("  月：\b\b\b\b\b\b");scanf("%s",m2);
    printf("  日：\b\b\b\b\b\b");scanf("%s",d2);
    printf("为您找到如下商品：\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",p->id,p->name,p->company,p->type,p->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
    p = p->next;//跳过前导
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
        getchar();
        printf("对不起！没有找到符合您要求的商品！\n");
        return;
    }
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        getchar();
    return;
}
void inventory_main_administration_find_quantity(inventory_list inventory_head,user_list mine)//商品查找-按库存量
{
    inventory_list p;
    int i,sel,answer = 0;
    p = inventory_head->next;
    printf("请输入您想查找的商品的库存最小值：");
    scanf("%d",&sel);
    printf("为您找到如下商品：\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",p->id,p->name,p->company,p->type,p->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
    p = p->next;//跳过前导
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
        getchar();
        printf("对不起！没有找到符合您要求的商品！\n");
        return;
    }
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        getchar();
    return;
}
void inventory_main_administration_find_pirce(inventory_list inventory_head,user_list mine)//商品查找-按进价区间
{
    inventory_list p;
    int i,sel,answer = 0;
    p = inventory_head->next;
    printf("请输入您想查找的商品的进价最小值：");
    scanf("%d",&sel);
    printf("为您找到如下商品：\n");
    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",p->id,p->name,p->company,p->type,p->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
    p = p->next;//跳过前导
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
        getchar();
        printf("对不起！没有找到符合您要求的商品！\n");
        return;
    }
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        getchar();
    return;
}

void inventory_main_administration_adds(inventory_list inventory_head,user_list mine)//批量入库
{
    inventory_list p,rear;
    char ch[30];
    int sum;
    sum = inventory_head->next->num;
    rear = inventory_head;
    while(rear->next)
        rear = rear->next;
    printf("请您严格按照以下格式要求输入数据，并以-1结束！\n");
    printf("%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-10s\n","13位识别码","15位名称","15位生产商","5位类型","XXXX.xx.xx","保质期","库存件数","进价","建议售价");
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
    printf("批量入库成功，以下为入库后的库存信息：\n");
    inventory_main_administration_ergodicity(inventory_head,mine);

}
void inventory_main_administration_de_weight(inventory_list inventory_head,user_list mine)//库存重复信息处理
{
    inventory_list a,b,c,d;
    if(inventory_head->next->next!=NULL)
    a = inventory_head->next->next;//指向首个包含信息的链表
    else
        return;
    if(inventory_head->next->next->next!=NULL)
    b = inventory_head->next->next->next;//指向第二个包含信息的链表
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

void inventory_main_administration_adds_file(inventory_list inventory_head,user_list mine)//批量导入库存数据
{
    inventory_list p,rear;
    FILE *fp;
    rear = inventory_head;
    while(rear->next)
        rear = rear->next;
    printf("请使用配套库存管理系统指定格式将符合要求的数据文件重命名为ADD Inventory information.dat,并将数据文件放在程序源目录！\n");
    printf("完成全部工作请继续：\n");
    getchar();
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
    printf("批量导入库存数据成功！\n");
    inventory_main_administration_ergodicity(inventory_head,mine);
    return;
}
void inventory_main_common(inventory_list inventory_head,user_list mine)//普通库存情况主函数
{
        int sel,i;
    while(1)
    {
    clear_display();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("当前用户为：%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("欢迎您进入库存情况查询程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.输出全部库存商品信息\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.库存商品信息查找\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.退出库存信息管理程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("请输入您想执行的操作代码：");

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


void commodity_main_administration(inventory_list inventory_head,commodity_list commodity_head,user_list mine)//高级销售主函数
{
    int sel,i;
    while(1)
    {
    clear_display();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("当前用户为：%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("欢迎您进入高级商品销售系统\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.查询商品&销售\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.商品销售程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("3.用户退货程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("4.销售记录调取\n\n");
    for(i=0;i<60;i++)printf(" ");printf("5.销售记录修改\n\n");
    for(i=0;i<60;i++)printf(" ");printf("6.销售记录分析\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.退出库存信息管理程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("请输入您想程序执行的操作代码：");

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

void commodity_main_administration_find(inventory_list inventory_head,commodity_list commodity_head,user_list mine)//查询与销售
{
    int sel,i;
    while(1)
    {
    clear_display();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("当前用户为：%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("欢迎您进入销售系统查询销售界面\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.库存遍历\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.库存查询\n\n");
    for(i=0;i<60;i++)printf(" ");printf("3.商品销售\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.退出商品查询界面\n\n");
    for(i=0;i<60;i++)printf(" ");printf("请输入您想程序执行的操作代码：");

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
void commodity_main_administration_sell(inventory_list inventory_head,commodity_list commodity_head,user_list mine)//销售程序
{
    time_t rawtime;
    struct tm *timeinfo;
    commodity_list commodity,p;
    inventory_list inventory,guide;
    char ch[20],serial[12],ni[30];
    int find,sel,num,len,i,j,a,fa,answer,gi=0;//fa-查找结果 找到值赋为1 gi——表头输出次数
    double price;
    char op[20];
    guide = inventory_head->next;//记录库存信息前导
    commodity = commodity_head->next;//跳过前导
    while(commodity->next)
        commodity = commodity->next;

    while(1)
    {
    clear_display();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("当前用户为：%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("欢迎您进入销售系统销售界面\n\n");
    for(i=0;i<60;i++)printf(" ");printf("请输入您想执行的操作代码（1.购物 2.退出）：");
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
        inventory = inventory_head->next->next;//跳过前导
        p = (commodity_list)malloc(sizeof(commodity_lnode));
        fa = 0;
        for(i=0;i<60;i++)printf(" ");printf("请输入销售商品的库存代码或者13位识别码（输入-1结束商品选购）：");
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
                    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
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
                printf("输入有误，请重新输入！\n");
                getchar();
                continue;
            }
            //考虑编号输入有误的情况

            if(gi==0)
                {
                    printf("%-6s%-15s%-30s%-30s%-10s%-20s%-12s%-15s%-15s%-15s\n","编号",guide->id,guide->name,guide->company,guide->type,guide->date_manufacture,"保质期（月）","库存（件）","进价（元）","建议售价（元）");
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
            printf("对不起，没有查询到相关商品信息，请重新输入！\n\n");
            printf("请输入销售商品的库存代码或者13位识别码（输入-1结束商品选购）：");
            continue;
        }
        printf("请输入购物数量：");
        scanf("%d",&num);
        if(num > inventory->quantity)
        {
            printf("销售数量大于库存数量，操作无效！\n\n");
            printf("是否销售将该商品全部售出？（1.全部售出 2.取消操作）");
            scanf("%d",&sel);
            if(sel==1)
                num = inventory->quantity;
            else
                break;
        }
        printf("请输入商品售出单价：");
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
        transition((timeinfo->tm_year+1900),ch);//年份转换
        strcpy(p->date_market,ch);
        strcat(p->date_market,".");//年
        transition((timeinfo->tm_mon+1),ch);//月份转换
        strcat(p->date_market,ch);
        strcat(p->date_market,".");//月
        transition((timeinfo->tm_mday),ch);//日子转换
        strcat(p->date_market,ch);
        strcat(p->date_market,".");//日
        strcat(p->date_market," ");//留白
        transition((timeinfo->tm_hour),ch);//小时转换
        strcat(p->date_market,ch);//时
        strcat(p->date_market,"：");
        transition((timeinfo->tm_min),ch);//分钟转换
        strcat(p->date_market,ch);//分
        strcat(p->date_market,"：");
        transition((timeinfo->tm_sec),ch);//秒数转换
        strcat(p->date_market,ch);//秒
        strcpy(p->serial_num,serial);//流水号
        commodity_head->next->num = commodity_head->next->num+1;
        commodity->next = p;
        commodity = p;
    }
    commodity->next = NULL;
    commodity_save(commodity_head);
    inventory_save(inventory_head);

    clear_display();
    for(i=0;i<80;i++)printf(" ");printf("本次交易记录\n");
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
        clear_display();
        printf("欢迎您的下次光临！\n");
        getchar();
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
    printf("本次购物结束！祝您购物满意，心情愉快！\n");
    getchar();
    }
    }
    return;
}
void commodity_main_administration_return(inventory_list inventory_head,commodity_list commodity_head,user_list mine)//退货流程
{
    time_t rawtime;
    struct tm *timeinfo;
    char serial[15],ch[20];
    commodity_list commodity,a,p;
    inventory_list inventory;
    int sel,num,i,b;
    clear_display();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("当前用户为：%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("欢迎您进入用户退货程序\n");
    printf("请通过销售记录查询系统查询你想要退货商品的售出编号并输入：");
    scanf("%d",&sel);
    if(sel>commodity_head->next->num)
    {
        printf("输入有误，退货失败！\n");
        getchar();
        return;
    }
    printf("订单信息：\n");
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
        printf("对不起，您选择的销售信息编码为退货商品，禁止多次退货！\n");
        getchar();
        return;
    }
    printf("请输入您的退货量（输入-1取消操作）：");
    scanf("%d",&num);
    if(num == -1)
        return;
    if(num>commodity->sell_num)
    {
        printf("对不起，退货量大于售货量，是否全部退货？（1.全部退货 2.取消）\n");
        scanf("%d",&b);
        if(b == 1)
            num = commodity->sell_num;
        else
            return;
    }
    printf("请确认商品是否完好，确认请输入1，不确认请输入-1取消操作：");
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
        transition((timeinfo->tm_year+1900),ch);//年份转换
        strcpy(p->date_market,ch);
        strcat(p->date_market,".");//年
        transition((timeinfo->tm_mon+1),ch);//月份转换
        strcat(p->date_market,ch);
        strcat(p->date_market,".");//月
        transition((timeinfo->tm_mday),ch);//日子转换
        strcat(p->date_market,ch);
        strcat(p->date_market,".");//日
        strcat(p->date_market," ");//留白
        transition((timeinfo->tm_hour),ch);//小时转换
        strcat(p->date_market,ch);//时
        strcat(p->date_market,"：");
        transition((timeinfo->tm_min),ch);//分钟转换
        strcat(p->date_market,ch);//分
        strcat(p->date_market,"：");
        transition((timeinfo->tm_sec),ch);//秒数转换
        strcat(p->date_market,ch);//秒
        strcpy(p->serial_num,serial);//流水号
        commodity_head->next->num = commodity_head->next->num + 1;
        a->next = p;
        a = p;
        inventory->quantity = inventory->quantity + num;
        a->next = NULL;
    }
    printf("退货成功！\n");
    getchar();
    return;
}
void commodity_main_administration_record(commodity_list commodity_head,user_list mine)//交易记录调取
{
    int sel,i;
    while(1)
    {
    clear_display();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("当前用户为：%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("欢迎您进入交易情况查询程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.输出全部交易记录\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.按年调取交易记录\n\n");
    for(i=0;i<60;i++)printf(" ");printf("3.按月调取交易记录\n\n");
    for(i=0;i<60;i++)printf(" ");printf("4.按天调取交易记录\n\n");
    for(i=0;i<60;i++)printf(" ");printf("5.调取销售员交易记录\n\n");
    for(i=0;i<60;i++)printf(" ");printf("6.调取订单交易记录\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.退出交易情况查询程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("请输入您想程序执行的操作代码：");

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
void commodity_main_administration_record_all(commodity_list commodity_head,user_list mine)//交易记录遍历
{
    int sum,i;
    commodity_list p;
    p = commodity_head->next;
        clear_display();
    sum = p->num;
    if(sum<=0)
    {
        for(i=0;i<15;i++)printf("\n");
        for(i=0;i<60;i++)printf(" ");printf("\n当前系统交易记录数据为空！\n");
        getchar();
        return;
    }
    //表头
    for(i=0;i<80;i++)printf(" ");printf("交易记录\n");
    commodity_main_administration_grade();
    p = p->next;
    while(p)
    {
        printf("%-6d%-12s%-15s%-30s%-10s%-27s%-15.2lf%-15.2lf%-15d%-15.2lf%-30s\n",p->num,p->serial_num,p->id,p->name,p->type,p->date_market,p->pirce_enter,p->pirce_sell,p->sell_num,p->pircr_profit,p->operator_name);
        p = p->next;
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
    getchar();
    return;
}
void commodity_main_administration_record_year(commodity_list commodity_head,user_list mine)//交易记录按年调取
{
    int i,answer = 0;
    char ch[30],year[10];
    commodity_list p;
    p = commodity_head->next->next;
    printf("请输入您想调取记录的年份：");
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
        clear_display();
        printf("对不起，没有找到相关数据！\n");
        getchar();
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
    getchar();
    return;
}
void commodity_main_administration_record_month(commodity_list commodity_head,user_list mine)
{
    int i,answer = 0;
    char ch[30],month[12];
    commodity_list p;
    p = commodity_head->next->next;
    printf("请输入您想调取记录的年月（****.**）：");
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
        clear_display();
        printf("对不起，没有找到相关数据！\n");
        getchar();
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
    getchar();
    return;
}
void commodity_main_administration_record_day(commodity_list commodity_head,user_list mine)//交易记录按日调取
{
    int i,answer = 0;
    char ch[30],day[15];
    commodity_list p;
    p = commodity_head->next->next;
    printf("请输入您想调取记录的年月日（****.**.**）：");
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
        clear_display();
        printf("对不起，没有找到相关数据！\n");
        getchar();
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
    getchar();
    return;
}
void commodity_main_administration_record_seller(commodity_list commodity_head,user_list mine)//调取销售员交易记录
{
    int i,answer = 0;
    char ch[30];
    commodity_list p;
    p = commodity_head->next->next;
    printf("请输入您想调取销售员销售记录的用户名：");
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
        clear_display();
        printf("对不起，没有找到相关数据！\n");
        getchar();
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
    getchar();
    return;
}
void commodity_main_administration_record_order(commodity_list commodity_head,user_list mine)//调取订单号交易记录
{
    int i,answer = 0;
    char ch[30];
    commodity_list p;
    p = commodity_head->next->next;
    printf("请输入您想调取销售记录的订单号：");
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
        clear_display();
        printf("对不起，没有找到相关数据！\n");
        getchar();
    }
    printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
    getchar();
    return;
}
void commodity_main_administration_revamp(commodity_list commodity_head,user_list mine)//修改交易记录
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
    clear_display();
    printf("请输入您想要修改的销售商品编号（可通过查找功能确定编号：输入-1退出）：");
    scanf("%d",&num);
    if(num>sum||num<0)
    {
        printf("输入有误，修改失败！\n");
        getchar();
        return;
    }
    if(num == -1) return;
    while(1)
    {
    printf("该序号指向的商品信息如下：\n");
    commodity_main_administration_grade();
    commodity_main_administration_printfi(commodity_head,num);//输出i处的信息
    printf("确认修改？（1.确认 2.取消）");
    scanf("%d",&sel);
    if(sel==2)return;
    i = num;
    while(i--)
    {
        b = p;
        p = p->next;
    }
        for(i=0;i<5;i++)printf("\n");
        for(i=0;i<50;i++)printf(" ");printf("操作清单：\n\n");
        for(i=0;i<60;i++)printf(" ");printf("1.修改商品名\n\n");
        for(i=0;i<60;i++)printf(" ");printf("2.修改商品生产企业名\n\n");
        for(i=0;i<60;i++)printf(" ");printf("3.修改商品分类\n\n");
        for(i=0;i<60;i++)printf(" ");printf("4.修改商品销售时间\n\n");//
        for(i=0;i<60;i++)printf(" ");printf("5.修改商品进价\n\n");//
        for(i=0;i<60;i++)printf(" ");printf("6.修改商品销售量\n\n");//
        for(i=0;i<60;i++)printf(" ");printf("7.修改商品利润\n\n");//
        for(i=0;i<60;i++)printf(" ");printf("8.删除当前商品销售信息\n\n");//
        for(i=0;i<60;i++)printf(" ");printf("0.退出该操作程序\n\n");
        for(i=0;i<60;i++)printf(" ");printf("请输入您想要执行操作的代码：");
        scanf("%d",&sel);
    switch(sel)
    {
    case 1:
        printf("当前商品名称为：%s\n",p->name);
        printf("请输入修改后的商品名（输入-1取消操作）：");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)
            continue;
        strcpy(p->name,ch);
        printf("修改后的商品信息为：\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        commodity_save(commodity_head);
        getchar();
        return;
    case 2:
        printf("当前商品生产企业名称为：%s\n",p->company);
        printf("请输入修改后的商品名（输入-1取消操作）：");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;
        if(strlen(ch)>30&&strlen(ch)<3)
        {
        printf("输入字符过长，请重新输入！");
        printf("请再次输入修改后的商品名称（内容控制在1~15字）：");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<3)
        {
            printf("对不起！修改失败！\n");
            getchar();
            break;
        }
        }
        strcpy(p->company,ch);
        printf("修改后的商品信息为：\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        commodity_save(commodity_head);
        getchar();
        return;
    case 3:
        printf("当前商品分类为：%s\n",p->type);
        printf("请输入修改后的商品分类（输入-1取消操作）：");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;
        if(strlen(ch)>30&&strlen(ch)<1)
        {
        printf("输入格式非法，请重新输入！");
        printf("请再次输入商品生产企业名（控制在15位汉字或30位英文）：");
        scanf("%s",ch);
        if(strlen(ch)>30&&strlen(ch)<1)
        {
            printf("对不起！修改失败！\n");
            getchar();
            break;
        }
        }
        strcpy(p->type,ch);
        printf("修改后的商品信息为：\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        commodity_save(commodity_head);
        getchar();
        return;
    case 4:
        printf("当前商品销售日期为：%s\n",p->date_market);
        printf("请输入修改后的商品销售日期（格式：xxxx.xx.xx xx:xx:xx;输入-1取消操作）：");
        scanf("%s",ch);
        if(strcmp(ch,"-1")==0)continue;
        strcpy(p->date_market,ch);
        scanf("%s",ch);
        strcat(p->date_market," ");
        strcat(p->date_market,ch);
        printf("修改后的商品信息为：\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        commodity_save(commodity_head);
        getchar();
        return;
    case 5://进价
        printf("当前商品进价为：%.2lf\n",p->pirce_enter);
        printf("请输入修改后的商品进价（输入-1取消操作）：");
        scanf("%lf",&ch_double);
        if(ch_double==-1)continue;
        p->pirce_enter = ch_double;
        printf("修改后的商品信息为：\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        commodity_save(commodity_head);
        getchar();
        return;
    case 6://销量
        printf("当前商品销售量为：%d\n",p->sell_num);
        printf("请输入修改后的商品销售量（输入-1取消操作）：");
        scanf("%d",&ch_int);
        if(ch_int==-1)continue;

        p->sell_num = ch_int;
        printf("修改后的商品信息为：\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        commodity_save(commodity_head);
        getchar();
        return;
    case 7://利润
        printf("当前商品利润为：%.2lf\n",p->pircr_profit);
        printf("请输入修改后的进价（输入-1取消操作）：");
        scanf("%lf",&ch_double);
        if(ch_double==-1)continue;

        p->pircr_profit = ch_double;
        printf("修改后的商品信息为：\n");
        commodity_main_administration_grade();
        commodity_main_administration_printfi(commodity_head,num);//输出i处的信息
        printf("\n");
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        commodity_save(commodity_head);
        getchar();
        return;
    case 8:
        printf("确认删除？（1.确认 2.取消）");
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
        printf("删除成功！\n");
        commodity_save(commodity_head);
        getchar();
        return;
    case 0:
        return;
    }
    }
    }
}
void commodity_main_administration_analyse(commodity_list commodity_head,user_list mine)//交易情况分析
{
    commodity_list p;
    int i,sel;
    double sum_sell,sum_enter,sum_return,sum_loss;
    char ch[20],info[20];
    while(1)
    {
        clear_display();
        for(i=0;i<5;i++)printf("\n");
        for(i=0;i<50;i++)printf(" ");printf("操作清单：\n\n");
        for(i=0;i<60;i++)printf(" ");printf("1.年度销售情况统计\n\n");
        for(i=0;i<60;i++)printf(" ");printf("2.月度销售情况统计\n\n");
        for(i=0;i<60;i++)printf(" ");printf("3.一日销售情况统计\n\n");
        for(i=0;i<60;i++)printf(" ");printf("0.退出该操作程序\n\n");
        for(i=0;i<60;i++)printf(" ");printf("请输入您想要执行操作的代码：");
        scanf("%d",&sel);
        p = commodity_head->next->next;//跳过前导
        sum_sell = 0;
        sum_enter = 0;
        sum_return = 0;
        sum_loss = 0;
    switch(sel)
    {
    case 1:
        for(i=0;i<60;i++)printf(" ");printf("请输入您想统计年度销售情况的年度：");
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
            for(i=0;i<50;i++)printf(" ");printf("没有与之相关的销售记录，无效操作！\n");
            getchar();
            continue;
        }
        for(i=0;i<50;i++)printf(" ");printf("%s年年度销售情况统计：\n\n",ch);
        for(i=0;i<50;i++)printf(" ");printf("本年度共销售额：%.2lf\n\n",sum_sell);
        for(i=0;i<50;i++)printf(" ");printf("本年度收益率（不含退货）：%.2f\n\n",(sum_sell-sum_enter)/sum_enter);
        for(i=0;i<50;i++)printf(" ");printf("本年度亏损额：%.2lf\n\n",sum_loss);
        for(i=0;i<50;i++)printf(" ");printf("本年度退货金额：%.2lf\n\n",sum_return);
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        getchar();
        return;
    case 2:
        for(i=0;i<60;i++)printf(" ");printf("请输入您想统计月度销售情况的月度（xxxx.xx）：");
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
            for(i=0;i<50;i++)printf(" ");printf("没有与之相关的销售记录，无效操作！\n");
            getchar();
            continue;
        }
        for(i=0;i<50;i++)printf(" ");printf("%s月月度销售情况统计：\n\n",ch);
        for(i=0;i<50;i++)printf(" ");printf("本月度共销售额：%.2lf\n\n",sum_sell);
        for(i=0;i<50;i++)printf(" ");printf("本月度收益率（不含退货）：%.2f\n\n",(sum_sell-sum_enter)/sum_enter);
        for(i=0;i<50;i++)printf(" ");printf("本月度亏损额：%.2lf\n\n",sum_loss);
        for(i=0;i<50;i++)printf(" ");printf("本月度退货金额：%.2lf\n\n",sum_return);
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        getchar();
        return;
    case 3:
        for(i=0;i<60;i++)printf(" ");printf("请输入您想统计一日销售情况的日期（xxxx.xx.xx）：");
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
            for(i=0;i<50;i++)printf(" ");printf("没有与之相关的销售记录，无效操作！\n");
            getchar();
            continue;
        }
        for(i=0;i<50;i++)printf(" ");printf("%s日一日销售情况统计：\n\n",ch);
        for(i=0;i<50;i++)printf(" ");printf("本日共销售额：%.2lf\n\n",sum_sell);
        for(i=0;i<50;i++)printf(" ");printf("本日收益率（不含退货）：%.2f\n\n",(sum_sell-sum_enter)/sum_enter);
        for(i=0;i<50;i++)printf(" ");printf("本日亏损额：%.2lf\n\n",sum_loss);
        for(i=0;i<50;i++)printf(" ");printf("本日退货金额：%.2lf\n\n",sum_return);
        for(i=0;i<120;i++)printf(" ");printf("操作人：%s\n",mine->name);
        getchar();
        return;
    case 0:
        return;
    }
    }
}
void commodity_main_administration_printfi(commodity_list commodity_head,int num)//输出销售表中i处的信息
{
    commodity_list p = commodity_head->next;//跳过前导
    while(num--)
    {
        p = p->next;
    }
        printf("%-6d%-12s%-15s%-30s%-10s%-27s%-15.2lf%-15.2lf%-15d%-15.2lf%-30s\n",p->num,p->serial_num,p->id,p->name,p->type,p->date_market,p->pirce_enter,p->pirce_sell,p->sell_num,p->pircr_profit,p->operator_name);
    return;
}
void commodity_main_administration_grade()//销售表表头
{
    printf("%-6s%-12s%-15s%-30s%-10s%-27s%-15s%-15s%-15s%-15s%-30s\n","编号","订单号","识别码","商品名称","商品分类","销售日期","标价","售价","销售量","利润","操作人");
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
int transition_ch(char ch[20])//类型转换 将数字串字符数组导出为整形数字
{
    int num,i;
    num = 0;
    for(i=0;ch[i]!='\0';i++)
    {
        num = num * 10 + ch[i] - '0';
    }
    return num;
}
void commodity_main_common(inventory_list inventory_head,commodity_list commodity_head,user_list mine)//普通销售主函数
{
    int sel,i;
    while(1)
    {
    clear_display();
    for(i=0;i<15;i++)printf("\n");
    for(i=0;i<120;i++)printf(" ");printf("当前用户为：%s\n",mine->name);
    for(i=0;i<60;i++)printf(" ");printf("欢迎您进入商品销售系统\n\n");
    for(i=0;i<60;i++)printf(" ");printf("1.查询商品&销售\n\n");
    for(i=0;i<60;i++)printf(" ");printf("2.商品销售程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("0.退出库存信息管理程序\n\n");
    for(i=0;i<60;i++)printf(" ");printf("请输入您想程序执行的操作代码：");
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

void clear_display() {
    #ifdef _WIN32
    clear_display();
    #endif
    #ifdef linux
    system("clear");
    #endif
    return;
}

void resize_window(int cols, int lines) {
    #ifdef _WIN32
    char cmd[80];
    sprintf(str, "mode con cols=%d lines=%d", clos, lines);
    system(cmd)
    #endif
    #ifdef linux
    char cmd[80];
    sprintf(str, "resize -s %d %d", clos, lines);
    system(cmd)
    #endif
    return;
}
