NAME = philo

CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -pthread
CC = cc
RM = rm -fr

SRC_DIR = src/
OBJ_DIR = obj/

HEADERS = src/philo.h

FILES = main.c
FILES += check.c data.c dinner.c finish.c log.c routine.c utils.c

SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

REQUIRED_DIRS = $(sort $(dir $(OBJ)))

$(NAME): $(REQUIRED_DIRS) $(HEADERS) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(REQUIRED_DIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

# utils

norm:
	@echo "norminette include src | grep Error"
	@norminette include src | grep Error || true

install: # ubuntu
	sudo apt install bear clang-format libcriterion-dev

bear:
	bear -- make re

leaks:
	clear
	valgrind -q --tool=helgrind ./$(NAME) 5 500 200 200
	valgrind -q --tool=drd ./$(NAME) 5 500 200 200

tests: norm
	@make -s -C tests
	./tests/unit-tests
	@make -s -C tests clean

.PHONY: all clean fclean re norm install bear tests
