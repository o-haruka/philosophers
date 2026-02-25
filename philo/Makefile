# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/24 12:55:59 by homura            #+#    #+#              #
#    Updated: 2026/02/24 13:38:22 by homura           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = philo

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread

SRCS        = main.c \
              init.c \
              monitor.c \
              philo_helpers.c \
              philo.c \
              utils.c

OBJ_PATH    = objs
OBJS        = $(addprefix $(OBJ_PATH)/, $(SRCS:.c=.o))

INCS        = -I.

# --- Rules ---
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re