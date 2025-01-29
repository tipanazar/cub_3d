/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isblank.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:20:35 by root              #+#    #+#             */
/*   Updated: 2024/02/12 16:26:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	issspace(char ch)
{
	return (ch == ' ' || (ch >= 9 && ch <= 13) || ch == '\n');
}

bool	is_blank(const char *buf)
{
	if (!buf)
		return (true);
	while (*buf)
	{
		if (!issspace(*buf))
			return (false);
		buf++;
	}
	return (true);
}
