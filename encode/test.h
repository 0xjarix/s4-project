#ifndef TEST_H
#define TEST_H

char* to_binary(int x,char* res);
void transpose_up(char* curosr,char** newp, char* current_block);
char* init_letters(char* letters, char* first,char*q);
void transpose_down(char* cursor,char** newp, char* current_block);
void transpose_left_up(char* cursor,char** newp, char* current_block);
void transpose_left_down(char* cursor,char** newp, char* current_block);
void go_up(size_t size,char *letters, char **newp,char*cursor,int* i);
void go_down(size_t size,char *letters, char**newp,char*cursor,int* i);
void test();
	
#endif
