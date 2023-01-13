#include "../inc/header.h"

void throw_replace(char * error, char * substr, int del_sub){
	if (substr){
		char * newstr = mx_replace_substr(error, "?", substr);
		if (del_sub) free(substr);
		mx_printerr(newstr);
		free(newstr); 	
	}
	else{
		mx_printerr(error);
	}
	exit(0);
}

int arr_len(char ** arr){
	int i = 0;
	for (; arr[i]; i++);
	return i;
}

t_list * validate(int argc, char * argv[], int * islands_count, int *** paths){
	if (argc != 2){
		throw_replace(USAGE_E, NULL, 0);
	}
	char * file_str = mx_file_to_str(argv[1]);
	if (file_str == NULL){
		throw_replace(NO_FILE_E, argv[1], 0);
	}
	else if (mx_strlen(file_str) == 0){
		throw_replace(EMPTY_FILE_E, argv[1], 0);
	}
	int err = 0;
	char ** lines = mx_strsplit(file_str, '\n');
	(*islands_count) = mx_atoi(lines[0], &err);
	int dists_sum = 0;
	int name_i = 0;
	int dup_isl_error = 0;
	int len_sum_error = 0;
	int dist;
	char ** names_lines;
	char ** names_count;
	int file_lines_count = mx_count_words(file_str, '\n');
	t_list * names = mx_create_node(malloc(sizeof(char)));
	free(file_str);
	if (err || (*islands_count) <= 0)
	{
		mx_del_strarr(&lines);
		mx_clear_list(&names, 1);
		throw_replace(INVALID_FLINE_E, NULL, 0); // nothing to replace
	}
	for (int i = 1; i < file_lines_count; i++)
	{
		dist = 0;
		names_lines = NULL;
		names_count = NULL;
		if (mx_get_char_index(lines[i], ',') != -1 && 
			validate_string(lines[i], '-', ','))
		{
			names_count = mx_strsplit(lines[i], ',');
			if (names_count){
				names_lines = mx_strsplit(names_count[0], '-');
			}
		}
		if (names_lines && names_count && 
			mx_strcmp(names_lines[0], names_lines[1])){
			dist = mx_atoi(names_count[1], &err);
		}
		if (err || dist <= 0){
			del_strarrarr(&lines, NULL, &names_count, &names_lines);
			mx_clear_list(&names, 1);
			throw_replace(INVALID_LINE_N_E, mx_itoa(i + 1), 1);
		}
		// && !lines_differ(names_lines, lines[j])
		for (int j = 1; j < file_lines_count; j++){
			if (validate_string(lines[j], '-', ',')){
				if (i != j && !lines_differ(names_lines, lines[j])){
					dup_isl_error = 1;
				}	
			}
		}
		//<-----FILLING NAMES ARR----->
		name_i += add_name(&names, names_lines[0], name_i); 
		name_i += add_name(&names, names_lines[1], name_i); 
		//mx_printint(names_len);
		//<-----FILLING NAMES ARR----->
		dists_sum += dist;
		if(dists_sum < 0) len_sum_error = 1;
		del_strarrarr(&names_count, &names_lines, NULL, NULL);
	}
	free(names->data);
	mx_pop_front(&names);
	int names_len = mx_list_size(names);
	if (names_len != *islands_count ||
		dup_isl_error || len_sum_error){
		mx_clear_list(&names, true);
		mx_del_strarr(&lines);
		if (names_len != *islands_count)
			throw_replace(INVALID_IS_C_E, NULL, 0); // nothing to replace	
		else if (dup_isl_error)
			throw_replace(DUP_BRIDGES_E, NULL, 0);	
		else
			throw_replace(LEN_SUM_E, NULL, 0);	
	}
	*paths = make_paths_matrix(names, lines, file_lines_count);
	mx_del_strarr(&lines);
	return names;
}

