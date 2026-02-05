# Ucode C Marathon: Auto-Testers Guide

This repository contains instructions and commands for automatically checking tasks for Sprints 01, 02, and 03. The testers are written so that the failure of one task does not stop the checking of the others (process isolation).

## 📁 Where to place files
The tester files (`tester_s01.c`, `tester_s02.c`, `tester_s03.c`) should be located in the **root** of the corresponding sprint repositories.
Example structure:
sprint01/ ├── tester_s01.c <-- Here ├── t00/ ├── t01/ │ └── mx_say_wake_up.c ...

## ⚠️ Important Rule
Before running testers, make sure that the `main` function in your task files (e.g. `t01/mx_say_wake_up.c`) is **COMMENTED OUT or REMOVED**.
The tester contains its own `main` function, and a second one will cause a compilation error.

---

## 🏃 Sprint 01 Instructions

This tester tests **Task 01 - Task 05**.
*Task 00 (Hello World)* is a standalone program with `main.c`, so it is checked manually by running `./hello_world`.

### Compilation
Run this command in the terminal (in the root of sprint 01):

```bash
clang -std=c11 -Wall -Wextra -Werror -Wpedantic \
tester_s01.c \
t01/mx_say_wake_up.c \
t02/mx_printchar.c \
t03/mx_print_alphabet.c \
t04/mx_strlen.c \
t05/mx_printstr.c \
-o tester_01
```

### Run
Run this command in the terminal (in the root of sprint 01):

./tester_01

---

## 🏃 Sprint 02 Instructions

This tester checks Task 00 - Task 08. Task 00 (mx_is_positive) requires Helper functions mx_printstr and mx_strlen inside the t00 folder, as specified in the assignment.

### Compilation

```bash
clang -std=c11 -Wall -Wextra -Werror -Wpedantic \
tester_s02.c\
t00/mx_is_positive.c t00/mx_printstr.c t00/mx_strlen.c \
t01/mx_isalpha.c \
t02/mx_isdigit.c \
t03/mx_isspace.c \
t04/mx_islower.c\
t05/mx_isupper.c \
t06/mx_tolower.c\
t07/mx_toupper.c \
t08/mx_printint.c t08/mx_printchar.c \
-o tester_02
```

### Launch

./tester_02

---

## 🏃 Sprint 03 Instructions

This tester tests Task 00 - Task 08. The test uses a modular approach via fork(), so memory errors (segfaults) in one task won't stop the test.

### Compilation

Make sure the file paths are correct (some tasks use files from previous tasks, for example, mx_strlen in t04).

```bash
clang -std=c11 -Wall -Wextra -Werror -Wpedantic \
tester_s03.c\
t00/mx_deref_pointer.c \
t01/mx_ref_pointer.c \
t02/mx_reverse_case.c t02/mx_tolower.c t02/mx_toupper.c t02/mx_islower.c t02/mx_isupper.c \
t03/mx_swap_char.c \
t04/mx_str_reverse.c t04/mx_strlen.c \
t05/mx_strcmp.c \
t06/mx_strcpy.c \
t07/mx_str_separate.c t07/mx_printchar.c \
t08/mx_pow.c \
-o tester_03
```

### Launch

./tester_03


---
Версия на русском языке:

# Ucode C Marathon: Auto-Testers Guide

Этот репозиторий содержит инструкции и команды для автоматической проверки задач для Sprint 01, 02 и 03. Тестеры написаны так, чтобы падение одной задачи не останавливало проверку остальных (process isolation).

## 📁 Где размещать файлы
Файлы тестеров (`tester_s01.c`, `tester_s02.c`, `tester_s03.c`) должны находиться в **корне** соответствующих репозиториев спринтов.
Пример структуры:
sprint01/ ├── tester_s01.c <-- Сюда ├── t00/ ├── t01/ │ └── mx_say_wake_up.c ...

## ⚠️ Важное правило
Перед запуском тестеров убедитесь, что в ваших файлах задач (например, `t01/mx_say_wake_up.c`) **ЗАКОММЕНТИРОВАНА или УДАЛЕНА функция `main`**.
Тестер содержит свой собственный `main`, и при наличии второго возникнет ошибка компиляции.

---

## 🏃 Sprint 01 Instructions

Этот тестер проверяет **Task 01 - Task 05**.
*Task 00 (Hello World)* является standalone-программой с `main.c`, поэтому проверяется вручную запуском `./hello_world`.

### Компиляция
Выполните эту команду в терминале (в корне спринта 01):

```bash
clang -std=c11 -Wall -Wextra -Werror -Wpedantic \
tester_s01.c \
t01/mx_say_wake_up.c \
t02/mx_printchar.c \
t03/mx_print_alphabet.c \
t04/mx_strlen.c \
t05/mx_printstr.c \
-o tester_01
```

### Запуск
Выполните эту команду в терминале (в корне спринта 01):

./tester_01

---

## 🏃 Sprint 02 Instructions

Этот тестер проверяет Task 00 - Task 08. Для Task 00 (mx_is_positive) требуются вспомогательные функции mx_printstr и mx_strlen внутри папки t00, как указано в задании.

### Компиляция

```bash
clang -std=c11 -Wall -Wextra -Werror -Wpedantic \
tester_s02.c \
t00/mx_is_positive.c t00/mx_printstr.c t00/mx_strlen.c \
t01/mx_isalpha.c \
t02/mx_isdigit.c \
t03/mx_isspace.c \
t04/mx_islower.c \
t05/mx_isupper.c \
t06/mx_tolower.c \
t07/mx_toupper.c \
t08/mx_printint.c t08/mx_printchar.c \
-o tester_02
```

### Запуск

./tester_02

---

## 🏃 Sprint 03 Instructions

Этот тестер проверяет Task 00 - Task 08. Тест использует модульный подход через fork(), поэтому ошибки памяти (segfault) в одной задаче не остановят тест.

### Компиляция

Убедитесь, что пути к файлам верны (в некоторых тасках используются файлы из прошлых тасков, например mx_strlen в t04).

```bash
clang -std=c11 -Wall -Wextra -Werror -Wpedantic \
tester_s03.c \
t00/mx_deref_pointer.c \
t01/mx_ref_pointer.c \
t02/mx_reverse_case.c t02/mx_tolower.c t02/mx_toupper.c t02/mx_islower.c t02/mx_isupper.c \
t03/mx_swap_char.c \
t04/mx_str_reverse.c t04/mx_strlen.c \
t05/mx_strcmp.c \
t06/mx_strcpy.c \
t07/mx_str_separate.c t07/mx_printchar.c \
t08/mx_pow.c \
-o tester_03
```

### Запуск

./tester_03