#include "../inc/header.h"

int main(int argc, char * argv[])
{
	int islands_count;
	int ** paths;
	t_list * islands_names = validate(argc, argv, &islands_count, &paths);   
	for (int i = 0; i < islands_count - 1; i++)
  	{
		dijkstra(paths, islands_names, islands_count, i);    
    }
	del_matrix(paths, islands_count);
	mx_clear_list(&islands_names, true);
	return 0;
}


