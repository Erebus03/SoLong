/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:11:39 by araji             #+#    #+#             */
/*   Updated: 2025/02/02 22:49:47 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl_list	*ft_lstlast(t_gnl_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	get_line_len(t_gnl_list *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
		i = i + tmp->len;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_lstclear(t_gnl_list **lst)
{
	t_gnl_list	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_gnl_list	*ft_lstnew(char *content)
{
	t_gnl_list	*new_node;

	new_node = malloc(sizeof(t_gnl_list));
	if (!new_node)
		return (NULL);
	new_node->str = content;
	new_node->len = 0;
	new_node->next = NULL;
	return (new_node);
}

void	lst_add_back(t_gnl_list **lst, t_gnl_list *new)
{
	t_gnl_list	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
}
