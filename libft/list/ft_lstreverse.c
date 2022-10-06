/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:10:07 by psharen           #+#    #+#             */
/*   Updated: 2022/08/23 17:34:20 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstreverse(t_list **lst)
{
	t_list	*first;
	t_list	*second;
	t_list	*third;

	if (!lst || !*lst)
		return ;
	first = NULL;
	second = *lst;
	third = (*lst)->next;
	while (third)
	{
		second->next = first;
		first = second;
		second = third;
		third = third->next;
	}
	second->next = first;
	*lst = second;
}
