NAME		=	woody_woodpacker

SRC			=	srcs/main.c		\
		  		srcs/error.c	\
				srcs/pack.c

SRC_ASM		= 	srcs/stub.s

OBJ_ASM		= 	$(SRC_ASM:.s=.o)

OBJ			= 	$(SRC:.c=.o)

INCLUDES	= 	./inc

CC			=	clang

NASM		=	nasm

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Wextra -fsanitize=address -g -I $(INCLUDES)

NFLAGS		= 	-f elf64

$(NAME):	$(OBJ) $(OBJ_ASM)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(OBJ_ASM)

$(OBJ_ASM):	$(SRC_ASM)
		$(NASM) $(NFLAGS) -o $@ $<

all:		$(NAME)

clean:
		$(RM) $(OBJ) $(OBJ_ASM)

fclean:		clean
		$(RM) $(NAME) exec

re:		fclean all

.PHONY:		all clean fclean re
