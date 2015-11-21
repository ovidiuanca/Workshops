#include "header.h"

void	test_ft_is_alpha()

// Tests ft_is_alpha function.

{
	char string1[20] = "NuMergeCodul";
	char string2[20] = "Merg3b1ine";
	if (!(ft_is_alpha(string1) == 1 && ft_is_alpha(string2) == 0))
		printf("ft_is_alpha function is wrong!\n");
}
