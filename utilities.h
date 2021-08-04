typedef enum LetterType
{
	number,
	smallLetter,
	bigLetter,
	negativeSign,
	positiveSign,
	blankLetter,
	step,
	newLine,
	eof,
	dot,
	colon,
	commentLine,
	registerSign,
	quoteSign,
	spSign
}LetterType;

LetterType letterType(char c);
int skipBlankSpots(char ** str);
char* concat(const char *s1, const char *s2);
