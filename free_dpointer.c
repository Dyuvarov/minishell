/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 22:51:51 by fmoaney           #+#    #+#             */
/*   Updated: 2021/01/25 21:52:48 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_dpointer(void ***p, size_t nmemb)
{
	void **dp;

	dp = *p;
	while (nmemb--)
		free(dp[nmemb]);
	free(*p);
	*p = NULL;
	return (1);
}
