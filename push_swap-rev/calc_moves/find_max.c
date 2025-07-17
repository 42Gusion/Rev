/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_max.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <stariq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:26:06 by stariq            #+#    #+#             */
/*   Updated: 2024/11/13 23:26:07 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../push_swap.h"

int	findmax(t_node *stack)
{
	int	max;

	max = stack->data;
	while (stack)
	{
		if (stack->data > max)
			max = stack->data;
		stack = stack->next;
	}
	return (max);
}

int	find_max(t_node *head)
{
	t_node	*current;
	int		max;
	int		ret;

	current = head;
	max = current->pos;
	ret = current->i;
	while (current != NULL)
	{
		if (current->pos > max)
		{
			ret = current->i;
			max = current->pos;
		}
		current = current->next;
	}
	return (ret);
}
