/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-doua <jle-doua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:48:11 by jle-doua          #+#    #+#             */
/*   Updated: 2024/10/16 19:53:03 by jle-doua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_puterror(char *str)
{
	write(2, "\033[1;31mERROR : \033[0m", 21);
	if (str)
	{
		write(2, "\033[1;31m", 8);
		write(2, str, ft_strlen(str));
		write(2, "\033[0m", 5);
	}
	write(2, "\n", 1);
}
