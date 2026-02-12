#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

// ==========================================
// ПРОТОТИПЫ (только для функций, T00-T02 тестируем через запуск бинарников)
// ==========================================
int mx_factorial_iter(int n);
int mx_factorial_rec(int n);

// ==========================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// ==========================================

// Функция для запуска внешней программы и захвата её вывода
// Возвращает 1, если вывод совпал с ожидаемым, иначе 0
int check_output(const char *cmd, const char *expected_output) {
    FILE *fp;
    char path[1035];
    char actual_output[4096] = "";

    // Запускаем команду
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 0;
    }

    // Читаем вывод
    while (fgets(path, sizeof(path), fp) != NULL) {
        strcat(actual_output, path);
    }
    pclose(fp);

    // Сравниваем
    if (strcmp(actual_output, expected_output) == 0) {
        return 1;
    } else {
        printf("   Expected:\n%s\n   Got:\n%s\n", expected_output, actual_output);
        return 0;
    }
}

// ==========================================
// ТЕСТЫ
// ==========================================

void test_t00(void) {
    // Проверяем ./t00/mx_print_name c аргументами
    // Ожидаем: ./t00/mx_print_name\n2\n (имя + кол-во аргументов включая имя)
    // Аргументы запуска: "arg1" -> argc будет 2
    
    // Внимание: путь к программе зависит от того, как вы её скомпилируете. 
    // Тестер предполагает, что бинарник лежит в папке t00
    if (access("t00/mx_print_name", F_OK) != 0) {
        printf(RED "[MISSING BINARY]" RESET " Compile t00/mx_print_name first!\n");
        exit(1);
    }

    if (check_output("./t00/mx_print_name \"Follow\"", "./t00/mx_print_name\n2\n")) {
        exit(0);
    } else {
        exit(1);
    }
}

void test_t01(void) {
    if (access("t01/mx_print_args", F_OK) != 0) {
        printf(RED "[MISSING BINARY]" RESET " Compile t01/mx_print_args first!\n");
        exit(1);
    }

    const char *cmd = "./t01/mx_print_args One Two Three";
    const char *expected = "One\nTwo\nThree\n";
    
    if (check_output(cmd, expected)) exit(0);
    else exit(1);
}

void test_t02(void) {
    if (access("t02/mx_sum_args", F_OK) != 0) {
        printf(RED "[MISSING BINARY]" RESET " Compile t02/mx_sum_args first!\n");
        exit(1);
    }

    // Тест 1: Обычная сумма
    if (!check_output("./t02/mx_sum_args 10 20 30", "60\n")) exit(1);

    // Тест 2: С мусором
    if (!check_output("./t02/mx_sum_args 10 a 20 b +10", "40\n")) exit(1); // 10 + 20 + 10

    // Тест 3: Отрицательные
    if (!check_output("./t02/mx_sum_args -5 -5", "-10\n")) exit(1);

    exit(0);
}

void test_t03(void) {
    if (mx_factorial_iter(0) == 1 &&
        mx_factorial_iter(1) == 1 &&
        mx_factorial_iter(5) == 120 &&
        mx_factorial_iter(12) == 479001600 &&
        mx_factorial_iter(-1) == 0 &&
        mx_factorial_iter(13) == 0) // Overflow check
        exit(0);
    else
        exit(1);
}

void test_t04(void) {
    if (mx_factorial_rec(0) == 1 &&
        mx_factorial_rec(1) == 1 &&
        mx_factorial_rec(5) == 120 &&
        mx_factorial_rec(12) == 479001600 &&
        mx_factorial_rec(-1) == 0 &&
        mx_factorial_rec(13) == 0)
        exit(0);
    else
        exit(1);
}

// ==========================================
// ЗАПУСКАТОР (Fork wrapper)
// ==========================================
void run_test(void (*func)(void), const char *task_name) {
    printf("Running %s... ", task_name);
    fflush(stdout);

    pid_t pid = fork();

    if (pid == 0) {
        func();
        exit(0);
    } else if (pid > 0) {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) printf(GREEN "[OK]" RESET "\n");
            else printf(RED "[FAIL]" RESET "\n");
        } else {
            printf(RED "[CRASH]" RESET "\n");
        }
    } else {
        perror("Fork failed");
    }
}

int main(void) {
    printf("=== SPRINT 05 MASTER TESTER ===\n");
    printf("Checking compiled binaries for T00-T02 and functions for T03-T04\n\n");

    run_test(test_t00, "Task 00 (Print Name)    ");
    run_test(test_t01, "Task 01 (Print Args)    ");
    run_test(test_t02, "Task 02 (Sum Args)      ");
    run_test(test_t03, "Task 03 (Iter Factorial)");
    run_test(test_t04, "Task 04 (Rec Factorial) ");

    printf("\n=== DONE ===\n");
    return 0;
}
