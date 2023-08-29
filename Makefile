# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/16 18:20:23 by kglebows          #+#    #+#              #
#    Updated: 2023/08/29 16:52:07 by kglebows         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = server
NAME2 = client

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

LIBFTNAME = bin/libft/libft.a
LIBFTDIR = src/libft
OBJDIR = ./bin
SRCDIR = ./src

SRC1 = server.c
SRC2 = client.c

SRCS1 = $(SRC1)
OBJS1 = $(SRCS1:%.c=$(OBJDIR)/%.o)

SRCS2 = $(SRC2)
OBJS2 = $(SRCS2:%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@OUTPUT=$$($(CC) $(CFLAGS) -Isrc -c $< -o $@ 2>&1); \
	if [ $$? -eq 0 ]; then \
		echo "\033[0;32m$< OK!\033[0m"; \
	else \
		echo "$$OUTPUT" && echo "\033[0;31m$< KO!\033[0m" && exit 1; \
	fi

all: makelibft $(NAME1) $(NAME2)

makelibft:
	@if [ ! -f "$(LIBFTNAME)" ]; then \
		OUTPUT=$$(make -C $(LIBFTDIR) --no-print-directory 2>&1); \
		if echo "$$OUTPUT" | grep -E "cc|ar" > /dev/null; then \
			echo "\033[0;32mLIBFT OK!\033[0m"; \
		fi; \
	fi

$(NAME1): $(OBJS1)
	@$(CC) $(CFLAGS) -o $(NAME1) $(OBJS1) -L$(OBJDIR)/libft -lft

$(NAME2): $(OBJS2)
	@$(CC) $(CFLAGS) -o $(NAME2) $(OBJS2) -L$(OBJDIR)/libft -lft

clean-empty-dirs:
	@if [ -d $(OBJDIR) ]; then find $(OBJDIR) -type d -empty -exec rmdir {} +; fi

clean: 
	@for obj in $(OBJS1); do \
		if [ -f "$$obj" ]; then \
			rm -f $$obj && echo "\033[0;33m$$obj deleted\033[0m"; \
		fi; \
	done
	@for obj_bonus in $(OBJS2); do \
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
	@if [ -f "$(NAME1)" ]; then \
		rm -f $(NAME1) && echo "\033[0;33m$(NAME1) deleted\033[0m"; \
	fi
	@if [ -f "$(NAME2)" ]; then \
		rm -f $(NAME2) && echo "\033[0;33m$(NAME2) deleted\033[0m"; \
	fi
	@OUTPUT=$$(make -C $(LIBFTDIR) fclean --no-print-directory 2>&1); \
	if echo "$$OUTPUT" | grep -E "deleted" > /dev/null; then \
		echo "\033[0;33mlibft.a deleted\033[0m"; \
	fi
	@$(MAKE) clean-empty-dirs

re: fclean all

.PHONY: all clean fclean norm re bonus