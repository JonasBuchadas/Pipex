CC=			gcc

CFLAGS=		-Wall -Werror -Wextra -g

NAME=		pipex

SRCS=		pipex.c \
			utils.c \
			error_handling.c \
			check_modes.c

OBJS=		$(SRCS:.c=.o)

OBJ_BOTH=	$(SRC_BOTH:.c=.o)

LIBFT_DIR=	./libft/

LIBFTMAKE=	make bonus --silent -C $(LIBFT_DIR)

LIBFT=		-L$(LIBFT_DIR) -lft

INC=		-I $(LIBFT_DIR)

all: $(NAME)

$(BONUS): $(OBJ_BONUS) $(OBJ_BOTH) $(LIBFT)
	@$(CC) $(CFLAGS) $^ $(INC) -o $@
	@echo -e "$(GREEN)$@ Program created$(DEFAULT)"

$(NAME): $(OBJS) 
	@$(LIBFTMAKE)
	@$(CC) $(CFLAGS) $^ $(INC) $(LIBFT) -o $@
	@echo -e "$(GREEN)$@ Program created$(DEFAULT)"

$(OBJS): $(SRCS) 
	@$(CC) $(CFLAGS) $(INC) -c $^

$(OBJ_BONUS): $(SRC_BONUS)
	@$(CC) $(CFLAGS) $(INC) -c $^

$(OBJ_BOTH): $(SRC_BOTH)
	@$(CC) $(CFLAGS) $(INC) -c $^

clean:
	@make clean --silent -C $(LIBFT_DIR)
	@rm -f $(OBJS) $(OBJ_BONUS) $(OBJ_BOTH)
	@echo -e "$(RED)Object files removed$(DEFAULT)"

fclean: clean
	@make fclean --silent -C $(LIBFT_DIR)
	@echo -e "$(RED)Libft removed$(DEFAULT)"
	@rm -f $(NAME)
	@echo -e "$(RED)$(NAME) Program removed$(DEFAULT)"

re: fclean all

GREEN= \033[1;32m
RED= \033[1;31m
DEFAULT= \033[0m
