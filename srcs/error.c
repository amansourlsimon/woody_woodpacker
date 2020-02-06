/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:11:56 by lsimon            #+#    #+#             */
/*   Updated: 2019/12/24 12:20:53 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/woody_woodpacker.h"

void	*null_error(const char *s)
{
	dprintf(2, "%s\n", s);
	return (NULL);
}

int		int_error(const char *s)
{
	dprintf(2, "%s\n", s);
	return (-1);
}

void	*null_perror(const char *s)
{
	perror(s);
	return (NULL);
}

int		int_perror(const char *s)
{
	perror(s);
	return (-1);
}
