#include <stdlib.h>
#include <stdio.h>
#include "fixed_patterns.h"


int main (int argc, char *argv[])
{
int version = atoi(argv[1]);
size_t col = (((version-1)*4)+21);   
size_t size = col * col; 
char *mat = calloc(size,sizeof(char));
char *cursor = mat;
char **newp = &cursor;

finder_pattern(mat,newp,col);
finder_pattern((mat+(col-7)),newp,col);
finder_pattern((mat+col*(col-7)),newp,col);

timing_pattern_horizontal((mat+(col*6)+8),col);
timing_pattern_vertical((mat+(col*8)+6),col);
if (version > 1)
{
alignment_pattern((mat+(col*17)+17),col);
}
//printing the matrix 

for(int i = 0; i< size;i++)
{
if (i% col == 0)
{
printf("\n");
}
printf("%d ",*(mat+ i));
}
//printf("\n");
//placement_from_file(2);

return 0;

}

// functions that draws the finder pattern

void finder_pattern(char *cursor, char**newp,size_t col)
{

full_line_finder(cursor,newp);
cursor += col;

two_line_finder(cursor,newp);
cursor += col;

five_line_finder(cursor,newp);
cursor += col;

five_line_finder(cursor,newp);
cursor += col;

five_line_finder(cursor,newp);
cursor += col;

two_line_finder(cursor,newp);
cursor += col;

full_line_finder(cursor,newp);
cursor += col;

}

void two_line_finder(char *cursor,char**newp)
{
*cursor = 1;
*(cursor + 6) = 1;
*newp = cursor;
}

void five_line_finder(char *cursor,char**newp)
{
for (int i = 0; i<7;i++)
{
if (i != 1 && i != 5)
{
*(cursor+i) =1;
}
}
*newp = cursor;
}

void full_line_finder(char *cursor,char**newp)
{
    for (int i = 0; i < 7;i++)
     { 
      *(cursor) = 1;
      cursor+=1;
     }
    *newp = cursor;
}

// functions that draw the timing pattern

void timing_pattern_horizontal(char*cursor,size_t col)
{
for (int i = 0; i < (col - 16);i+=2)
{
*(cursor+i) = 1;
}
}

void timing_pattern_vertical(char*cursor,size_t col)
{
for (int i = 0; i < (col - 16);i+=2)
{
*(cursor+(col*i)) = 1;
}
}

// functions that draw the alignment pattern 

void full_line_alignment(char*cursor)
{
for (int i = 0; i< 5;i++)
{
*(cursor+i) = 1;
}
}

void two_line_alignment(char*cursor)
{
*cursor = 1;
*(cursor+4) = 1;
}

void three_line_alignment(char*cursor)
{
*cursor = 1;
*(cursor+2) = 1;
*(cursor+4) = 1;
}

void alignment_pattern(char*cursor,size_t col)
{

full_line_alignment(cursor);
cursor += col;

two_line_alignment(cursor);
cursor += col;

three_line_alignment(cursor);
cursor += col;

two_line_alignment(cursor);
cursor += col;

full_line_alignment(cursor);
cursor += col;

}
/*
int placement_from_file(int i)
{
    FILE *fp;
    char* filename = "./data.txt";
    char ch;
    int line = 1;
    char nb[1000];
    int res[1000];
    int index = 0;
    int res_index = 0;


    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s",filename);
        return 1;
    }
    while ((ch = fgetc(fp)) != EOF)
    {	
	if (line == i)
	{
	while(ch = fgetc(fp) != '\n')
	{
	while (ch = fgetc(fp) != ' ' && ch != '\n')
	{
	//ch = fgetc(fp);
        nb[index] = ch;
	index+=1;
	}
	res[res_index] = atoi(nb);
	index = 0;
	res_index +=1;
        //ch = fgetc(fp);
	}
	
	}
	if (ch == '\n')
	{
	line +=1;
	}
	
    }
        printf("%d",res[1]);
        fclose(fp);
        return 0;

}*/
