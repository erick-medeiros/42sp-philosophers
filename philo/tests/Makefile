NAME = unit-tests

CFLAGS = -Wall -Wextra -I../include -g
CFLAGS += --coverage -fprofile-arcs -ftest-coverage -lcriterion
CC = cc
RM = rm -fr
FORMAT = clang-format -i
SRC = $(filter-out ../src/main.c, $(wildcard ../src/*/*.c ../src/*.c *.c))

$(NAME): $(FILES) $(SRC)
	$(FORMAT) *.c
	$(CC) -o $(NAME) $(SRC) $(CFLAGS)

all: $(NAME)

clean:
	$(RM) *.gcda *.gcno

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean re