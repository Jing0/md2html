/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
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

#include "md2html.h" 
int main() {
	FILE *in_fp, *out_fp;
	char input[100], output[100];
	int code_color_scheme;
	// get the file address of input file
	get_input(input);
	get_color_scheme(&code_color_scheme);
	// get the name of the output file
	// which is exactly the same as input file but format
	name_output(output, input, ".html");

	open_file(&in_fp, input);
	create_file(&out_fp, output);
	
	mdparser(out_fp, in_fp, code_color_scheme);

	close_files(&in_fp, &out_fp);
	return 0;
}
