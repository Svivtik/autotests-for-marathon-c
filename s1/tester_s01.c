#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Colors
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

// Prototypes
void mx_say_wake_up(void);
void mx_printchar(char c);
void mx_print_alphabet(void);
int mx_strlen(const char *s);
void mx_printstr(const char *s);

// Tests
void test_t01(void) {
    printf("   [Visual Check] Expected: 'Wake up, NEO \\ (^_^)/ ...' then 'The Matrix has you ...'\n");
    mx_say_wake_up();
    exit(0);
}

void test_t02(void) {
    printf("   [Visual Check] Expected: 'G'\n");
    mx_printchar('G');
    printf("\n");
    exit(0);
}

void test_t03(void) {
    printf("   [Visual Check] Expected: AbCdEfGhIjKlMnOpQrStUvWxYz\n");
    mx_print_alphabet();
    exit(0);
}

void test_t04(void) {
    if (mx_strlen("Hello") == 5 && mx_strlen("") == 0 && mx_strlen("123") == 3) exit(0);
    else exit(1);
}

void test_t05(void) {
    printf("   [Visual Check] Expected: 'Knock, knock, Neo.'\n");
    mx_printstr("Knock, knock, Neo.");
    printf("\n");
    exit(0);
}

// Launching functoin (fork)
void run_test(void (*func)(void), const char *task_name) {
    printf("Running %s... \n", task_name);
    fflush(stdout);
    pid_t pid = fork();

    if (pid == 0) {
        func();
        exit(0);
    } else {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) printf(GREEN "[OK]" RESET "\n\n");
            else printf(RED "[FAIL]" RESET " (Logic Error)\n\n");
        } else printf(RED "[CRASH]" RESET " (Segfault)\n\n");
    }
}

int main(void) {
    printf("=== SPRINT 01 TESTER (Tasks 01-05) ===\n\n");
    run_test(test_t01, "Task 01 (Say Wake Up)");
    run_test(test_t02, "Task 02 (Print Char)");
    run_test(test_t03, "Task 03 (Print Alphabet)");
    run_test(test_t04, "Task 04 (Strlen)");
    run_test(test_t05, "Task 05 (Printstr)");
    return 0;
}
