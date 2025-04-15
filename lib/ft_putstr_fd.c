/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:42:32 by mbah              #+#    #+#             */
/*   Updated: 2024/11/12 23:46:06 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	ft_putstr_fd(char *str, int fd)
{
	int		i;
	char	*copy;

	i = 0;
	while (str[i])
		i++;
	copy = (char *) malloc(sizeof(char) * (i + 2));
	if (!copy)
		return ;
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\n';
	copy[i + 1] = '\0';
	write(fd, copy, (i + 1));
	free(copy);
}
