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
//#include "minishell.h"
#include "../lib/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	max;
	char	*rst;

	if (!s)
		return (NULL);
	max = ft_strlen(s);
	if (len > (max - start))
		len = max - start;
	if (start > max)
		len = 0;
	rst = (char *)malloc(sizeof(char) * (len + 1));
	if (rst == NULL)
		return (NULL);
	if (len == 0)
		rst[0] = '\0';
	else
		ft_strlcpy(rst, &((char *)s)[start], len + 1);
	return (rst);
}

size_t	ft_strlcpy(char *dest, char *src, size_t destsize)
{
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(src);
	if (destsize > 0)
	{
		while (src[i] && i < (destsize - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (s_len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rst;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	rst = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (rst == NULL)
		return (NULL);
	ft_memcpy(rst, s1, len_s1);
	ft_memcpy(&rst[len_s1], s2, len_s2);
	rst[len_s1 + len_s2] = 0;
	return (rst);
}

int	ft_change_var(char **dst, int i, int j, char **str)
{
	char *var;

	var = NULL;
	//dst ho hauriem de inicialitzar dalguna manera??
        *dst = ft_strjoin(*dst,ft_substr(*str,j,i-j));
        i ++;
        j = i;
        while ((*str)[i] != ' ' && i < (int)ft_strlen(*str) && (*str)[i] != '$')
        	i++;
        //hauria de fer malloc de la variable VAr?
	
  
	if ((var = getenv((const char *)ft_substr(*str, j, i - j))))
        	*dst = ft_strjoin(*dst, var);
        else
        	*dst = ft_strjoin(*dst,"\0");
	if (var==NULL)
		free(var);
	return(i);
}



char	*ft_expand(char *str)
{
	char	*dst;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{	
		if (str[i] == '$')
		{	
			i = ft_change_var(&dst, i, j, &str);
i			j = i;
		}
		if ((str[i] != '$') || !str[i + 1] || ((str[i]=='$' && ((str[i + 1] == ' ') || str[i + 1] == '?'))))
		{
			i ++;
			while (str[i + 1]=='$')
				i++;
			if (str[i] == '$' && (str[i + 1] == ' '))
				i ++;
			if ((str[i] =='$') && (str[i + 1] == '?'))
			{
				i++;
				dst = ft_strjoin(dst,ft_substr(str,j,i-j-1));
				j = i + 1;
				dst = ft_strjoin(dst, "lastpipe");
			}
		}
	}
	if (i > j)
		dst = ft_strjoin(dst, ft_substr(str, j, i -j));
//no estic alliberant el punter original que em venia(str)com no esta al projecte gran peta
//	if (str)
//		free(str);
	return (dst);
}
//cometes simples ha de ignorar?
//$? deberá expandirse al estado de salida del comando más reciente ejecutado en la pipeline.
//$$ tampoc surt igual que el bash nos en borrem un dels 2
//$$? fem igual que $$
int main()
{
	char 	*src;
	char	*dst;

	src="$proba$HOMEgdfds$pepe udsah $HOMEsdfgs dsg s& sgfd$dasf dfsd $HOMEdsfd t&?$HOME$t";
	dst = ft_expand(src);
	printf("\nResultat:%s",dst);
}
