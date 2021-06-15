#ifndef FIXED_PATTERNS_H
#define FIXED_PATTERNS_H

void full_line_finder(char*cursor,char**newp);
void finder_pattern(char*cursor,char**newp,size_t col);
void two_line_finder(char *cursor,char**newp);
void five_line_finder(char*cursor,char**newp);
void timing_pattern_horizontal(char*cursor,size_t col);
void timing_pattern_vertical(char*cursor,size_t col);
void full_line_alignment(char* cursor);
void two_line_alignment(char* cursor);
void three_line_alignment(char* cursor);
void alignment_pattern(char*cursor,size_t col);
int placement_from_file(int i);
int mine(char*cursor, char* mat,int size,int col);
char* init_letters(char* letters, char* first,char*q);
char* to_binary(char* res,int len_letters);
int find_nb(char c);
char* find_alignment(int version);

#endif
