/*
 * =====================================================================================
 *
 *       Filename:  md2html.c
 *
 *    Description:  a C implementation of the Markdown to HTML system.
 *
 *        Version:  0.6
 *        Created:  08/15/2014 14:01:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jackie Kuo (http://jackiekuo.com), j.kuo2012@gmail.com
 *
 * =====================================================================================
 */

#include "markdown.h"

void get_input(char *file_dest){
	printf("Please input the directory of the target file:\n");
	scanf("%s", file_dest);
}

//get the filename of output file
void name_output(char *new, char *old, const char *format){
	int dot, len = strlen(old);

	strcpy(new, old);
	
	for(dot = len-1; new[dot] != '.'; dot--);
	new[dot] = '\0';

	//get filename
	for(--dot; new[dot] != '/' && dot >= 0; dot--);
	strcpy(title, new + dot + 1);
	
	strcat(new, format);
}

int open_file(char *file){
	if((in_fp = fopen(file, "r")) == NULL){
		ERROR_CODE = 1;
		printf("\nerror!\nERROR_CODE:%d\tcan't open input file(%s)", ERROR_CODE, file);
		return 1;
	}
	return 0;
}

int create_file(char *file){
	if((out_fp = fopen(file, "w")) == NULL){
		ERROR_CODE = 2;
		printf("\nerror!\nERROR_CODE:%d\tcan't create output file(%s)", ERROR_CODE, file);
		return 1;
	}
	return 0;
}

int main(){
	char input[100], output[100];

	// get the file address of input file
	get_input(input);
	// name the output file
	name_output(output, input, ".html");

	open_file(input);
	create_file(output);
	
	convert();

	if( !ERROR_CODE ){
		printf("\nDone!\n");
	}

	fclose(in_fp);
	fclose(out_fp);

	return 0; 
}
