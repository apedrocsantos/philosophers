# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 20:05:00 by anda-cun          #+#    #+#              #
#    Updated: 2023/08/23 09:49:07 by anda-cun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS =	philo_bonus.c\
		utils_bonus.c\
		init_bonus.c\
		main_bonus.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

FSANITIZE = -fsanitize=thread

INCLUDES = -I ./includes

HEADERFILES = ./includes/philosophers.h

LIBS = -pthread

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $^ $(INCLUDES) $(LIBS) -o $(NAME) -g -O1
	@echo "compilation OK."

clean:
	@echo "removing ./philo."
	@rm -f $(NAME)

fclean:
	@echo "removing ./philo."
	@rm -f $(NAME)

sanitize: clean $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(FSANITIZE) $(INCLUDES) $(LIBS) -o $(NAME) -g -O1
	@echo "compilation OK."
	@rm $(OBJS)
	@echo "\e[1;31m*************************************\e[0m"
	@echo "\e[1;32m**********-fsanitize=thread**********\e[0m"
	@echo "\e[1;31m*************************************\e[0m"
	@./$(NAME) 4 110 200 200

valgrind: clean $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBS) -o $(NAME) -g -O1
	@echo "compilation OK."
	@rm $(OBJS)
	@echo "\e[1;31m*************************************\e[0m"
	@echo "\e[1;32m***********--tool=helgrind***********\e[0m"
	@echo "\e[1;31m*************************************\e[0m"
	@valgrind --tool=helgrind -s ./$(NAME) 4 110 200 200

memcheck: clean $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBS) -o $(NAME) -g -O1
	@echo "compilation OK."
	@echo "\e[1;31m*************************************\e[0m"
	@echo "\e[1;32m**********valgrind memcheck**********\e[0m"
	@echo "\e[1;31m*************************************\e[0m"
	@rm $(OBJS)
	@valgrind -s ./$(NAME) 4 110 200 200

$(OBJS): $(SRCS)
	@$(CC) -c $(CFLAGS) $^ $(INCLUDES) $(LIBS)

re: fclean all

.PHONY: all clean fclean re sanitize valgrind memcheck

