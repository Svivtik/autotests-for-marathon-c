#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Colors
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

// --- Includes for tasks ---
// We need to define structs here because header paths might vary in compilation
typedef struct s_intarr {
    int *arr;
    int size;
} t_intarr;

typedef struct s_agent {
    char *name;
    int power;
    int strength;
} t_agent;

// Prototypes
t_intarr *mx_del_dup_sarr(t_intarr *src);
// Task 02 is tested by including the header directly, tricky with single file tester
// so we will simulate Task 02 check logic
t_agent *mx_create_agent(char *name, int power, int strength);
t_agent **mx_create_new_agents(char **name, int *power, int *strength, int count);
void mx_exterminate_agents(t_agent ***agents);
t_agent **mx_only_smiths(t_agent **agents, int strength);
int mx_strcmp(const char *s1, const char *s2);

// --- Tests ---

void test_t01(void) {
    printf("Task 01 (Dup Struct): ");
    int data[] = {1, 2, 2, 3, 4, 4, 5};
    t_intarr src;
    src.arr = malloc(7 * sizeof(int));
    memcpy(src.arr, data, 7 * sizeof(int));
    src.size = 7;

    t_intarr *res = mx_del_dup_sarr(&src);
    
    bool ok = true;
    if (res->size != 5) ok = false;
    int expected[] = {1, 2, 3, 4, 5};
    for(int i=0; i<5; i++) if (res->arr[i] != expected[i]) ok = false;

    if (ok) printf(GREEN "[OK]" RESET "\n");
    else printf(RED "[FAIL]" RESET "\n");

    free(src.arr);
    free(res->arr);
    free(res);
}

void test_t03(void) {
    printf("Task 03 (Create Agent): ");
    t_agent *a = mx_create_agent("Smith", 100, 50);
    if (a && strcmp(a->name, "Smith") == 0 && a->power == 100) {
        printf(GREEN "[OK]" RESET "\n");
        free(a->name);
        free(a);
    } else {
        printf(RED "[FAIL]" RESET "\n");
    }
}

void test_t04_05(void) {
    printf("Task 04/05 (Arr Agents & Exterminate): ");
    char *names[] = {"Smith", "Neo", "Morpheus"};
    int powers[] = {100, 200, 150};
    int strengths[] = {50, 60, 55};
    
    t_agent **agents = mx_create_new_agents(names, powers, strengths, 3);
    if (agents && agents[0] && strcmp(agents[1]->name, "Neo") == 0) {
        mx_exterminate_agents(&agents);
        if (agents == NULL) printf(GREEN "[OK]" RESET "\n");
        else printf(RED "[FAIL - Not NULLed]" RESET "\n");
    } else {
        printf(RED "[FAIL - Creation]" RESET "\n");
    }
}

void test_t06(void) {
    printf("Task 06 (Only Smiths): ");
    char *names[] = {"Smith", "Neo", "Smith", "Smith"};
    int powers[] = {100, 200, 100, 100};
    int strengths[] = {150, 60, 50, 300}; // Only Smith(50) matches < 100
    
    t_agent **agents = mx_create_new_agents(names, powers, strengths, 4);
    
    // Filter strength < 100
    t_agent **smiths = mx_only_smiths(agents, 100);
    
    if (smiths && smiths[0] && smiths[1] == NULL) {
        if (smiths[0]->strength == 50 && strcmp(smiths[0]->name, "Smith") == 0) {
            printf(GREEN "[OK]" RESET "\n");
        } else printf(RED "[FAIL - Wrong Data]" RESET "\n");
    } else {
        printf(RED "[FAIL - Wrong Count]" RESET "\n");
    }
    
    mx_exterminate_agents(&smiths);
}

int main(void) {
    printf("=== SPRINT 08 TESTER ===\n");
    test_t01();
    test_t03();
    test_t04_05();
    test_t06();
    return 0;
}
