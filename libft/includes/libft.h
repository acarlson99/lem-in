/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 16:13:51 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/30 22:06:22 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>

/*
** Handy macros
*/

# define FT_FD_MAX 256
# define BUFF_SIZE 4096

# define RET_IF(cond, ret) if (cond) return (ret)
# define RET_NONE(cond) if (cond) return
# define NULL_CHECK(x) if (x) return (NULL)
# define DO_IF(cond, do_me) if (cond) do_me
# define DO_ALL(cond, ...) if (cond) __VA_ARGS__
# define WHILE_DO(cond, do_me) while (cond) do_me
# define ELSE_DO(do_me) else do_me
# define IF_ELSE(cond, a, b) DO_IF(cond, a); ELSE_DO(b)

# define MIN(a, b) (a < b) ? a : b
# define MAX(a, b) (a > b) ? a : b
# define ABS(x) (x < 0) ? -x : x
# define CEIL(a) (((a - (int)(a)) > 0) ? (typeof(a))(size_t)(a + 1) : a)
# define FLOOR(a) (((a - (int)(a)) > 0) ? (typeof(a))(size_t)(a - 1) : a)

# define ABS_I(x) (x ^ (x >> 31)) - (x >> 31)
# define MAX_I(a, b) (b & ((a-b) >> 31) | a & (~(a-b) >> 31))
# define MIN_I(a, b) (a & ((a-b) >> 31) | b & (~(a-b) >> 31))o
# define LETTER_POS(c) (c & 0x1f)

# define ISBLANK(c) (c == ' ' || c == '\t')
# define ISWHITE(c) (c == ' ' || c == '\n' || c == '\t')
# define ISWHITE2(c) (c == '\r' || c == '\v' || c == '\f' || ISWHITE(c))

# define TODIGIT(c) ((c) - '0')
# define TOCHAR(n) ((n) + '0')

/*
** Stupid macros
*/

# define ISALPHA(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
# define ISDIGIT(c) (c >= '0' && c <= '9')
# define ISALNUM(c) (ISALPHA(c) || ISDIGIT(c))
# define ISASCII(c) (c >= 0 && c <= 0177)
# define ISPRINT(c) (c >= 040 && c <= 0176)
# define TOUPPER(c) ((c >= 'a' && c <= 'z') ? c & '_' : c)
# define TOLOWER(c) ((c >= 'A' && c <= 'Z') ? c | ' ' : c)

/*
** limits stuff because we can't use limits.h for whatever reason
*/

# define FT_CHAR_BIT 8

# define FT_UCHAR_MAX 255
# define FT_SCHAR_MAX 127
# define FT_SCHAR_MIN (-128)
# define FT_CHAR_MAX (FT_UCHAR_MAX / (unsigned char)2)
# define FT_CHAR_MIN ((int)(char)(FT_SCHAR_MAX + 1))

# define FT_USHRT_MAX ((int)(unsigned short)(-1))
# define FT_SHRT_MAX (FT_USHRT_MAX / (unsigned short)2)
# define FT_SHRT_MIN ((int)(short)(FT_SHRT_MAX + 1))

# define FT_UINT_MAX ((unsigned int)(-1))
# define FT_INT_MAX (FT_UINT_MAX / 2)
# define FT_INT_MIN (FT_INT_MAX + 1)

# define FT_ULONG_MAX ((unsigned long)(-1))
# define FT_LONG_MAX (FT_ULONG_MAX / 2)
# define FT_LONG_MIN (FT_LONG_MAX + 1)

# define FT_ULLONG_MAX ((unsigned long long)(-1))
# define FT_LLONG_MAX (FT_ULLONG_MAX / 2)
# define FT_LLONG_MIN (FT_LLONG_MAX + 1)

# define FT_UINTMAX_MAX ((uintmax_t)(-1))
# define FT_INTMAX_MAX (FT_UINTMAX_MAX / 2)
# define FT_INTMAX_MIN (FT_INTMAX_MAX + 1)

# define FT_SIZE_T_MAX ((size_t)(-1))
# define FT_SSIZE_T_MAX (FT_SIZE_T_MAX / 2)
# define FT_SSIZE_T_MIN (FT_SSIZE_T_MAX + 1)

# ifdef __LP64__
#  define FT_LONG_BIT 64
# else
#  define FT_LONG_BIT 32
# endif

# define FT_STDIN_FILENO 0
# define FT_STDOUT_FILENO 1
# define FT_STDERR_FILENO 2

/*
** Colors
*/

/*
** TYPOGRAPHICAL EMPHASIS
*/

# define TE(n) TE_ ## n

# define TE_BOL "\033[1m"
# define TE_DIM "\033[2m"
# define TE_UND "\033[4m"
# define TE_BLN "\033[5m"
# define TE_HID "\033[8m"
# define TE_INV "\033[7m"
# define TE_RST_ALL "\033[0m"
# define TE_RST_BLD "\033[21m"
# define TE_RST_DIM "\033[22m"
# define TE_RST_UND "\033[24m"
# define TE_RST_BLN "\033[25m"
# define TE_RST_INV "\033[27m"
# define TE_RST_HID "\033[28m"

/*
** FOREGROUND
*/

# define FG(n) FG_ ## n

