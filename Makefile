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

NAME		=	libft_malloc.so

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC			=	clang
# NASM		= 	nasm
FLAGS		=	-Wall -Werror -Wextra -O3 -ffast-math -march=native -flto -fPIC
# SFLAGS		=	-f elf64 -O3
# LIB_FLAGS	=	-L$(LIB_PATH) $(LIB_FLAG)
INC_DIR		=	./includes/
INCLUDES	=	libft_malloc.h
# OTOOL_INC_DIR	=	otool/includes/
# OTOOL_INCLUDES	=	ft_otool.h
# COMMON_INC_DIR	=	common/includes/
# COMMON_INCLUDES	=	common.h

SRC_PATH	=	./srcs/
# OTOOL_SRC_PATH	=	./otool/srcs/
# COMMON_SRC_PATH	=	./common/srcs/

BIN_PATH	=	./bins/
# OTOOL_BIN_PATH	=	./otool/bins/
# COMMON_BIN_PATH	=	./common/bins/
# LIB_PATH	=	./libft/

SRC		=		malloc.c		\
				free.c			\
				realloc.c		\
				reallocarray.c	\
				calloc.c		\
				show_alloc_mem.c		\
				ft_putnbr.c		\

# ASM_SRC	= unpack.s	\

BIN			=	$(SRC:.c=.o)
# ASM_BIN = $(ASM_SRC:.s=.o)

# LIB_FLAG			=	-lft
# LIB						=	libft.a

BINS				=	$(addprefix $(BIN_PATH), $(BIN))
# SRCS				=	$(addprefix $(SRC_PATH), $(SRC))
# ASM_BINS			= $(addprefix $(BIN_PATH), $(ASM_BIN))
# LIBS				=	$(addprefix $(LIB_PATH), $(LIB))
INCS				=	$(addprefix $(INC_DIR), $(INCLUDES))

.PHONY: all clean fclean re

#__________COLORS__________#

R			=	\033[0;31m
G			=	\033[32;7m
B			=	\033[0;34m
N			=	\33[0m

#__________RULES__________#

all: $(NAME)

# libft: $(LIBS)

$(NAME): $(BINS)
	@$(CC) $(FLAGS) -shared -o $@ $(BINS) -I $(INCS)
	@echo "\n\n$(B)[Dylib \"$(NAME)\" READY]"
# make_libft:

# 		@make -C $(LIB_PATH)

# $(LIBS):

# 	@make -C $(LIB_PATH)

$(BIN_PATH)%.o: $(SRC_PATH)%.c $(INCS)

	@mkdir -p $(BIN_PATH) || true
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $< && echo "${G} ${N}\c"

# $(BIN_PATH)%.o: $(SRC_PATH)%.s $(INCS)

# 	@mkdir -p $(BIN_PATH) || true
# 	@$(NASM) $(SFLAGS) -I $(INC_DIR) -o $@ $< && echo "${G} \c"

test:
	@LD_PRELOAD=./$(NAME) /bin/ls

clean:

	@echo "${R}[CLEANING $(NAME) BINARIES]\n"
	@rm -Rf $(BIN_PATH)

fclean: clean

	@echo "\n${R}[REMOVING \"$(NAME)\"]"
	@rm -f $(NAME)

re: fclean all
