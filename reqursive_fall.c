#include <stdio.h>
#include "syntax_analysis.h"

int main()
{
	printf("%d\n", GetG0("100*8-10*100"));
	return 0;
}
