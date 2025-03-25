# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_test
{
	char 	*str;
	int		n;
}				t_est;

t_est	*test_set(void)
{
	static t_est	*test;

	if (!test)
	{
		test = malloc(sizeof(t_est));
		test->str = malloc(sizeof(char) * 2);
		test->str[0] = 'c';
		test->str[1] = '\0';
		test->n = 537;
	}
	return (test);
}

// t_est	*test_get(void);
// {
// 	static t_est	*test;
// }

void	rndm_fct(void)
{
	t_est	*test;
	t_est	*test2;

	test2 = NULL;
	test = test_set();
	printf("add->%p\nstr->%s\nn->%d\n", test, test->str, test->n);
	test2 = test_set();
	test->n = 666;
	printf("add->%p\nn->%d\n", test2, test2->n);
	free(test->str);
	free(test);
}

int	main (void)
{
	test_set();
	rndm_fct();
}
