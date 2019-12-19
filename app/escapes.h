#ifndef ESCAPES_H
#define ESCAPES_H
//Source: https://www.rosettacode.org/wiki/URL_encoding#C

#include <ctype.h>
#include <stdio.h>

#define SIZE 256

static char rfc3986[SIZE] = {0};
static int init = 0;

static void escapes_init(){
    int i;
    for (i = 0; i < SIZE; i++) {
        rfc3986[i] = isalnum(i)||i == '~'||i == '-'||i == '.'||i == '_'
                    ? i : 0;
	}
}

void escapes_encode(const char *s, char *enc){
    if(!init){
        escapes_init();
        init = 1;
    }

	for (; *s; s++) {
		if (rfc3986[*s]) sprintf(enc, "%c", rfc3986[*s]);
		else        sprintf(enc, "%%%02X", *s);
		while (*++enc);
	}
}

#endif
