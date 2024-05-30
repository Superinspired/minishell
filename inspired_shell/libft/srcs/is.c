/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:40:02 by bifernan          #+#    #+#             */
/*   Updated: 2024/04/05 14:40:04 by bifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/common.h"

int	ft_isspace(char c)
{
	return ((c > 7 && c < 14) || (c == 32));
}

int	ft_is_sc_or_eq(char c)
{
	return (c == ':' || c == '=');
}
