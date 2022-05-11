/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:51:51 by msoler-e          #+#    #+#             */
/*   Updated: 2022/05/11 15:37:48 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	*ft_expand(char *str)
{
	char	*dst;
	char	*temp;
	char	*word;
	int		len;
	int		i;

	i = 0;
	corxt = 0;
	len = ft_strlen(str);	
	while (str[i] != '$')
	{
		i ++;
	}
	i ++;
	if (str[i] == '{')
	{
		i ++;
		temp = ft_strrchr(str,'}');
	}	
	if (temp)
	{
		word = ft_substr(str, i, temp);
	}
	else
		word = ft_substr(str,i,len);
	dst = getenv(word);
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
