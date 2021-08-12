#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"
#include "commandsHandler.h"

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
* This function get a file name and check that he is a asembly file and return the name without the file type.
* *currFileName - a file name.
* Return - the name without the file type, return NULL if the file type isn't asembly.
*/
char *getFileName(const char *currFileName){
	char *retVal = NULL, checkFileType[2];
	int i = 0,fileTypeIndex = 0,nameEndSpot = -1;
	Boolean isDone = false;

	while(letterType(currFileName[i]) != eof){
		if(letterType(currFileName[i]) == dot){
			isDone = true;
			nameEndSpot = i -1;
		}
		if(isDone == true && letterType(currFileName[i]) != dot){
			if(fileTypeIndex < 2){
				checkFileType[fileTypeIndex] = currFileName[i];
				fileTypeIndex++;
			}
			else{
				return NULL;
			}
		}
		i++;
	}
	if(strcmp(checkFileType,"as") == 0){
		retVal = (char *)malloc((nameEndSpot + 2) * sizeof(char));
		strncpy(retVal,&(currFileName[0]),(nameEndSpot + 1));
		retVal[nameEndSpot + 1] = '\0';
		return retVal;
	}
	return NULL;
}

/*
* This function gets 2 const strings and return the concatenate of them.
* s1 - the first String that suppose to be the start of the concate.
* s2 - the second String that suppose to be the end of the concate.
* Return - The concatenate of them, if there is a error the function will return NULL.
*/
char *concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    if(result){
        strcpy(result, s1);
        strcat(result, s2);
        return result;
    }
    return NULL;
}
