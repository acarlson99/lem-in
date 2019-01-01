# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/11 14:45:59 by acarlson          #+#    #+#              #
#    Updated: 2018/12/30 22:08:56 by acarlson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror
OBJDIR = .obj/
INCLUDES = -I includes/
FILES = ft_memset ft_bzero ft_memcpy ft_memccpy ft_memmove ft_memchr ft_memcmp \
		ft_strlen ft_strdup ft_strcpy ft_strncpy ft_strcat ft_strncat          \
		ft_strlcat ft_strchr ft_strrchr ft_strstr ft_strnstr ft_strcmp         \
		ft_strncmp ft_atoi ft_isalpha ft_isdigit ft_isalnum ft_isascii         \
		ft_isprint ft_toupper ft_tolower                                       \
		\
		ft_memalloc ft_memdel ft_strnew ft_strdel ft_strclr ft_striter         \
		ft_striteri ft_strmap ft_strmapi ft_strequ ft_strnequ ft_strsub        \
		ft_strjoin ft_strtrim ft_strsplit ft_itoa ft_putchar ft_putstr         \
		ft_putendl ft_putnbr ft_putchar_fd ft_putstr_fd ft_putendl_fd          \
		ft_putnbr_fd                                                           \
		\
		ft_lstnew ft_lstdelone ft_lstdel ft_lstadd ft_lstiter ft_lstmap        \
		\
		get_next_line                                                          \
		\
		ft_isprime ft_strndup ft_itoabase ft_atoibase ft_strrev ft_isin        \
		ft_wordnum ft_wordlen ft_reduce ft_memrealloc ft_floor ft_ceil         \
		ft_putflt ft_putflt_fd ft_putdbl ft_putdbl_fd ft_abs ft_sqrt ft_snumlen\
		ft_unumlen ft_strlcpy ft_round ft_swap ft_strchri ft_lstrev            \
		ft_lstadd_tail ft_strspn ft_strcspn ft_putchar_fd_2 ft_putdbl_fd_2     \
		ft_putendl_fd_2 ft_putflt_fd_2 ft_putnbr_base_2 ft_putnbr_fd_2         \
		ft_putstr_fd_2 ft_putnstr ft_putnstr_fd ft_putcstr_fd ft_atosize_tbase \
		ft_size_ttoabase ft_ssize_ttoabase ft_wcharlen ft_putwchar_fd          \
		ft_wstrlen ft_putwstr ft_putnwstr ft_putrstr_fd ft_strrealloc ft_exit  \
		ft_numpair ft_numunpair ft_vectnew ft_vectadd ft_vectscalarmult
FILES += ft_printf pf_disp pf_print_str_char pf_print_int pf_print_unsigned    \
		pf_print_oct pf_print_hex pf_print_pointer pf_print_percent            \
		pf_print_padding pf_parse_input pf_find_options pf_print_bin           \
		pf_find_colors
CFILES = $(addsuffix .c, $(FILES))
OFILES = $(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))
NAME = libft.a

CL_CYAN = \033[0;36m
CL_GREEN = \033[0;32m
CL_RED = \033[0;31m
CL_WHITE = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJDIR) $(OFILES)
	@ar -rcs $@ $(OFILES)
	@echo "  $(CL_WHITE)+ libft : Compiled $(CL_GREEN)$@$(CL_WHITE)"

clean:
	@echo " $(shell \
		if [ -d $(OBJDIR) ]; \
		then \
			echo " $(CL_WHITE)- libft : Removing $(CL_RED)$(OBJDIR)$(CL_WHITE) with$(CL_RED)"; \
			ls $(OBJDIR) | wc -w | tr -d '[:blank:]'; echo "$(CL_WHITE)object files"; \
			rm -Rf $(OBJDIR); \
		else \
			echo " $(CL_WHITE)# libft : Nothing to clean"; \
		fi) "

fclean: clean
	@echo " $(shell \
		if [ -f $(NAME) ]; \
		then \
			echo " $(CL_WHITE)- libft : Removing  $(CL_RED)$(NAME)$(CL_WHITE)"; \
			rm -f $(NAME); \
		else \
			echo " $(CL_WHITE)# libft : Nothing to fclean"; \
		fi) "

re: fclean all

$(addprefix $(OBJDIR), %.o): %.c
	@$(CC) $(INCLUDES) $(CFLAGS) -o $@ -c $<

$(OBJDIR):
	@echo " $(shell \
	if [ -d $(OBJDIR) ]; \
	then \
		: ; \
	else \
		mkdir $(OBJDIR); \
		echo " + libft : Created  $(CL_GREEN)$(OBJDIR)$(CL_WHITE)$(CL_WHITE)"; \
	fi) "
