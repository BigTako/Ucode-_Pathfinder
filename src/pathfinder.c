#include "../inc/header.h"

static void permutate(t_list ** paths, t_list ** lists, t_list * names, int * buf, int index, const int cur, int start){
  if (cur == start){
    buf[index++] = start;
    int i = 0;
    int j = 0;
    int * arr = malloc(index*sizeof(int));
    for (i = index - 2; i >= 0; i--)
    { 
      arr[j++] = buf[i];
    }
    mx_push_back(&paths[buf[1]], arr);
  }
  else{
    for (t_list * temp = lists[cur]; temp; temp = temp->next)
    {
      buf[index++] = *(int*)temp->data;
      permutate(paths, lists, names, buf, index, *(int*)temp->data, start);
      index--;
    }
  }
}

t_list ** generate_permutations(t_list ** lists, t_list * names, int len, int startnode)
{
  int nums[200];
  t_list ** ways = malloc((len+1) * sizeof(t_list*));
  for (int i = 0; i < len; i++){
    ways[i] = mx_create_node(malloc(1));
  }
  ways[len] = NULL;
  for (int i = 0; i < len; i++){
    if (i != startnode){
      nums[0] = -1;
      nums[1] = i;
      permutate(ways, lists, names, nums, 2, i, startnode);
      free(ways[i]->data);
      mx_pop_front(&ways[i]);
    }
  }
  free(ways[startnode]->data);
  free(ways[startnode]);
  return ways;
}


void dijkstra(int ** G, t_list * names, int n, int startnode)
{
  /*Functiond of searching all shortest paths from startnode to others.
    G - 2d array of edges weights.
    names - list of names of nodes.
    n - row and cols in G and count of values in names.
    startnode - index of startnode.
  */
  int cost[n][n], distance[n];
  int arr_for_nums[200];
  int count_nums = 0;
  t_list ** pred_lists = malloc(n*sizeof(t_list *));
  int visited[n], count, mindistance, nextnode, i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (G[i][j] == 0)
        cost[i][j] = INFINITY;
      else
        cost[i][j] = G[i][j];
  for (i = 0; i < n; i++)
  {
    distance[i] = cost[startnode][i];
    int t = startnode;
    pred_lists[i] = mx_create_node((void *)&t);
    visited[i] = 0;
  }
  distance[startnode] = 0;
  visited[startnode] = 1;
  count = 1;
  while (count < n - 1)
  {
    mindistance = INFINITY;
    for(i=0;i<n;i++){
      if(distance[i] < mindistance&&!visited[i])
      {
          mindistance=distance[i];
          nextnode=i;
      }
    }
    visited[nextnode]=1;
    for(i=0;i<n;i++)
    {
      if(!visited[i])
      {
        if(mindistance + cost[nextnode][i] < distance[i] && 
          mindistance + cost[nextnode][i] > 0)
        {
            arr_for_nums[count_nums] = nextnode;
            distance[i]=mindistance+cost[nextnode][i];
            mx_clear_list(&pred_lists[i], false);
            pred_lists[i] = mx_create_node((void *)(&arr_for_nums[count_nums++]));
        }
        else if (mindistance + cost[nextnode][i] == distance[i] && 
                mindistance + cost[nextnode][i] > 0)
        {
          arr_for_nums[count_nums] = nextnode;
          mx_push_front(&pred_lists[i], (void *)(&arr_for_nums[count_nums++]));
        } 
      } 
    }
    count++; 
  }
  print_results(G, pred_lists, names, distance, startnode);
}


