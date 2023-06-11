# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aotsala <aotsala@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 22:27:48 by aotsala           #+#    #+#              #
#    Updated: 2023/06/08 04:19:45 by aotsala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
OBJ = $(SRC:.c=.o)

SRC = philo_bonus.c utils_bonus.c setup_bonus.c routine_bonus.c

CC = cc
CFLAGS = -Wall -Werror -Wextra

COMP = $(CC) $(CFLAGS)

RM = rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
		$(COMP) $(OBJ) -o $(NAME)

bonus:	$(NAME)

clean:
		$(RM) $(OBJ)
		
fclean:	clean
		$(RM) $(NAME)

re:		fclean all