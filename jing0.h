/*
 * =====================================================================================
 *
 *       Filename:  jing0.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/02/2014 20:59:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jackie Kuo (http://jackiekuo.com), j.kuo2012@gmail.com
 *
 * =====================================================================================
 */


#ifndef JING0_H
#define JING0_H

#include "code2html.h"

char title[257];
int ERROR_CODE = 0;

/*
 * ERROR_CODE
 *
 * 0 Everything is OK
 * 1 cannot open input file
 * 2 cannot create output file
 * 3 cannot find css file
 *
 */

void get_input(char *file_dest) {
	printf("Please input the directory of the target file:\n");
	scanf("%s", file_dest);
}

void get_color_scheme(int *style_type) {
	printf("Please input the color scheme of your code:\n");
	int i;
	for (i = 0; i < SYNTAX_MAX; i++) {
		printf("%d.%s\n", i, syntax[i]);
	}
	while (1) {
		scanf("%d", style_type);
		if (*style_type != 0 && *style_type != 1 && *style_type != 2) {
			printf("Style not found!\nPlease input one of the style numbers above.\n");
		}
		else {
			break;
		}
	}
}

int open_file(FILE **fp, const char *file_dir) {
	if ((*fp = fopen(file_dir, "r")) == NULL) {
		ERROR_CODE = 1;
		printf("\nerror!\nERROR_CODE:%d\tcan't open style file(%s)\n", ERROR_CODE, file_dir);
		return 1;
	}
	return 0;
}

int create_file(FILE **fp, const char *file_dir) {
	if ((*fp = fopen(file_dir, "w")) == NULL) {
		ERROR_CODE = 2;
		printf("\nerror!\nERROR_CODE:%d\tcan't open style file(%s)\n", ERROR_CODE, file_dir);
		return 1;
	}
	return 0;
}

//get the filename of output file
void name_output(char *new_name, const char *old_name, const char *format) {
	int dot, len = (int)strlen(old_name);

	strcpy(new_name, old_name);
	for (dot = len-1; new_name[dot] != '.'; dot--) {}
	new_name[dot] = '\0';
	//get filename
	for (--dot; new_name[dot] != '/' && dot >= 0; dot--) {}
	strcpy(title, new_name + dot + 1);
	strcat(new_name, format);
}

void close_files(FILE **fpa, FILE **fpb) {
	if (!ERROR_CODE) {
		printf("\nDone!\n");
	}
	fclose(*fpa);
	fclose(*fpb);
	*fpa = NULL;
	*fpb = NULL;
}

void add_style(FILE *out_fp, const char *css_file) {
	FILE *css_fp;
	char ch;

	fprintf(out_fp, "%s", "<style>\n");
	if ((css_fp = fopen(css_file, "rw+")) == NULL) {
		ERROR_CODE = 3;
		printf("\nerror!\nERROR_CODE:%d\tcan't open style file(%s)\n", ERROR_CODE, css_file);
	}
	else {
		while ((ch = fgetc(css_fp)) != EOF) {
			fputc(ch, out_fp);
		}
	}
	fprintf(out_fp, "%s", "\n</style>\n");
}

void add_head(FILE *out_fp, const char *css_file) {
	fprintf(out_fp, "%s", head1);
	add_style(out_fp, css_file);
	fprintf(out_fp, "%s%s%s", head2, title, head3);
}

void add_foot(FILE *out_fp) {
	fprintf(out_fp, "%s", foot);
}

#endif // JING0_H
