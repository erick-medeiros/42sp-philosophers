NAME = philo

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g
CC = cc
RM = rm -fr

INC_DIR = include/
SRC_DIR = src/
OBJ_DIR = obj/

HEADERS = philo.h
FILES = main.c
FILES += init/arguments.c
FILES += utils/ft_atoi.c

SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))
INC = $(addprefix $(INC_DIR), $(HEADERS))

REQUIRED_DIRS = $(sort $(dir $(OBJ)))

$(NAME): $(REQUIRED_DIRS) $(INC) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(REQUIRED_DIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# utils

norm:
	@echo "norminette include src | grep Error"
	@norminette include src | grep Error || true

install: # ubuntu
	sudo apt install bear clang-format libcriterion-dev

bear:
	bear -- make re

tests: norm
	@make -s -C tests
	./tests/unit-tests
	@make -s -C tests clean

.PHONY: all clean fclean re norm install bear tests