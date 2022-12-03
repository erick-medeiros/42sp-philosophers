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
	norminette | grep Error || true

install:
	sudo apt install bear

bear:
	bear -- make re

.PHONY: all clean fclean re norm install bear