/*
 * =====================================================================================
 *
 *       Filename:  md2html.c
 *
 *    Description:  a C implementation of the Markdown to HTML system.
 *
 *        Version:  1.0
 *        Created:  08/15/2014 14:01:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jackie Kuo (http://jackiekuo.com), j.kuo2012@gmail.com
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>

char title[257];

void get_dest(char *file_dest){
	printf("Please input the directory of the target file:\n");
	scanf("%s", file_dest);
}

//get the filename of output file
void new_name(char *new, char *old){
	int dot, len = strlen(old);

	strcpy(new, old);
	
	for(dot = len-1; new[dot] != '.'; dot--);
	new[dot] = '\0';

	//get filename
	for(--dot; new[dot] != '/' && dot >= 0; dot--);
	strcpy(title, new + dot + 1);
	
	strcat(new, ".html");
}

void add_style(FILE *fp){
	FILE *css_fp;
	char ch, style_file[12] = "./style.css";

	fprintf(fp, "%s", "<style>\n");

	if((css_fp = fopen(style_file, "r")) == NULL){
		printf("error! can't open style file(%s)", style_file);
	}
	while((ch = fgetc(css_fp)) != EOF){
		fputc(ch, fp);;
	}
	fprintf(fp, "%s", "\n</style>\n");
}

void add_header(FILE *fp){
	char *header1 = "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">\n\n";
	char *header2 = "<title>";
	char *header3 = "</title>\n</head>\n<body>\n";

	fprintf(fp, "%s", header1);

	add_style(fp);
		
	fprintf(fp, "%s%s%s", header2, title, header3);
}

void add_footer(FILE *fp){
	char *footer = "\n</body>\n</html>\n";
	fprintf(fp, "%s", footer);
}

void convert(FILE *out_fp, FILE *in_fp){
	char ch;
	int isNewLine = 0, count;

	add_header(out_fp);
	fprintf(out_fp, "<p>");
	
	while((ch = fgetc(in_fp)) != EOF){
		if(ch == '\n'){
			if(isNewLine){
				continue;
			}
			else{
				fprintf(out_fp, "</p>\n");
			}
			isNewLine = 1;
		}
		else{
			if(isNewLine){
				isNewLine = 0;
				if(ch == '#'){
					count = 1;
					while((ch = fgetc(in_fp)) == '#'){
						++count;
					}
					fprintf(out_fp, "<h%d>%c", count, ch);
					while((ch = fgetc(in_fp)) != '\n'){
						fputc(ch, out_fp);
					}
					fprintf(out_fp, "</h%d>\n\n", count);
				}
				
				else{
					fprintf(out_fp, "<p>");
				}
			}
			fputc(ch, out_fp);
		}
	}

	add_footer(out_fp);
}

int main(){
	FILE *in_fp, *out_fp;
	char in_file[100], out_file[100];

	get_dest(in_file);
	new_name(out_file, in_file);

	if((in_fp = fopen(in_file, "r")) == NULL){
		printf("error! can't open file(%s)", in_file);
	}
	if((out_fp = fopen(out_file, "w")) == NULL){
		printf("error! can't create file(%s)", out_file);
	}

	convert(out_fp, in_fp);

	printf("\nDone!\n");
	fclose(in_fp);
	fclose(out_fp);

	return 0; 
}
