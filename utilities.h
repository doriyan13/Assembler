/* Define of const and functions -*/
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
char *getFileName(const char *currFileName);
char *concat(const char *s1, const char *s2);
