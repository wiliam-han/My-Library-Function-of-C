#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int myabs(int x)
{
    return x*((x>>31<<1)+1);//负数右移补1，正数补0，左移全是补0,x>>31<<1的结果为全0或者（全1仅最后一位是0），加1之后就是1或者-1
}
double myatof(const char* str)
{
    char flag = 0;  //表示正数
    double res = 0.0;
    double d = 10.0;
    int e = 0;
    while(*str != '\0'){
        if( !(*str >= '0' && *str <= '9')){  //找到字符串中的第一个数字
        str++;
        continue;
        }
        if(*(str-1) == '-'){
            flag = 1;  //表示是一个负数
        }
        while(*str >= '0' && *str <= '9'){
            res = res *10.0 + (*str - '0');
            str++;
        }
        if(*str == '.'){
            str++;
        }
///////因为突然收到蚂蚁的电话面试，所以转而去准备相关的资料了
        while(*str >= '0' && *str <= '9')
    {
        res = res + (*str - '0')/d;
    d = d*10;
    str++;
    }
    if(*str == 'e' || *str == 'E')
    {
        str++;
    if(*str == '+')
    {
        str++;
    while(*str >= '0' && *str <= '9')
    {
        e = e*10 + (*str - '0');
        str++;
    }
    while(e>0)
    {
        res = res*10;
        e--;
    }
    }
    if(*str == '-')
    {
        str++;
    while(*str >= '0' && *str <= '9')
    {
        e = e*10 + (*str - '0');
        str++;
    }
    while(e>0)
    {
        res = res/10;
        e--;
    }
    }
            if(*str >= '0' && *str <= '9')
    {
    while(*str >= '0' && *str <= '9')
    {
        e = e*10 + (*str - '0');
        str++;
    }
    while(e>0)
    {
        res = res*10;
        e--;
    }
    }
    }
    return res*(flag?-1:1);  
    }
}
int myatoi(const char* str)
{
    return 0;
}
int main()
{
    int a=-6;
    printf("%d的绝对值为%d或者%d\n",a,abs(a),myabs(a));
    {
        char str[20];
        strcpy(str,"1.125");
        double ans1=atof(str);
        double ans2=myatof(str);
        printf("%s字符串代表的数字为%lf或者%lf\n",str,ans1,ans2);
    }
    {
        char str[20];
        strcpy(str,"032861");
        double ans1=atof(str);
        double ans2=myatof(str);
    }
    return 0;
}