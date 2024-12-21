#include <stdio.h>
#include <string.h>

void replace_text(char *line, const char *old_text, const char *new_text) {
    char buffer[1024];
    char *pos;
    while ((pos = strstr(line, old_text)) != NULL) {
        strncpy(buffer, line, pos - line); // Копируем часть строки до старого текста
        buffer[pos - line] = '\0'; // Завершаем буфер
        sprintf(buffer + (pos - line), "%s%s", new_text, pos + strlen(old_text));
        strcpy(line, buffer); // Копируем измененную строку обратно
    }
}
