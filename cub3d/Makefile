# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thibault <thibault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/29 17:09:42 by thibault          #+#    #+#              #
#    Updated: 2024/01/24 20:16:06 by thibault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d
SOURCES		=	./src
OBJECTS		=	./bin
INCLUDES	=	-I./includes \
				-I./minilibx-linux

SRCS		=	libft/ft_strcmp.c \
				libft/ft_strdup.c \
				libft/ft_strdup2.c \
				libft/ft_strjoin.c \
				libft/ft_strlen.c \
				libft/ft_substr.c \
				libft/ft_atoi.c \
				libft/ft_itoa.c \
				libft/ft_strlcpy.c \
				ft_launch_map.c \
				ft_parsing.c \
				parsing_utils.c \
				check_parsing.c \
				ft_fill_tab.c \
				ft_mlx_init.c \
				ft_draw_minimap.c \
				ft_player.c \
				ft_raycasting.c

OBJS		=	$(addprefix ${OBJECTS}/, $(SRCS:.c=.o))

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror ${INCLUDES} -L/usr/local/bin -O3 -g -fsanitize=undefined -fsanitize=address
LIBS		=	-lmlx -lXext -lX11 -lm
CINCLUDES	=	${INCLUDES}

BLACK		=	"\033[1;30m"
RED			=	"\033[1;31m"
GREEN		=	"\033[1;32m"
CYAN		=	"\033[1;35m"
BLUE		=	"\033[1;36m"
WHITE		=	"\033[1;37m"
EOC			=	"\033[0;0m"

TOTAL_OBJS := $(words $(OBJS))
COMPILED_OBJS := 0

define print_progress
	printf $(WHITE)"\r● [Compiling]  : "
	$(eval PERCENTAGE=$(shell echo "$(2)*100/$(1)" | bc))
	$(eval FILLED_BLOCKS=$(shell if [ "$(shell echo "$(PERCENTAGE)/10" | bc)" -lt "1" ]; then echo "1"; else echo "$(shell echo "$(PERCENTAGE)/10" | bc)"; fi))
	$(eval EMPTY_BLOCKS=$(shell echo "10 - $(FILLED_BLOCKS)" | bc))
	for i in `seq 1 $(shell echo "$(FILLED_BLOCKS)" | awk '{print int($$1)}')`; do \
		printf $(GREEN)"▇▇▇"; \
	done
	if [ "$(PERCENTAGE)" != "100" ]; then \
		for i in `seq 1 $(EMPTY_BLOCKS)`; do \
			printf $(WHITE)"▇▇▇"; \
		done; \
	fi
	printf $(WHITE)" $(PERCENTAGE)%% $(2) /$(1)files"$(EOC)
endef

${OBJECTS}/%.o: ${SOURCES}/%.c
	@mkdir -p $(dir $@)
	@$(call print_progress, $(TOTAL_OBJS), $(COMPILED_OBJS))
	@$(CC) $(CFLAGS) -o $@ -c $< $(CINCLUDES)
	@$(eval COMPILED_OBJS=$(shell echo "$(COMPILED_OBJS)+1" | bc))

all: ${NAME} #norminette

${NAME}: ${OBJS} ${OBJECTS}/${NAME}.o
	@echo $(GREEN)"\n● Compilation of ${NAME}...\n"$(EOC)
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${OBJECTS}/${NAME}.o ${LIBS}

#norminette:
#	@norminette | grep "Error!" > /dev/null && echo $(WHITE)"● [Norminette]: "$(RED)"KO\n"$(EOC) || echo $(WHITE)"● [Norminette]: "$(GREEN)"OK\n"$(EOC)

clean:
	@echo ${RED}"● Deletion of binary files (.o)..."$(EOC)
	@rm -rf ${OBJECTS}

fclean: clean
	@echo ${RED}"● Deletion of executables and libraries..."$(EOC)
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re