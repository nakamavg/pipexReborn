# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 21:18:48 by dgomez-m          #+#    #+#              #
#    Updated: 2024/02/24 21:23:45 by dgomez-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ... and then the rules to compile the program
# Compiler and flags
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror 
includes		=	./includes
CFLAGS			+=	-I. -I./includes
RM				=	rm -rf
NAME			=	pipex
BONUS_NAME		=	pipex_bonus

# Libft
LIBFT_DIR		=	lib/libft
LIBFT			=	$(LIBFT_DIR)/libft.a
CFLAGS			+=	-I $(LIBFT_DIR)

# Sources and objects
SRC				=	main.c process.c free.c  error.c here_doc.c
BONUS_SRC		=	main_bonus.c process.c free.c  error.c here_doc.c
OBJ				=	$(SRC:.c=.o)


all: $(NAME) $(BONUS_NAME)
	
$(NAME): $(LIBFT) $(OBJ)
	$(CC)	$(CFLAGS)	-o	$(NAME)	$(OBJ)	-L$(LIBFT_DIR)	-lft
$(BONUS_NAME): $(LIBFT) $(BONUS_SRC)
	$(CC)	$(CFLAGS)	-o	$(BONUS_NAME)	$(BONUS_SRC)	-L$(LIBFT_DIR)	-lft
$(LIBFT):
	 make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	$(RM) $(BONUS_OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re


# ... and then the rules to compile the program