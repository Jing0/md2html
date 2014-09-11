/*
 * =====================================================================================
 *
 *       Filename:  code2html.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/03/2014 10:24:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jackie Kuo (http://jackiekuo.com), j.kuo2012@gmail.com
 *
 * =====================================================================================
 */

#ifndef CODE2HTML_H
#define CODE2HTML_H

#define CODE_CSS_PATH "./code.css"

#define SYNTAX_MAX 3
const char syntax[][20] = {
	"no highlight",
	"Jing0's style",
	"GitHub style"
};

const char common_style[][100] = {
	"",
	"style=\"\"",
	"style=\"\"",
};
const char char_style[][100] = {
	"",
	"style=\"color:#FF2D8F;\"",
	"style=\"color:#dd1144;\"",
};
const char string_style[][100] = {
	"",
	"style=\"color:#FF1E18;\"",
	"style=\"color:#dd1144;\"",
};
const char identifier_style[][100] = {
	"",
	"style=\"\"",
	"style=\"\"",
};
const char delimiter_style[][100] = {
	"",
	"style=\"color:#00B79D;\"",
	"style=\"\"",
};
const char keywords_style[][100] = {
	"",
	"style=\"color:#021F8C;font-weight:bold;\"",
	"style=\"font-weight:bold;\"",
};
const char operator_style[][100] = {
	"",
	"style=\"color:#FCA038;font-weight:bold;\"",
	"style=\"\"",
};
const char basictype_style[][100] = {
	"",
	"style=\"color:#2C92E0;font-weight:bold;\"",
	"style=\"color:#445588;font-weight:bold;\"",
};
const char main_style[][100] = {
	"",
	"style=\"color:#990000;font-weight:bold;\"",
	"style=\"color:#990000;font-weight:bold;\"",
};
const char number_style[][100] = {
	"",
	"style=\"color:#992C9A;\"",
	"style=\"color:#009999;\"",
};
const char comment_style[][100] = {
	"",
	"style=\"color:#999988;\"",
	"style=\"color:#999988;\"",
};
const char macro_style[][100] = {
	"",
	"style=\"color:#A9A9A9;font-weight:bold;\"",
	"style=\"color:#999999;font-weight:bold;\"",
};

#define SEPCIAL_CH_FOR_HTML_MAX 5
const char *special_ch_for_html =
	"\n\t <&";
const char special_ch_in_html[][30] = {
	"\n<br>\n",
	"&nbsp;&nbsp;&nbsp;&nbsp;",
	"&nbsp;",
	"&lt;",
	"&amp;"
};

const char *head1 =
	"<!DOCTYPE html>\n"
	"<html>\n"
	"<head>\n"
	"<meta charset=\"utf-8\">\n"
	"<meta name=\"viewport\" "
	"content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">\n\n";

const char *head2 =
	"<title>";

const char *head3 =
	"</title>\n"
	"</head>\n\n"
	"<body>\n";

const char *foot =
	"\n</body>\n"
	"</html>\n";

#endif // CODE2HTML_H
