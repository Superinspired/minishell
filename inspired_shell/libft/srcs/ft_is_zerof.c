/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_zerof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:38:29 by bifernan          #+#    #+#             */
/*   Updated: 2024/01/02 14:38:35 by bifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_is_zerof(const char *flags)
{
	while (*flags != '\0')
	{
		if (*flags == '0')
			return (1);
		flags++;
	}
	return (0);
}
