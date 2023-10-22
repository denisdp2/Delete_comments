#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define usi unsigned short int
#define SINGLE_QUOTE 39


FILE * open_files(FILE* names, char* file_name, char* type_of_open) {
	names = fopen(file_name, type_of_open);
	return(names);
}


int exit_failure(FILE* names) {
	if (names == NULL)
		return EXIT_FAILURE;
}


int search_count_of_files(FILE* names, char* count_of_files) {
	char* index = NULL;
	fgets(count_of_files, 34, names);
	index = strchr(count_of_files, '\n');
	count_of_files[index - count_of_files] = '\0';
	return(atoi(count_of_files));
}


void crop_name(char* name_of_file, FILE* names) {
	fgets(name_of_file, 34, names);
	for (usi i = 0; i < strlen(name_of_file); i++) {
		if (name_of_file[i] == '.') {
			name_of_file[i + 2] = '\0';
			break;

		}
	}
}


void refactoring_of_name_of_file(char * name_of_file) {
	for (usi i = 0; i < strlen(name_of_file); i++) {
		if (name_of_file[i] == '.') {
			name_of_file[i + 1] = 'w';
			name_of_file[i + 2] = 'c';
			name_of_file[i + 3] = '\0';
			break;
		}
	}
}


void flag_symbols(char symbol1, char symbol2, int flag_in_comment, 
	int flag_comment, int flag_transfer_comment, int* flag_continue, 
	int flag_false_symbol, FILE* file_c, FILE* file_wc) {
	if (symbol1 == '\\' && flag_in_comment == 0 && 
		flag_comment == 0 && flag_transfer_comment == 0 && flag_false_symbol == 0) {
		if (flag_comment == 0 && flag_in_comment == 0 && flag_transfer_comment == 0) {
			if (!feof(file_c))fputc(symbol1, file_wc);
			if (!feof(file_c))fputc(symbol2, file_wc);
		}
		*flag_continue = 1;
	}
}


void flag_in_one_str_1(int *flag_in_one_str, int flag_comment, int flag_in_comment, 
	int flag_transfer_comment, int flag_in_str, int *flag_continue, char symbol1, FILE* file_c, FILE* file_wc) {
	if (symbol1 == SINGLE_QUOTE && *flag_in_one_str == 0 && flag_in_str == 0 && 
		flag_comment == 0 && flag_in_comment == 0 && flag_transfer_comment == 0) {
		*flag_in_one_str = 1;
		if (!feof(file_c))fputc(symbol1, file_wc);
		if (!feof(file_c))fseek(file_c, -1, SEEK_CUR);
		*flag_continue = 1;
	}
}


void flag_in_one_str_0(int *flag_in_one_str, int flag_in_str, char symbol1) {
	if (symbol1 == SINGLE_QUOTE && *flag_in_one_str == 1 && flag_in_str == 0) {
		*flag_in_one_str = 0;
	}
}


void flag_in_str_0(int* flag_in_str, int flag_comment, int flag_in_comment, 
	int flag_transfer_comment, int flag_in_one_str, int *flag_continue, 
	char symbol1, FILE* file_c, FILE* file_wc) {
	if (symbol1 == '\"' && *flag_in_str == 1 && flag_in_one_str == 0) {
		*flag_in_str = 0;
		if (flag_comment == 0 && flag_in_comment == 0 && flag_transfer_comment == 0)
			if (!feof(file_c))fputc(symbol1, file_wc);
		if (!feof(file_c))fseek(file_c, -1, SEEK_CUR);
		*flag_continue = 1;
	}
}


void flag_in_str_1(int *flag_in_str, int flag_comment, int flag_in_comment,
	int flag_transfer_comment, int flag_in_one_str, char symbol1) {
	if (symbol1 == '\"' && *flag_in_str == 0 &&
		flag_comment == 0 && flag_in_comment == 0 &&
		flag_transfer_comment == 0 && flag_in_one_str == 0)
		*flag_in_str = 1;
}


void flag_in_comment_0(char symbol1, char symbol2, int flag_in_str, 
	int *flag_in_comment, int *flag_continue, int flag_in_one_str) {
	if (symbol1 == '*' && symbol2 == '/' && flag_in_str == 0 && flag_in_one_str == 0 && *flag_in_comment == 1) {
		*flag_in_comment = 0;
		*flag_continue = 1;
	}
}


