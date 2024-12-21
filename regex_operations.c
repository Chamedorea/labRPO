#include <stdio.h>
#include <regex.h>

int match_regex(const char *line, const char *pattern) {
    regex_t regex;
    int reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return 0; // ошибка
    }
    reti = regexec(&regex, line, 0, NULL, 0);
    regfree(&regex);
    return reti == 0; // Вернуть 1 при совпадении, 0 в ином случае
}
					                      

