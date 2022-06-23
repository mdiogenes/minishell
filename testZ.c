

typedef struct s_prueba {
	int type;
	void *content;
	struct s_prueba *next;
} t_prueba;




//==============================
int	ft_regex_lit(char *haystack, char *pattern, size_t *ih, size_t *ip)
{
	while((pattern[*(ip)] && haystack[*(ih)]) && (pattern[*(ip)] == haystack[*(ih)]))
	{
		*(ip) += 1;
		*(ih) += 1;
		if(pattern[*(ip)] && pattern[*(ip) + 1] == '*')
			return (IS_TRUE);
	}
	if (*(ih) == 0)
		return (IS_FALSE);
	return (IS_TRUE);
}

int	ft_regex_wc(char *haystack, char *pattern, size_t *ih, size_t *ip)
{
	if (!pattern[*(ip) + 1])
	{
		while (haystack[*(ih)])
			*(ih) += 1;
		return (IS_TRUE);
	}
	else
	{
		printf ("estamos aqui con: %zu %zu \n", *(ih), *(ip));
		while (haystack[*(ih)] && haystack[*(ih)] != pattern[*(ip) + 1])
			*(ih) += 1;
		printf ("salimos con con: %zu %zu \n", *(ih), *(ip));
		*(ip) += 1;
		return (IS_TRUE);
	}
}

int	ft_check_hit(char *pattern, size_t *ip, size_t *len_p)
{
	if (pattern[*(ip)] == '*')
	{
		printf("aqui nos trancamos %zu %zu\n", *(ip), *(len_p));
		if (*(ip) + 1 == *(len_p))
			return (IS_TRUE);
		if (pattern[*(ip) + 1])
			*(ip) += 1;
		printf("aqui nos  %zu %zu\n", *(ip), *(len_p));
		return (IS_FALSE);
	}
	else
	{
		if (*(ip) == *(len_p))
			return (IS_TRUE);
	}
	return (IS_FALSE);
}

int ft_regex(char *haystack, char *pattern)
{
	size_t lp;
	size_t lh;
	size_t ip;
	size_t ih;

	lp = strlen(pattern);
	lh = strlen(haystack);
	ih = 0;
	ip = 0;
	if (lp > lh)
		return (IS_FALSE);
	while (pattern[ih])
	{
		if (pattern[ip] != '*')
		{
			if (ft_regex_lit(haystack, pattern, &ih, &ip) == IS_FALSE)
				return (IS_FALSE);
		}
		else if (pattern[ip] == '*')
		{
			if (ft_regex_wc(haystack, pattern, &ih, &ip) == IS_FALSE)
				return (IS_FALSE);
			if (ip + 1 == lp)
				return (IS_TRUE);
		}
		if (ft_check_hit(pattern, &ip, &lp) == IS_TRUE)
				return (IS_TRUE);
		if (ip + 1 == lp || ih + 1 == lh)
			return (IS_TRUE);
	}
	return (IS_FALSE);
}

int main()
{
	char *pattern;
	char *haystack;
	char **battery;
	char **pattern_bat;

	pattern = "*.* *.c Make* *ADME* *ADME bas* b* cke* m*n*s*e*l *i*i*h*l*";
	haystack = "Makefile README.md a a.out b bash bu c cat checker checker.dSYM inc lib lol ls minishell minishell.dSYM obj pipex proba proba2 push_swap push_swap.dSYM repo somefile srcs test test.sh testZ.c tester";
	battery = ft_split(haystack, ' ');
	pattern_bat = ft_split(pattern, ' ');
	for (int y = 0; pattern_bat[y]; y++)
	{
		printf("\n===== %s =====\n", pattern_bat[y]);
		for (int i = 0; battery[i]; i++)
		{
			printf("eval:  %s ", battery[i]);
			if (ft_regex(battery[i], pattern_bat[y]) == IS_TRUE)
				printf(" OK ");
			printf("\n");
		}
	}
			/*
	char *patron;
	char *texto;
	size_t lp;
	size_t lt;
	size_t ip;
	size_t it;
	int flag;

	patron = "*nish*";
	texto = "minishell";
	lp = strlen(patron);
	lt = strlen(texto);
	it = 0;
	ip = 0;
	flag = strlen(texto);
	while (patron[it])
	{
		if (patron[ip] != '*')
		{
			while((patron[ip] && texto[it]) && (patron[ip] == texto[it]))
			{
				ip++;
				it++;
				if(patron[ip] && patron[ip] == '*')
					break ;
			}
			if (it == 0)
			{
				printf("no hay coincidencia\n");
				break;
			}
		}
		else if (patron[ip] == '*')
		{
			if (ip == 0 && texto[it + 1] && texto[it] == patron[ip + 1])
			{
					printf("condicion al inicio, no hit\n");
					break ;
			}
			if (patron[ip + 1])
			{
				while (texto[it] && texto[it] != patron[ip + 1])
					it++;
			}
			else
			{
				while (texto[it])
					it++;
			}
			if (patron[ip] == '*')
			{
				if (ip + 1 == lp)
				{
					printf("esto deberia ser un hit en condicion 1\n");
					break ;
				}
				if (patron[ip + 1])
					ip++;
			}
			else
			{
				if (ip == lp)
				{
					printf ("esto deberia ser un hit en condicion 2\n");
					break ;
				}
			}
		}
		if (it == lt || ip == lp)
		{
			printf("salida en condicion??\n");
			break;
		}
	}
	printf("%d patron %d texto\n", ip, it);
	*/
	
}