void flag_in_comment_1(char symbol1, char symbol2, int flag_in_str, 
	int *flag_in_comment, int flag_in_one_str, int flag_comment, FILE* file_c) {
	if (symbol1 == '/' && symbol2 == '*' && *flag_in_comment == 0 
		&& flag_in_str == 0 && flag_in_one_str == 0 && flag_comment == 0) {
		*flag_in_comment = 1;
		fseek(file_c, 1, SEEK_CUR);
	}
}


void flag_comment_0(int *flag_comment, char symbol1, int *flag_continue, FILE* file_c) {
	if (*flag_comment == 1 && (symbol1 == '\n' || symbol1 == '\r')) {
		*flag_comment = 0;
		fseek(file_c, -2, SEEK_CUR);
		*flag_continue = 1;
	}
}


void flag_comment_1(char symbol1, char symbol2, int flag_in_str, 
	int flag_in_comment, int* flag_comment, int flag_in_one_str) {
	if (symbol1 == '/' && symbol2 == '/' && flag_in_str == 0 
		&& flag_in_comment == 0 && flag_in_one_str == 0)
		*flag_comment = 1;

}


void flag_transfer_comment_0(int* flag_transfer_comment, char symbol1, char symbol2, int* flag_continue, FILE* file_c) {
	if (*flag_transfer_comment == 1 && symbol1 != '\\' && (symbol2 == '\n' || symbol2 == '\r')) {
		*flag_transfer_comment = 0;
		fseek(file_c, -1, SEEK_CUR);
		*flag_continue = 1;
	}
	else if (*flag_transfer_comment == 1 && symbol1 == '\\' && (symbol2 == '\n' || symbol2 == '\r')) {
		fseek(file_c, 1, SEEK_CUR);
	}
}


void flag_transfer_comment_1(int* flag_comment, char symbol1, char symbol2, 
	int* flag_transfer_comment, int* flag_continue, FILE* file_c) {
	if (*flag_comment == 1 && symbol1 == '\\' && (symbol2 == '\n' || symbol2 == '\r')) {
		if (symbol2 == '\r')
			fseek(file_c, 1, SEEK_CUR);
		else
			fseek(file_c, 0, SEEK_CUR);
		*flag_transfer_comment = 1;
		*flag_comment = 0;
		*flag_continue = 1;
	}
}


void writing(int flag_comment, int flag_in_comment, int flag_transfer_comment, 
	char symbol1, FILE* file_c, FILE* file_wc) {
	if (flag_comment == 0 && flag_in_comment == 0 && flag_transfer_comment == 0)
		if (!feof(file_c))fputc(symbol1, file_wc);
}


void seek(FILE* file_c) {
	if (!feof(file_c))fseek(file_c, -1, SEEK_CUR);
}


void writing_final_symbol(char symbol1, char symbol2, int flag_comment, 
	int flag_in_comment, int flag_transfer_comment, FILE* file_wc) {
	if (symbol2 == -1 && symbol1 != -1 && flag_comment == 0 && flag_in_comment == 0 && flag_transfer_comment == 0)
		fputc(symbol1, file_wc);
}


void check_false_symbol(char symbol1, int *flag_false_symbol) {
	if (symbol1 != '\\')
		*flag_false_symbol = 0;
}


void check_new_line(char symbol1, char symbol2,	int *flag_false_symbol, 
	int* flag_in_str, int* flag_in_one_str, int *flag_transfer_str, 
	int* flag_transfer_false_symbol) {
	if (symbol1 == '\n') {
		*flag_false_symbol = 1;
		*flag_in_str = 0;
		*flag_in_one_str = 0;
		if (*flag_transfer_str == 1) {
			*flag_in_str = 1;
			*flag_transfer_str = 0;
		}
		if (*flag_transfer_false_symbol == 1) {
			*flag_false_symbol = 0;
			*flag_transfer_false_symbol = 0;
		}
	}
}


void check_transfer_str(char symbol1, char symbol2, int flag_comment, 
	int flag_in_comment, int flag_transfer_comment, int flag_in_str, 
	int* flag_transfer_str, int* flag_transfer_false_symbol) {
	if (((symbol1 == '\\' && (symbol2 == '\r' || symbol2 == '\n')) &&
		flag_comment == 0 && flag_in_comment == 0 && flag_transfer_comment == 0)) {
		if (flag_in_str == 1)
			*flag_transfer_str = 1;
		*flag_transfer_false_symbol = 1;
	}
}


