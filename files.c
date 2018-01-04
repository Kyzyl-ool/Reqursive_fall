#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

unsigned int sizeof_file(const char* file_name)
{
	FILE* fi = fopen(file_name, "r");
	fseek(fi, 0, SEEK_END);
	return ftell(fi)*sizeof(char);
}

char* readfile(const char* filename)
{
	assert(filename);
	FILE* fi = fopen(filename, "r");
	assert(fi);
	
	fseek(fi, 0, SEEK_END);
	char* text = (char*)calloc(ftell(fi), sizeof(char));
	assert(text != NULL);
	
	fseek(fi, 0, SEEK_SET);
	int i = 0;
	char c = fgetc(fi);
	while (c != EOF)
	{
		text[i] = c;
		i++;
		c = fgetc(fi);
	}
	fclose(fi);
	return text;
}

int amount_of_char(const char* s, char c)
{
	assert(s != NULL);
	int i = 0, n = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c) n++;
		i++;
	}
	return n;
}

int amount_of_strings(const char* s)
{
	assert(s != NULL);
	int i = 0, n = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\n') i++;
		while (s[i+1] == '\n') i++;
		n++;
		i++;
	}
	return n;
}

char** make_array_of_strings_beginnings(char* s)
{
	assert(s != NULL);
	
	char** strings = (char**)malloc(amount_of_strings(s)*sizeof(char*));
	assert(strings);
		
	strings[0] = s;
	int i = 0, j = 1;
	while (s[i] != '\0')
	{
		while (s[i] != '\n') i++;
		while (s[i+1] == '\n') i++;
		strings[j] = &s[i+1];
		i++;
		j++;
	}
	return strings;
}

char** make_array_of_strings_beginnings_with_sep(char* s, char sep)
{
	assert(s != NULL);
	
	char** strings = (char**)calloc(amount_of_char(s, sep)+1, sizeof(char*));
	assert(strings);
	
	strings[0] = s;
	int i = 0, j = 1;
	while (s[i] != '\0' && j < amount_of_char(s, sep)+1)
	{
		while (s[i] != sep) i++;
		strings[j] = &s[i+1];
		i++;
		j++;
	}
	return strings;
}

int replace_in_array(char* s, char what_to_replace, char what_replace)
{
	assert(s);
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == what_to_replace)
		{
			s[i] = what_replace;
		}
		i++;
	}
	return 0;
}
