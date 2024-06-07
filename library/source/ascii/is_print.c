/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:20:33 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/30 12:20:33 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/slib.h"

inline bool	is_print(const int32_t ch)
{
	return (ch >= ' ' && ch <= '~');
}