#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

/* This function get a char c and check if he is a letter.
* if he is a number the function will retun 'number'
* if he is a Big letter the function will return 'bigLetter'
* if he is a small letter or the char '_' the function will return 'smallLetter'
* if he is a '-' letter the function will return 'negetiveSign'
* if he is a '+' letter the function will return 'positiveSign'
* if he is a ' ' or '	' letter the function will return 'blankLetter'
* if he is a ',' letter the function will return 'step'
* if he is a '\n' letter the function will return 'newLine'
* if he is a '\0' letter the function will return 'eof'
* if he is a '.' letter the function will return 'dot'
* if he is a '$' letter the function will return 'registerSign'
* if he is a '"' letter the function will return 'quoteSign'
* else the function will return spSign*/
LetterType letterType(char c)
{
	if(c >= '0' && c <= '9') 
		return number;
	else if((c >= 'A' && c <= 'Z'))
		return bigLetter;
	else if ((c >= 'a' && c <= 'z') || (c == '_'))
		return smallLetter;
	else if(c == '-')
		return negativeSign;
	else if(c == '+')
		return positiveSign;
	else if(c == ' ' || c == '	')
		return blankLetter;
	else if(c == ',')
		return step;
	else if(c == '\n')
		return newLine;
	else if(c == '\0')
		return eof;
	else if(c == '.')
		return dot;
	else if(c == ':')
		return colon;
	else if(c == ';')
		return commentLine;
	else if(c == '$')
		return registerSign;
	else if(c == '"')
		return quoteSign;

	return spSign;
}

/*
* This function is getting a char array and return the first non blank spot.
* **str - array of chars that i want to scan.
* Return - if i get to EOF, the function will return -1, if i get to '\n' return -2.
*/
int skipBlankSpots(char ** str){
	int curr_spot = 0;

	while(letterType((*str)[curr_spot]) != eof || letterType((*str)[curr_spot]) != newLine || letterType((*str)[curr_spot]) != blankLetter ){
		curr_spot++;
	}

	if(letterType((*str)[curr_spot]) == eof){
		return -1;
	}
	else if(letterType((*str)[curr_spot]) == newLine){
		return -2;
	}

	return curr_spot;
}

/**/
char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    if(result)
    {
        strcpy(result, s1);
        strcat(result, s2);
        return result;
    }
    else
    {
        return NULL;
    }
}
