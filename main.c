/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  0.63
 *        Created:  08/15/2014 14:01:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jackie Kuo (http://jackiekuo.com), j.kuo2012@gmail.com
 *
 * =====================================================================================
 */

#include "md2html.h"

int main(){
	char input[100], output[100];

	// get the file address of input file
	get_input( input );
	// name the output file
	name_output( output, input, ".html" );

	open_file( input );
	create_file( output );
	
	convert();

	close();

	return 0; 
}
