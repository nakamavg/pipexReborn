/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:34:33 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/02 23:13:28 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	send_error(char *str)
{
	perror(str);
	exit(1);
}

int	msg_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
