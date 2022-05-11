/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:51:51 by msoler-e          #+#    #+#             */
/*   Updated: 2022/05/11 13:55:26 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	*ft_expand(char *str)
{
	char	*dst;
	int		len;
	int		i;
	
	i = 0;
	len = ft_strlen(str);	
	

	dst = getenv(str);
	if (!dst)
		dst= "";
	return (dst);
}

int main()
{
	char 	*src;
	char	*dst;

	src="";

	dst = ft_expand(src);
	printf("\nResultat:%s",dst);
}	
