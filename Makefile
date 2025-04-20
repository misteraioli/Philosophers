#######################################################
## ARGUMENTS

# NAME

NAME	=	philo

# CC FLAG INC

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
INC		=	-Iinc
LDFLAGS	=	-lpthread

# SRC & OBJ DIR

SRC_DIR	=	src/
OBJ_DIR	=	obj/

# RM

RM	=	rm -rf

# HEADERS

HEADER	=	inc/philo.h

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

$(NAME) : $(OBJ_DIR) $(OBJS) Makefile
		$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR) :
		mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER)
		$(CC) $(CFLAGS) $(INC) -c $< -o $@

norm :
		norminette inc src

clean :
		$(RM) $(OBJ_DIR)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re norm
