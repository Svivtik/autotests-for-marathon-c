clang-command:

clang -std=c11 -Wall -Wextra -Werror -Wpedantic \
tester.c \
t00/mx_deref_pointer.c \
t01/mx_ref_pointer.c \
t02/mx_reverse_case.c t02/mx_tolower.c t02/mx_toupper.c t02/mx_islower.c t02/mx_isupper.c \
t03/mx_swap_char.c \
t04/mx_str_reverse.c t04/mx_strlen.c \
t05/mx_strcmp.c \
t06/mx_strcpy.c \
t07/mx_str_separate.c \
t08/mx_pow.c \
-o master_test


start command:

./master_test