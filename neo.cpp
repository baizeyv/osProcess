#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

/* A Part Of Macro */
#define RUNNING 1
#define ALREADY 2
#define FINISH 3
#define BLOCK 4
#define N 10
#define TIME 5

/* A Part Of Class */
class PCB{
public:
    PCB(int name, int status=0, int ax=0, int bx=0, int cx=0, int dx=0, int pc=0, int psw=0, int time=0){
        this->name = name;
        this->status = status;
        this->status = ax;
        this->ax = bx;
        this->cx = cx;
        this->dx = dx;
        this->pc = pc;
        this->psw = psw;
        this->time = time;
        this->totalTime = time;
    }
    void printPCB(){
        cout << "name:" << name << " ";
        cout << "ax:" << ax << " ";
        cout << "bx:" << bx << " ";
        cout << "cx:" << cx << " ";
        cout << "dx:" << dx << " ";
        cout << "pc:" << pc << " ";
        cout << "psw:" << psw << " ";
        cout << "totalTime:" << totalTime << " ";
        cout << endl;
    }
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
};

void pressKey(){
    system("echo 'Press Any Key To Continue!'");
    system("read -n 1");
}

void initFreeQueue(queue<int> &freeQueue){
    for(int i = 0; i < 10; i++){
        freeQueue.push(0);
    }
}

void printQueue(queue<PCB> &q){
    int size = q.size();
    for(int i = 0; i < size; i++){
        q.push(q.front());
        q.back().printPCB();
        q.pop();
    }
}

void createProcess(int &name, int &status, int &ax, int &bx, int &cx, int &dx, int &pc, int &psw, int &time, int &totalTime, queue<int> &freeQueue, queue<PCB> &alreadyQueue){
    if(freeQueue.size() == 0){
        cout << "******************" << endl;
        cout << "无空闲块，创建失败" << endl;
        cout << "******************" << endl;
        return;
    }
    freeQueue.pop();
    PCB p(name,status,ax,bx,cx,dx,pc,psw,time);
    alreadyQueue.push(p);
    cout << "进入就绪队列" << endl;
    printQueue(alreadyQueue);
    cout << endl;
    pressKey();
}

void executeProcess(queue<PCB> &runQueue, queue<PCB> &alreadyQueue, queue<PCB> &blockQueue,int leastTime){
    if(runQueue.size()==0){
        runQueue.push(alreadyQueue.front());
        alreadyQueue.pop();
        if(runQueue.front().time > leastTime){
            if(runQueue.front().time == 0){
                runQueue.pop();
                cout << "执行结束" << endl;
                return;
            }
            cout << runQueue.front().name << " 开始执行" << endl;

            pressKey();

            runQueue.front().time -= leastTime;
            blockQueue.push(runQueue.front());
            runQueue.pop();
            cout << blockQueue.front().name << " 进入阻塞队列" << endl;
            blockQueue.back().status = BLOCK;
            printQueue(blockQueue);

            pressKey();

            alreadyQueue.push(blockQueue.front());
            blockQueue.pop();
            cout << alreadyQueue.back().name << "进入就绪队列" << endl;
            alreadyQueue.back().status = ALREADY;
            printQueue(alreadyQueue);

            pressKey();

            leastTime = TIME;
            if(runQueue.size()==0 && alreadyQueue.size() == 0 && blockQueue.size() == 0){
                cout << "执行结束" << endl;
                return;
            }
            executeProcess(runQueue, alreadyQueue, blockQueue, leastTime);
        }else if(runQueue.front().time == leastTime){
            cout << runQueue.front().name << " 执行完成" << endl;
            runQueue.pop();

            if(runQueue.size()!=0){
                executeProcess(runQueue, alreadyQueue, blockQueue, leastTime);
            }else if(runQueue.size()==0 && alreadyQueue.size() == 0 && blockQueue.size() == 0){
                cout << "THE END" <<endl;
                return;
            }
        }else{
            leastTime = leastTime - runQueue.front().time;
            runQueue.front().time = 0;
            cout << runQueue.front().name << " 执行完成" << endl;
            runQueue.pop();
            if(runQueue.size()==0 && alreadyQueue.size() == 0 && blockQueue.size() == 0){
                cout << "THE END" <<endl;
                return;
            }

            pressKey();

            executeProcess(runQueue, alreadyQueue, blockQueue, leastTime);
        }
    }else{
        while(1){
            executeProcess(runQueue, alreadyQueue, blockQueue, leastTime);
        }
    }
}

int main(int argc, char *argv[])
{
    queue<int> freeQueue; /* 空闲块队列 */
    initFreeQueue(freeQueue);
    queue<PCB> blockQueue; /* 阻塞队列 */
    queue<PCB> runQueue; /* 执行队列 */
    queue<PCB> alreadyQueue; /* 就绪队列 */

    int name, status,ax,bx,cx,dx,pc,psw,time,totalTime;
    int leastTime = TIME;

    system("clear");
    cout << "************ 模拟单处理机系统的进程调度 ************" <<endl << endl;
    int flag = 1;
    cout << "Create Process 负数结束，最多10个进程" << " flag:" << flag << endl;
    cout << "现在还可以创建" << ((N-flag + 1)>=0?(N-flag+1):0) << "个进程" << endl;
    cout << "Input Process ID:" << endl;
    cout << " > ";
    cin >> name;
    if(name >= 0)
    {
        cout << "AX:" << endl << " > ";
        cin >> ax;
        cout << "BX:" << endl << " > ";
        cin >> bx;
        cout << "CX:" << endl << " > ";
        cin >> cx;
        cout << "DX:" << endl << " > ";
        cin >> dx;
        cout << "PC:" << endl << " > ";
        cin >> pc;
        cout << "PSW:" << endl << " > ";
        cin >> psw;
        cout << "Time:" << endl << " > ";
        cin >> time;

        pressKey();

    }else {
        cout << "Process END!" << endl;
        return 0;
    }
    while(name >= 0){
        flag++;
        createProcess(name, status, ax, bx, cx, dx, pc, psw, time, totalTime,freeQueue,alreadyQueue);
        cout << "************ 模拟单处理机系统的进程调度 ************" << endl << endl;
        cout << "Create Process 负数结束，最多10个进程" << " flag:" << flag << endl;
        cout << "现在还可以创建" << ((N-flag + 1)>=0?(N-flag+1):0) << "个进程" << endl;
        cout << "Input Process ID:" << endl;
        cout << " > ";
        cin >> name;
        if(name >= 0)
        {
            cout << "AX:" << endl << " > ";
            cin >> ax;
            cout << "BX:" << endl << " > ";
            cin >> bx;
            cout << "CX:" << endl << " > ";
            cin >> cx;
            cout << "DX:" << endl << " > ";
            cin >> dx;
            cout << "PC:" << endl << " > ";
            cin >> pc;
            cout << "PSW:" << endl << " > ";
            cin >> psw;
            cout << "Time:" << endl << " > ";
            cin >> time;

            pressKey();

        }else {
            break;
        }
    }

    executeProcess(runQueue, alreadyQueue, blockQueue,leastTime);

    return 0;
}
