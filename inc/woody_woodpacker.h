/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody_woodpacker.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:48:39 by lsimon            #+#    #+#             */
/*   Updated: 2019/12/13 13:08:38 by lsimon           ###   ########.fr       */
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

typedef struct s_content
{
	void	*start;
	size_t	len;
}				t_content;

void	*null_error(char *s);

#endif
