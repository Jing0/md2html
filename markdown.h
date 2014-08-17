/*
 * =====================================================================================
 *
 *       Filename:  markdown.h
 *
 *    Description:  
 *
 *        Version:  0.5
 *        Created:  08/17/2014 16:48:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jackie Kuo (http://jackiekuo.com), j.kuo2012@gmail.com
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>

#define CSS_PATH "./style.css"

FILE *in_fp, *out_fp;
char title[257];
int isHr = 0, ERROR_CODE = 0;

/*
 * ERROR_CODE
 *
 * 0 Everything is OK
 * 1 cannot open input file
 * 2 cannot create output file
 * 3 cannot find style.css
 *
 */

int onHeader(){
	int count = 1;
	char ch;

	while((ch = fgetc(in_fp) ) == '#'){
		++count;
	}

	if( count > 6 ){
		while(count--){
			fprintf(out_fp, "#");
		}
		fprintf(out_fp, "%c", ch);
		return 1;
	}

	fprintf(out_fp, "<h%d>%c", count, ch);

	ch = fgetc(in_fp);
	while(ch != '\n' && ch != EOF){
		fprintf(out_fp, "%c", ch);
		ch = fgetc(in_fp);
	}

	fprintf(out_fp, "</h%i>\n", count);
	return 0;
}

int onUrl(){
	int i = 0;
	char ch, name[1000], url[1000];

	while((ch = fgetc(in_fp)) != EOF){
		if( ch == ']' || ch == '\n' || i > 999 ){
			break;
		}
		name[i++] = ch;
	}
	name[i] = '\0';

	if( ch != ']' ){
		fprintf(out_fp, "[%s%c", name, ch);
		return 1;
	}

	while((ch = fgetc(in_fp)) == ' ');

	if( ch != '(' ){
		fprintf(out_fp, "[%s]%c", name, ch);
		return 2;
	}

	i = 0;
	while((ch = fgetc(in_fp)) != EOF){
		if( ch == ')' || ch == '\n' || i > 999 ){
			break;
		}
		url[i++] = ch;
	}
	url[i] = '\0';

	if( ch != ')' ){
		fprintf(out_fp, "[%s](%s%c", name, url, ch);
		return 3;
	}

	fprintf(out_fp, "<a href=\"%s\">%s</a>", url, name);
	return 0;
}

int onHr(){
	int count = 1;
	char ch;

	ch = fgetc(in_fp);
	while(ch != '\n' && ch == '-'){
		++count;
		ch = fgetc(in_fp);
	}

	if( count >= 3 ){
		fprintf(out_fp, "\n<hr/>\n");
		isHr = 1;
	}
	else{
		while(count--){
			fprintf(out_fp, "-");
		}
		fputc(ch, out_fp);
		return 1;
	}
	return 0;
}

int onImg(){
	int i = 0;
	char ch, name[1000], url[1000];

	ch = fgetc(in_fp);
	if( ch != '[' ){
		fprintf(out_fp, "!%c", ch);
		return 1;
	}

	while((ch = fgetc(in_fp)) != EOF){
		if( ch == ']' || ch == '\n' || i > 999 ){
			break;
		}
		name[i++] = ch;
	}

	name[i] = '\0';
	if( ch == '\n' || ch == EOF ){
		fprintf(out_fp, "![%s%c", name, ch);
		return 2;
	}
	
	while((ch = fgetc(in_fp)) == ' ');

	if( ch != '(' ){
		fprintf(out_fp, "![%s]%c", name, ch);
		return 3;
	}

	i = 0;
	while((ch = fgetc(in_fp)) != EOF){
		if( ch == ')' || ch == '\n' || i > 999 ){
			break;
		}
		url[i++] = ch;
	}
	url[i] = '\0';

	if( ch != ')' ){
		fprintf(out_fp, "![%s](%s%c", name, url, ch);
		return 4;
	}

	fprintf(out_fp, "<img src=\"%s\" alt=\"%s\">", url, name);
	return 0;
}

