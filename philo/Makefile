NAME      		=		philo

CC              =       cc

FLAG            =		-Wextra -Wall -Werror -pthread

C_FILE      	=       main.c	\
						ft_atoll.c \
						time.c \
						init.c \
						thread.c \
						exit.c \
						routine.c \
						monitoring.c \

SRC_DIR         =       ./

INC_DIR         =       ./

SRC				=		$(addprefix $(SRC_DIR),$(C_FILE))

OBJ				=		$(SRC:.c=.o)

.c.o:
		$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
		@echo "\033[0;33m\nCOMPILING PHILOSOPHERS...\n"
		$(CC) $(FLAG) $(OBJ) -o $(NAME)
		@echo "\033[1;32m./philo created\033[0m\n"

clean:
		@echo "\033[0;31mDeleting all object...\n"
		@rm -f $(OBJ) $(NAME)
		@echo "\033[1;32mDone\033[0m\n"

fclean: clean
		@echo "\033[0;31mDeleting executable..."
		@rm -f $(NAME)
		@echo "\033[1;32mDone\033[0m\n"

re: fclean all

.PHONY: all clean fclean re