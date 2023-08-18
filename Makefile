# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/16 18:20:23 by kglebows          #+#    #+#              #
#    Updated: 2023/08/18 16:45:44 by kglebows         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
NAME_BONUS = checker

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

LIBFTNAME = bin/libft/libft.a
LIBFTDIR = src/libft
OBJDIR = ./bin
SRCDIR = ./src

SRC = 			push_swap.c
SRC_BONUS = 	checker.c
SRC_GNL = 		gnl/get_next_line_utils.c gnl/get_next_line.c

SRC_INI = 		ini/ini.c ini/utils.c
SRC_SORT = 		sort/distance.c sort/phase1.c sort/phase2.c sort/solve.c \
				sort/sort.c sort/utils.c
SRC_STACK = 	stack/push.c stack/rotate.c stack/rrotate.c stack/swap.c \
				stack/stack.c


SRCS = $(SRC) $(SRC_INI) $(SRC_SORT) $(SRC_STACK)
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

SRCS_BONUS = $(SRC_BONUS) $(SRC_INI) $(SRC_STACK) $(SRC_GNL)
OBJS_BONUS = $(SRCS_BONUS:%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@OUTPUT=$$($(CC) $(CFLAGS) -Isrc -c $< -o $@ 2>&1); \
	if [ $$? -eq 0 ]; then \
		echo "\033[0;32m$< OK!\033[0m"; \
	else \
		echo "$$OUTPUT" && echo "\033[0;31m$< KO!\033[0m" && exit 1; \
	fi

all: makelibft $(NAME)

makelibft:
	@if [ ! -f "$(LIBFTNAME)" ]; then \
		OUTPUT=$$(make -C $(LIBFTDIR) --no-print-directory 2>&1); \
		if echo "$$OUTPUT" | grep -E "cc|ar" > /dev/null; then \
			echo "\033[0;32mLIBFT OK!\033[0m"; \
		fi; \
	fi

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(OBJDIR)/libft -lft

bonus: makelibft $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) -L$(OBJDIR)/libft -lft

clean-empty-dirs:
	@if [ -d $(OBJDIR) ]; then find $(OBJDIR) -type d -empty -exec rmdir {} +; fi

clean: 
	@for obj in $(OBJS); do \
		if [ -f "$$obj" ]; then \
			rm -f $$obj && echo "\033[0;33m$$obj deleted\033[0m"; \
		fi; \
	done
	@for obj_bonus in $(OBJS_BONUS); do \
		if [ -f "$$obj_bonus" ]; then \
			rm -f $$obj_bonus && echo "\033[0;33m$$obj_bonus deleted\033[0m"; \
		fi; \
	done
	@OUTPUT=$$(make -C $(LIBFTDIR) clean --no-print-directory 2>&1); \
	if echo "$$OUTPUT" | grep -E "deleted" > /dev/null; then \
		echo "\033[0;33mlibft *.o deleted\033[0m"; \
	fi
	@$(MAKE) clean-empty-dirs

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME) && echo "\033[0;33m$(NAME) deleted\033[0m"; \
	fi
	@if [ -f "$(NAME_BONUS)" ]; then \
		rm -f $(NAME_BONUS) && echo "\033[0;33m$(NAME_BONUS) deleted\033[0m"; \
	fi
	@OUTPUT=$$(make -C $(LIBFTDIR) fclean --no-print-directory 2>&1); \
	if echo "$$OUTPUT" | grep -E "deleted" > /dev/null; then \
		echo "\033[0;33mlibft.a deleted\033[0m"; \
	fi
	@$(MAKE) clean-empty-dirs

re: fclean all

.PHONY: all clean fclean norm re bonus

#tester
TESTER_GET  =   https://raw.githubusercontent.com/lorenuars19/push_swap_tester/main/push_swap_tester.pl
TESTER      =   ./ps_tester.pl

$(TESTER):
	curl $(TESTER_GET) -o $(TESTER)
3: $(NAME) $(TESTER)
	perl $(TESTER) 3 100
5: $(NAME) $(TESTER)
	perl $(TESTER) 5 100
100: $(NAME) $(TESTER)
	perl $(TESTER) 100 100
500: $(NAME) $(TESTER)
	perl $(TESTER) 500 100
