#ifndef HEADER_H
#define HEADER_H
#define USAGE_E "usage: ./pathfinder [filename]\n"
#define NO_FILE_E "error: file ? does not exist\n"
#define EMPTY_FILE_E "error: file ? is empty\n"
#define INVALID_FLINE_E "error: line 1 is not valid\n"
#define INVALID_IS_C_E "error: invalid number of islands\n"
#define INVALID_LINE_N_E "error: line ? is not valid\n"
#define DUP_BRIDGES_E "error: duplicate bridges\n"
#define LEN_SUM_E "error: sum of bridges lengths is too big\n"
#define INFINITY 2147483647

#include "../libmx/inc/libmx.h"
int mx_atoi(const char* str, int * err);
void del_strarrarr(char *** a1, char ***a2, char *** a3, char *** a4);
int validate_string(char * str, char delim, int end);
int lines_differ(char ** b1, char * line2);
void * find_by_i(t_list * list, int i);
int get_i_by_value(t_list * list, void * value);
int add_name(t_list ** names, char * name, int i_to);
void mx_clear_list(t_list **list, bool free_content);
void del_matrix(int ** matrix, int size);
int ** make_paths_matrix(t_list * names, char ** lines, int l_count);
void throw_replace(char * error, char * substr, int del_sub);
t_list * validate(int argc, char * argv[], int * islands_count, int *** paths);
int get_i_by_value(t_list * list, void * value);
t_list *mx_sort_by_ord(t_list * list, t_list * names);
t_list ** generate_permutations(t_list ** lists, t_list * names, int len, int startnode);
void print_distance(int ** G, int * real, int dist);
void print_route(t_list * names, int * path, int last);
void print_results(int ** G, t_list ** pred_lists, t_list * names, int * distance, int startnode);
void dijkstra(int ** G, t_list * names, int n, int startnode);
#endif


