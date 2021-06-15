#include <stdlib.h>
#include <stdio.h>
#include "test.h"

int main (int argc, char *argv[])
{
char *big = calloc(441,sizeof(char));
//int i = 441;

char *first = argv[1];
size_t size = 0;
char *q = first;

while(*q!='\0')
{
size++;
q++;
}
if (size > 17)
{
printf("size of message should be smaller than 17, current size = %ld\n",size);
return 0;
}

char *letters = calloc(17,sizeof(char));
init_letters(letters,first,q);
char *cursor = (big + 440);

size_t index = 0;
char **newp = &cursor;
//encoding mode:
//cursor-=1;
//(*cursor) = 1;
//cursor = cursor - 41;
//length of the message:
//(*newp) = cursor;

//char *res = calloc(8,sizeof(char));
//printf("size = %d\n",(int)size);
//res = to_binary((int)(size),res);
//transpose_up(cursor,newp,res);
//free(res);
//cursor = *newp - 20;


if (index<size)
{
char *res1 = calloc(8,sizeof(char));
res1 = to_binary((int)*(letters+index),res1);
transpose_up(cursor,newp,res1);
index++;
free(res1);
}

cursor = *newp - 20;

if (index<size)
{
char *res11 = calloc(8,sizeof(char));
res11 = to_binary((int)*(letters+index),res11);
transpose_up(cursor,newp,res11);
index++;
free(res11);
}

cursor = *newp - 20;

if (index<size)
{
char *res2 = calloc(8,sizeof(char));
res2 = to_binary((int)*(letters+index),res2);
transpose_left_down(cursor,newp,res2);
free(res2);
index++;
}

cursor = *newp + 22;

if (index<size)
{
char *res3 = calloc(8,sizeof(char));
res3 = to_binary((int)*(letters+index),res3);
transpose_down(cursor,newp,res3);
free(res3);
index++;
}

cursor = *newp + 22;

if (index<size)
{
char *res4 = calloc(8,sizeof(char));
res4 = to_binary((int)*(letters+index),res4);
transpose_down(cursor,newp,res4);
free(res4);
index++;
}

cursor = *newp + 22;

if (index<size)
{
char *res5 = calloc(8,sizeof(char));
res5 = to_binary((int)*(letters+index),res5);
transpose_left_up(cursor,newp,res5);
free(res5);
index++;
}
/*
cursor = *newp - 20;

if (index<size)
{
char *res6 = calloc(8,sizeof(char));
res6 = to_binary((int)*(letters+index),res6);
transpose_up(cursor,newp,res6);
free(res6);
index++;
}

cursor = *newp - 20;

if (index<size)
{
char *res7 = calloc(8,sizeof(char));
res7 = to_binary((int)*(letters+index),res7);
transpose_up(cursor,newp,res7);
free(res7);
index++;
}

cursor = *newp - 20;

if (index<size)
{
char *res8 = calloc(8,sizeof(char));
res8 = to_binary((int)*(letters+index),res8);
transpose_left_down(cursor,newp,res8);
free(res8);
index++;
}

cursor = *newp + 22;

if (index<size)
{
char *res9 = calloc(8,sizeof(char));
res9 = to_binary((int)*(letters+index),res9);
transpose_down(cursor,newp,res9);
free(res9);
index++;
}

cursor = *newp + 22;

if (index<size)
{
char *res10 = calloc(8,sizeof(char));
res10 = to_binary((int)*(letters+index),res10);
transpose_left_down(cursor,newp,res10);
free(res10);
index++;
}

cursor = *newp + 22;

if (index<size)
{
char *res11 = calloc(8,sizeof(char));
res11 = to_binary((int)*(letters+index),res11);
transpose_down(cursor,newp,res11);
free(res11);
index++;
}

cursor = *newp + 22;

if (index<size)
{
char *res12 = calloc(8,sizeof(char));
res12 = to_binary((int)*(letters+index),res12);
transpose_up(cursor,newp,res12);
free(res12);
index++;
}


cursor = *newp - 20;

if (index<size)
{
char *res13 = calloc(8,sizeof(char));
res13 = to_binary((int)*(letters+index),res13);
transpose_up(cursor,newp,res13);
free(res13);
index++;
}


cursor = *newp - 20;

if (index<size)
{
char *res14 = calloc(8,sizeof(char));
res14 = to_binary((int)*(letters+index),res14);
transpose_up(cursor,newp,res14);
free(res14);
index++;
}


cursor = *newp + 22;

if (index<size)
{
char *res15 = calloc(8,sizeof(char));
res15 = to_binary((int)*(letters+index),res15);
transpose_up(cursor,newp,res15);
free(res15);
index++;
}
*/

for(int i = 0; i< 441;i++)
{
if (i%21 == 0)
{
printf("\n");
}
printf("%d ",*(big + i));
}


}

char* to_binary(int x,char *res)
{
    int bin = 0;
    for(;x>0;x/=2)
    {
	bin = bin*10 + (x%2);
    }
    for(int i = 7; i>=0;i--)
    {
    if (bin%10==1)
    	*(res+i) = 1;
    bin /=10;
    }
    return res;
}

void transpose_up(char*cursor,char**newp, char* current_block)
{
for (int i = 0; i<4;i++)
{
  *(cursor) = *(current_block);
   current_block += 1; 
   cursor -= 1; 
  *(cursor) = *(current_block);
   current_block += 1;   
  if(i<3)
    {
    cursor = cursor - 20; 
    }
}
*newp = cursor;
}

void transpose_down(char*cursor,char ** newp, char* current_block)
{
for (int i = 0; i<4;i++)
{
  *(cursor) = *(current_block);
    current_block += 1; 
    cursor-= 1; 
  *(cursor) = *(current_block);
    current_block += 1; 
  if (i <3)
    {
    cursor = cursor + 22; 
    }
}
*newp = cursor;
}

char* init_letters(char* letters,char*first, char* q)
{
   int i = 0;
   while ((first+i)<q)
   {
        *(letters+i) = *(first+i);
	i+=1;
   }
   return letters;
}

void transpose_left_down(char*cursor,char ** newp, char* current_block)
{
  for (int i = 0; i < 2;i++)
  {
   *(cursor) = *(current_block);
   current_block += 1; 
   if (i <1) 
   {
   cursor-= 1; 
   }
  }
  cursor -= 20;
  for (int i = 0; i<4;i++)
   {
  *(cursor) = *(current_block);
   current_block += 1; 
  if (i<3)
    {
    cursor-= 1; 
    }
   }
   cursor += 22;
  for (int i = 0; i < 2;i++)
  {
   *(cursor) = *(current_block);
    current_block += 1; 
   if(i <1)
   { 
    cursor-= 1; 
   } 
  }
*newp = cursor;
}
void transpose_left_up(char*cursor,char ** newp, char* current_block)
{
  for (int i = 0; i < 2;i++)
  {
   *(cursor) = *(current_block);
   current_block += 1; 
   if (i <1) 
   {
   cursor-= 1; 
   }
  }
  cursor += 22;
  for (int i = 0; i<4;i++)
   {
  *(cursor) = *(current_block);
   current_block += 1; 
  if (i<3)
    {
    cursor-= 1; 
    }
   }
   cursor -= 20;
  for (int i = 0; i < 2;i++)
  {
   *(cursor) = *(current_block);
    current_block += 1; 
   if(i <1)
   { 
    cursor-= 1; 
   } 
  }
 *newp = cursor;
}


