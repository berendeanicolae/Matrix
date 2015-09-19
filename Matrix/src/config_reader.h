#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdint>
#define MAX_LINE_SIZE 256

typedef void(*handler) (char *key, char * value);

static char* lstrip(char *str) {
	while (*str && !isspace(*str))
		*str++ = 0;
	return str;
}

static char* rstrip(char *str) {
	char *p = str + strlen(str);

	while (p > str && isspace(*--p))
		*p = 0;
	return p;
}

static char* findChar(char *str, char chr) {
	while (*str && *str != chr)
		++str;
	return str;
}

uint32_t parse(FILE *stream, handler handler) {
	char *start, *end;
	char *line;
	uint32_t lineNo = 0;


	while (fgets(line, MAX_LINE_SIZE, stream)) {
		++lineNo;

		start = line;
		start = lstrip(rstrip(start));

		//ignore empty and commented lines
		if (!start || !*start || *start == '#' || *start == ';')
			continue;
		end = findChar(start, '=');
		if (!end || !*end)
			continue;
		*end = 0;
		start = lstrip(rstrip(start));
		end = lstrip(rstrip(end + 1));
		if (start && *start && end && *end)
			handler(start, end);
	}
}

uint32_t parse(const char *filePath, handler handler) {
	FILE *f = NULL;
	
	if (!fopen_s(&f, filePath, "r") || !f)
		return 0xffffffff;
	return parse(f, handler);
}

#endif //CONFIG_READER_H
