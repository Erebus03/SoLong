/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:12:00 by araji             #+#    #+#             */
/*   Updated: 2024/12/10 15:09:58 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20000
# endif

# ifndef MAX_OPEN_FDS
#  define MAX_OPEN_FDS 1024
# endif

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct node
{
	char		*str;
	int			len;
	struct node	*next;
}	t_list;

int		get_line_len_bns(t_list *tmp);
t_list	*ft_lstlast_bns(t_list *lst);
t_list	*ft_lstnew_bns(char *content);
void	extract_bns(t_list *lst, char **line);
char	*get_next_line(int fd);
int		found_newline_bns(t_list *node);
void	lst_add_back_bns(t_list **lst, t_list *new);
void	ft_lstclear_bns(t_list **lst);
void	create_t_list_bns(t_list **lst, int fd);
void	clean_bns(t_list **lst);

#endif
