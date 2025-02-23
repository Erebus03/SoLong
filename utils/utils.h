/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:42:31 by araji             #+#    #+#             */
/*   Updated: 2025/02/02 20:42:32 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct node
{
	char		*str;
	int			len;
	struct node	*next;
}	t_gnl_list;

/* gnl functions */
int			get_line_len(t_gnl_list *tmp);
t_gnl_list	*ft_lstlast(t_gnl_list *lst);
t_gnl_list	*ft_lstnew(char *content);
void		extract(t_gnl_list *lst, char **line);
char		*get_next_line(int fd);
int			found_newline(t_gnl_list *node);
void		lst_add_back(t_gnl_list **lst, t_gnl_list *new);
void		ft_lstclear(t_gnl_list **lst);
void		create_t_gnl_list(t_gnl_list **lst, int fd);
void		clean(t_gnl_list **lst);

/* ft_printf functions */
int			ft_printf(const char *input, ...);
int			put_s(char *s);
int			put_nb(int n);

/* other funtions */
char		*ft_strrchr(char *s, int c);
size_t		ft_strlen(const char *str);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_itoa(unsigned int n);


#endif
