#include <stdio.h>
#include <assert.h>
#include "syntax_analysis.h"
#include "files.h"

const char* s = NULL;
int p = 0;

int GetG0(const char* what)
{
	s = what;
	p = 0;
	int val = GetE();
	//~ printf("%c", s[p]);
	assert(s[p] == 0);
	return val;
}

int GetN()
{
	int val = 0;
	while ('0' <= s[p] && s[p] <= '9')
	{
		val = val*10 + s[p] - '0';
		p++;
	}
	return val;
}

int GetE()
{
	int val = GetN();
	while (s[p] == '+' || s[p] == '-')
	{
		char op = s[p];
		p++;
		int val2 = GetN();
		if (op == '+') val += val2; else val -= val2;
	}
	return val;
}
