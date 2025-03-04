/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:18:33 by aomont            #+#    #+#             */
/*   Updated: 2025/01/06 22:38:35 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isblank(int c);
int			ft_iscntrl(int c);
int			ft_isdigit(int c);
int			ft_isgraph(int c);
int			ft_islower(int c);
int			ft_isprint(int c);
int			ft_ispunct(int c);
int			ft_isspace(int c);
int			ft_isupper(int c);

void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_list_foreach(t_list *begin_list, void (*f)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);

void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);

char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dest, const char *src);
size_t		ft_strcspn(const char *s, const char *reject);
char		*ft_strdup(const char *s1);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin_char(const char *str, char c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strndup(const char *src, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strpbrk(const char *s1, const char *s2);
char		*ft_strrchr(const char *s, int c);
char		*ft_strrev(char *str);
size_t		ft_strspn(const char *s, const char *accept);
char		*ft_strstr(const char *big, const char *little);
char		*ft_strtok(char *string, const char *delim);
long		ft_strtol(const char *string, char **end);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);

int			ft_atoi_base(const char *str, int str_base);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
int			ft_tolower(int c);
int			ft_toupper(int c);

// ft_printf
int			ft_printf_character(char c);
int			ft_printf_number(int n);
int			ft_printf_pointer(void *ptr);
int			ft_printf_string(const char *str);
int			ft_printf_unsigned_number(unsigned int n);
int			ft_printf_hex(unsigned long long x, char x_or_x);
char		*ft_utoa(unsigned int n);

#endif
