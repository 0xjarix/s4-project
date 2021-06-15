#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "demo.h"


int main (int argc, char *argv[])
{
    if (argc == 10)
        return 0;
    int version = atoi(argv[1]);
    size_t col = (((version-1)*4)+21);
    size_t size = col * col;
    char *mat = calloc(size,sizeof(char));
    char *cursor = mat;
    char **newp = &cursor;

    printf("\n");

    finder_pattern(mat,newp,col);
    finder_pattern((mat+(col-7)),newp,col);
    finder_pattern((mat+col*(col-7)),newp,col);

    if (version > 1)
    {
        char *l = find_alignment(version);

        for (int i = 0;*(l+i);i++)
        {
            int n = atoi(l+i);
            n = (col*(n-2) + n-2);

            if (mine(mat+n,mat,size,col)<10)
            {

                alignment_pattern(mat+n,col);
            }
        }

    }


    timing_pattern_horizontal((mat+(col*6)+8),col);
    timing_pattern_vertical((mat+(col*8)+6),col);

    char *letters_begin = argv[2];

    //case we have space

    //for (int i = 1; i < argc;i++)
    //{
    //*(letters_begin + i) = argv[i];
    //}


    size_t len_letters = 0;
    char *end_letters = letters_begin;
    //char str[size];
    //fgets(str,sizeof(str),stdin);

    //char *stop = &(*(mat+col*(col-1)));
    //char *detected = &(*(mat+7));
    //char *change = &(*(mat+6));

    //getting the size of the argument (the message to encode)
    while(*end_letters != '\0')
    {
        len_letters++;
        end_letters++;
    }


    char *letters = calloc (len_letters,sizeof(char));
    init_letters(letters,letters_begin,end_letters);

    //for(size_t i = 0;i< len_letters;i++)
    //{
    //printf("%c",*(letters+i));
    //}



    //int len = (11*(len_letters/2))+(len_letters%2)*6;
    //char* res = calloc();
    char* res = to_binary(letters,len_letters);
    for(int i = 0; i < 11;i++)
    {
        printf("%d",(*(res+i)));
    }

    printf("\n");

    cursor = mat + size-1;

    //while (cursor > mat)
    // (int i = 4; i > 0;i--)

    int j = version; //not really meaningful just for the presentation
    for (int i = j;i > 0; i--)
    {
        //going up
        //while (cursor -col > mat)
        while (cursor-col > mat-col)
        {
            if (*cursor != 5 && (mine(cursor,mat,size,col) < 10))
            {
                *cursor = *res;
                res+=1;
            }
            cursor -=1;

            if(*cursor!=5 && (mine(cursor,mat,size,col) < 10))
            {
                *cursor = *res;
                res+=1;
            }
            //		if (cursor ==  detected)

            //	{
            //	printf("movdeeeeeeeeeeeeeee\n");
            //	printf("i am %d\n",*(cursor-1));

            //	cursor -=1;// &(*change);
            //		cursor = 6;
            //		printf("%d\n",cursor-col > mat-col);

            //	}
            cursor -=col - 1;

        }
        cursor+=col+1;
        cursor -=3;
        //if (mine(cursor,mat,size,col) <10)
        //	*cursor = *res;

        //going down

        while (cursor + col+1 < mat + size-1)
        {
            if (*cursor != 5 && (mine(cursor,mat,size,col) < 10))
            {
                *cursor = *res;
                res +=1;
            }
            cursor -=1;
            if (*cursor!= 5 && (mine(cursor,mat,size,col) < 10))
            {
                *cursor = *res;
                res +=1;
            }
            cursor +=col + 1;

        }

        if (mine(cursor,mat,size,col) <10)
        {
            *cursor =*res;
            res+=1;
        }

        cursor -= 1;

        if (mine(cursor,mat,size,col) <10)
        {
            *cursor =*res;
            res+=1;
        }
        cursor-=1;

    }



    //if (version > 1)
    //{
    //alignment_pattern((mat+(col*17)+17),col);
    //}

    //printing the matrix

    for(size_t i = 0; i< size;i++)
    {
        if (i% col == 0)
        {
            printf("\n");
        }
        printf("%d ",*(mat+ i));
    }
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
    *cursor = 5;
    *(cursor + 6) = 5;
    *newp = cursor;
}

void five_line_finder(char *cursor,char**newp)
{
    for (int i = 0; i<7;i++)
    {
        if (i != 1 && i != 5)
        {
            *(cursor+i) =5;
        }
    }
    *newp = cursor;
}

