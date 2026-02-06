#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

// Цвета для вывода
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

// ==========================================
// ПРОТОТИПЫ ФУНКЦИЙ (из заданий Sprint 04)
// ==========================================
void mx_print_arr_int(const int *arr, int size);
int mx_sqrt(int x);
char *mx_strchr(const char *s, int c);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strcat(char *s1, const char *s2);
void mx_sort_arr_int(int *arr, int size);
int mx_atoi(const char *src);
int mx_count_words(const char *str, char delimiter);
int mx_popular_int(const int *arr, int size);
int mx_strncmp(const char *s1, const char *s2, int n);
char *mx_strstr(const char *s1, const char *s2);
int mx_count_substr(const char *str, const char *sub);

// ==========================================
// ТЕСТЫ
// ==========================================

void test_t00(void) {
    int arr[] = {1, 2, 3, 4, 5};
    printf(YELLOW "\n   [Visual Check] Expected:\n   1\n   2\n   3\n   4\n   5\n" RESET);
    printf("   --- OUTPUT START ---\n");
    mx_print_arr_int(arr, 5);
    printf("   --- OUTPUT END ---\n");
    exit(0);
}

void test_t01(void) {
    if (mx_sqrt(4) == 2 && mx_sqrt(3) == 0 && mx_sqrt(16) == 4 && mx_sqrt(2147395600) == 46340) 
        exit(0);
    else 
        exit(1);
}

void test_t02(void) {
    const char *str = "Game Over";
    if (mx_strchr(str, 'm') == &str[2] && mx_strchr(str, 'Z') == NULL && mx_strchr(str, '\0') == &str[9]) 
        exit(0);
    else 
        exit(1);
}

void test_t03(void) {
    char dst[20];
    char src[] = "Hello";
    
    // Case 1: len > src length
    memset(dst, 'x', 20);
    mx_strncpy(dst, src, 10);
    if (strcmp(dst, "Hello") == 0 && dst[5] == '\0' && dst[6] == '\0') {
        // Case 2: len < src length
        mx_strncpy(dst, src, 2);
        if (dst[0] == 'H' && dst[1] == 'e' && dst[2] == 'l') exit(0); // dst[2] не должен был измениться
    }
    exit(1);
}

void test_t04(void) {
    char s1[20] = "Hello";
    const char *s2 = " World";
    mx_strcat(s1, s2);
    if (strcmp(s1, "Hello World") == 0) exit(0);
    else exit(1);
}

void test_t05(void) {
    int arr[] = {3, 55, 11, 1, 0, 4, 22};
    int sorted[] = {0, 1, 3, 4, 11, 22, 55};
    mx_sort_arr_int(arr, 7);
    
    for (int i = 0; i < 7; i++) {
        if (arr[i] != sorted[i]) exit(1);
    }
    exit(0);
}

void test_t06(void) {
    if (mx_atoi("   -123") == -123 && 
        mx_atoi("   +007") == 7 && 
        mx_atoi("100junk") == 100 &&
        mx_atoi("junk") == 0) 
        exit(0);
    else 
        exit(1);
}

void test_t07(void) {
    const char *s = "  follow  * the  white rabbit ";
    if (mx_count_words(s, '*') == 2 && mx_count_words(s, ' ') == 5) exit(0);
    else exit(1);
}

void test_t08(void) {
    int arr1[] = {2, 2, 4, 4};
    int arr2[] = {5, 5, 5, 1, 2};
    // Task says: "Returns the first number found if there is more than one most common"
    // In {2, 2, 4, 4}, 2 comes first.
    if (mx_popular_int(arr1, 4) == 2 && mx_popular_int(arr2, 5) == 5) exit(0);
    else exit(1);
}

void test_t09(void) {
    if (mx_strncmp("abc", "abd", 2) == 0 && 
        mx_strncmp("abc", "abd", 3) < 0 && 
        mx_strncmp("abd", "abc", 3) > 0) 
        exit(0);
    else 
        exit(1);
}

void test_t10(void) {
    const char *haystack = "Hello Neo";
    if (mx_strstr(haystack, "Neo") == &haystack[6] && 
        mx_strstr(haystack, "Morpheus") == NULL) 
        exit(0);
    else 
        exit(1);
}

void test_t11(void) {
    const char *s = "yo, yo, yo Neo";
    if (mx_count_substr(s, "yo") == 3 && mx_count_substr(s, "Neo") == 1) exit(0);
    else exit(1);
}

// ==========================================
// ФУНКЦИЯ ЗАПУСКА (Fork Wrapper)
// ==========================================
void run_test(void (*func)(void), const char *task_name) {
    printf("Running %s... ", task_name);
    fflush(stdout);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        func();
        exit(0); 
    } else if (pid > 0) {
        // Parent process
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            if (exit_code == 0) {
                printf(GREEN "[OK]" RESET "\n");
            } else {
                printf(RED "[FAIL]" RESET " (Wrong Answer)\n");
            }
        } else if (WIFSIGNALED(status)) {
            printf(RED "[CRASH]" RESET " (Segfault/Bus Error)\n");
        }
    } else {
        perror("Fork failed");
    }
}

int main(void) {
    printf("=== SPRINT 04 MASTER TESTER ===\n\n");

    run_test(test_t00, "Task 00 (Print Array)   ");
    run_test(test_t01, "Task 01 (Sqrt)          ");
    run_test(test_t02, "Task 02 (Strchr)        ");
    run_test(test_t03, "Task 03 (Strncpy)       ");
    run_test(test_t04, "Task 04 (Strcat)        ");
    run_test(test_t05, "Task 05 (Sort Array)    ");
    run_test(test_t06, "Task 06 (Atoi)          ");
    run_test(test_t07, "Task 07 (Count Words)   ");
    run_test(test_t08, "Task 08 (Popular Int)   ");
    run_test(test_t09, "Task 09 (Strncmp)       ");
    run_test(test_t10, "Task 10 (Strstr)        ");
    run_test(test_t11, "Task 11 (Count Substr)  ");

    printf("\n=== DONE ===\n");
    return 0;
}
