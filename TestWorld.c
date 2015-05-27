#include <stdio.h>
#include <string.h>
#include <time.h>

// A macro has the same name with strlen function.
#define strlen(s) 666

void foo(char *flag) {
    printf("Foo to you too! %s\n", flag);
};

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

    // crazy function pointers
    // --------------------
    char *strTmp = "a string";
    int jTmp = (strlen) (strTmp);
    printf("\nstrlen macro defined: \n");
    printf("(strlen) (str) = %zu\n", jTmp);

    printf("strlen(str) = %zu\n\n", strlen(strTmp));

    // --------------------
    // links: http://stackoverflow.com/questions/6893285/why-do-all-these-crazy-function-pointer-definitions-all-work-what-is-really-goi
    void (*p1_foo)() = foo;
    void (*p2_foo)() = *foo;
    void (*p3_foo)() = &foo;
    void (*p4_foo)() = *&foo;
    void (*p5_foo)() = &*foo;
    void (*p6_foo)() = **foo;
    void (*p7_foo)() = **********************foo;

    (*p1_foo)("p1");
    (*p2_foo)("p2");
    (*p3_foo)("p3");
    (*p4_foo)("p4");
    (*p5_foo)("p5");
    (*p6_foo)("p6");
    (*p7_foo)("p7");

    char *str4 = "12345";
    char strArr[5 + 100];
    strcat(strArr, str4);
    printf("strcat 1 strArr = %s\n", strcat(strArr, "67890ABCDEF"));
    printf("strcat 2 strArr = %s\n", strcat(strArr, "54321"));

    time_t t = time(NULL);
    printf("%s", asctime(localtime(&t)));
    printf("%d seconds since the Epoch\n", (int)t);

    return 0;
}