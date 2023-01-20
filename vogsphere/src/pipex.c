/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:19:25 by alevra            #+#    #+#             */
/*   Updated: 2023/01/19 21:49:26 by alevra           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(void)
{
	ft_printf("Quand on veut transmettre une information via un pipe, il faut ouvrir le fd en entree et surtout, fermer le fd en sortie.
	Ensuite, pour lire cette information, il faut fermer le fd de lecture et ouvrir le fd decriture\n");
	return (0);
}
