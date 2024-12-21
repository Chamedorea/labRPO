#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_operations.h"
#include "regex_operations.h"

#define MAX_LINE_LENGTH 1024

void process_file(const char *filename, const char *operation) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Error opening file");
	return;
    }
    char line[MAX_LINE_LENGTH];
    fseek(file, 0, SEEK_SET); // Сброс указателя на начало файла
    if (strstr(operation, "s/")) {
        // Замена текста
	 char temp_operation[MAX_LINE_LENGTH];
	    strncpy(temp_operation, operation, sizeof(temp_operation));
	       char *old_text = strtok(temp_operation + 2, "/");
	char *new_text = strtok(NULL, "/");
	if (new_text != NULL) {
	    while (fgets(line, sizeof(line), file)) {
	        // Замена текста в строке
	        replace_text(line, old_text, new_text);
	        //Записываем измененную строку обратно в файл
		fputs(line, file);
	    }
	}
    } else if (strncmp(operation, "/", 1) == 0 && strstr(operation, "/d") != NULL) {
        //Удаление строк по регулярному выражению
        size_t regex_len = strlen(operation) - 2;  //длина регулярного выражения
        char *regex_pattern = (char *)malloc(regex_len + 1);
	memcpy(regex_pattern, operation + 1, regex_len);
	regex_pattern[regex_len] = '\0'; //добавляем нуль-терминатор;
	while (fgets(line, sizeof(line), file)) {
       	    if (!match_regex(line, regex_pattern)) {
	        fputs(line, file);
	    }
	}
	free(regex_pattern);
    } else if (strstr(operation, "^/") != NULL) {
       char temp_prefix[MAX_LINE_LENGTH];
       strncpy(temp_prefix, operation + 2, sizeof(temp_prefix));
       while (fgets(line, sizeof(line), file)) {
           fprintf(file, "%s%s", temp_prefix, line);
       }
    } else if (strstr(operation, "/$") != NULL) {
        char temp_suffix[MAX_LINE_LENGTH];
	strncpy(temp_suffix, operation + 2, sizeof(temp_suffix));
	while (fgets(line, sizeof(line), file)) {
   	    fprintf(file, "%s%s", line, temp_suffix);
	}
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
       fprintf(stderr, "Usage: %s filename 'operation'\n", argv[0]);
       return EXIT_FAILURE;
    }
    process_file(argv[1], argv[2]);
    return EXIT_SUCCESS;
}

