NAME			= woody_woodpacker

SRCS_DIR = srcs
INC_DIR = inc

SRC_NAMES		=	srcs/main.c \
					srcs/error.c

SRC_ASM_NAMES	=

OBJ_ASM			= $(SRC_ASM_NAMES:.asm=.o)

OBJ		 		= $(SRC_NAMES:.c=.o)

INCLUDES		= ./inc

LIBFT			= ./libft/libft.a

CC				= clang

NASM			= nasm

RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror -I $(INCLUDES)

NFLAGS			=

SRC	 			= $(addprefix $(SRCS_DIR)/, $(SRC_NAMES))
SRC_ASM			= $(addprefix $(SRCS_DIR)/, $(SRC_ASM_NAMES))

# $(LIBFT):
# 	@make -C libft/

$(NAME):	 $(OBJ) $(OBJ_ASM)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(OBJ_ASM)

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

all:		$(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJ) $(OBJ_ASM)

fclean:		clean
	$(RM) libft/libft.a
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
