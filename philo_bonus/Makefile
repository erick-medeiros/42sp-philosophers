NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -pthread
CC = cc
RM = rm -fr

SRC_DIR = src/
OBJ_DIR = obj/

HEADERS = src/philo_bonus.h

FILES = main_bonus.c
FILES += check_bonus.c data_bonus.c dinner_bonus.c finish_bonus.c log_bonus.c
FILES += routine_bonus.c semaphore_bonus.c string_bonus.c utils_bonus.c

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

.PHONY: all clean fclean re norm install bear
