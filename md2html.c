/*
 * =====================================================================================
 *
 *       Filename:  md2html.c
 *
 *    Description:  a C implementation of the Markdown to HTML system.
 *
 *        Version:  0.5
 *        Created:  08/15/2014 14:01:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jackie Kuo (http://jackiekuo.com), j.kuo2012@gmail.com
 *
 * =====================================================================================
 */

#include "markdown.h"

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

int main(){
	char in_file[100], out_file[100];

	get_dest(in_file);
	new_name(out_file, in_file);

	if((in_fp = fopen(in_file, "r")) == NULL){
		ERROR_CODE = 1;
		printf("\nerror!\nERROR_CODE:%d\tcan't open input file(%s)", ERROR_CODE, in_file);
		return 1;
	}
	if((out_fp = fopen(out_file, "w")) == NULL){
		ERROR_CODE = 2;
		printf("\nerror!\nERROR_CODE:%d\tcan't create output file(%s)", ERROR_CODE, out_file);
		return 2;
	}

	convert();

	if( !ERROR_CODE ){
		printf("\nDone!\n");
	}
	fclose(in_fp);
	fclose(out_fp);

	return 0; 
}
