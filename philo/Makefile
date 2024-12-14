#######################################################
## ARGUMENTS

NAME	=	philo

CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror
HEADER	=	-Iinc
LIB		=	-lpthread

SRC_DIR	=	src/
OBJ_DIR	=	obj/

RM	=	rm -rf

#######################################################
## SRCS & OBJS

FILES	= \
		main \
		time \
		parse \
		init \
		dinner \
		clean \
		end \

SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

#######################################################
## RULES

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(HEADER) -o $(NAME) $(LIB)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

norm :
		norminette inc src

clean :
		$(RM) $(OBJ_DIR)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean norm re
