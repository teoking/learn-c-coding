#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void die(const char *message)
{
    printf("errno = %d\n", errno);
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void write_long(FILE * out, long num) {
   if (NULL == out) {
       fprintf(stderr, "I bet you saw THAT coming.\n");
       exit(EXIT_FAILURE);
   }
   fwrite(&num, sizeof(long) , 1, out);
   if(ferror(out)) {
      perror(__func__);
      exit(EXIT_FAILURE);
   }
}

long read_long(FILE *in)
{
    if (NULL == in) {
        fprintf(stderr, "I bet you saw THAT coming.\n");
        exit(EXIT_FAILURE);
    }
    long data[1];
    int ret_code = fread(data, sizeof *data, 1, in);
    if (ferror(in)) {
        perror(__func__);
        exit(EXIT_FAILURE);
    }
    if (ret_code == 1) {
        return data[0];
    }

    return -1;
}

int main()
{
    if (0)
        printf("aaaaaa");
    if (111)
        printf("bbbbbb");
    
    FILE *file = fopen("file.bin", "w");
    long data = 1024;
    long row = 1000;
    printf("sizeof(data)=%ld\n", sizeof data);
    write_long(file, data);
    write_long(file, row);

    fclose(file);

    FILE *file2 = fopen("file.bin", "r+");
    printf("data = %ld\n", read_long(file2));
    printf("row = %ld\n", read_long(file2));

    fclose(file2);

}