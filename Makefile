CC=			gcc

CFLAGS=		-Wall -Werror -Wextra

NAME=		pipex

SRC_NAME=	$(NAME).c

SRC_BONUS=	$(NAME)_bonus.c

SRCS=		utils.c \
			check_modes.c \
			cmd_exec.c \
			error_handling.c \

OBJ_NAME=	$(SRC_NAME:.c=.o)

OBJ_BONUS=	$(SRC_BONUS:.c=.o)

OBJS=		$(SRCS:.c=.o)

LIBFT_DIR=	./libft/

LIBFTMAKE=  make bonus --silent -C $(LIBFT_DIR)

LIBFT=      -L$(LIBFT_DIR) -lft

INC=		-I $(LIBFT_DIR)

all: $(OBJ_NAME) $(OBJS) 
	@$(LIBFTMAKE)
	@$(CC) $(CFLAGS) $^ $(INC) $(LIBFT) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) Program created$(DEFAULT)"

bonus: $(OBJ_BONUS) $(OBJS)
	@$(LIBFTMAKE)
	@$(CC) $(CFLAGS) $^ $(INC) $(LIBFT) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) Program created$(DEFAULT)"

$(OBJ_NAME): $(SRC_NAME) 
	@$(CC) $(CFLAGS) $(INC) -c $^

$(OBJ_BONUS): $(SRC_BONUS)
	@$(CC) $(CFLAGS) $(INC) -c $^

$(OBJS): $(SRCS) 
	@$(CC) $(CFLAGS) $(INC) -c $^

clean:
	@make $@ --silent -C $(LIBFT_DIR)
	@rm -f $(OBJ_NAME) $(OBJS) $(OBJ_BONUS)
	@echo -e "$(RED)Object files removed$(DEFAULT)"

fclean: clean
	@make fclean --silent -C $(LIBFT_DIR)
	@echo -e "$(RED)Libft removed$(DEFAULT)"
	@rm -f $(NAME)
	@echo -e "$(RED)$(NAME) Program removed$(DEFAULT)"

re: fclean all

.PHONY:	all clean fclean bonus re

GREEN= \033[1;32m
RED= \033[1;31m
DEFAULT= \033[0m
