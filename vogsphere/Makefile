# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 16:18:39 by alevra            #+#    #+#              #
#    Updated: 2023/02/16 17:21:29 by alevra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

HEADER = $(NAME).h

SRC =	pipex.c \
		execute_cmd.c \
		get_args_w_flags_and_paths.c\
		get_path.c\
		utils.c \
		execute_all_cmds.c \
		execute_all_cmds_utils.c

BONUS_FLAG = -DBONUS_FLAG
FLAGS = -Wall -Wextra -Werror
FSAN = -fsanitize=address

OBJ = $(addprefix obj/,$(SRC:.c=.o))
OBJ_BONUS = $(addprefix bonus/,$(SRC:.c=.o))


all	: create_obj_folder
	make -C libft
	make $(NAME)
	@make end_message

obj/%.o : src/%.c src/$(HEADER) Makefile
		cc -c -g3 ${FLAGS} $(FSAN) -I libft $< -o $@

bonus/%.o : src/%.c src/$(HEADER) Makefile
				cc -c -g3 -O3 ${FLAGS} $(FSAN) $(BONUS_FLAG) -I libft $< -o $@

$(NAME): libft/libft.a $(OBJ)
	cc $(OBJ) $(FSAN) -g3  -L ./libft -lft -o $(NAME)

$(NAME)_bonus: libft/libft.a $(OBJ_BONUS)
	cc $(OBJ_BONUS) $(FSAN) -g3  -L ./libft -lft -o $(NAME)

create_obj_folder :
	mkdir -p obj
	mkdir -p obj_bonus

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
	make create_obj_folder
	make -C libft
	make $(NAME)_bonus
	@make end_message

.PHONY: all clean fclean re create_obj_folder end_message bonus
