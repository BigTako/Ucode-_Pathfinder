#include "../inc/header.h"

void del_matrix(int ** matrix, int size){
	for (int j = 0; j < size; j++){
		free(matrix[j]);
	}	
	free(matrix);
}

int ** make_paths_matrix(t_list * names, char ** lines, int l_count){
	int size = mx_list_size(names);
	int fro_i;
	int to_i;
	int ** paths = malloc(size*sizeof(int *));
	for (int i = 0; i < size; i++){
		paths[i] = malloc(size*sizeof(int));
		for (int j = 0; j < size; j++)
		{
			paths[i][j] = 0;
		}
	}
	for (int i = 1; i < l_count; i++){
		char ** names_count = mx_strsplit(lines[i], ',');
		char ** names_lines = mx_strsplit(names_count[0], '-');
		int dist = mx_atoi(names_count[1], NULL);
		fro_i = get_i_by_value(names, names_lines[0]);
		to_i = get_i_by_value(names, names_lines[1]);  
		if (fro_i != -1 && to_i != -1){
			paths[fro_i][to_i] = dist;
			paths[to_i][fro_i] = dist;
		}	
		else{
			del_strarrarr(&names_count, &names_lines, NULL, NULL);
			del_matrix(paths, size);
			return NULL;
		}
		del_strarrarr(&names_count, &names_lines, NULL, NULL);
	}
	return paths;
}

