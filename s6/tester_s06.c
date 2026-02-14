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

// ПРОТОТИПЫ
int mx_linear_search(char **arr, const char *s);
int mx_bubble_sort(char **arr, int size);
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_insertion_sort(char **arr, int size);
int mx_selection_sort(char **arr, int size);
void mx_arr_rotate(int *arr, int size, int shift);

// ТЕСТЫ
void test_t01(void) {
    char *arr[] = {"222", "Abcd", "abc", "ab", "az", "z", NULL};
    if (mx_linear_search(arr, "z") == 5 && 
        mx_linear_search(arr, "abc") == 2 && 
        mx_linear_search(arr, "not_found") == -1) exit(0);
    else exit(1);
}

void test_t02(void) {
    char *arr1[] = {"abc", "xyz", "ghi", "def"};
    char *arr2[] = {"abc", "acb", "a"};
    
    if (mx_bubble_sort(arr1, 4) == 3 && mx_bubble_sort(arr2, 3) == 2) {
        // Проверяем, отсортировался ли реально
        if (strcmp(arr1[0], "abc") == 0 && strcmp(arr1[3], "xyz") == 0) exit(0);
    }
    exit(1);
}

void test_t03(void) {
    // Используем правильный лексикографически отсортированный массив
    char *arr[] = {"222", "Abcd", "ab", "abc", "az", "z"};
    int count = 0;
    
    // "ab" находится по индексу 2.
    // Binary Search (size 6):
    // 1. L=0, R=5, Mid=2 ("ab"). MATCH. Count = 1.
    int res1 = mx_binary_search(arr, 6, "ab", &count);
    
    if (res1 == 2 && count == 1) {
        // Тест 2: Ищем "222" (index 0)
        // 1. Mid=2 ("ab") > "222". Right = 1.
        // 2. L=0, R=1. Mid=0 ("222"). MATCH. Count = 2.
        count = 0;
        int res2 = mx_binary_search(arr, 6, "222", &count);
        if (res2 == 0 && count == 2) exit(0);
    }
    
    printf("Debug T03: res=%d, count=%d\n", res1, count);
    exit(1);
}

void test_t04(void) {
    char *arr1[] = {"12aaaaaaaaaa", "11aaaaaaaaa", "13aaaaaaaaaaa", "5aaaa", "6aaaaa"};
    char *arr2[] = {"abc", "ab", "aaaaa", "aaaa", "aaa"};
    if (mx_insertion_sort(arr1, 5) == 7 && mx_insertion_sort(arr2, 5) == 4) exit(0);
    else exit(1);
}

void test_t05(void) {
    char *arr1[] = {"Abcd", "a", "abc", "abc", "Z", "z", "AbCd"};
    // Сортировка выбором по длине, потом лексикографически
    // Ожидаемый порядок: Z, a, z, abc, abc, AbCd, Abcd
    
    int swaps = mx_selection_sort(arr1, 7);
    
    // Проверяем первые элементы (длина 1)
    if (strlen(arr1[0]) == 1 && strlen(arr1[1]) == 1 && strlen(arr1[2]) == 1) {
        // Проверяем стабильность сортировки по длине
        if (strlen(arr1[6]) == 4) exit(0);
    }
    
    printf("Debug T05: swaps=%d\n", swaps);
    exit(1);
}

void test_t06(void) {
    int arr[5] = {1, 2, 3, 4, 5};
    mx_arr_rotate(arr, 5, 2);
    if (arr[0] != 4 || arr[1] != 5) exit(1); // 4, 5, 1, 2, 3

    int arr2[5] = {1, 2, 3, 4, 5};
    mx_arr_rotate(arr2, 5, -2);
    if (arr2[0] != 3 || arr2[4] != 2) exit(1); // 3, 4, 5, 1, 2
    
    int arr3[5] = {1, 2, 3, 4, 5};
    mx_arr_rotate(arr3, 5, 11);
    if (arr3[0] != 5 || arr3[1] != 1) exit(1); // 5, 1, 2, 3, 4

    exit(0);
}

void run_test(void (*func)(void), const char *task_name) {
    printf("Running %s... ", task_name);
    fflush(stdout);
    pid_t pid = fork();
    if (pid == 0) { func(); exit(0); }
    else if (pid > 0) {
        int status; wait(&status);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) printf(GREEN "[OK]" RESET "\n");
            else printf(RED "[FAIL]" RESET "\n");
        } else printf(RED "[CRASH]" RESET "\n");
    }
}

int main(void) {
    printf("=== SPRINT 06 MASTER TESTER ===\n\n");
    run_test(test_t01, "Task 01 (Linear Search) ");
    run_test(test_t02, "Task 02 (Bubble Sort)   ");
    run_test(test_t03, "Task 03 (Binary Search) ");
    run_test(test_t04, "Task 04 (Insertion Sort)");
    run_test(test_t05, "Task 05 (Selection Sort)");
    run_test(test_t06, "Task 06 (Array Rotate)  ");
    printf("\n=== DONE ===\n");
    return 0;
}
