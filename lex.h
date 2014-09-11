/*
 * =====================================================================================
 *
 *       Filename:  lex.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/03/2014 10:23:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jackie Kuo (http://jackiekuo.com), j.kuo2012@gmail.com
 *
 * =====================================================================================
 */

#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include <string.h>

#include "code2html.h"
#include "jing0.h"
#include "token.h"

void deal_sepcial_ch_in_str(FILE *output, const char *str) {
	int t, len = (int)strlen(str);
	for (t = 0 ; t < len ; ++t) {
		if (is_special_ch_for_html(str[t])) {
			int ch_type = is_special_ch_for_html(str[t]);
			fprintf(output, "%s", special_ch_in_html[ch_type-1]);
		}
		else {
			fputc(str[t], output);
		}
	}
}

int get_char_or_string(char *str, const char *code, int i, const char ch) {
	// this function deal with string
	// and return the length of the string
	int t = 0, back_slash = 1;
	++i;
	while (1) {
		if (code[i] == ch) {
			while (code[i-back_slash] == '\\') {
				++back_slash;
			}
			--back_slash;
			if (back_slash % 2 == 0) {
				break;
			}
		}
		str[t++] = code[i++];
	}
	str[t] = '\0';
	return (t+1);
}

int write_file(FILE *output, const char *str,
		const int flag, const int write_type, const int style_type) {
	int id = 0;
	switch (flag) {
		case SPACE_FLAG:
			break;
		case DELIMITER_FLAG:
			id = delimiter_token(str);
			break;
		case ID_FLAG:
			id = identifier_token(str);
			break;
		case OPERATOR_FLAG:
			id = operator_token(str);
			break;
		case BASICTYPE_FLAG:
			id = basictype_token(str);
			break;
		case CHAR_FLAG:
			id = 2;
			break;
		case STRING_FLAG:
			id = 3;
			break;
		case COMMENTA_FLAG:
			id = -1;
			break;
		case COMMENTB_FLAG:
			id = -2;
			break;
		case MACRO_FLAG:
			id = -3;
			break;
		case MAIN_FLAG:
			id = 69;
			break;
		default:
			id = 0;
			break;
	}

	switch (write_type) {
		case WRITE_AS_HTML:
			if (flag == SPACE_FLAG) {
				fprintf(output, "%s", "&nbsp;");
			return 0;
			}
			else if (flag == MAIN_FLAG) {
				fprintf(output, "<span %s>%s</span>", main_style[style_type], str);
				return 0;
			}
			else if (flag == DELIMITER_FLAG) {
				if (strcmp(str, "\n") == 0) {
					fprintf(output, "\n<br>\n");
				}
				else if (strcmp(str, "\t") == 0) {
					fprintf(output, "&nbsp;&nbsp;&nbsp;&nbsp;");
				}
				else {
					fprintf(output, "<span %s>%s</span>", delimiter_style[style_type], str);
				}
				return 0;
			}
			else if (flag == COMMENTA_FLAG) {
				fprintf(output, "<span %s>//", comment_style[style_type]);
				deal_sepcial_ch_in_str(output, str);
				fprintf(output, "</span>");
				return 0;
			}
			else if (flag == COMMENTB_FLAG) {
				fprintf(output, "<span %s>/*", comment_style[style_type]);
				deal_sepcial_ch_in_str(output, str);
				fprintf(output, "*/</span>");	
				return 0;
			}
			else if (flag == MACRO_FLAG) {
				fprintf(output, "<span %s>#", macro_style[style_type]);
				deal_sepcial_ch_in_str(output, str);
				fprintf(output, "</span>");
				return 0;
			}

			if (id == 0) {
				fprintf(output, "<span %s>%s</span>", common_style[style_type], str);
			}
			else if (id == 1) {
				fprintf(output, "<span %s>%s</span>", identifier_style[style_type], str);
			}
			else if (id == 2) {
				fprintf(output, "<span %s>\'", char_style[style_type]);
				deal_sepcial_ch_in_str(output, str);
				fprintf(output, "\'</span>");
			}
			else if (id == 3) {
				// 2014-09-04
				// interesting bug!!!
				// founded when i scan this file
				// string like "<span %s>%s" may cause html syntax error!!
				// and this bug exists in string, char, comment
				
				fprintf(output, "<span %s>\"", string_style[style_type]);
				deal_sepcial_ch_in_str(output, str);
				fprintf(output, "\"</span>");
			}
			else if (id == 4) {
				fprintf(output, "<span %s>%s</span>", number_style[style_type], str);
			}
			else if (id == 5) {
				fprintf(output, "<span %s>%s</span>", common_style[style_type], str);
			}
			else if (id >= 6 && id < 30) {
				fprintf(output, "<span %s>%s</span>", delimiter_style[style_type], str);
			}
			else if (id >= 30 && id < 60) {
				fprintf(output, "<span %s>%s</span>", keywords_style[style_type], str);
			}
			else if (id >= 60 && id < 70) {
				fprintf(output, "<span %s>%s</span>", basictype_style[style_type], str);
			}
			else if (id >= 70) {
				fprintf(output, "<span %s>%s</span>", operator_style[style_type], str);
			}
			else if (id == -4) {
				fprintf(output, "%s undefined(-4: id)\n", str);
			}
			else if (id == -5) {
				fprintf(output, "%s undefined(-5: op)\n", str);
			}
			else if (id == -6) {
				fprintf(output, "%s undefined(-6: de)\n", str);
			}
			else {
				printf("Unknown Error!\n");
				return -1;
			}
			break;
		case WRITE_AS_SS1:
			if (flag == SPACE_FLAG) {
				fprintf(output, "(%s, %s)\n", type[4], str);
				return 0;
			}
			else if (flag == MAIN_FLAG) {
				fprintf(output, "(%s, %s)\n", type[6], str);
				return 0;
			}
			else if (flag == DELIMITER_FLAG) {
				if (strcmp(str, "\n" ) == 0 || strcmp(str, "\t") == 0) {
					;
				}
				else {
					fprintf(output, "(%s, %s)\n", type[5], str);
				}
				return 0;
			}
			else if (flag == COMMENTA_FLAG) {
				fprintf(output, "(%s, %s)\n", type[9], type[9]);
				return 0;
			}
			else if (flag == COMMENTB_FLAG) {
				fprintf(output, "(%s, %s)\n", type[9], type[9]);
				return 0;
			}
			else if (flag == MACRO_FLAG) {
				fprintf(output, "(%s, %s)\n", type[10], str);
				return 0;
			}

			if (id == 0 || id == 1) {
				fprintf(output, "(%s, %s)\n", type[0], str);
			}
			else if (id >= 2 && id < 6) {
				fprintf(output, "(%s, %s)\n", type[id-1], str);
			}
			else if (id >= 6 && id < 30) {
				fprintf(output, "(%s, %s)\n", type[5], str);
			}
			else if (id >= 30 && id < 60) {
				fprintf(output, "(%s, %s)\n", type[6], str);
			}
			else if (id >= 60 && id < 70) {
				fprintf(output, "(%s, %s)\n", type[7], str);
			}
			else if (id >= 70) {
				fprintf(output, "(%s, %s)\n", type[8], str);
			}
			else {
				fprintf(output, "%s undefined\n", str);
			}
			break;
		case WRITE_AS_SS2:
			if (flag == SPACE_FLAG) {
				fprintf(output, "(%d, %s)\n", 5, str);
				return 0;
			}
			else if (flag == MAIN_FLAG) {
				fprintf(output, "(%d, %s)\n", 69, str);
				return 0;
			}
			else if (flag == DELIMITER_FLAG) {
				if (strcmp(str, "\n") != 0 && strcmp(str, "\t") != 0) {
					fprintf(output, "(%d, %s)\n", id, str);
				}
				return 0;
			}
			else if (flag == COMMENTA_FLAG) {
				fprintf(output, "(%d, %s)\n", -1, "comment");
				return 0;
			}
			else if (flag == COMMENTB_FLAG) {
				fprintf(output, "(%d, %s)\n", -2, "comments");
				return 0;
			}
			else if (flag == MACRO_FLAG) {
				fprintf(output, "(%d, #%s)\n", -3, str);
				return 0;
			}
	
			if (id >= 0) {
				fprintf(output, "(%d, %s)\n", id, str);
				return 0;
			}
			else {
				printf("Unknown Error!\n");
				return -1;
			}
			break;

		default:
			printf("%d :Unknown Write_Type!\n", write_type);
			break;
	}
	return 0;
}

void code_token(FILE *out, const char *code,
		const int write_type, const int style_type) {
	char comment_str[1000], string_str[100], macro_str[100];
	char identifier_str[10], operator_str[3], char_str[3], delimiter_str[2];
	int i, j, on;

	i = j = on = 0;
	while (code[i] != '\0') {
		if (is_identifier_character(code[i])) {
			identifier_str[j++] = code[i++];
			identifier_str[j] = '\0';
			on = 1;
		}
		else {
            if (strlen(identifier_str) && on) {
				if (is_main(identifier_str)) {
					write_file(out, identifier_str, MAIN_FLAG, write_type, style_type);
				}
				else if (is_basictype(identifier_str)) {
					write_file(out, identifier_str, BASICTYPE_FLAG, write_type, style_type);
				}
				else {
					write_file(out, identifier_str, ID_FLAG, write_type, style_type);
				}
			}
			j = 0;
            identifier_str[j] = '\0';

            if (!is_alpha_or_num(code[i])) {
				// deal with space
				if (code[i] == ' ') {
					write_file(out, " ", SPACE_FLAG, write_type, style_type);
				}
				// deal with macro
				else if (code[i] == '#') {
					int t = 0;
					++i;
					while (code[i] != '\n') {
						macro_str[t++] = code[i++];
					}
					macro_str[t] = '\0';
					write_file(out, macro_str, MACRO_FLAG, write_type, style_type);
					--i;
				}

				// deal with delimiter
				else if (is_delimiter(code[i])) {
					int delimiter_type;
					delimiter_type = is_delimiter(code[i]);
					
					if (code[i] == '\"') {
						// most insteresting bug!! ever!!
						// \"
						// \" \\
						// ....
						i += get_char_or_string(string_str, code, i, '\"');

						write_file(out, string_str, STRING_FLAG, write_type, style_type);
					}
					else if (code[i] == '\'') {
						i += get_char_or_string(char_str, code, i, '\'');

						write_file(out, char_str, CHAR_FLAG, write_type, style_type);
					}
					else if (delimiter_type < 11) {
						strcpy(delimiter_str, delimiter[delimiter_type-1]);
						write_file(out, delimiter_str, DELIMITER_FLAG, write_type, style_type);
					}
					else {
						printf("ERROR!\n");
					}
				}

				// deal with comment
				else if (is_comment(code, i, COMMENT_ON)) {
					int t = 0, comment_type;

					comment_type = is_comment(code, i, COMMENT_ON);

					i += 2;
					
					if (comment_type == 1) {
						while (code[i] != '\n') {
							comment_str[t++] = code[i++];
						}
						comment_str[t] = '\0';
						write_file(out, comment_str, COMMENTA_FLAG, write_type, style_type);
						--i;
					}
					else if (comment_type == 2) {
						while (1) {
							if (is_comment(code, i, COMMENT_OFF)) {
								break;
							}
							comment_str[t++] = code[i++];
						}
						comment_str[t] = '\0';
						write_file(out, comment_str, COMMENTB_FLAG, write_type, style_type);
						++i;
					}
				}
				// deal with common operator
				else if (!is_special_operator(code[i])) {
					operator_str[0] = code[i];
					operator_str[1] = '\0';
					write_file(out, operator_str, OPERATOR_FLAG, write_type, style_type);
				}
				// deal with bioperator, such as "*=","%=","++","->"
				// bioperator is a name I created ^_^
				else if (is_bioperator(code, i)) {
					operator_str[0] = code[i];
					operator_str[1] = code[i+1];
					operator_str[2] = '\0';
					write_file(out, operator_str, OPERATOR_FLAG, write_type, style_type);
					++i;
				}
				else {
					operator_str[0] = code[i];
					operator_str[1] = '\0';
					write_file(out, operator_str, OPERATOR_FLAG, write_type, style_type);
				}
				++i;
			}
		}
	}
}

#endif // LEX_H