int onBold(){
	int i = 0;
	char ch, content[1000];

	while((ch = fgetc(in_fp)) == ' ');
	
	if( ch == '*' ){
		ch = fgetc(in_fp);
		if( ch == '*' ){
			fprintf(out_fp, "<strong></strong>");
			return 1;
		}
		else{
			fprintf(out_fp, "<i>*</i>");
			return 2;
		}
	}
	else if( ch == '\n' ){
		fputc(ch, out_fp);
		return 3;
	}

	content[i++] = ch;
	while((ch = fgetc(in_fp)) != EOF){
		if( ch == '*' || ch == '\n' || i > 999 ){
			break;
		}
		content[i++] = ch;
	}
	content[i] = '\0';

	if( ch != '*' ){
		fprintf(out_fp, "%s%c", content, ch);
		return 4;
	}
	
	ch = fgetc(in_fp);
	if( ch != '*' ){
		fprintf(out_fp, "<i>*%s</i>%c", content, ch);
		return 5;
	}

	fprintf(out_fp, "<strong>%s</strong>", content);
	return 0;
}

int onIorB(){
	// this function deal with italic or bold style
	// if what it deals with is bold style
	// it will return -1
	// if what it deals with is italic style
	// it will return -2

	int i = 0, state, isSpace;
	char ch, content[1000];
	
	ch = fgetc(in_fp);
	if( ch == '*' ){
		state = onBold();
		if( state != 0 ){
			return state;
		}
		else{
			return -1;
		}
	}
	else if( ch == ' ' ){
		isSpace = 1;
	}
	else{
		isSpace = 0;
		content[i++] = ch;
	}
	if( isSpace ){
		while((ch = fgetc(in_fp)) == ' ' );
		content[i++] = ch;
	}
	while((ch = fgetc(in_fp)) != EOF){
		if( ch == '*' || ch == '\n' || i> 999 ){
			break;
		}
		content[i++] = ch;
	}
	content[i] = '\0';

	if( ch != '*' ){
		fprintf(out_fp, "*%s%c", content, ch);
		return 10;
	}

	fprintf(out_fp, "<i>%s</i>", content);
	return -2;
}
int onList(){
	// There are still some problems with this function, obviously
	int i;
	char ch, item[1000];
	
	fprintf(out_fp, "<ul>\n");
	
	while((ch = fgetc(in_fp)) == ' ');
	
	i = 0;
	item[i++] = ch;
	while((ch = fgetc(in_fp)) != EOF){
		if( ch == '\n' || i > 999 ){
			break;
		}
		item[i++] = ch;
	}
	item[i] = '\0';

	fprintf(out_fp, "<li>%s</li>\n", item);
	fprintf(out_fp, "</ul>\n");
	return 0;
}

int onAster(){
	// if what it deal with is bold style
	// it will return -1
	// and if what it deal with is italic style
	// it will return -2
	// and if what it deal with is a list
	// it will return -3

	int state, i = 0;
	char ch, content[1000];

	ch = fgetc(in_fp);
	if( ch == ' ' ){
		state = onList();
		if( state == 0){
			return -3;
		}
		else{
			return state;
		}
	}
	else if( ch == '*' ){
		fputc('\n', out_fp);
		state = onBold();
		if( state == 0 ){
			return -1;
		}
		else{
			return state;
		}
	}
	else if( ch == '\n' ){
		fprintf(out_fp, "<p>*</p>\n");
	}
	content[i++] = ch;
	
	while((ch = fgetc(in_fp)) != EOF){
		if( ch == '*' || ch == '\n' || i> 999){
			break;
		}
		content[i++] = ch;
	}
	content[i] = '\0';

	if( ch != '*' ){
		if( ch == '\n' ){
			fprintf(out_fp, "<p>*%s</p>\n", content);
		}
		else{
			fprintf(out_fp, "<p>*%s%c", content, ch);
		}
		return 10;
	}

	fprintf(out_fp, "<p><i>%s</i>", content);
	return -2;

}

int onCode(){
	int i = 0, isSpace, isNewLine;
	char ch, content[1000];

	ch = fgetc(in_fp);
	if( ch == ' ' ){
		isSpace = 1;
	}
	else{
		isSpace = 0;
		content[i++] = ch;
	}
	if( isSpace ){
		while((ch = fgetc(in_fp)) == ' ' );
		content[i++] = ch;
	}

	while((ch = fgetc(in_fp)) != EOF){
		if( isNewLine && ch == '\n' ){
			break;
		}
		else if( !isNewLine && ch == '\n' ){
			isNewLine = 1;
		}
		else{
			isNewLine = 0;
			if( ch == '`' || i > 999 ){
				break;
			}
		}
		content[i++] = ch;
	}
	content[i] = '\0';

	if( ch != '`' ){
		fprintf(out_fp, "`%s%c", content, ch);
		return 1;
	}

	fprintf(out_fp, "<code>%s</code>", content);
	return 0;
}

