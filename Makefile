# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/12/10 21:06:37 by pduhard-     #+#   ##    ##    #+#        #
#    Updated: 2019/03/04 11:32:24 by pduhard-    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

##__________CONFIG__________#


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		=	libft_malloc_$(HOSTTYPE).so

CC			=	clang

FLAGS		=	-Wall -Werror -Wextra -O3 -ffast-math -march=native -flto -fPIC

INC_PATH	=	./includes/
SRC_PATH	=	./srcs/
BIN_PATH	=	./bins/

INCLUDES	=	libft_malloc.h

SRC		=		malloc.c				\
				free.c					\
				realloc.c				\
				reallocarray.c			\
				calloc.c				\
				show_alloc_mem.c		\
				show_alloc_mem_hex.c	\
				show_utils.c			\
				heap.c					\
				block.c					\
				find.c					\
				ft_putnbr.c				\
				ft_putstr.c				\
				ft_strlen.c				\
				ft_bzero.c				\

BIN			=	$(SRC:.c=.o)

BINS				=	$(addprefix $(BIN_PATH), $(BIN))
INCS				=	$(addprefix $(INC_PATH), $(INCLUDES))

.PHONY: all clean fclean re

#__________COLORS__________#

R			=	\033[0;31m
G			=	\033[32;7m
B			=	\033[0;34m
N			=	\33[0m

#__________RULES__________#

all: $(NAME)

$(NAME): $(BINS)
	@$(CC) $(FLAGS) -shared -lpthread  -Wl,-soname,libft_malloc.so -o $@ $(BINS) -I $(INC_PATH)
	@test -f libft_malloc.so || ln -s libft_malloc_$(HOSTTYPE).so libft_malloc.so
	@echo "\n\n$(B)[Dylib \"$(NAME)\" READY]"

$(BIN_PATH)%.o: $(SRC_PATH)%.c $(INCS)

	@mkdir -p $(BIN_PATH) || true
	@$(CC) $(FLAGS) -I $(INC_PATH) -o $@ -c $< && echo "${G} ${N}\c"

clean:

	@echo "${R}[CLEANING $(NAME) BINARIES]\n"
	@rm -Rf $(BIN_PATH)

fclean: clean

	@echo "\n${R}[REMOVING \"$(NAME)\"]"
	@rm -f $(NAME)
	@echo "\n${R}[REMOVING \"libft_malloc.so\"]"
	@rm -f libft_malloc.so

re: fclean all
