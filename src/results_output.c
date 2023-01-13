#include "../inc/header.h"

bool compare_routes(void * a, void *b)
{
    int * r1 = (int *)a;
    int * r2 = (int *)b;
    int i = 0;
  	while (r1[i] != -1
		  && r2[i] != -1)
	  {
			if (r1[i] != r2[i]) return r1[i] > r2[i];
		 	i++;
	  }
	  return r1[i] > r2[i];
}

void print_distance(int ** G, int * real, int dist)
{
  /*Functiond of printing all paths in from startnode to other ones > him.
    G - 2d array of edges weights.
    real - array of vertexes(indexes) vice versa.
    dist - minimum distance.
    dists - count of nums in real number.
  */
  bool print_equal = 0;
  mx_printstr("Distance: ");
  int i = 0;
  int j = 1;
  mx_printint(G[real[i++]][real[j++]]);
  for ( ;real[j] != -1; i++, j++){
      mx_printstr(" + ");
      mx_printint(G[real[i]][real[j]]);
      print_equal = 1;
  }
  if (print_equal){
      mx_printstr(" = ");
      mx_printint(dist);
  }
  mx_printstr("\n"); 
}

void print_route(t_list * names, int * path, int last){
    /*Functiond of printing a paths.
    names - list of names of nodes.
    real - array of vertexes(indexes) vice versa.
    num - count of indexes in real array.
    */
    int j = 0;
    mx_printstr("Path: ");
    mx_printstr(find_by_i(names, path[0]));
    mx_printstr(" -> ");
    mx_printstr(find_by_i(names, path[last]));
    mx_printstr("\nRoute: ");
    for (; path[j+1] != -1; j++){
        mx_printstr(find_by_i(names, path[j]));    
        mx_printstr(" -> ");
    }
    mx_printstr(find_by_i(names, path[j]));
}



void print_results(int ** G, t_list ** pred_lists, t_list * names, int * distance, int startnode)
{
  /*Functiond of printing all paths in from startnode to other ones > him.
    G - 2d array of edges weights.
    pred_lists - array of indexes to previous node of specific node.
    names - list of names of nodes.
    distance - array of minimum distances from startnode to i node(distance[startnode] = 0).
    startnode - index of startnode.
  */
    int n = mx_list_size(names);
    int j = 0;
    t_list ** paths = generate_permutations(pred_lists, names, n, startnode);
    for (int i = 1; paths[i]; i++){
      if (i != startnode){
          mx_sort_list(paths[i], compare_routes);
          for (t_list * path = paths[i]; path; path = path->next){
            int * way = path->data;
            for (j = 0; way[j + 1] != -1; j++);
            if (way[j] > startnode){
              mx_printstr("========================================\n");
              print_route(names, way, j);
              mx_printstr("\n");
              print_distance(G, way, distance[i]);
              mx_printstr("========================================\n");
            }
          }
      }
    }
    for (int i = 0; i < n; i++){
      if (i != startnode){
        t_list * temp = paths[i];
        mx_clear_list(&temp, true);
      }
    }
    for (int p = 0; p < n; p++){
      mx_clear_list(&pred_lists[p], false); 
    }
    free(paths);
    free(pred_lists);
}


