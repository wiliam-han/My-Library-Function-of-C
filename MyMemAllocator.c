//线程不安全版本的malloc与free
#define NULL 0//这个在stdio.h里面已经定义了
typedef struct mcb{
    int available;
    int size;
} mcb;
void* memStart;//空闲内存的起始地点
void* lastAddr;//当前堆尾
int hasInit;//仅代表是否进行初始化

void init()
{
    //初始化有效内存
    lastAddr=sbrk(0);//sbrk会改变program break的位置，这个pb为程序数据分配区（含data段，bss段，heap）的结束位置，也就是heap的结束位置
    //sbrk用来增加heap，传入的参数就是增加的大小，返回值为增加大小前的heap的program break，sbrk(0)其实就是返回program break，即设置一个程序中断点用来跟踪堆大小
    memStart=lastAddr;
    hasInit=1;
}
void* mymalloc(const int length)
{
    if(!hasInit) init();
    void* current=memStart;
    void* ret=NULL;

    int num=length+sizeof(mcb);//mcb代表内存控制块，没有这个块没法把分配的内存联系到一起
    
    while(current!=lastAddr){
        //先找找之前的内存中有没有合适的
        mcb *pcurrent=current;//void* 的好处：可以方便的变成任意其它指针
        if(pcurrent->available==1&&pcurrent->size>num){
            pcurrent->available=0;
            ret=current;//这里注意ret本质还是void*
            break;
        }
        pcurrent+=pcurrent->size;//这里是一块一块地遍历
        current=pcurrent;//void* 指针不能直接加，因为不知道偏移数量
    }
    if(!ret){
        //重复使用内存失败
        sbrk(num);
        ret=lastAddr;
        mcb *pcurrent=lastAddr;
        pcurrent+=num;
        lastAddr=pcurrent;//先改变系统heap堆顶
        pcurrent=ret;
        pcurrent->size=num;//你会发现只有开辟新的内存的时候才会声明这一块到底是多大
        pcurrent->available=0;
    }
    mcb *ptemp=ret;
    ptemp+=sizeof(mcb);
    ret=ptemp;//返回值为真正可以用的部分
    return ret;
}

void myfree(void* start)
{
    mcb *ptemp=(mcb*)start-sizeof(mcb);//这个1实际上会是sizeof(mcb)
    ptemp->available=1;
}