#include <stdio.h>
#include <string.h>
 
int main(void)
{
    char str[] = "Hello, world!";
    char copy[40] = { 0 };
 
    /* no buffer overflow */
    strncpy(copy, str, sizeof(copy)-1);
    printf("%s\n", copy);
 
    /* copy partial amount of data */
    strncpy(copy, str, 5);
 
    /* add manually nullbyte.
     * comment it to see difference */
    copy[5] = '\0';
    printf("%s\n", copy);

    char str1[255];
    puts(str1);
    memset(str1, 'd', 100);
    puts(str1);

    char *str2;
    if (!str2)
        puts("str2 is not initailized");
    puts(str2);
 
    return 0;
}