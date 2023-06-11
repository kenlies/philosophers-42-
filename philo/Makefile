# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aotsala <aotsala@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 22:27:48 by aotsala           #+#    #+#              #
#    Updated: 2023/06/09 14:24:37 by aotsala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
OBJ = $(SRC:.c=.o)

SRC = philo.c utils.c setup.c routine.c

CC = cc
CFLAGS = -Wall -Werror -Wextra

COMP = $(CC) $(CFLAGS)

RM = rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
		$(COMP) $(OBJ) -o $(NAME)

clean:
		$(RM) $(OBJ)
		
fclean:	clean
		$(RM) $(NAME)

re:		fclean all