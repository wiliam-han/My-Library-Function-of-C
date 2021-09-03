#include<ctype.h>
#include<stdio.h>

int mytolower(int c)
{
    if(c>='A'&&c<='Z'){
        return 'a'+c-'A';
    }else{
        return c;//注意这里如果是非法字符就返回传入字符
    }
}

int main()
{
    char a='A';
    char b,c;
    b=tolower(a);//同样的还有
    c=mytolower(a);
    printf("%c的小写结果是%c或者%c\n",a,b,c);
    return 0;
}