
NAME			= woody_woodpacker

SRC				= srcs/main.c

SRC_ASM			=

OBJ_ASM			= $(SRC_ASM:.asm=.o)

OBJ				= $(SRC:.c=.o)

INCLUDES		= ./inc

LIBFT			= ./libft/libft.a

CC				= clang

NASM			= nasm

RM				= rm -f

override CFLAGS	= -Wall -Wextra -Werror -I $(INCLUDES)

override NFLAGS	+=

$(LIBFT):
	@make -C libft/

$(NAME):	$(OBJ) $(OBJ_ASM) $(LIBFT)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(OBJ_ASM)

$(OBJ_ASM):	$(SRC_ASM)
		$(NASM) $(NFLAGS) -o $@ $<

all:		$(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJ) $(OBJ_ASM)

fclean:		clean
	$(RM) libft/libft.a
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
