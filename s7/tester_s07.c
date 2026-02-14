#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

// Prototypes
char *mx_strnew(const int size);
char *mx_strdup(const char *str);
char *mx_strjoin(char const *s1, char const *s2);
int *mx_copy_int_arr(const int *src, int size);
void mx_strdel(char **str);
char *mx_concat_words(char **words);
char *mx_strtrim(const char *str);
char *mx_del_extra_whitespaces(const char *str);
char **mx_strsplit(const char *s, char c);
int *mx_del_dup_arr(int *src, int src_size, int *dst_size);
void mx_del_strarr(char ***arr);

// Helper macro for checking strings
#define ASSERT_STR_EQ(a, b) if ((a)==NULL || (b)==NULL || strcmp((a), (b)) != 0) { printf("Expected '%s', got '%s'\n", (b), (a)); exit(1); }

void test_t00(void) {
    char *s = mx_strnew(10);
    if (s != NULL && s[0] == '\0' && s[10] == '\0') {
        free(s); exit(0);
    }
    exit(1);
}

void test_t01(void) {
    char *dup = mx_strdup("Hello");
    ASSERT_STR_EQ(dup, "Hello");
    free(dup);
    exit(0);
}

void test_t02(void) {
    char *j1 = mx_strjoin("Follow ", "White Rabbit");
    ASSERT_STR_EQ(j1, "Follow White Rabbit");
    char *j2 = mx_strjoin(NULL, "Neo");
    ASSERT_STR_EQ(j2, "Neo");
    free(j1); free(j2);
    exit(0);
}

void test_t03(void) {
    int src[] = {1, 2, 3};
    int *cpy = mx_copy_int_arr(src, 3);
    if (cpy[0] == 1 && cpy[1] == 2 && cpy[2] == 3) {
        free(cpy); exit(0);
    }
    exit(1);
}

void test_t04(void) {
    char *s = strdup("Test"); // using std strdup for setup
    mx_strdel(&s);
    if (s == NULL) exit(0);
    exit(1);
}

void test_t05(void) {
    char *words[] = {"Free", "your", "mind.", NULL};
    char *res = mx_concat_words(words);
    ASSERT_STR_EQ(res, "Free your mind.");
    free(res);
    exit(0);
}

void test_t06(void) {
    char *trim = mx_strtrim("  \t Hello World  \n ");
    ASSERT_STR_EQ(trim, "Hello World");
    free(trim);
    exit(0);
}

void test_t07(void) {
    char *clean = mx_del_extra_whitespaces("  My   name...   is  ");
    ASSERT_STR_EQ(clean, "My name... is");
    free(clean);
    exit(0);
}

void test_t08(void) {
    char **arr = mx_strsplit("**Good bye, **Mr.Anderson.****", '*');
    ASSERT_STR_EQ(arr[0], "Good bye, ");
    ASSERT_STR_EQ(arr[1], "Mr.");
    ASSERT_STR_EQ(arr[2], "Anderson.");
    if (arr[3] != NULL) exit(1);
    
    // Cleanup manually for test
    for(int i=0; arr[i]; i++) free(arr[i]);
    free(arr);
    exit(0);
}

void test_t09(void) {
    int src[] = {1, 2, 2, 8, 4, 6, 8, 9, 4, 3, 4};
    int dst_size = 0;
    int *res = mx_del_dup_arr(src, 11, &dst_size);
    // Expected: {1, 2, 8, 4, 6, 9, 3} size 7
    if (dst_size != 7) exit(1);
    int expected[] = {1, 2, 8, 4, 6, 9, 3};
    for(int i=0; i<7; i++) if(res[i] != expected[i]) exit(1);
    free(res);
    exit(0);
}

void test_t10(void) {
    // Hard to test void function, checking for no crash
    char **arr = malloc(3 * sizeof(char*));
    arr[0] = strdup("One");
    arr[1] = strdup("Two");
    arr[2] = NULL;
    mx_del_strarr(&arr);
    if (arr == NULL) exit(0);
    exit(1);
}

void run_test(void (*func)(void), const char *name) {
    printf("Running %s... ", name); fflush(stdout);
    pid_t pid = fork();
    if (pid == 0) { func(); exit(0); }
    else {
        int status; wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) printf(GREEN "[OK]" RESET "\n");
        else printf(RED "[FAIL]" RESET "\n");
    }
}

int main(void) {
    printf("=== SPRINT 07 MEMORY TESTER ===\n");
    printf(RED "Note: This tester checks LOGIC. Use valgrind to check MEMORY LEAKS!\n" RESET);
    
    run_test(test_t00, "T00 (Strnew)       ");
    run_test(test_t01, "T01 (Strdup)       ");
    run_test(test_t02, "T02 (Strjoin)      ");
    run_test(test_t03, "T03 (Copy Int Arr) ");
    run_test(test_t04, "T04 (Strdel)       ");
    run_test(test_t05, "T05 (Concat Words) ");
    run_test(test_t06, "T06 (Strtrim)      ");
    run_test(test_t07, "T07 (Clean String) ");
    run_test(test_t08, "T08 (Strsplit)     ");
    run_test(test_t09, "T09 (Del Dups)     ");
    run_test(test_t10, "T10 (Del Strarr)   ");
    
    return 0;
}
