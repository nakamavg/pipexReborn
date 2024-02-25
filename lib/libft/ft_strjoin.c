/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:11:33 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/02/07 10:58:24 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	size_t	lens_dst;
	char	*new_string;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	lens_dst = lens1 + lens2 + 1 ;
	new_string = ft_calloc(sizeof(char), lens_dst);
	if (!new_string)
		return (NULL);
	ft_memcpy(new_string, s1, lens1);
	ft_memcpy(new_string + lens1, s2, lens2);
	return (new_string);
}
