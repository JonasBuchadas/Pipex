### COMPILATION ###
CC=			gcc
CFLAGS=		-Wall -Werror -Wextra

### EXECUTABLE ###
NAME=		pipex

### PATHS ###
LIBFT_PATH=	./libft/
INCL_PATH=	incl/
SRCS_PATH=	srcs/
OBJS_PATH=	objs/

### SOURCE FILES ###
SRC_NAME=	$(NAME).c
SRC_BONUS=	$(NAME)_bonus.c
SRCS=		utils.c \
			check_modes.c \
			cmd_exec.c \
			error_handling.c 
SRCS_NAME=	$(addprefix $(SRCS_PATH), $(SRC_NAME) $(SRCS))
SRCS_BONUS=	$(addprefix $(SRCS_PATH), $(SRC_BONUS) $(SRCS))

### OBJECT FILES ### 
OBJ_NAME=	$(SRC_NAME:.c=.o)
OBJ_BONUS=	$(SRC_BONUS:.c=.o)
OBJS=		$(SRCS:.c=.o)
OBJS_NAME=	$(addprefix $(OBJS_PATH), $(OBJ_NAME) $(OBJS))
OBJS_BONUS=	$(addprefix $(OBJS_PATH), $(OBJ_BONUS) $(OBJS))

### LIBFT ###
LIBFTMAKE=  make bonus --silent -C $(LIBFT_PATH)
LIBFT=      -L$(LIBFT_PATH) -lft

### INCLUDES ###
INC=		-I $(LIBFT_PATH)$(INCL_PATH) -I $(INCL_PATH)

### COLOURS ###
GREEN= \033[1;32m
RED= \033[1;31m
DEFAULT= \033[0m

### IMPLICT RULES ###
%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

### ACTIVE RULES ###
all: $(OBJS_PATH) $(OBJS_NAME)
	@$(LIBFTMAKE)
	@$(CC) $(CFLAGS) $(OBJS_NAME) $(INC) $(LIBFT) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) Program created$(DEFAULT)"

bonus: $(OBJS_PATH) $(OBJS_BONUS)
	@$(LIBFTMAKE)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(INC) $(LIBFT) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) Program created$(DEFAULT)"

$(OBJS_PATH):
	@mkdir -p $@
	
clean:
	@make $@ --silent -C $(LIBFT_PATH)
	@rm -rf $(OBJS_PATH)
	@echo -e "$(RED)Object files removed$(DEFAULT)"

fclean: clean
	@make $@ --silent -C $(LIBFT_PATH)
	@echo -e "$(RED)Libft removed$(DEFAULT)"
	@rm -f $(NAME)
	@echo -e "$(RED)$(NAME) Program removed$(DEFAULT)"

re: fclean all

### NORMINETTE ###
norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS_PATH)
	@norminette -R CheckDefine $(INCL_PATH)

### PHONY RULE ###
.PHONY:	all bonus clean fclean re norm
