#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <limits.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

// Prototypes
void mx_is_positive(int i);
bool mx_isalpha(int c);
bool mx_isdigit(int c);
bool mx_isspace(char c);
bool mx_islower(int c);
bool mx_isupper(int c);
int mx_tolower(int c);
int mx_toupper(int c);
void mx_printint(int n);

void test_t00(void) {
    printf("   [Check] 5 -> positive, -5 -> negative, 0 -> zero\n");
    mx_is_positive(5);
    mx_is_positive(-5);
    mx_is_positive(0);
    exit(0);
}

void test_t01(void) { if(mx_isalpha('A') && mx_isalpha('z') && !mx_isalpha('1')) exit(0); else exit(1); }
void test_t02(void) { if(mx_isdigit('0') && mx_isdigit('9') && !mx_isdigit('a')) exit(0); else exit(1); }
void test_t03(void) { if(mx_isspace(' ') && mx_isspace('\t') && !mx_isspace('A')) exit(0); else exit(1); }
void test_t04(void) { if(mx_islower('z') && !mx_islower('Z') && !mx_islower('3')) exit(0); else exit(1); }
void test_t05(void) { if(mx_isupper('Z') && !mx_isupper('z') && !mx_isupper('!')) exit(0); else exit(1); }
void test_t06(void) { if(mx_tolower('Z') == 'z' && mx_tolower('a') == 'a') exit(0); else exit(1); }
void test_t07(void) { if(mx_toupper('z') == 'Z' && mx_toupper('A') == 'A') exit(0); else exit(1); }

void test_t08(void) {
    printf("   [Check] Expected: 25, -2147483648, 0\n");
    mx_printint(25); printf("\n");
    mx_printint(-2147483648); printf("\n");
    mx_printint(0); printf("\n");
    exit(0);
}

void run_test(void (*func)(), const char *name) {
    printf("Running %s... ", name);
    fflush(stdout);
    pid_t pid = fork();
    if(pid == 0) {
        // For visual tests, we add a line break
        if(name[6] == '0' || name[6] == '8') printf("\n"); 
        func(); exit(0);
    } else {
        int s; wait(&s);
        if(WIFEXITED(s) && WEXITSTATUS(s)==0) printf(GREEN "[OK]" RESET "\n");
        else if(WIFSIGNALED(s)) printf(RED "[CRASH]" RESET "\n");
        else printf(RED "[FAIL]" RESET "\n");
    }
}

int main(void) {
    printf("=== SPRINT 02 TESTER ===\n");
    run_test(test_t00, "Task 00 (Is Positive)");
    run_test(test_t01, "Task 01 (Is Alpha)");
    run_test(test_t02, "Task 02 (Is Digit)");
    run_test(test_t03, "Task 03 (Is Space)");
    run_test(test_t04, "Task 04 (Is Lower)");
    run_test(test_t05, "Task 05 (Is Upper)");
    run_test(test_t06, "Task 06 (To Lower)");
    run_test(test_t07, "Task 07 (To Upper)");
    run_test(test_t08, "Task 08 (Print Int)");
    return 0;
}