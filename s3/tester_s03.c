#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

// ==========================================
// Colors for nice output
// ==========================================
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

// ==========================================
// Prototypes of sprint functions (from tasks)
// ==========================================
void mx_deref_pointer(char ******str);
void mx_ref_pointer(int i, int ******ptr);
void mx_reverse_case(char *c);
void mx_swap_char(char *s1, char *s2);
void mx_str_reverse(char *s);
int mx_strcmp(const char *s1, const char *s2);
char *mx_strcpy(char *dst, const char *src);
void mx_str_separate(const char *str, char delim);
double mx_pow(double n, unsigned int pow);

// Auxiliary function for Task 07 (needed to check output, but here we just run it)
// ==========================================

// ==========================================
// LOGIC OF TESTS
// ==========================================

void test_t00(void) {
    char *p1;
    char **p2 = &p1;
    char ***p3 = &p2;
    char ****p4 = &p3;
    char *****p5 = &p4;
    char ******p6 = &p5;

    mx_deref_pointer(p6);

    if (strcmp(p1, "Follow the white rabbit!") == 0) exit(0);
    else {
        fprintf(stderr, "Expected 'Follow the white rabbit!', got '%s'\n", p1);
        exit(1);
    }
}

void test_t01(void) {
    int val;
    int *p1 = &val;
    int **p2 = &p1;
    int ***p3 = &p2;
    int ****p4 = &p3;
    int *****p5 = &p4;
    int ******p6 = &p5;

    mx_ref_pointer(42, p6);

    if (val == 42) exit(0);
    else exit(1);
}

void test_t02(void) {
    char str[] = "HeLLo Neo";
    mx_reverse_case(str);
    if (strcmp(str, "hEllO nEO") == 0) exit(0);
    else exit(1);
}

void test_t03(void) {
    char s[] = "ONE";
    mx_swap_char(&s[0], &s[1]); // "NOE"
    if (strcmp(s, "NOE") != 0) exit(1);
    mx_swap_char(&s[1], &s[2]); // "NEO"
    if (strcmp(s, "NEO") != 0) exit(1);
    exit(0);
}

void test_t04(void) {
    char str[] = "game over";
    mx_str_reverse(str);
    if (strcmp(str, "revo emag") == 0) exit(0);
    else exit(1);
}

void test_t05(void) {
    if (mx_strcmp("abc", "abc") == 0 &&
        mx_strcmp("abc", "abd") < 0 &&
        mx_strcmp("abd", "abc") > 0) exit(0);
    else exit(1);
}

void test_t06(void) {
    char src[] = "CopyMe";
    char dst[20];
    mx_strcpy(dst, src);
    if (strcmp(dst, "CopyMe") == 0) exit(0);
    else exit(1);
}

void test_t07(void) {
    printf(YELLOW "\n   [Check output manually below] expected: 'game' then 'over'\n" RESET);
    printf("   --- START OUTPUT ---\n");
    mx_str_separate("game over", ' ');
    printf("   --- END OUTPUT ---\n");
    exit(0);
}

void test_t08(void) {
    if (mx_pow(2, 3) == 8 && mx_pow(2.5, 2) == 6.25 && mx_pow(5, 0) == 1) exit(0);
    else exit(1);
}

// ==========================================
// Test runner function (process isolation with fork)
// ==========================================
void run_test(void (*func)(void), const char *task_name) {
    printf("Running %s... ", task_name);
    fflush(stdout);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        // Close stderr to prevent errors from dumping into the console if you don't want to see them
        // (You can comment out the line below if you need debugging)
        // freopen("/dev/null", "w", stderr); 
        
        func(); // Run the test function
        exit(0); // If function doesn't crash and tests pass
    } else if (pid > 0) {
        // Parent process
        int status;
        wait(&status); // Wait for child to finish
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            if (exit_code == 0) {
                printf(GREEN "[OK]" RESET "\n");
            } else {
                printf(RED "[FAIL]" RESET " (Wrong Answer)\n");
            }
        } else if (WIFSIGNALED(status)) {
            // If the child process was terminated by a signal (e.g., segmentation fault)
            printf(RED "[CRASH]" RESET " (Segmentation Fault or Bus Error)\n");
        }
    } else {
        perror("Fork failed");
    }
}

// ==========================================
// MAIN
// ==========================================
int main(void) {
    printf("=== SPRINT 03 MASTER TESTER ===\n\n");

    run_test(test_t00, "Task 00 (Deref Pointer) ");
    run_test(test_t01, "Task 01 (Ref Pointer)   ");
    run_test(test_t02, "Task 02 (Reverse Case)  ");
    run_test(test_t03, "Task 03 (Swap Char)     ");
    run_test(test_t04, "Task 04 (Str Reverse)   ");
    run_test(test_t05, "Task 05 (Str Cmp)       ");
    run_test(test_t06, "Task 06 (Str Cpy)       ");
    run_test(test_t07, "Task 07 (Str Separate)  ");
    run_test(test_t08, "Task 08 (Pow)           ");

    printf("\n=== DONE ===\n");
    return 0;
}
