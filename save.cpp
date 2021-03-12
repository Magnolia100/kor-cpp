#ifndef _SAVE_CPP_
#define _SAVE_CPP_

#include <string.h>
#include <cstdio>
#include <stdlib.h>

struct char_two 
{
	char str[10][99];
};

void make_str()
{
	
}

void Save(char_two str)
{
	FILE *f = fopen("write.cpp","w");
	int i, j;
	for(i=0;i<10;i++)
	{
		fputs(str.str[i],f);
		fprintf(f,"\n");
	}
	fclose(f);
	
}

#endif
