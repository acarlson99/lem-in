#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/15 14:08:57 by acarlson          #+#    #+#              #
#    Updated: 2019/01/08 20:55:17 by callen           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = clang
CTAGS = /usr/bin/env ctags
NORM = /usr/bin/env norminette
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -Wall -Wextra -g
LLDBFLAGS = $(DFLAGS) -DLLDB
SRCS = srcs/
OBJDIR = .obj/
INCLUDES = -I includes/ -I libft/includes/
FILES = main struct parse util validate lines_to_rooms print_struct
CFILES = $(addsuffix .c, $(FILES))
OFILES = $(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))
LIBS = -L libft/ -lft
DNAME = d_lem-in
NAME = lem-in

CL_CYAN = \033[0;36m
CL_GREEN = \033[0;32m
CL_RED = \033[0;31m
CL_WHITE = \033[0m

.PHONY: tags clean debug dclean fsan lldb norme

all: $(NAME)

$(NAME): $(OBJDIR) $(OFILES)
	@make -C libft/
	@$(CC) $(CFLAGS) $(INCLUDES) $(FRAMEWORKS) $(LIBS) $(OFILES) -o $(NAME)
	@echo "  $(CL_WHITE)+ $(NAME): Compiled $(CL_GREEN)$@$(CL_WHITE)"

clean:
	@make -C libft/ clean
	@echo " $(shell \
	if [ -d $(OBJDIR) ]; \
	then \
		echo " $(CL_WHITE)- $(NAME) : Removing $(CL_RED)$(OBJDIR)$(CL_WHITE) with$(CL_RED)"; \
		ls $(OBJDIR) | wc -w | tr -d '[:blank:]'; echo "$(CL_WHITE)object files"; \
		rm -Rf $(OBJDIR); \
	else \
		echo " $(CL_WHITE)# $(NAME) : Nothing to clean"; \
	fi) "

fclean: clean
	@make -C libft/ fclean
	@echo " $(shell \
	if [ -f $(NAME) ]; \
	then \
		echo " $(CL_WHITE)- $(NAME) : Removing  $(CL_RED)$(NAME)$(CL_WHITE)"; \
		rm -f $(NAME); \
	else \
		echo " $(CL_WHITE)# $(NAME): Nothing to fclean"; \
	fi) "

re: fclean all

$(addprefix $(OBJDIR), %.o): $(addprefix $(SRCS), %.c)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR):
	@echo " $(shell \
	if [ ! -d $(OBJDIR) ]; \
	then \
		mkdir $(OBJDIR); \
		echo " + $(NAME): Created  $(CL_GREEN)$(OBJDIR)$(CL_WHITE)$(CL_WHITE)"; \
	fi) "

tags:
	$(CTAGS) -t includes/*.h srcs/*.c

norme:
	$(NORM) includes/*.h srcs/*.c

etags:
	find . -type f -iname "*.[ch]" | etags -

debug:
	make -C libft/
	$(CC) $(DFLAGS) $(INCLUDES) $(FRAMEWORKS) $(LIBS) $(addprefix $(SRCS), $(CFILES)) -o $(DNAME)

j: debug

dclean:
	rm -f $(DNAME)
	rm -rf $(DNAME).dSYM

fsan:
	make -C libft/
	$(CC) $(DFLAGS) $(INCLUDES) $(FRAMEWORKS) $(LIBS) $(addprefix $(SRCS), $(CFILES)) -o $(DNAME) -fsanitize=address

k: dclean fclean
	rm -rf *.dSYM

lldb:
	make -C libft/
	$(CC) $(LLDBFLAGS) $(INCLUDES) $(FRAMEWORKS) $(LIBS) $(addprefix $(SRCS), $(CFILES)) -o $(DNAME)
