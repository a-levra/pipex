# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 16:18:39 by alevra            #+#    #+#              #
#    Updated: 2023/01/19 17:57:01 by alevra           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = pipex

HEADER = $(NAME).h

SRC =	pipex.c

SRC_BONUS =

FLAGS = -Wall -Wextra -Werror	

OS := $(shell uname)
ifeq ($(OS),Darwin)
 
else

endif
	
OBJ = $(addprefix obj/,$(SRC:.c=.o))
OBJ_BONUS = $(addprefix obj/,$(SRC_BONUS:.c=.o))

FSAN = #-fsanitize=address

all	: create_obj_folder
	make -C libft
	make $(NAME)
	@make end_message

$(NAME): libft/libft.a $(OBJ)
	cc $(OBJ) $(FSAN) -g3  -L ./libft -lft -o $(NAME)

$(NAME)_bonus: libft/libft.a $(OBJ) $(OBJ_BONUS)
	cc $(OBJ) $(OBJ_BONUS) $(FSAN) -g3  -L ./libft -lft -o $(NAME)_bonus

obj/%.o : src/%.c src/$(HEADER) Makefile
		cc -c -g3 ${FLAGS} $(FSAN) -I libft $< -o $@

create_obj_folder :
	mkdir -p obj

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	@if [ -d "./obj" ]; then\
		rm -r obj;\
	fi
	make clean -C libft

fclean: clean
	make fclean -C libft
	rm -f $(NAME)
	rm -f $(NAME)_bonus

re: 
	make fclean
	make all

end_message:
	@echo "Done !"

bonus:

.PHONY: all clean fclean re create_obj_folder end_message bonus