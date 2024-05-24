/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:12:06 by pollivie          #+#    #+#             */
/*   Updated: 2024/03/14 14:12:06 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_node	*node_next(t_node *self)
{
	if (!self)
		return (0);
	return (self->next);
}