void deleting_of_comments(FILE* file_c, FILE* file_wc) {
	int flag_in_one_str = 0, flag_in_str = 0, flag_transfer_comment = 0,
		flag_comment = 0, flag_in_comment = 0, flag_continue = 0, 
		flag_false_symbol = 1, flag_transfer_str = 0, flag_transfer_one_str = 0, 
		flag_transfer_false_symbol = 0;
	char symbol1 = 0, symbol2 = 0;
	while (!feof(file_c)) {
		symbol1 = fgetc(file_c);
		symbol2 = fgetc(file_c);

		check_false_symbol(symbol1, &flag_false_symbol);

		check_new_line(symbol1, symbol2, &flag_false_symbol,
			&flag_in_str, &flag_in_one_str, &flag_transfer_str, 
			&flag_transfer_false_symbol);

		check_transfer_str(symbol1, symbol2, flag_comment,
			flag_in_comment, flag_transfer_comment, flag_in_str,
			&flag_transfer_str, &flag_transfer_false_symbol);

		flag_symbols(symbol1, symbol2, flag_in_comment, flag_comment, 
			flag_transfer_comment, &flag_continue, flag_false_symbol, file_c, file_wc);

		flag_in_one_str_1(&flag_in_one_str, flag_comment, flag_in_comment, 
			flag_transfer_comment, flag_in_str, &flag_continue, symbol1, file_c, file_wc);
		if (flag_continue == 1) {
			flag_continue = 0;
			continue;}

		flag_in_one_str_0(&flag_in_one_str, flag_in_str, symbol1);

		flag_in_str_0(&flag_in_str, flag_comment, flag_in_comment,
			flag_transfer_comment, flag_in_one_str, &flag_continue, 
			symbol1, file_c, file_wc);
		if (flag_continue == 1) {
			flag_continue = 0;
			continue;}

		flag_in_str_1(&flag_in_str, flag_comment, flag_in_comment,
			flag_transfer_comment, flag_in_one_str,	symbol1);

		flag_in_comment_0(symbol1, symbol2, flag_in_str, &flag_in_comment, &flag_continue, flag_in_one_str);
		if (flag_continue == 1) {
			flag_continue = 0;
			continue;}
		
		flag_in_comment_1(symbol1, symbol2, flag_in_str, &flag_in_comment, flag_in_one_str, flag_comment, file_c);

		flag_comment_0(&flag_comment, symbol1, &flag_continue, file_c);
		if (flag_continue == 1) {
			flag_continue = 0;
			continue;}

		flag_comment_1(symbol1, symbol2, flag_in_str, flag_in_comment, &flag_comment, flag_in_one_str);

		flag_transfer_comment_0(&flag_transfer_comment, symbol1, symbol2, &flag_continue, file_c);
		if (flag_continue == 1) {
			flag_continue = 0;
			continue;}

		flag_transfer_comment_1(&flag_comment, symbol1, symbol2, &flag_transfer_comment, &flag_continue, file_c);

		writing(flag_comment, flag_in_comment, flag_transfer_comment, symbol1, file_c, file_wc);

		seek(file_c);
	}
	writing_final_symbol(symbol1, symbol2, flag_comment, flag_in_comment, flag_transfer_comment, file_wc);

	fclose(file_c);
	fclose(file_wc);
}


void main_programm() {
	char name_of_file[34] = { 0 }, count_of_files[34] = { 0 }, * index = NULL;
	int count_of_files_int = 0;
	FILE* names = NULL;
	names = open_files(names, "project.txt", "r");

	exit_failure(names);

	count_of_files_int = search_count_of_files(names, count_of_files);

	for (int i = 0; i < count_of_files_int; i++) {
		crop_name(name_of_file, names);
		FILE* file_c = NULL;
		file_c = open_files(file_c, name_of_file, "rb");

		if (file_c == NULL) {
			fclose(file_c);
			continue;
		}

		refactoring_of_name_of_file(name_of_file);
		FILE* file_wc = NULL;
		file_wc = open_files(file_wc, name_of_file, "wb");

		deleting_of_comments(file_c, file_wc);
	}
	fclose(names);
}


int main()
{
	main_programm();
	return 0;
}


