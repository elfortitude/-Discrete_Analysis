#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int CHARACTERS_ASCII = 91;

typedef	struct 			TMyStruct {
	unsigned char		key[7];
	unsigned long long	value;
}						TMap;

void	RadixSort(TMap *source, unsigned long int size) {
	TMap				*tmp;
	int					i;
	unsigned int		j;
	unsigned long long	count[CHARACTERS_ASCII];
	unsigned long long	sum;
	unsigned long long	bubble;

	i = 5;
	tmp = NULL;
	tmp = (TMap*)malloc(sizeof(TMap) * size);
	if (!tmp) {
		return ;
	}
	if (size > 0) {
		while (i >= 0) {
			sum = 0;
			bubble = 0;
			j = 0;
			while (j < CHARACTERS_ASCII)
				count[j++] = 0;
			j = 0;
			while (j < size) {
				count[source[j].key[i]]++;
				j++;
			}
			j = 0;
			while (j < CHARACTERS_ASCII) {
				bubble = count[j];
				count[j] = sum;
				sum += bubble;
				j++;
			}
			j = 0;
			while (j < size) {
				tmp[count[source[j].key[i]]] = source[j];
				count[source[j].key[i]]++;
				j++;
			}
			i--;
			memcpy(source, tmp, sizeof(TMap) * size);
		}
	}
	free(tmp);
}

int		main(void)
{
	TMap				*kvalue;
	char				c;
	int					uselessVar;
	unsigned long long	count;
	unsigned long long	size;

	count = 0;
	size = 1;
	kvalue = (TMap*)malloc((sizeof(TMap)));
	while((c = getchar()) != EOF) {
		if (c != '\n') {
			TMap		tmp;
			if (size == count) {
				kvalue = (TMap*)realloc(kvalue, sizeof(TMap) * 2 * size);
				if (!kvalue) {
					return (0);
				}
				size *= 2;
			}
			tmp.key[0] = c;
			c = getchar();
			c = getchar();
			tmp.key[1] = c;
			c = getchar();
			tmp.key[2] = c;
			c = getchar();
			tmp.key[3] = c;
			c = getchar();
			c = getchar();
			tmp.key[4] = c;
			c = getchar();
			tmp.key[5] = c;
			tmp.key[6] = '\0';
			c = getchar();
			uselessVar = scanf("%llu", &tmp.value);
			kvalue[count] = tmp;
			c = getchar();
			count++;
			if (!uselessVar) {
				;
			}
		}
	}
	RadixSort(kvalue, count);
	size = 0;
	printf("\n");
	while (size != count) {
		printf("%c %c%c%c %c%c\t%llu\n", kvalue[size].key[0], kvalue[size].key[1],
			kvalue[size].key[2], kvalue[size].key[3], kvalue[size].key[4], kvalue[size].key[5],
			kvalue[size].value);
		size++;
	}
	free(kvalue);
	return (0);
}
