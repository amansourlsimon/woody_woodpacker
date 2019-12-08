/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:44:08 by lsimon            #+#    #+#             */
/*   Updated: 2019/12/08 15:10:55 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/woody_woodpacker.h"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		dprintf(2, "usage: ./woody_woodpacker elf_path\n");
		return (1);
	}
	printf("About to pack \"%s\"\n", av[1]);
	return (0);
}
