#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/15 14:08:57 by acarlson          #+#    #+#              #
#    Updated: 2019/02/11 17:56:27 by callen           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC := $(shell which clang)
CTAGS := $(shell which ctags)
NORM := $(shell which norminette)
CFLAGS := -Wall -Wextra -Werror
DFLAGS := -Wall -Wextra -g
FSANFLAGS := -fsanitize=address
SRCS := srcs/
OBJDIR := .obj/
INCLUDES := -I includes/ -I libft/includes/
FILES := main struct parse util validate lines_to_rooms print_struct solve\
	lines queue_other find_path
CFILES := $(addsuffix .c, $(FILES))
OFILES := $(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))
LIBS := -L libft/ -lft
DNAME := d_lem-in
NAME := lem-in

CL_CYAN := \033[0;36m
CL_GREEN := \033[0;32m
CL_RED := \033[0;31m
CL_WHITE := \033[0m

.PHONY: tags etags clean debug dclean fsan lldb norme

all: $(NAME)

$(NAME): $(OBJDIR) $(OFILES)
	@make -C libft/
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OFILES) -o $(NAME)
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
	$(CTAGS) $(shell find . -type f -iname "*.[ch]")

norme:
	@$(NORM) $(addprefix $(SRCS), $(CFILES))
	@$(NORM) includes/lem_in.h

etags:
	find . -type f -iname "*.[ch]" | etags -

debug:
	make -C libft/
	$(CC) $(DFLAGS) $(INCLUDES) $(LIBS) $(addprefix $(SRCS), $(CFILES)) -o $(DNAME)

j: debug

dclean:
	rm -f $(DNAME)
	rm -rf $(DNAME).dSYM

fsan:
	make -C libft/
	$(CC) $(DFLAGS) $(INCLUDES) $(LIBS) $(addprefix $(SRCS), $(CFILES)) -o $(DNAME) $(FSANFLAGS)

k: dclean fclean
	rm -rf *.dSYM

lldb:
	make -C libft/
	$(CC) $(DFLAGS) -DLLDB $(INCLUDES) $(LIBS) $(addprefix $(SRCS), $(CFILES)) -o $(DNAME)
	$(shell which lldb) -s other_tests/test_lldb

leaks:
	make -C libft/
	$(CC) $(DFLAGS) -DLEAKS $(INCLUDES) $(LIBS) $(addprefix $(SRCS), $(CFILES)) -o $(DNAME)
