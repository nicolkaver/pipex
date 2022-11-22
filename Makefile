# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboratko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 15:13:15 by nboratko          #+#    #+#              #
#    Updated: 2022/07/07 17:09:07 by nboratko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_BONUS = pipex_bonus

SRCS = srcs/pipex.c srcs/parsing.c srcs/pipex_utils.c srcs/pipex_utils2.c

BONUS = srcs/pipex_bonus.c srcs/parsing_bonus.c srcs/pipex_utils_bonus.c \
	srcs/pipex_utils2_bonus.c srcs/here_doc_bonus.c srcs/get_next_line.c \
	srcs/pipex_utils3_bonus.c

_RED=	$'\033[1;31m
_GREEN=	$'\033[1;32m
_END=	$'\033[0m

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${BONUS:.c=.o}

LIBFTDIR = ./libft

INCLUDE = inc

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

HEADER = inc/pipex.h

BONUSHEADER = inc/pipex_bonus.h

all: ${NAME}

${NAME}: ${OBJS} ${HEADER}
	@make -C ./libft
	@echo "$(_GREEN)Libft compiled$(_END)"
	@make -C ./ft_printf
	@echo "$(_GREEN)Ft_printf compiled$(_END)"
	${CC} ${CFLAGS} ${OBJS} ./libft/libft.a ./ft_printf/libftprintf.a -o ${NAME}
	@echo "$(_GREEN)Executable created : pipex$(_END)"

bonus:	${OBJSBONUS} ${BONUSHEADER}
	@make -C ./libft
	@echo "$(_GREEN)Libft compiled$(_END)"
	@make -C ./ft_printf
	@echo "$(_GREEN)Ft_printf compiled$(_END)"
	${CC} ${CFLAGS} ${OBJSBONUS} ./libft/libft.a ./ft_printf/libftprintf.a -o ${NAME_BONUS}
	@echo "$(_GREEN)Executable created : pipex_bonus$(_END)"

clean: 
	${RM} ${OBJS} ${OBJSBONUS}
	@make -C ./ft_printf fclean
	@make -C ./libft fclean
	@echo "$(_RED).o files removed$'\033[0m"

fclean: clean
	${RM} ${NAME} ${NAME_BONUS}
	@echo "$(_RED)Executable removed$'\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus
