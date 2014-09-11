/*
 * =====================================================================================
 *
 *       Filename:  token.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/03/2014 00:46:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jackie Kuo (http://jackiekuo.com), j.kuo2012@gmail.com
 *
 * =====================================================================================
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <ctype.h>
#include "constant.h"
#include "code2html.h"

// ---------------- is --------------

int is_delimiter(const char ch) {
	int i;
	for (i = 0; i < DELIMITER_MAX; ++i) {
		if (ch == delimiter_ch[i]) {
			return (i+1);
		}
	}
	return 0;
}

int is_alpha_or_num(const char ch) {
	if (isalpha(ch) || (ch >='0' && ch <= '9')) {
		return 1;
	}
	return 0;
}

int is_identifier_character(const char ch) {
	if (isalpha(ch) || (ch >= '0' && ch <= '9') || ch =='_') {
		return 1;
	}
	return 0;
}

int is_special_operator(const char ch) {
	int i;
	for (i = 0; i < SPECIAL_OP_MAX; ++i) {
		if (ch == special_operator[i]) {
			return (i+1);
		}
	}
	return 0;
}

int is_basictype(const char *str) {
	int i;
	for (i = 0; i < BASICTYPE_MAX; ++i) {
		if (strcmp(str, basictype[i]) == 0) {
			return (i+1);
		}
	}
	return 0;
}

int is_main(const char *str) {
	if (strcmp(str, "main") == 0) {
		return 1;
	}
	return 0;
}

int is_bioperator(const char *code, const int i) {
	char biop[3] = {code[i], code[i+1], '\0'};
	int t;
	for (t = 0; t < BIOPERATOR_MAX; ++t) {
		if (strcmp(biop, bioperator[t]) == 0) {
			return (t+1);
		}
	}
	return 0;
}

int is_comment(const char *code, const int i, const int flag) {
	char bico[3] = {code[i], code[i+1], '\0'};
	switch (flag) {
		case COMMENT_ON:
			if (strcmp(bico, comment_sign[0]) == 0) {
				return 1;
			}
			else if (strcmp(bico, comment_sign[1]) == 0) {
				return 2;
			}
			return 0;
		case COMMENT_OFF:
			if (strcmp(bico, comment_sign[2]) == 0) {
				return 2;
			}
			return 0;
	}
	return 0;
}

int is_special_ch_for_html(const char ch) {
	int i;
	for (i = 0; i < SEPCIAL_CH_FOR_HTML_MAX; ++i) {
		if (ch == special_ch_for_html[i]) {
			return (i+1);
		}
	}
	return 0;
}

// ---------------- token --------------

int identifier_token(const char *str) {
    if (isalpha(str[0])) {
		int i;
		for (i = 0; i < KEYWORDS_MAX; ++i) {
			if (strcmp(str, keywords[i]) == 0) {
				return (i+30);
			}
		}
		return 1;
    }
    else {
		int i, count = 0;
		for (i = 0; i < (int)strlen(str); ++i) {
			if (isdigit(str[i])) {
				++count;
			}
		}
		if (count == (int)strlen(str)) {
			return 4; // number
		}
		else if (str[0] == '_' && isalpha(str[1])) {
			return 1; // identifier
		}
        else {
			return -4; // id undefined
		}
	}
	return 0;
}

int basictype_token(const char *str) {
	int i;
	for (i = 0; i < BASICTYPE_MAX; ++i) {
		if (strcmp(str, basictype[i]) == 0) {
			return (i+60);
		}
	}
	return 0;
}

int operator_token(const char *str) {
	int i;
	for (i = 0; i < OPERATOR_MAX; ++i) {
		if (strcmp(str, operators[i]) == 0) {
			return (i+70);
		}
	}
	return -5; // op undefined
}

int delimiter_token(const char *str) {
	int i;
	for (i = 0; i < DELIMITER_MAX; ++i) {
		if (strcmp(str, delimiter[i]) == 0) {
			return (i+6);
		}
	}
	return -6; // de undefined
}

#endif
