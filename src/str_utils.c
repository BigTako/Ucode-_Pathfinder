#include "../inc/header.h"

int mx_atoi(const char* str, int * err)
{
    int num = 0;
    int i = 0;
    int ten_pow;
    int num_len = 0;
    if (!str) return 0;
    for (int c = 0; !mx_isdigit(str[c]); c++)
    	if (mx_isspace(str[c])){
    		*err = 1;
    		return 0;
    	}
    	else if ( str[c] == '-' || str[c] == '+')
    		if ( mx_isdigit(str[c + 1])) i = c + 1;
    		else{
    			*err = 1;
    			 return 0;
    		    }
    	else{
    		*err = 1;
    		return 0;
    	}
    for (; mx_isdigit(str[num_len + i]); num_len++);
    if (!mx_isdigit(str[i + num_len + 1]) && str[i + num_len] != '\0'){
    	*err = 1;
    	return 0;}
    for (int q = i; q < i + num_len; q++) {
        ten_pow = 1;
	for (int j = 0; j < num_len + i - q - 1; j++) ten_pow *= 10;
	num += (str[q] - 48) * ten_pow; 
    }
    if (str[0] == '-') num = -num;
    return num;
}

void del_strarrarr(char *** a1, char ***a2, char *** a3, char *** a4)
{
	if (a1 && *a1) mx_del_strarr(a1);
	if (a2 && *a2) mx_del_strarr(a2);
	if (a3 && *a3) mx_del_strarr(a3);
	if (a4 && *a4) mx_del_strarr(a4);
}

int validate_string(char * str, char delim, int end){
	int del_count = 0;
	if (!mx_isalpha(str[0])) return 0;
	for (int i = 0; str[i] != end; i++){
		if (str[i] == delim) del_count++;
		if (!mx_isalpha(str[i]))
		{
			if (!mx_isalpha(str[i + 1])) return 0;
		}
	}
	if (del_count != 1) return 0;
	return 1;
}

int lines_differ(char ** b1, char * line2)
{
	char ** names_count = mx_strsplit(line2, ',');
	char **bnames = mx_strsplit(names_count[0], '-');
	if ((!mx_strcmp(b1[0], bnames[0]) && !mx_strcmp(b1[1], bnames[1])) ||
		(!mx_strcmp(b1[0], bnames[1]) && !mx_strcmp(b1[1], bnames[0])))
	{
		del_strarrarr(&names_count, &bnames, NULL, NULL);
		return 0;
	}else{
		del_strarrarr(&names_count, &bnames, NULL, NULL);
		return 1;
	}
}


