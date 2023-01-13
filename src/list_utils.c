#include "../inc/header.h"

void * find_by_i(t_list * list, int i){
	int j = 0;
	for (t_list*temp = list; temp; temp = temp->next){
		if (j++ == i) return temp->data;
	}
	return NULL;
}

int get_i_by_value(t_list * list, void * value){
	int i = 0;
	for (t_list * temp = list; temp; temp = temp->next, i++){
		if (!mx_strcmp(value, temp->data)) return i;
	}
	return -1;
}

int add_name(t_list ** names, char * name, int i_to){
	if (i_to < 0 || !*names) return 0;
	for (t_list * temp = *names; temp; temp = temp->next){
		char * name_i = temp->data;
		if (mx_strcmp(name_i, name) == 0) return 0;
	}
	mx_push_back(names, mx_strdup(name));
	return 1;
}

void mx_clear_list(t_list **list, bool free_content){
	t_list * temp = *list;
	t_list * copy = temp;
	if(!list) return;
	while (temp){
		copy = temp->next;
		if (free_content){
			free(temp->data);
		}
		free(temp);
		temp = copy;
	}
	*list = temp;
}


