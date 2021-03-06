/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaetan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:32:35 by jocaetan          #+#    #+#             */
/*   Updated: 2021/10/18 13:32:37 by jocaetan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
The ft_memcmp() function compares the first n bytes (each interpreted as 
unsigned char) of the memory areas s1 and s2.

RETURN VALUE
The ft_memcmp() function returns an integer less than, equal to, or greater 
than zero if the first n bytes of s1 is found, respectively, to be less than, 
to match, or be greater than the first n bytes of s2.
For a nonzero return value, the sign is determined by the sign of the 
difference between the first pair of bytes (interpreted as unsigned char) 
that differ in s1 and s2.
If n is zero, the return value is zero.
*/

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = -1;
	while (++i < n)
	{
		c1 = *((unsigned char *)(s1 + i));
		c2 = *((unsigned char *)(s2 + i));
		if ((c1 != c2))
			return (c1 - c2);
	}
	return (0);
}
