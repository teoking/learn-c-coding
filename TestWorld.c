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

    printf("====================\n");
    int count = 0;
    switch (count) {
        case 0: printf("0\n");
        case 1: printf("1\n");
        case 2: printf("2\n");
        case 3: printf("3\n");
        case 4: printf("4\n");
        case 5: printf("5\n");
        case 6: printf("6\n");
        case 7: printf("7\n");
    }

    // --------------------
    char strTmp = "a string";
    int jTmp = (strlen) (&strTmp);
    printf("(strlen) (str) = %d\n", jTmp);

    char *strArr[10];
    strArr[0] = "a string a";
    strArr[1] = "a string b";
    strArr[2] = "a string b";
    strArr[3] = "a string b";
    strArr[4] = "a string b";
    strArr[5] = "a string b";
    strArr[6] = "a string b";
    strArr[7] = "a string b";
    strArr[8] = "a string b";
    strArr[9] = "a string b";
    jTmp = (strlen) (strArr);
    printf("(strlen) (strArr) = %d\n", jTmp);
 
    return 0;
}