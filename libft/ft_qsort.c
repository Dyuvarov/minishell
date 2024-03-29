/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 12:13:35 by fmoaney           #+#    #+#             */
/*   Updated: 2020/12/24 12:40:08 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_qsort(int v[], int left, int right)
{
	int i;
	int last;

	if (left >= right)
		return ;
	ft_swap(v, left, (left + right) / 2);
	last = left;
	i = left + 1;
	while (i <= right)
	{
		if (v[i] < v[left])
			ft_swap(v, ++last, i);
		i++;
	}
	ft_swap(v, left, last);
	ft_qsort(v, left, last - 1);
	ft_qsort(v, last + 1, right);
}
