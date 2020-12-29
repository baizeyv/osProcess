#include<stdio.h>
#include<stdlib.h>
#define RUNNING 1
#define WAIT 2
#define FINISH 3
#define TIME_PIECE 5 
#define MAX_PROCESS_NUM 10

int AX,BX,CX,DX,PC,PSW,TIME;
int run;
int pfree;
struct {
    int head;
    int tail;
}ready;

struct{
    int name; 
    int status;
    int ax;
    int bx;
    int cx;
    int dx;
    int pc;
    int psw;
    int time;
    int totalTime;
    int remainingTime;
    int next; 
}pcbarea[MAX_PROCESS_NUM];

void Init(){
    int i;
    run=ready.head=ready.tail=-1;
    pfree=0;
    for(i = 0; i<MAX_PROCESS_NUM-1;++i)
        pcbarea[i].next=i+1;
        pcbarea[MAX_PROCESS_NUM-1].next=-1;
    }

void Create(int process_name,int ax,int bx,int cx,int dx,int pc,int psw,int totalTime){
int i;
    if(pfree==-1){
        printf("无空闲进程控制块，进程创建失败\n");
        return;
    }
    i=pfree;
    pfree=pcbarea[pfree].next;
    pcbarea[i].name=process_name;
    pcbarea[i].status=WAIT;
    pcbarea[i].ax=ax;
    pcbarea[i].bx=bx;
    pcbarea[i].cx=cx;
    pcbarea[i].dx=dx;
    pcbarea[i].pc=pc;
    pcbarea[i].psw=psw;
    pcbarea[i].time=TIME_PIECE;
    pcbarea[i].totalTime=totalTime;
    pcbarea[i].remainingTime=totalTime;

    if(ready.head!=-1){
        pcbarea[ready.tail].next=i;
        ready.tail=i;
        pcbarea[ready.tail].next=-i;
    }
else{
ready.head=i;
ready.tail=i;
pcbarea[ready.tail].next=-1;
}
printf("\n");
}

void Sheduling(){
    getchar();
        if(ready.head==-1){
        printf("进程调度完毕! \n\n\n");
        return;
    }

    run=ready.head;
    ready.head=pcbarea[ready.head].next;
    if(ready.head==-1)ready.tail=-1;
    pcbarea[run].status=RUNNING;
    AX=pcbarea[run].ax;
    BX=pcbarea[run].bx;
    CX=pcbarea[run].cx;
    DX=pcbarea[run].dx;
    PC=pcbarea[run].pc;
    PSW=pcbarea[run].psw;
    TIME=pcbarea[run].time; 
    printf("n进程编号:%d\n ",pcbarea[run].name);
    printf("进程状态:运行\n");
    printf("寄存器内容: \n");printf("AX:%d\n",AX);
    printf("BX:%d\n",BX);
    printf("CX:%d\n",CX);
    printf("DX:%d\n",DX);
    printf("PC:%d\n",PC);
    printf("PSW:%d\n",PSW);
    printf("TIME:%d\n\n",TIME);
    printf("\n**时间片用完**\n");
    AX=BX=CX=DX=PC=PSW=TIME=0;
    if(pcbarea[run].remainingTime<=TIME_PIECE){
        getchar();
        pcbarea[run].remainingTime=0;
        pcbarea[run].status=FINISH;
        ready.head=pcbarea[run].next;

        printf("\n进程编号:%d\n",pcbarea[run].name);
        printf("进程状态:完成\n");
        printf("寄存器内容: \n");
        printf("AX:%d\n",AX);
        printf("BX:%d\n",BX);
        printf("CX:%d\n",CX);
        printf("DX:%d\n",DX);
        printf("PC:%d\n",PC);
        printf("PSW:%d\n",PSW);
        printf("TIME: %d\n\n",TIME);
        
        if(pfree==-1){
            pfree=run;
            pcbarea[pfree].next=-1;
        }else{
            pcbarea[pfree].next=run;
            pfree=run;
            pcbarea[run].next=-1;
        }
    }else{
        getchar();
        pcbarea[run].remainingTime=TIME_PIECE;
        pcbarea[run].status=WAIT;
        if(ready.tail!=-1)
            pcbarea[ready.tail].next=run;
        else
            ready.head=ready.tail=run;
        pcbarea[run].next=-1;
        ready.tail=run;
        printf("\n进程编号:%d\n",pcbarea[run].name);
        printf("进程状态:等待\n");
        printf("寄存器内容: \n");
        printf("AX:%d\n",AX);
        printf("BX:%d\n",BX);
        printf("CX:%d\n",CX);
        printf("DX:%d\n",DX);
        printf("PC:%d\n",PC);
        printf("PSW:%d\n",PSW);
        printf("TIME:%d\n\n",TIME);
        Sheduling();
    }
}
    
void main(){
    int process_name,ax,bx,cx,dx,pc,psw,totalTime;
    int i;
    char quit; 
    do {
        i=MAX_PROCESS_NUM;
        printf("=====模拟单处理器系统的进程调度================\n\n\n");
        Init();
        printf("**创建进程，输入负数可结束创建**\n");
        printf("输入一个进程的编号(现在还可以创建%d个进程): ",i);
        scanf("%d",&process_name);
    while(process_name>0){

        printf("请输入该进程中ax、bx、cx、dx、pc、psw的初始现场信息:");
        scanf("%d%d%d%d%d%d",&ax,&bx,&cx,&dx,&pc,&psw);
        printf("请输入该进程运行所需的总时间:");
        scanf("%d",&totalTime);
        Create(process_name,ax,bx,cx,dx,pc,psw,totalTime);

        if(i>0)
            --i;
            printf("输入一个进程的编号(现在还可以创建%d个进程): ",i);
            scanf(" %d",&process_name);
        }

        system("clear");
        printf("请按回车开始调度……");
        getchar();
        Sheduling();
        printf("退出请按0，重新测试请按任意键:");
        quit=getchar();
        system("clear");
    } while(quit!=0);
    printf("\n\n");
}

