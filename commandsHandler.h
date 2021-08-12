/*Define of enum and structs -*/
typedef enum Boolean
{
	false,
	true
}Boolean;

typedef enum CommandType
{
	R,
	I,
	J,
	notCommand
}CommandType;

typedef enum CommandName
{
	Add,
	Sub,
	And,
	Or,
	Nor,
	Move,
	Mvhi,
	Mvlo,
	Addi,
	Subi,
	Andi,
	Ori,
	Nori,
	Bne,
	Beq,
	Blt,
	Bgt,
	Lb,
	Sb,
	Lw,
	Sw,
	Lh,
	Sh,
	Jmp,
	La,
	Call,
	Stop,
	None
}CommandName;

typedef enum doStatement
{
	Dh,
	Dw,
	Db,
	Asciz,
	Entry,
	Extern,
	NotStatement
}doStatement;

typedef enum Attributes
{
	code,
	data,
	entry,
	external,
	emptyAtt
}Attributes;

typedef enum AddressType
{
	ICType,
	DCType
}AddressType;

typedef enum DataType
{
	OneByte,
	TwoByte,
	FourByte
}DataType;

typedef struct Command{
	CommandName cmdName;
	CommandType cmdType;
	signed int funct;
	signed int opCode;
} Command;

typedef struct Label{
	char *name;
	long int value;
	int attributes[4];
	struct Label *next;
} Label;

/* The Struct that will hold the finVals of each line of the file before transforming to hex - */
typedef struct BinaryLine{	
	long signed int address;
	long signed int binary;
	char * secondScan;
	Boolean isDone;
	AddressType addressType;
	DataType dataType;
	CommandType cmdType;
	int line;
	struct BinaryLine *next;
} BinaryLine;

/* Define of const and functions -*/

#define lineSize 81

/*The number of line in the file i'm in, for each file i reset the size of line*/
extern int lineNumber;

CommandName CmdType(char *val);
CommandName rCmdType(char *val);
CommandName iCmdType(char *val);
CommandName jCmdType(char *val);
doStatement doStatementType(char *val);
void printLabelList(Label **labelList);
Label *getLabelFromList(char *currString,Label **labelList);
void freeLabelList(Label **labelList);
void initCommandsList(Command ** arr);
char getNextChar(FILE *file);
void setNextChar(char ch);
void connectNewBinaryLine(BinaryLine **binLineList,BinaryLine **currBinLine);
void printBinaryLineList(BinaryLine **binLineList);
void freeBinaryList(BinaryLine **binLineList);
char *getLine(FILE *file);
void labelHandle(char *line, Label **labelList, Attributes currAttributes);
int registerHandler(char * line, short signed int *regArr,short int amountOfRegisters,int i);
int registerHandlerArrSpot(char *line, short signed int *regArr,int i,int spot);
int immedHandler(char * line, int **immed , int i);
int numHandlerBySize(char * line, long signed int **currNum,int size , int i);
char *charsHandler(char * line, int i);
char *getLabel(char * line, int i);
void doStatementHandler(char * line,doStatement currDoState, BinaryLine **binLineList, Label **labelList);
void RcmdHandler(char * line,Command * cmd,BinaryLine **binLineList);
void IcmdHandler(char * line,Command * cmd,BinaryLine **binLineList);
void JcmdHandler(char * line,Command * cmd,BinaryLine **binLineList);
void firstScan(FILE *file, Command ** arrCmd, Label **labelList, BinaryLine **binLineList);
void secondScan( Label **labelList, BinaryLine **binLineList);
