/*
 * This is an implementation for runtests.sh in C.
 */

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "../src/dbg.h"

// check the file is executable file or not.
int is_executable(char *file)
{
    struct stat sb;
    // executable and not directory
    if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR && !S_ISDIR(sb.st_mode))
        return 1;
    return 0;
}

// get the file's relative path
char *get_file_path(char *path, char *parent, char *name)
{
    memset(path, '\0', strlen(path));
    strcpy(path, parent);
    strcat(path, name);
    return path;
}

void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        die("Usage: runtests [project path]");

	printf("Running unit tests:\n");

    char *name = "_tests";
    struct dirent *dp;
    struct stat sb;
    FILE *logFile;
    char *path = argv[1];

    int pathLen = strlen(path);

    DIR *dirp = opendir("./tests");
    check(dirp != NULL, "open tests directory failed");

    // Open the log file
    logFile = fopen("./tests/tests.log", "a");
    if (logFile) {
        // Redirect the stderr to the log file
        dup2(fileno(logFile), STDERR_FILENO);
    } else {
        printf("tests/tests.log open failed!");
    }

    char tmpStr[8 + 255];
    char *filePath;
    // Iterate the directory
    while ((dp = readdir(dirp)) != NULL) {
        filePath = get_file_path(tmpStr, "./tests/", dp->d_name);
        if (strstr(dp->d_name, name) != NULL && is_executable(filePath)) {
            // TODO run the tests in a child process.
            // run the test file
            execlp("valgrind", "valgrind", filePath, (char *)0);
        }
    }

    // Clean up
    if (logFile) {
        fclose(logFile);
    }
    (void)closedir(dirp);

    return 0;

error:
    return 1;
}

