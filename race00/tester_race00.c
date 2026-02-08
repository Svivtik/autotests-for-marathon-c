#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Цвета для удобства
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

// Прототипы функций (согласно race00.pdf)
void mx_printchar(char c);
void mx_cube(int n);
void mx_pyramid(int n);

// ==========================================
// ЛОГИКА ТЕСТОВ
// ==========================================

void test_cube() {
    printf(CYAN "\n=== TESTING TASK 00: CUBE ===" RESET "\n");

    printf(YELLOW "1. Test n=1 (Edge case)" RESET ": Expect [NO OUTPUT]\n");
    printf("--- START ---\n");
    mx_cube(1);
    printf("--- END ---\n");

    printf(YELLOW "2. Test n=4 (Standard)" RESET ": Expect [CUBE size 4]\n");
    printf("--- START ---\n");
    mx_cube(4);
    printf("--- END ---\n");
    
    printf(YELLOW "3. Test n=5 (Standard)" RESET ": Expect [CUBE size 5]\n");
    printf("--- START ---\n");
    mx_cube(5);
    printf("--- END ---\n");

    exit(0);
}

void test_pyramid() {
    printf(CYAN "\n=== TESTING TASK 01: PYRAMID ===" RESET "\n");

    printf(YELLOW "1. Test n=1 (Edge case)" RESET ": Expect [NO OUTPUT]\n");
    printf("--- START ---\n");
    mx_pyramid(1);
    printf("--- END ---\n");

    printf(YELLOW "2. Test n=3 (Odd number)" RESET ": Expect [NO OUTPUT] (Must be even)\n");
    printf("--- START ---\n");
    mx_pyramid(3);
    printf("--- END ---\n");

    printf(YELLOW "3. Test n=4 (Standard)" RESET ": Expect [PYRAMID size 4]\n");
    printf("--- START ---\n");
    mx_pyramid(4);
    printf("--- END ---\n");

    printf(YELLOW "4. Test n=6 (Standard)" RESET ": Expect [PYRAMID size 6]\n");
    printf("--- START ---\n");
    mx_pyramid(6);
    printf("--- END ---\n");

    exit(0);
}

// ==========================================
// ЗАПУСК В ОТДЕЛЬНЫХ ПРОЦЕССАХ
// ==========================================
void run_test(void (*func)(), const char *task_name) {
    pid_t pid = fork();

    if (pid == 0) {
        // Дочерний процесс
        func();
        exit(0);
    } else if (pid > 0) {
        // Родительский процесс
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            // Тест завершился штатно (даже если вывод кривой, программа не упала)
            printf(GREEN "[DONE] %s finished without crashing." RESET "\n", task_name);
        } else if (WIFSIGNALED(status)) {
            // Программа упала (Segfault и т.д.)
            printf(RED "[CRASH] %s failed (Segmentation Fault or similar)!" RESET "\n", task_name);
        }
    } else {
        perror("Fork failed");
    }
}

int main() {
    printf("=== RACE 00 MASTER TESTER ===\n");
    printf("Note: Verify the ASCII shapes visually.\n");

    run_test(test_cube, "MX_CUBE");
    run_test(test_pyramid, "MX_PYRAMID");

    printf("\n=== ALL TESTS FINISHED ===\n");
    return 0;
}