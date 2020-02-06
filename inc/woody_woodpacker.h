/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody_woodpacker.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:48:39 by lsimon            #+#    #+#             */
/*   Updated: 2019/12/24 12:22:50 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_WOODPACKER_H

# define WOODY_WOODPACKER_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <elf.h>

typedef struct s_content
{
	void	*start;
	size_t	len;
}				t_content;

/*
** error
*/

void	*null_error(const char *s);
int		int_error(const char *s);
void	*null_perror(const char *s);
int		int_perror(const char *s);

#endif
