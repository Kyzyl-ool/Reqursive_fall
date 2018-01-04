#include <stdio.h>
#include "syntax_analysis.h"

int main()
{
	printf("%d\n", GetG0("((2+2)*8-3*8)*2"));
	return 0;
}
