 #include <string.h>

char * strrev(char *str)

{

    int i = strlen(str)-1,j=0;

    char ch;
    while(i>j)
    {
        ch = str[i];
        str[i]= str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}