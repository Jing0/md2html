/*
 * =====================================================================================
 *
 *       Filename:  constant.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/02/2014 16:41:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jackie Kuo (http://jackiekuo.com), j.kuo2012@gmail.com
 *
 * =====================================================================================
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

#define VERSION "0.66"

#define ID_FLAG        1
#define OPERATOR_FLAG  2
#define DELIMITER_FLAG 3
#define STRING_FLAG    4
#define SPACE_FLAG     5 
#define CHAR_FLAG      6
#define BASICTYPE_FLAG 7
#define MAIN_FLAG      8
#define COMMENTA_FLAG  9  // comment like this
#define COMMENTB_FLAG  10 /* comment like this */
#define MACRO_FLAG     11

#define COMMENT_ON     1
#define COMMENT_OFF    0

#define WRITE_AS_HTML  1
#define WRITE_AS_SS1   2
#define WRITE_AS_SS2   3

static const char output_format[][10] = {
	"",
	".html",
	".txt",
	".txt",
};

#define TYPE_MAX 11
static const char type[][11] = {
	"identifier",
	"char",
	"string",
	"number",
	"space",
	"delimiter",
	"keywords",
	"basictype",
	"operator",
	"comment",
	"macro",
};

#define BASICTYPE_MAX 6
static const char basictype[][10] = {
	// 6 in all, from 60 to 66
	"char",
	"double",
	"float",
	"int",
	"long",
	"short",
};

#define KEYWORDS_MAX 28
static const char keywords[][10] = {
	// 34-6 in all, from 30 to 57
    "auto",
    "break",
    "case",
    //"char",
    "const",
    "continue",
    "default",
    "do",
    //"double",
    "else",
    "enum",
    "extern",
    //"float",
    "for",
    "goto",
    "if",
    "inline",
    //"int",
    //"long",
    "register",
    "restrict",
    "return",
    //"short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while"
};

#define OPERATOR_MAX 56
static const char operators[][5] = {
	// 37-3 in all, from 70 to 106-3
	"=",
	"==",

	"+",
	"++",
	"+=",
	
	"-",
	"--",
	"-=",
	"->",
	
	"*",
	"*=",
	
	"/",
	"/=",
	
	"%",
	"%=",
	
	"!",
	"!=",
	
	"^",
	"^=",

	"&",
	"&&",
	"&=",

	"|",
	"||",
	"|=",
	
	"<",
	"<<",
	"<=",
	"<<=",
	
	">",
	">>",
	">=",
	">>=",
	
	//"'",
	".",
	"?",
	":",
};

#define SPECIAL_OP_MAX 12
static const char *special_operator =
	"+-*/%=!<>&|^";

#define BIOPERATOR_MAX 19
static const char bioperator[][5] = {
	"!=",
	"==",
	"^=",
	">>",
	">=",
	"<<",
	"<=",
	"++",
	"+=",
	"--",
	"-=",
	"->",
	"*=",
	"/=",
	"%=",
	"&&",
	"&=",
	"||",
	"|=",
};

#define DELIMITER_MAX 12
static const char *delimiter_ch =
	";,(){}[]\n\t\"\'";
	// 12 in all

static const char delimiter[][3] ={
	";",
	",",
	"(",
	")",
	"{",
	"}",
	"[",
	"]",
	"\n",
	"\t",
	"\"",
	"\'",
};

#define COMMENT_MAX 3
static const char comment_sign[][3] = {
	"//",
	"/*",
	"*/"
};

#endif /* CONSTANT_H_ */
