# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abourenn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/19 22:13:37 by abourenn          #+#    #+#              #
#    Updated: 2019/06/19 22:15:54 by abourenn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCPATH	=	src/

LIB		=	lib/

SRC		=	$(SRCPATH)main.c \
			$(SRCPATH)draw.c \

OBJ = $(SRC:.c=.o)

FLAGS = -Wall\
		-Wextra\
		-Werror\

HEADER = includes\

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB)libft
	make -C $(LIB)mlx
	gcc $(FLAGS) $^ -o $(NAME) $(LIB)libft/libft.a $(LIB)mlx/libmlx.a -I $(HEADER) -lmlx -framework OpenGL -framework AppKit -g

%.o: %.c
	gcc $(FLAGS) -o $@ -c $^ -I $(HEADER)

clean:
	/bin/rm -rf $(OBJ)
	make -C $(LIB)libft clean
	make -C $(LIB)mlx clean

fclean: clean
	/bin/rm -rf $(NAME)
	/bin/rm -rf $(LIB)libft/libft.a
	/bin/rm -rf $(LIB)mlx/libmlx.a

re: fclean all