# define FG_BLK "\033[30m"
# define FG_RED "\033[31m"
# define FG_GRN "\033[32m"
# define FG_YLW "\033[33m"
# define FG_BLU "\033[34m"
# define FG_MGN "\033[35m"
# define FG_CYN "\033[36m"
# define FG_GRY "\033[37m"
# define FG_WHT "\033[97m"
# define FG_LGRY "\033[37m"
# define FG_DGRY "\033[90m"
# define FG_LRED "\033[91m"
# define FG_LGRN "\033[92m"
# define FG_LYLW "\033[93m"
# define FG_LBLU "\033[94m"
# define FG_LMGN "\033[95m"
# define FG_LCYN "\033[96m"
# define FG_DFT "\033[39m"

/*
** BACKGROUND
*/

# define BG(n) BG_ ## n

# define BG_BLK "\033[40m"
# define BG_RED "\033[41m"
# define BG_GRN "\033[42m"
# define BG_YLW "\033[43m"
# define BG_BLU "\033[44m"
# define BG_MGN "\033[45m"
# define BG_CYN "\033[46m"
# define BG_GRY "\033[47m"
# define BG_LGRY "\033[47m"
# define BG_DGRY "\033[100m"
# define BG_LRED "\033[101m"
# define BG_LGRN "\033[102m"
# define BG_LYLW "\033[103m"
# define BG_LBLU "\033[104m"
# define BG_LMGN "\033[105m"
# define BG_LCYN "\033[106m"
# define BG_WHT "\033[107m"
# define BG_DFT "\033[49m"

# define NC "\033[0m"

/*
** Part one
*/

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *dst, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack,\
const char *needle, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

/*
** Part two
*/

void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s1, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
** Bonus part
*/

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void const *content, size_t constent_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** Projects
*/

int				get_next_line(const int fd, char **line);

int				ft_printf(char *fmt, ...);
int				ft_dprintf(int fd, char *fmt, ...);
int				ft_vdprintf(int fd, const char *format, va_list args_list);

/*
** My functions
*/

int				ft_isprime(size_t n);
int				ft_atoibase(const char *str, int base);
int				ft_isin(char c, const char *str);
int				ft_reduce(int *arr, size_t size, int (*f)(int a, int b));
int				ft_floor(double n);
int				ft_ceil(double n);
double			ft_abs(double n);
double			ft_sqrt(double n);
double			ft_round(double n, size_t p);
size_t			ft_wordlen(const char *s, char c);
size_t			ft_wordnum(const char *s, char c);
size_t			ft_snumlen(ssize_t n, int base);
size_t			ft_unumlen(size_t n, int base);
size_t			ft_strlcpy(char *dst, const char *src, size_t len);
size_t			ft_strspn(const char *s, const char *charset);
size_t			ft_strcspn(const char *s, const char *charset);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_itoabase(int n, int base);
char			*ft_strrev(const char *s);
char			*ft_strrealloc(char *str, size_t len);
void			ft_putflt(float n, size_t precision);
void			ft_putflt_fd(float n, size_t precision, int fd);
void			ft_putdbl(double n, size_t precision);
void			ft_putdbl_fd(double n, size_t precision, int fd);
void			*ft_memrealloc(void *ptr, size_t size);
void			ft_swap(int *a, int *b);

int				ft_putchar_fd_2(char c, int fd);
int				ft_putdbl_fd_2(double n, size_t precision, int fd);
int				ft_putendl_fd_2(char const *s, int fd);
int				ft_putflt_fd_2(float n, size_t precision, int fd);
int				ft_putnbr_base_2(int n, int base);
int				ft_putnbr_fd_2(int n, int fd);
int				ft_putstr_fd_2(char const *s, int fd);
int				ft_putnstr(char *s, size_t n);
int				ft_putnstr_fd(char *s, size_t n, int fd);
int				ft_putcstr_fd(char *s, int c, int fd);
int				ft_putrstr_fd(char *s, int fd);

int				ft_wcharlen(wchar_t wc);
size_t			ft_wstrlen(wchar_t *s);
int				ft_putwchar_fd(wchar_t wc, int fd);
int				ft_putwstr_fd(wchar_t *str, int fd);
int				ft_putnwstr_fd(wchar_t *ws, size_t n, int fd);

size_t			ft_atosize_tbase(const char *str, int base);
char			*ft_size_ttoabase(size_t n, int base);
char			*ft_ssize_ttoabase(ssize_t n, int base);

int				ft_strchri(const char *s, int c);
void			ft_lstrev(t_list **alst);
void			ft_lstadd_tail(t_list **alst, t_list *new);
void			ft_exit(char *message, char *color, int code);

uint64_t		ft_numpair(uint32_t x, uint32_t y);
void			ft_numunpair(uint64_t p, uint32_t *x, uint32_t *y);

/*
** 3D vectors
*/

typedef struct	s_vect3
{
	double	x;
	double	y;
	double	z;
}				t_vect3;

typedef double	t_mtx4[4][4];

t_vect3			*ft_vectnew(double x, double y, double z);
t_vect3			*ft_vectadd(t_vect3 *v, t_vect3 *w);
t_vect3			*ft_vectsubtract(t_vect3 *v, t_vect3 *w);
t_vect3			*ft_vectscalarmult(double n, t_vect3 *v);

#endif