/*
int onBlock(){
	// this function deals with code block
	// but it cannot work well
	int i = 0;
	char ch, content[1000];

	while((ch = fgetc(in_fp)) != EOF){
		if( ch == '\n' ){
			ch = fgetc(in_fp);
			if( ch != '\t' ){
				break;
			}
		}
		content[i++] = ch;
	}
	content[i] = '\0';

	fprintf(out_fp, "<pre>%s</pre>\n<p>%c", content, ch);
	return 0;
}
*/

/*
int onNewLine(char parameter){
	return 0;
}
*/

void add_style(){
	FILE *css_fp;
	char ch, style_file[12] = CSS_PATH;

	fprintf(out_fp, "%s", "<style>\n");

	css_fp = fopen(style_file, "rw+");
	if( css_fp == NULL ){
		ERROR_CODE = 3;
		printf("\nerror!\nERROR_CODE:%d\tcan't open style file(%s)\n", ERROR_CODE, style_file);
	}
	else{
		while((ch = fgetc(css_fp)) != EOF){
			fputc(ch, out_fp);
		}
	}

	fprintf(out_fp, "%s", "\n</style>\n");
}

void add_head(){
	char *head1 = "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">\n\n";
	char *head2 = "<title>";
	char *head3 = "</title>\n</head>\n\n<body>\n";

	fprintf(out_fp, "%s", head1);

	add_style();
		
	fprintf(out_fp, "%s%s%s", head2, title, head3);
}

void add_foot(){
	char *foot = "\n</body>\n</html>\n";
	fprintf(out_fp, "%s", foot);
}

void convert(){
	char ch;
	int isNewLine, isQuote, isCode;
	isNewLine = 1;
	isQuote = isCode = 0;

	add_head();
	
	while((ch = fgetc(in_fp)) != EOF){
		if( isNewLine && ( ch == '>' ||  ch == '#' || ch == '-' || ch == '*' )){
				if( ch == '>' ){
					if( isQuote == 0 ){
						fprintf(out_fp, "<blockquote>\n");
						isQuote = 1;
					}
				}
				else if( ch == '#'){
					onHeader();
					ch = '\n';
				}
				else if( ch == '-' ){
					onHr();
				}
				else if( ch == '*' ){
					int state = onAster();
					if( state == -3 ){
						ch ='\n';
					}
					// if ch is a aterisk in a new line,
					// it can be a list,
					// or italic style
					// or bold style
					// or just common text
				}
				else{
					fputc(ch, out_fp);
				}
			}
		else if( isNewLine && isQuote && ch != '>' ){
			fprintf(out_fp, "</blockquote>\n");
			isQuote = 0;
		}
		
		// This is characters cannot display
		/*
		else if( ch == '&' || ch == '<' ){
			if( ch == '&' ){
				fprintf(out_fp, "&amp;");
			}
			else{
				fprintf(out_fp, "&lt;");
			}
		}
		*/
		else if( ch == '[' ){
			if( isNewLine ){
				fprintf(out_fp, "<p>");
			}
            onUrl();
        }
		else if( ch == '!' ){
			if( isNewLine ){
				fprintf(out_fp, "<p>");
			}

			onImg();
		}
		else if( ch == '`' ){
			if( isNewLine ){
				fprintf(out_fp, "<p>");
			}

			onCode();
		}
		else if( ch == '*' ){
			if( isNewLine ){
				fprintf(out_fp, "<p>%c", ch);
			}

			onIorB();
			// if ch is a asterish and not in a new line,
			// it can be italic style
			// or it can be bold style
		}
        else if( ch != '\n'){
			if( isNewLine ){
				fprintf(out_fp, "<p>%c", ch);
			}
			else{
            	fputc(ch, out_fp);
			}
        }

        if( ch != '\n' ){
            isNewLine = 0;
        }
        else{
			if( !isHr && !isNewLine ){
				fprintf(out_fp, "</p>\n");
			}
			isNewLine = 1;
			isHr = 0;
        }

	}

	add_foot();
}
