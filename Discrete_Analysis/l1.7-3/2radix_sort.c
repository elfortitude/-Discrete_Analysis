#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef	struct 			my_struct {
	unsigned long long	value;
	unsigned char		key[7];
}						map;

void	radix_sort(map *source, unsigned long int n) {
	map					*tmp;
	unsigned long long	count[91];
	int					i;
	unsigned int		j;
	unsigned long long	sum;
	unsigned long long	bubble;

	i = 5;
	tmp = (map*)malloc(sizeof(map) * n);
	if (!tmp)
		return ;
	if (n > 0) {
		while (i >= 0) {
			sum = 0;
			bubble = 0;
			j = 0;
			while (j < 91)
				count[j++] = 0;
			j = 0;
			while (j < n) {
				count[source[j].key[i]]++;
				j++;
			}
			j = 0;
			while (j < 91) {
				bubble = count[j];
				count[j] = sum;
				sum += bubble;
				j++;
			}
			j = 0;
			while (j < n) {
				tmp[count[source[j].key[i]]] = source[j];
				count[source[j].key[i]]++;
				j++;
			}
			i--;
			memcpy(source, tmp, sizeof(map) * n);
		}
	}
	free(tmp);
}

int		main(void) {
	map					*kvalue;
	unsigned long int	i;
	unsigned long int	j;
	unsigned char		c;
	int					n;

	i = 0;
	j = 1;
	kvalue = (map*)malloc((sizeof(map)));
	while((n = scanf("%c", &c)) != EOF) {
		if (c != '\n') {
			map				tmp;
			tmp.key[6] = '\0';
			if (j == i)
			{
				kvalue = (map*)realloc(kvalue, sizeof(map) * 2 * j);
				if (!kvalue)
					return (0);
				j *= 2;
			}
			tmp.key[0] = c;
			n = scanf("%c%c%c%c%c%c%c%c%llu", &c, &tmp.key[1], &tmp.key[2], &tmp.key[3],
				&c, &tmp.key[4], &tmp.key[5], &c, &tmp.value);
			kvalue[i] = tmp;
			i++;
			n = scanf("%c", &c);
			if (!n)
				;
		}
	}
	radix_sort(kvalue, i);
	j = 0;
	printf("\n");
	while (j < i) {
		printf("%c %c%c%c %c%c\t%llu\n", kvalue[j].key[0], kvalue[j].key[1],
			kvalue[j].key[2], kvalue[j].key[3], kvalue[j].key[4], kvalue[j].key[5],
			kvalue[j].value);
		j++;
	}
	free(kvalue);
	return (0);
}