void full_line_finder(char *cursor,char**newp)
{
    for (int i = 0; i < 7;i++)
    {
        *(cursor) = 5;
        cursor+=1;
    }
    *newp = cursor;
}

// functions that draw the timing pattern

void timing_pattern_horizontal(char*cursor,size_t col)
{
    for (size_t i = 0; i < (col - 16);i+=2)
    {
        *(cursor+i) = 5;
    }
}

void timing_pattern_vertical(char*cursor,size_t col)
{
    for (size_t i = 0; i < (col - 16);i+=2)
    {
        *(cursor+(col*i)) = 5;
    }
}

// functions that draw the alignment pattern

void full_line_alignment(char*cursor)
{
    for (int i = 0; i< 5;i++)
    {
        *(cursor+i) = 5;
    }
}

void two_line_alignment(char*cursor)
{
    *cursor = 5;
    *(cursor+4) = 5;
}

void three_line_alignment(char*cursor)
{
    *cursor = 5;
    *(cursor+2) = 5;
    *(cursor+4) = 5;
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
int mine(char *cursor,char* mat, int size,int col)
{
    int sum = *cursor + *(cursor-1) + *(cursor+1);

    if (cursor < mat + col)
    {
        return sum + *(cursor-1) + *(cursor+1);
    }

    if  (cursor - col > mat)
    {
        sum += *(cursor - col ) ;
    }
    if (cursor + col < mat + size)
    {

        sum += *(cursor + col);
    }
    return sum;
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


char* to_binary(char *letters,int len_letters)
{

    int len = (11*(len_letters/2)) + (len_letters%2)*6;

    char* arr = calloc(len,sizeof(char));
    int i = 0;
    int col = 0;
    //int tmp = (len_letters/2)- (len_letters%2 ==0? 1: 0);

    while (i < len_letters)
    {

        int second = 0;


        int first = find_nb(*(letters+i));

        i+=1;

        if (*(letters + i))
        {
            second = find_nb(*(letters+i));
        }


        int nb = (45*first)+second;


        if (i > 0)
        {
            if (i > 2)
                col += 11 ;
            if (len_letters == 1)
                col = (i-1)*11;
        }

        for (int j = 10; j >= 0;j--)
        {
            if (nb > 0 && nb % 2 == 1)
            {
                *(arr+j+col) = 1;
            }
            if (nb > 0)
            {
                nb /= 2;

            }
        }
        i+=1;
    }
    //odd nb of characters



    if (i  == len_letters)
    {
        if (i > 0)
        {
            if (i > 2)
                col += 11 ;
            //  if(len_letters == 1)
            //	  col = (i-1)*11;
        }

        int nb = find_nb(*(letters+i));

        for (int j = 5; j >= 0;j--)
        {
            if (nb > 0 && nb % 2 == 1)
            {
                *(arr+j+col) = 1;
            }
            if (nb > 0)
            {
                nb /= 2;
            }
        }

    }

    for (int i = 0; i< len;i++)
    {
        printf("%d",*(arr+i));
        if (i > 0 && i % 11 == 0)
            printf(" ");
    }
    printf("\n");
    return arr;

}

int find_nb(char c)
{
    FILE *fptr = fopen("./alphanumeric.txt","r");
    int fd = fileno(fptr);
    int r;
    char buf[1024];
    char* tmp = calloc(3,sizeof(char));
    int tmp_index = 0;
    int nb = 0;
    //int mult = 10;

    while ((r = read(fd,buf,1024)))
    {
        for (int i = 0; i < r; i++)
        {
            if (buf[i] == c)
            {
                i++;
                while (buf[i] != '\n')
                {
                    if (buf[i] != ' ')
                    {
                        *(tmp + tmp_index) = buf[i];
                        tmp_index++;
                    }
                    i++;

                }

            }
        }

    }
    nb = atoi(tmp);

    return nb;
}

char* find_alignment(int version)
{
    FILE *fptr = fopen("./alignment.txt","r");
    int fd = fileno(fptr);
    int r;
    char buf[1024];
    char* tmp = calloc(3,sizeof(int));
    int tmp_index = 0;
    //int nb = 0;
    //int mult = 10;
    int line = 2;

    while ((r = read(fd,buf,1024)))
    {
        for (int i = 0; i < r; i++)
        {
            if (line == version)
            {
                i++;
                while (buf[i] != '\n')
                {
                    if (buf[i] != ' ')
                    {
                        *(tmp + tmp_index) = buf[i];
                        tmp_index++;
                    }
                    i++;
                }
            }
            while(buf[i] != '\n')
            {i++;}
            line++;
        }
    }

    return tmp;
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
