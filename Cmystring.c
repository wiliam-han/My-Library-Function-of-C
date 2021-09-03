#include<string.h>

void* mymemset(void* str,int c,size_t n)//复制n个字符c到str的前n个字符
{
    if(str==NULL) return NULL;
    char* ret=str;
    while(n!=0){
        --n;
        *ret=c;
        ++ret;
    }
    return str;
}
char* mystrcpy(char* dest,const char* src)
{
    if((dest==NULL)||(src==NULL)) return NULL;
    char* ret=dest;
    while(*src!='\0'){
        *dest=*src;
        ++dest;
        ++src;
    }
    return ret;
}
char* mystrncat(char* dest,const char* src,size_t n)//src后面的n个字符追加到dest的字符串结尾，返回新的dest
{
    //类似的strcat其实就是没有最后一个n
    //printf("src等于%s\n",src);
    if((dest==NULL)||(src==NULL)) return NULL;
    char* cp=dest;
    while(*cp!='\0'){
        ++cp;
    }
    while((n!=0)&&(*src!='\0')){//const char* src指不通过指针src的方式修改*src的值
        *cp=*src;
        ++cp;
        ++src;
        --n;
    }
    return dest;
}
void* mymemchr(const void*str,int c,unsigned int count)//返回指向字符串str的前n个字节中找到第一次出现c的位置
{
    if(str==NULL) return NULL;//或者assert(str!=NULL);
    while(count--){
        if(*(char*)str==c)
            return (void*)str;
        str++; //也可以写成 str=(char*)str+1;
    }
    return NULL;//找不到
}
void* mymemcpy(void* dest,const void* src,int n)//src复制n个字符到dest，返回dest
{
    if((dest==NULL)||(src==NULL)) return NULL;
    char* pd=(char*) dest;//包装,不然最后找不到返回的指针
    char* ps=(char*) src;
    if(pd>ps&&pd<ps+n){//说明会有写覆盖，需要从后往前写
        pd = pd+n-1;
        pd = ps+n-1;
        while(n--){
            *pd=*ps;//三行可以写为 *pd--=*ps--; 因为*p--是先使用再--
            ps--;
            pd--;
        }
    }else{
        while(n--){//正常写，从前往后写
            *pd=*ps;
            ps++;
            pd++;
        }
    }
    return dest;
}
void* mymemmove(void* dest, const void* src, size_t n)
{
    char * d  = (char*) dest;
    const char * s = (const char*) src;
    //位置相同：不用拷贝
    //源位置大于目标位置：正向拷贝
    //源位置小于目标位置（有可能重叠）：反向拷贝
    if (s>d)
    {
         // start at beginning of s
         while (n--)
            *d++ = *s++;
    }
    else if (s<d)
    {
        // start at end of s
        d = d+n-1;
        s = s+n-1;
  
        while (n--)
           *d-- = *s--;
    }
	
    return dest;
}
int main()
{
    char* p=mymemchr("Hello World!",'W',8);
    char* p1=memchr("Hello World!",'W',8);
    printf("%s&&%s\n",p,p1);//这样会输出找到W之后的全部字符串
    //mymemcpy不好验证
    //memmove实现完全可以照抄memcpy
    char dest[48];//dest[20]会运行出1Hello Hello ，dest[50]会运行出1@Hello Hello ，可能因为没有实现用memset清空，导致大内存中有一些杂数
    //printf打印char[]就会出现一直打印直到出现\0为止，其中各种杂量都是与IDE有关
    mymemcpy(dest,"1",1);
    strncat(dest,"Hello World!",6);
    mystrncat(dest,"Hello World!",6);
    printf("%s\n",dest);
    char src[40];
    char dst[100];
    memset(dst,'\0',sizeof(dst));
    strcpy(src,"This is a test");
    mystrcpy(dst,src);
    printf("%s\n",dst);
    char res[200];
    mymemset(res,'k',sizeof(res));
    printf("%s里共%d个k\n",res,sizeof(res));
    memcpy(NULL,NULL,1);//证明memcpy函数不检查缓存区域，直接操作内存
    return 0;
}