#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "commandsHandler.h"
#include "binaryHandler.h"
#include "utilities.h"

char buffer[100];
static int bufferIndex = -1;
long int IC = 100, DC = 0; /*address of the memory*/

/* Boolean flag to represent if there is a error in currentLine: */
Boolean lineError = false, isFileVaild = true;

/*
* This function is getting a string and check if he is a type of command and return the type.
* *val - array of chars that suppose to be a command.
* Return - the type of command,if it doesn't it will return None.
*/
CommandName CmdType(char *val)
{
	#if DEBUG
	int i, length = strlen(val);
	printf("\n");
	printf("The Command is: ");
	
	for(i=0;i<length;i++){
		printf("%c",val[i]);
	}
	printf("\n");
	#endif

	if(strcmp(val,"add") == 0)
		return Add;
	else if(strcmp(val,"sub") == 0)
		return Sub;
	else if(strcmp(val,"and") == 0)
		return And;
	else if(strcmp(val,"or") == 0)
		return Or;
	else if(strcmp(val,"nor") == 0)
		return Nor;
	else if(strcmp(val,"move") == 0)
		return Move;
	else if(strcmp(val,"mvhi") == 0)
		return Mvhi;
	else if(strcmp(val,"mvlo") == 0)
		return Mvlo;
	else if(strcmp(val,"addi") == 0)
		return Addi;
	else if(strcmp(val,"subi") == 0)
		return Subi;
	else if(strcmp(val,"andi") == 0)
		return Andi;
	else if(strcmp(val,"ori") == 0)
		return Ori;
	else if(strcmp(val,"nori") == 0)
		return Nori;
	else if(strcmp(val,"bne") == 0)
		return Bne;
	else if(strcmp(val,"beq") == 0)
		return Beq;
	else if(strcmp(val,"blt") == 0)
		return Blt;
	else if(strcmp(val,"bgt") == 0)
		return Bgt;
	else if(strcmp(val,"lb") == 0)
		return Lb;
	else if(strcmp(val,"sb") == 0)
		return Sb;
	else if(strcmp(val,"lw") == 0)
		return Lw;
	else if(strcmp(val,"sw") == 0)
		return Sw;
	else if(strcmp(val,"lh") == 0)
		return Lh;
	else if(strcmp(val,"sh") == 0)
		return Sh;
	else if(strcmp(val,"jmp") == 0)
		return Jmp;
	else if(strcmp(val,"la") == 0)
		return La;
	else if(strcmp(val,"call") == 0)
		return Call;
	else if(strcmp(val,"stop") == 0)
		return Stop;
	return None;
}
/*
* This function is getting a string and check if he is a type of R command and return the type.
* *val - array of chars that suppose to be a command.
* Return - the type of command,if it doesn't it will return None.
*/
CommandName rCmdType(char *val)
{
	#if DEBUG
	int i, length = strlen(val);
	printf("\n");
	printf("The Command is: ");
	
	for(i=0;i<length;i++){
		printf("%c",val[i]);
	}
	printf("\n");
	#endif

	if(strcmp(val,"add") == 0)
		return Add;
	else if(strcmp(val,"sub") == 0)
		return Sub;
	else if(strcmp(val,"and") == 0)
		return And;
	else if(strcmp(val,"or") == 0)
		return Or;
	else if(strcmp(val,"nor") == 0)
		return Nor;
	else if(strcmp(val,"move") == 0)
		return Move;
	else if(strcmp(val,"mvhi") == 0)
		return Mvhi;
	else if(strcmp(val,"mvlo") == 0)
		return Mvlo;
	return None;
}

/*
* This function is getting a string and check if he is a type of I command and return the type.
* *val - array of chars that suppose to be a command.
* Return - the type of command,if it doesn't it will return None.
*/
CommandName iCmdType(char *val)
{
	#if DEBUG
	int i, length = strlen(val);
	printf("\n");
	printf("The Command is: ");
	
	for(i=0;i<length;i++){
		printf("%c",val[i]);
	}
	printf("\n");
	#endif

	if(strcmp(val,"addi") == 0)
		return Addi;
	else if(strcmp(val,"subi") == 0)
		return Subi;
	else if(strcmp(val,"andi") == 0)
		return Andi;
	else if(strcmp(val,"ori") == 0)
		return Ori;
	else if(strcmp(val,"nori") == 0)
		return Nori;
	else if(strcmp(val,"bne") == 0)
		return Bne;
	else if(strcmp(val,"beq") == 0)
		return Beq;
	else if(strcmp(val,"blt") == 0)
		return Blt;
	else if(strcmp(val,"bgt") == 0)
		return Bgt;
	else if(strcmp(val,"lb") == 0)
		return Lb;
	else if(strcmp(val,"sb") == 0)
		return Sb;
	else if(strcmp(val,"lw") == 0)
		return Lw;
	else if(strcmp(val,"sw") == 0)
		return Sw;
	else if(strcmp(val,"lh") == 0)
		return Lh;
	else if(strcmp(val,"sh") == 0)
		return Sh;
	return None;
}

/*
* This function is getting a string and check if he is a type of J command and return the type.
* *val - array of chars that suppose to be a command.
* Return - the type of command,if it doesn't it will return None.
*/
CommandName jCmdType(char *val)
{
	#if DEBUG
	int i, length = strlen(val);
	printf("\n");
	printf("The Command is: ");
	
	for(i=0;i<length;i++){
		printf("%c",val[i]);
	}
	printf("\n");
	#endif

	if(strcmp(val,"jmp") == 0)
		return Jmp;
	else if(strcmp(val,"la") == 0)
		return La;
	else if(strcmp(val,"call") == 0)
		return Call;
	else if(strcmp(val,"stop") == 0)
		return Stop;
	return None;
}

/*
* This function is getting a string and check if he is a type of do statement and return the type.
* *val - array of chars that suppose to be a doStatement.
* Return - the type of doStatement,if it doesn't it will return NotStatement.
*/
doStatement doStatementType(char *val)
{
	#if DEBUG
	int i, length = strlen(val);
	printf("\n");
	printf("The doStatement is: ");
	
	for(i=0;i<length;i++){
		printf("%c",val[i]);
	}
	printf("\n");
	#endif

	if(strcmp(val,".dh") == 0)
		return Dh;
	else if(strcmp(val,".dw") == 0)
		return Dw;
	else if(strcmp(val,".db") == 0)
		return Db;
	else if(strcmp(val,".asciz") == 0)
		return Asciz;
	else if(strcmp(val,".entry") == 0)
		return Entry;
	else if(strcmp(val,".extern") == 0)
		return Extern;
	return NotStatement;
}

/*
* This function is getting a string and check if he is a type of Attributes and return the type.
* *val - array of chars that suppose to be a doStatement.
* Return - the type of Attributes,if it doesn't it will return emptyAtt.
*/
Attributes attributesType(char *val)
{
	#if DEBUG
	int i, length = strlen(val);
	printf("\n");
	printf("The doStatement is: ");
	
	for(i=0;i<length;i++){
		printf("%c",val[i]);
	}
	printf("\n");
	#endif

	if((strcmp(val,".dh") == 0) || (strcmp(val,".dw") == 0) || (strcmp(val,".db") == 0) || (strcmp(val,".asciz") == 0))
		return data;
	else if(strcmp(val,".entry") == 0)
		return entry;
	else if(strcmp(val,".extern") == 0)
		return external;
	return emptyAtt;
}

/*
* This function get a label list and print it.
*/
void printLabelList(Label **labelList){

	Label *temp = *labelList;
	
	while(temp != NULL){
		printf("name: %s, val: %ld, code: %d, data: %d, entry: %d, external: %d\n",temp->name,temp->value,temp->attributes[0],temp->attributes[1],temp->attributes[2],temp->attributes[3]);
		temp = temp->next;
	}
}

/*
* free the memory of all the Labels in the list in the end of each file
*/
void freeLabelList(Label **labelList){
	#if DEBUG
	printf("current label: %s\n",(*labelList)->name);
	#endif
	if((*labelList)->next != NULL){	
		#if DEBUG
		printf("next label: %s\n\n",(*labelList)->next->name);
		#endif
		freeLabelList(&(*labelList)->next);
	}
	#if DEBUG
	printf("free label: %s\n",(*labelList)->name);
	#endif
	free((*labelList)->name);
	free(*labelList);
	return;
}

/*
* This function initiate the array of Commands there are in the assembler.
* *arr - will hold the address of the array of Commands that i will have in the main function.
*/
void initCommandsList(Command ** arr){
	short int i = 0;	
	
	Command temp[27] = {{Add ,R,1,0},
						{Sub ,R,2,0},
						{And ,R,3,0},
						{Or  ,R,4,0},
						{Nor ,R,5,0},
						{Move,R,1,1},
						{Mvhi,R,2,1},
						{Mvlo,R,3,1},
			
						{Addi ,I,0,10},
						{Subi ,I,0,11},
						{Andi ,I,0,12},
						{Ori  ,I,0,13},
						{Nori ,I,0,14},
						{Bne  ,I,0,15},
						{Beq  ,I,0,16},
						{Blt  ,I,0,17},
						{Bgt  ,I,0,18},
						{Lb   ,I,0,19},
						{Sb   ,I,0,20},
						{Lw   ,I,0,21},
						{Sw   ,I,0,22},
						{Lh   ,I,0,23},
						{Sh   ,I,0,24},

						{Jmp  ,J,0,30},
						{La   ,J,0,31},
						{Call ,J,0,32},
						{Stop ,J,0,63}};

	for(;i < 27;i++){
		(*arr)[i].cmdName = (temp[i]).cmdName;
		(*arr)[i].cmdType = (temp[i]).cmdType;
		(*arr)[i].funct = (temp[i]).funct;
		(*arr)[i].opCode = (temp[i]).opCode;
	}
}

/**/
char getNextChar(FILE *file){

	if(bufferIndex > -1)
	{
		return buffer[bufferIndex--];
	}
	return getc(file);
}

/**/
void setNextChar(char ch){

	buffer[++bufferIndex] = ch;
}

/*
* This function is getting a pointer to a file and return a char* that will hold the current line (command) that i have in the file.
* **file - a pointer to the current file that i want to get his current line.
* Return - char* that will hold the current line (command).
*/
char *getLine(FILE *file){
	char ch;
	char *arr;
	int i;

	if((ch = getNextChar(file))!= EOF){
		setNextChar(ch);
	}
	else{
		return NULL;
	}

	arr = (char*)malloc(lineSize * sizeof(char));

	if(arr){
		i = 0;
		while((ch = getNextChar(file)) != EOF && ch != '\n' && i < (lineSize - 1))
		{
			arr[i] = ch;
			i++;
		}
		arr[i] = '\0';
		
		/* In case that the command is longer then 80 chars and the 81th char isn't \n or \0 (EOF) then i will move the file pointer up to the next line and will display a error, also in case this is the last line i will hold in the buffer the EOF and in the next getLine will get NULL and know to stop scaning this file*/
		if(i <= (lineSize-1) && ch!= EOF && ch != '\n')
		{
			setNextChar(ch);

			while((ch = getNextChar(file)) != EOF && ch != '\n'){
				;
			}
			if(ch == EOF){			
				setNextChar(ch);	
			}
			lineError = true;		
			return "~Syntax error, the command is too long.\0";
		}
		else
			return arr;
	}
	else
	{
		lineError = true;
		return "~Dynamic allocation error, don't have enough space.\0";
	}	
}

/*
* This function will get an char* that suppose to be a label and check if he exist and accordingly add him to the list of Labels or return his address.
* *line - An char* that suppose to be a label.
* *labelList - the list of Labels.
* currAttributes - an enum value of Attributes that represents the type of Attribute of the label currently.
*/
void labelHandle(char *line, Label **labelList, Attributes currAttributes){
	int startSpot = -1, endSpot = -1, i = 0;	
	char * currlabel = NULL;
	Boolean isDone = false,isExist = false;
	Label *labelListPointer = NULL;
	Label *newLabel = NULL;

	/* First part we going to check if the potential label is vaild: */
	while(letterType(line[i]) != eof && isDone == false && i < 32){
		if((letterType(line[i]) == smallLetter || letterType(line[i]) == bigLetter || letterType(line[i]) == number) && startSpot == -1){
			startSpot = i;
			endSpot = i;
		}
		else if((letterType(line[i]) == smallLetter || letterType(line[i]) == bigLetter || letterType(line[i]) == number)){
			endSpot = i;
		}
		else if(letterType(line[i]) == colon && startSpot != -1){
			endSpot = i - 1;
			 isDone = true;
		}
		else if(startSpot != -1){
			lineError = true;
			printf("Line: %d illegal Label\n",lineNumber);
			return;
		}
		i++;
	}

	if(letterType(line[i]) != eof && isDone == false){
		lineError = true;
		printf("Line: %d Too much args!\n",lineNumber);
		return; /* Too much args! */
	}
	if(startSpot == -1 || isDone == false){
		lineError = true;
		printf("Line: %d illegal Label\n",lineNumber);
		return;
	}

	currlabel = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
	strncpy(currlabel,&(line[startSpot]),(endSpot - startSpot + 1));
	currlabel[endSpot - startSpot + 1] = '\0';

	labelListPointer = (*labelList);

	/* after we know this label is vaild we check if this label exist or this is a new one: */
	if(strcmp(labelListPointer->name,"empty") != 0){
		while(isExist == false && labelListPointer->next != NULL){
			if(strcmp(currlabel,labelListPointer->name) == 0){
				isExist = true;
			}
			labelListPointer = labelListPointer->next;
		}
		if(isExist == true){
			if(currAttributes == code){
				if(labelListPointer->attributes[data] == 1){
					lineError = true;
					printf("Line: %d trying to define a code Label for a data Label definition\n",lineNumber);
					return;
				}
				else if(labelListPointer->attributes[external] == 1){
					lineError = true;
					printf("Line: %d trying to define a code Label for a extern Label definition\n",lineNumber);
					return;
				}
				else if(labelListPointer->attributes[code] != 1){
					labelListPointer->attributes[code] = 1;
				}
			}
			else if(currAttributes == data){
				if(labelListPointer->attributes[code] == 1){
					lineError = true;
					printf("Line: %d trying to define a data Label for a code Label definition\n",lineNumber);
					return;
				}
				else if(labelListPointer->attributes[external] == 1){
					lineError = true;
					printf("Line: %d trying to define a data Label for a extern Label definition\n",lineNumber);
					return;
				}
				else if(labelListPointer->attributes[data] != 1){
					labelListPointer->attributes[data] = 1;
				}
			}
			return;
		}
		/* If i got to this part then this is a new Label that we need to add: */
		newLabel = (Label *)malloc(sizeof(Label));
		newLabel->name = currlabel;
		newLabel->next = NULL;

		if(currAttributes == code){
			newLabel->attributes[code] = 1;
			newLabel->value = IC;
		}
		else if(currAttributes == data){
			newLabel->attributes[data] = 1;
			newLabel->value = DC;
		}
		/* Defining .entry and .extern is handled spreadly - can be achived only from those type of doStatements*/
		labelListPointer->next = newLabel;
		return;
	}
	else{
		/* If i got to this part then this is the first Label that we need to add: */
		labelListPointer->name = currlabel;

		if(currAttributes == code){
			labelListPointer->attributes[code] = 1;
			labelListPointer->value = IC;
		}
		else if(currAttributes == data){
			labelListPointer->attributes[data] = 1;
			labelListPointer->value = DC;
		}
		return;
	}
}


/*
* This function Handle adding the registers in *line and add them to regArr.
* *line - the line that suppose to hold the cmd and the wanted register.
* *regArr - Array of the registers values.
* amountOfRegisters - The amount of spots that suppose to be in the array that i want to fill - regArr.
* i - The starting spot that i need to scan *line from.
* Return - the spot that i end the scaning inside *line , return -1 if error occured.
*/
int registerHandler(char * line, short signed int *regArr,short int amountOfRegisters,int i){
	int startSpot = -1, endSpot = -1, tempReg = -1;	
	char * currRegister = NULL;
	Boolean isRegSign = false, isStep = true;

	while(letterType(line[i]) != eof && amountOfRegisters >= 0){
		if(letterType(line[i]) == registerSign && isRegSign == false && isStep == true){
			isRegSign = true;
			isStep = false;
		}
		else if(letterType(line[i]) == number && isRegSign == true && startSpot == -1){
			startSpot = i;
			endSpot = i;
		}
		else if(letterType(line[i]) == number && isRegSign == true && startSpot != -1){
			endSpot = i;
		}
		else if(letterType(line[i]) == step && isStep == false && isRegSign == true){
			isStep = true;
			isRegSign = false;

			currRegister = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
			strncpy(currRegister,&(line[startSpot]),(endSpot - startSpot + 1));
			currRegister[endSpot - startSpot + 1] = '\0';

			tempReg = atoi(currRegister);

			if(tempReg >= 0 && tempReg <= 31){
				regArr[amountOfRegisters] = tempReg;
				amountOfRegisters--;
				tempReg = -1;
				startSpot = -1;
				endSpot = -1;
			}
			else{
				free(currRegister);
				currRegister = NULL;
				lineError = true;
				printf("Line: %d Invaild Register\n",lineNumber);
				return -1;/* Invaild Register*/
			}
			
			free(currRegister);
			currRegister = NULL;	
		}
		else if(letterType(line[i]) != blankLetter){
			lineError = true;
			printf("Line: %d Invaild structure of R cmd\n",lineNumber);
			return -1;/* Invaild structure of R cmd*/
		}
		i++;
	}
	if(startSpot != -1 && endSpot != -1 && letterType(line[i]) == eof){
		currRegister = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
		strncpy(currRegister,&(line[startSpot]),(endSpot - startSpot + 1));
		currRegister[endSpot - startSpot + 1] = '\0';

		tempReg = atoi(currRegister);

		if(tempReg >= 0 && tempReg <= 31){
			regArr[amountOfRegisters] = tempReg;
			amountOfRegisters--;
			tempReg = -1;
			startSpot = -1;
			endSpot = -1;
		}
		else{
			free(currRegister);
			currRegister = NULL;
			lineError = true;
			printf("Line: %d Invaild Register\n",lineNumber);
			return -1;/* Invaild Register*/
		}
		
		free(currRegister);
		currRegister = NULL;
	}
	
	if(amountOfRegisters > -1){
		lineError = true;
		printf("Line: %d Not Enough arguments!\n",lineNumber);
		return -1; /* Not Enough arguments! */
	}
	return i;
}

/*
* This function Handle adding the next register to the wanted 'spot' in regArr.
* *line - the line that suppose to hold the cmd and the wanted register.
* *regArr - Array of the registers values.
* i - The starting spot that i need to scan *line from.
* spot - The spot in the array that i want to fill in regArr.
* Return - the spot that i end the scaning inside *line , return -1 if error occured.
*/
int registerHandlerArrSpot(char *line, short signed int *regArr,int i,int spot){
	int startSpot = -1, endSpot = -1, tempReg = -1;	
	short int amountOfRegisters = 0;
	char * currRegister = NULL;
	Boolean isRegSign = false, isStep = true;

	while(letterType(line[i]) != eof && amountOfRegisters >= 0){
		if(letterType(line[i]) == registerSign && isRegSign == false && isStep == true){
			isRegSign = true;
			isStep = false;
		}
		else if(letterType(line[i]) == number && isRegSign == true && startSpot == -1){
			startSpot = i;
			endSpot = i;
		}
		else if(letterType(line[i]) == number && isRegSign == true && startSpot != -1){
			endSpot = i;
		}
		else if(letterType(line[i]) == step && isStep == false && isRegSign == true){
			isStep = true;
			isRegSign = false;

			currRegister = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
			strncpy(currRegister,&(line[startSpot]),(endSpot - startSpot + 1));
			currRegister[endSpot - startSpot + 1] = '\0';

			tempReg = atoi(currRegister);

			if(tempReg >= 0 && tempReg <= 31){
				regArr[spot] = tempReg;
				amountOfRegisters--;
				tempReg = -1;
				startSpot = -1;
				endSpot = -1;
			}
			else{
				free(currRegister);
				currRegister = NULL;
				lineError = true;
				printf("Line: %d Invaild Register\n",lineNumber);
				return -1;/* Invaild Register*/
			}
			
			free(currRegister);
			currRegister = NULL;	
		}
		else if(letterType(line[i]) != blankLetter){
			lineError = true;
			printf("Line: %d Invaild structure of I cmd\n",lineNumber);
			return -1;/* Invaild structure of I cmd*/
		}
		i++;
	}
	if(startSpot != -1 && endSpot != -1 && letterType(line[i]) == eof){
		currRegister = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
		strncpy(currRegister,&(line[startSpot]),(endSpot - startSpot + 1));
		currRegister[endSpot - startSpot + 1] = '\0';

		tempReg = atoi(currRegister);

		if(tempReg >= 0 && tempReg <= 31){
			regArr[spot] = tempReg;
			amountOfRegisters--;
			tempReg = -1;
			startSpot = -1;
			endSpot = -1;
		}
		else{
			free(currRegister);
			currRegister = NULL;
			lineError = true;
			printf("Line: %d Invaild Register\n",lineNumber);
			return -1;/* Invaild Register*/
		}
		
		free(currRegister);
		currRegister = NULL;
	}
	
	if(amountOfRegisters > -1){
		lineError = true;
		printf("Line: %d Not Enough arguments!\n",lineNumber);
		return -1; /* Not Enough arguments! */
	}
	return i;
}

/*
* This function Handle adding the immed in *line and set the val to currImmed.
* *line - the line that suppose to hold the cmd and the wanted register.
* *currImmed - pointer to the currImmed.
* i - The starting spot that i need to scan *line from.
* Return - the spot that i end the scaning inside *line , return -1 if error occured.
*/
int immedHandler(char * line, int **immed , int i){
	int startSpot = -1, endSpot = -1;
	long int tempImmed = -1;	
	char * currImmed = NULL;
	Boolean isNegSign = false, isPosSign = false, isImmed = false;

	while(letterType(line[i]) != eof && isImmed != true){
		if(letterType(line[i]) == negativeSign && isNegSign == false && isPosSign == false){
			isNegSign = true;
		}
		else if(letterType(line[i]) == positiveSign && isNegSign == false && isPosSign == false){
			isPosSign = true;
		}
		else if(letterType(line[i]) == number && startSpot == -1){
			startSpot = i;
			endSpot = i;
		}
		else if(letterType(line[i]) == number && startSpot != -1){
			endSpot = i;
		}
		else if(letterType(line[i]) == step){
			currImmed = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
			strncpy(currImmed,&(line[startSpot]),(endSpot - startSpot + 1));
			currImmed[endSpot - startSpot + 1] = '\0';

			tempImmed = (long int)atoi(currImmed);		

			if(tempImmed > INT_MIN && tempImmed < INT_MAX){
				if(isNegSign == true){
					**immed = (int)-(tempImmed);
				}
				else {
					**immed = (int)tempImmed;
				}
				startSpot = -1;
				endSpot = -1;
			}
			else{
				free(currImmed);
				currImmed = NULL;
				lineError = true;
				printf("Line: %d Invaild Immed\n",lineNumber);
				return -1;/* Invaild Immed*/
			}
			
			free(currImmed);
			currImmed = NULL;
			isImmed = true;	
		}
		else if(letterType(line[i]) != blankLetter){
			lineError = true;
			printf("Line: %d Invaild structure of I cmd\n",lineNumber);
			return -1;/* Invaild structure of I cmd*/
		}

		i++;
	}
	if(startSpot != -1 && endSpot != -1 && letterType(line[i]) == eof){
		currImmed = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
		strncpy(currImmed,&(line[startSpot]),(endSpot - startSpot + 1));
		currImmed[endSpot - startSpot + 1] = '\0';

		tempImmed = atoi(currImmed);

		if(tempImmed > INT_MIN && tempImmed < INT_MAX){
				if(isNegSign == true){
					**immed = (int)-(tempImmed);
				}
				else {
					**immed = (int)tempImmed;
				}
				startSpot = -1;
				endSpot = -1;
		}
		else{
			free(currImmed);
			currImmed = NULL;
			lineError = true;
			printf("Line: %d Invaild Immed\n",lineNumber);
			return -1;/* Invaild Immed*/
		}
		
		free(currImmed);
		currImmed = NULL;
		isImmed = true;	
	}
	return i;
}

/*
* This function Handle testing the next number in *line and set the val to currNum.
* *line - the line that suppose to hold numbers i need to test.
* **currNum - the pointer to the spot that suppose to hold the next number.
* size - the size that the number cannot exceed.
* i - The starting spot that i need to scan *line from.
* Return - the spot that i end the scaning inside *line , return -1 if error occured.
*/
int numHandlerBySize(char * line, long signed int **currNum,int size , int i){
	int startSpot = -1, endSpot = -1;
	long signed int tempNum = -1, maxSize =0, minSize = 0;	
	char *num = NULL;
	Boolean isNegSign = false, isPosSign = false, isNum = false;

	if(size == 4){
		/*.dw defintion: */
		maxSize = INT_MAX;
		minSize = INT_MIN;
	}
	else if(size == 2){
		/*.dh defintion: */
		maxSize = SHRT_MAX;
		minSize = SHRT_MIN;
	}
	else{
		/*.db or .asciz defintion: */
		maxSize = SCHAR_MAX;
		minSize = SCHAR_MIN;
	}

	while(letterType(line[i]) != eof && isNum != true){
		if(letterType(line[i]) == negativeSign && isNegSign == false && isPosSign == false){
			isNegSign = true;
		}
		else if(letterType(line[i]) == positiveSign && isNegSign == false && isPosSign == false){
			isPosSign = true;
		}
		else if(letterType(line[i]) == number && startSpot == -1){
			startSpot = i;
			endSpot = i;
		}
		else if(letterType(line[i]) == number && startSpot != -1){
			endSpot = i;
		}
		else if(letterType(line[i]) == step){
			num = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
			strncpy(num,&(line[startSpot]),(endSpot - startSpot + 1));
			num[endSpot - startSpot + 1] = '\0';

			tempNum = (long int)atoi(num);

			if(tempNum > minSize && tempNum < maxSize){
				if(isNegSign == true){
					**currNum = (long signed)-(tempNum);
				}
				else {
					**currNum = (long signed)tempNum;
				}
				startSpot = -1;
				endSpot = -1;
			}
			else{
				free(num);
				num = NULL;
				lineError = true;
				printf("Line: %d Args value size is too big\n",lineNumber);
				return -1;/* Invaild Immed*/
			}
			free(num);
			num = NULL;
			isNum = true;
		}
		else if(letterType(line[i]) != blankLetter){
			lineError = true;
			printf("Line: %d Invaild structure of do statement\n",lineNumber);
			return -1;/* Invaild structure of do statement*/
		}

		i++;
	}
	if(startSpot != -1 && endSpot != -1 && letterType(line[i]) == eof){
		num = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
		strncpy(num,&(line[startSpot]),(endSpot - startSpot + 1));
		num[endSpot - startSpot + 1] = '\0';

		tempNum = atoi(num);

		if(tempNum > minSize && tempNum < maxSize){
				if(isNegSign == true){
					**currNum = -(tempNum);
				}
				else {
					**currNum = tempNum;
				}

				startSpot = -1;
				endSpot = -1;
		}
		else{
			free(num);
			num = NULL;
			lineError = true;
			printf("Line: %d Invaild Number\n",lineNumber);
			return -1;/* Invaild Number*/
		}
		
		free(num);
		num = NULL;
		isNum = true;	
	}
	return i;
}

/*
* This function Handle testing the String in *line and return it if he is vaild.
* *line - the line that suppose to hold numbers i need to test.
* i - The starting spot that i need to scan *line from.
* Return - if the string is correct return the string else return NULL.
*/
char *charsHandler(char * line, int i){
	int startSpot = -1, endSpot = -1;
	char *currString = NULL;	
	Boolean isQuoteSignStart = false, isQuoteSignEnd = false;

	while(letterType(line[i]) != eof && isQuoteSignEnd != true){
		/*printf("currChar: %c , isPrint? %d,isQuoteSignStart: %d,isQuoteSignEnd: %d\n",line[i],isprint(line[i]),isQuoteSignStart,isQuoteSignEnd);*/
		if(letterType(line[i]) == quoteSign && isQuoteSignStart == false && isQuoteSignEnd == false){
			isQuoteSignStart = true;
		}
		else if(letterType(line[i]) == quoteSign && isQuoteSignStart == true && isQuoteSignEnd == false){
			isQuoteSignEnd = true;

			if(currString == NULL){
				currString = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
				strncpy(currString,&(line[startSpot]),(endSpot - startSpot + 1));
				currString[endSpot - startSpot + 1] = '\0';
			}
		}
		else if(isprint(line[i]) > 0 && isQuoteSignStart == true && startSpot == -1){
			startSpot = i;
			endSpot = i;
		}
		else if(isprint(line[i]) > 0 && isQuoteSignStart == true && startSpot != -1){
			endSpot = i;
		}
		else if(letterType(line[i]) != blankLetter){
			lineError = true;
			printf("Line: %d Invaild structure of .asciz command\n",lineNumber);
			return NULL;/* Invaild structure of .asciz command*/
		}
		i++;
	}
	if(startSpot != -1 && endSpot != -1 && letterType(line[i]) == eof){
		if(currString == NULL){
			currString = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
			strncpy(currString,&(line[startSpot]),(endSpot - startSpot + 1));
			currString[endSpot - startSpot + 1] = '\0';
		}
	}
	return currString;
}

/*
* This function is getting a line that suppose to hold a doStatement, the function check the doStatement is correct and add it to the BinaryLine list!.
* *line - A line that suppose to hold a doStatement.
* currDoState - the Type of do statement.
* **binLineList - list of all the binary lines. (going to add to them the doStatement lines accordingly)
*/
void doStatementHandler(char * line,doStatement currDoState, BinaryLine **binLineList){
	int i = 0;
	long signed int *currNum = NULL, tempBinary = 0;
	char *currString = NULL;
	Boolean isAsciz = false;

	BinaryLine *currBinLine = NULL;
	
	while(i < strlen(line) && lineError != true && i != -1 && isAsciz != true){
		if(currDoState == Db){
			currNum = (long signed *)malloc(sizeof(long signed));
			i = numHandlerBySize(line,&currNum,1,i);
			if(i != -1){
				/*Transform the number to Binary*/
				if((*currNum) < 0){
					*currNum = (-1) * (*currNum);
					negNumberToBinary((*currNum),&tempBinary,0,7);
				}				
				else {
					numberToBinary((*currNum),&tempBinary,0,7);
				}

				if((*binLineList)->secondScan != NULL && strcmp((*binLineList)->secondScan,"empty") == 0){
					(*binLineList)->address = DC;
					(*binLineList)->addressType = DCType;
					(*binLineList)->dataType = OneByte;
					DC = DC + 1;
					(*binLineList)->binary = tempBinary;
					(*binLineList)->secondScan = NULL;
					(*binLineList)->isDone = true;
					(*binLineList)->next = NULL;
				}
				else{
					currBinLine = (BinaryLine *)malloc(sizeof(BinaryLine));
					currBinLine->address = DC;
					currBinLine->addressType = DCType;
					currBinLine->dataType = OneByte;
					DC = DC + 1;
					currBinLine->binary = tempBinary;
					currBinLine->secondScan = NULL;
					currBinLine->isDone = true;
					currBinLine->next = NULL;
					/*Adding the New BinaryLine to the list: */
					connectNewBinaryLine(binLineList,&currBinLine);
				}
			}
			free(currNum);
			currNum = NULL;
		}
		else if(currDoState == Dh){
			currNum = (long signed *)malloc(sizeof(long signed));
			i = numHandlerBySize(line,&currNum,2,i);
			if(i != -1){
				/*Transform the number to Binary*/
				if((*currNum) < 0){
					*currNum = (-1) * (*currNum);
					negNumberToBinary((*currNum),&tempBinary,0,15);
				}				
				else {
					numberToBinary((*currNum),&tempBinary,0,15);
				}

				if((*binLineList)->secondScan != NULL && strcmp((*binLineList)->secondScan,"empty") == 0){
					(*binLineList)->address = DC;
					(*binLineList)->addressType = DCType;
					(*binLineList)->dataType = TwoByte;
					DC = DC + 2;
					(*binLineList)->binary = tempBinary;
					(*binLineList)->secondScan = NULL;
					(*binLineList)->isDone = true;
					(*binLineList)->next = NULL;
				}
				else{
					currBinLine = (BinaryLine *)malloc(sizeof(BinaryLine));
					currBinLine->address = DC;
					currBinLine->addressType = DCType;
					currBinLine->dataType = TwoByte;
					DC = DC + 2;
					currBinLine->binary = tempBinary;
					currBinLine->secondScan = NULL;
					currBinLine->isDone = true;
					currBinLine->next = NULL;
					/*Adding the New BinaryLine to the list: */
					connectNewBinaryLine(binLineList,&currBinLine);
				}
			}
			free(currNum);
			currNum = NULL;
		}
		else if(currDoState == Dw){
			currNum = (long signed *)malloc(sizeof(long signed));
			i = numHandlerBySize(line,&currNum,4,i);
			if(i != -1){
				/*Transform the number to Binary*/
				if((*currNum) < 0){
					*currNum = (-1) * (*currNum);
					negNumberToBinary((*currNum),&tempBinary,0,31);
				}				
				else {
					numberToBinary((*currNum),&tempBinary,0,31);
				}

				if((*binLineList)->secondScan != NULL && strcmp((*binLineList)->secondScan,"empty") == 0){
					(*binLineList)->address = DC;
					(*binLineList)->addressType = DCType;
					(*binLineList)->dataType = FourByte;
					DC = DC + 4;
					(*binLineList)->binary = tempBinary;
					(*binLineList)->secondScan = NULL;
					(*binLineList)->isDone = true;
					(*binLineList)->next = NULL;
				}
				else{
					currBinLine = (BinaryLine *)malloc(sizeof(BinaryLine));
					currBinLine->address = DC;
					currBinLine->addressType = DCType;
					currBinLine->dataType = FourByte;
					DC = DC + 4;
					currBinLine->binary = tempBinary;
					currBinLine->secondScan = NULL;
					currBinLine->isDone = true;
					currBinLine->next = NULL;
					/*Adding the New BinaryLine to the list: */
					connectNewBinaryLine(binLineList,&currBinLine);
				}
			}
			free(currNum);
			currNum = NULL;
		}
		else if(currDoState == Asciz){
			isAsciz = true;
		}
		else{
			printf("Line: %d Invaild doStatementType\n",lineNumber);
		}

		if(tempBinary != 0){
			tempBinary = 0;
		}
	}
	if(isAsciz == true){
		/*need to handle each char*/
		currString = charsHandler(line,i);
	
		if(currString != NULL){
			i = 0;

			while(i <= strlen(currString)){
				if(letterType(currString[i]) != blankLetter){
					if((*binLineList)->secondScan != NULL && strcmp((*binLineList)->secondScan,"empty") == 0){
						(*binLineList)->address = DC;
						(*binLineList)->addressType = DCType;
						(*binLineList)->dataType = OneByte;
						DC = DC + 1;

						numberToBinary((long signed)currString[i],&tempBinary,0,7);

						(*binLineList)->binary = tempBinary;
						(*binLineList)->secondScan = NULL;
						(*binLineList)->isDone = true;
						(*binLineList)->next = NULL;
					}
					else{
						currBinLine = (BinaryLine *)malloc(sizeof(BinaryLine));
						currBinLine->address = DC;
						currBinLine->addressType = DCType;
						currBinLine->dataType = OneByte;
						DC = DC + 1;

						numberToBinary((long signed)currString[i],&tempBinary,0,7);

						currBinLine->binary = tempBinary;
						currBinLine->secondScan = NULL;
						currBinLine->isDone = true;
						currBinLine->next = NULL;
						/*Adding the New BinaryLine to the list: */
						connectNewBinaryLine(binLineList,&currBinLine);
					}
				}
				i++;
				tempBinary = 0;
			}
		}
		if(currString != NULL){		
			free(currString);
			currString = NULL;
		}
	}
	if(lineError == true){
		printf("Line: %d Invaild args in a doStatement line\n",lineNumber);
	}
}

/*
*
*/
void connectNewBinaryLine(BinaryLine **binLineList,BinaryLine **currBinLine){
	BinaryLine *temp = (*binLineList);
	
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = (*currBinLine);
}

/*
*
*/
void printBinaryLineList(BinaryLine **binLineList){
	BinaryLine *temp = (*binLineList);
	
	while(temp != NULL){
		printf("address: %ld, addressType: %d, dataType: %d, bin: %ld, secScan: %s, isDone: %d\n",temp->address,temp->addressType,temp->dataType,temp->binary,temp->secondScan,temp->isDone);
		printBinary(&temp->binary,0,31);
		printf("\n");
		temp = temp->next;
	}
}

/*
* free the memory of all the Labels in the list in the end of each file
*/
void freeBinaryList(BinaryLine **binLineList){
	printf("current address: %ld\n",(*binLineList)->address);
	if((*binLineList)->next != NULL){	

		printf("next address: %ld\n\n",(*binLineList)->next->address);

		freeBinaryList(&(*binLineList)->next);
	}
	if((*binLineList)->secondScan != NULL){
		printf("free secondScan: %s\n",(*binLineList)->secondScan);
		free((*binLineList)->secondScan);
	}
	free(*binLineList);
	return;
}

/*
* This function is getting a line that suppose to hold a R command, the function check the cmd is correct and return the binary display of it.
* *line - A line that suppose to hold a R command.
* *cmd - pointer to the Rcmd data.
* Return - the binary display of the current Rcmd , if there is an error it will return -1.
*/
long signed int RcmdHandler(char * line,Command * cmd){
	int i = 0;
	long signed int retVal = 0;	
	short signed int regArr[3] = {-1,-1,-1}; /*Register is between 0-31 , will init with -1 to mark untouched spot*/
	short int amountOfRegisters = 0;

	if(cmd->cmdName == Add || cmd->cmdName == Sub || cmd->cmdName == And || cmd->cmdName == Or || cmd->cmdName == Nor){
		amountOfRegisters = 2; /* Getting 3 registers */
	}else{
		amountOfRegisters = 1; /* Getting 2 registers */
	}
	/* fill the registers inside regArr , if error occured then i == -1*/
	i = registerHandler(line,regArr,amountOfRegisters,i);

	if(i == -1){
		return -1; /* Invaild structure of R cmd */
	}
	else if(letterType(line[i]) != eof){
		while(letterType(line[i]) != eof){
			if(letterType(line[i]) != blankLetter){
				lineError = true;
				printf("Line: %d Too much args!\n",lineNumber);
				return -1; /* Too much args! */
			}
		}
	}
	/* Handle the binary Transformation of R cmd: */
	numberToBinary(cmd->opCode,&retVal,26,31); /* opCode */	
	if(regArr[2] != (short signed int)-1){
		numberToBinary(regArr[2],&retVal,21,25); /* rs */
		/*printf("val of regArr[2]: %d\n",regArr[2]);*/
		numberToBinary(regArr[1],&retVal,16,20); /* rt */
		/*printf("val of regArr[1]: %d\n",regArr[1]);*/
		numberToBinary(regArr[0],&retVal,11,15); /* rd */
		/*printf("val of regArr[0]: %d\n",regArr[0]);*/
	}
	else {
		numberToBinary(regArr[1],&retVal,21,25); /* rs */
		/*printf("val of regArr[1]: %d\n",regArr[1]);*/
		numberToBinary(0,&retVal,16,20); /* rt */
		/*printf("val of regArr[2]: %d\n",regArr[2]);*/
		numberToBinary(regArr[0],&retVal,11,15); /* rd */
		/*printf("val of regArr[0]: %d\n",regArr[0]);*/
	}
	numberToBinary(cmd->funct,&retVal,6,10); /* funct */
	numberToBinary(0,&retVal,0,5); /* Not used bits */

	/*TODO DEBUG print r cmd to check - */
	printBinary(&retVal,0,31);

	return retVal;
}


/*
* This function is getting a line that suppose to hold a I command, the function check the cmd is correct and return the binary display of it.
* *line - A line that suppose to hold a I command.
* *cmd - pointer to the Icmd data.
* Return - the binary display of the current Icmd , if there is an error it will return -1.
*/
long signed int IcmdHandler(char * line,Command * cmd){
	int i = 0;
	long signed int retVal = 0;	
	short signed int regArr[2] = {-1,-1}; /*Register is between 0-31 , will init with -1 to mark untouched spot*/
	int *currImmed = NULL,immed = 0;

	if(cmd->cmdName == Beq || cmd->cmdName == Bne || cmd->cmdName == Blt || cmd->cmdName == Bgt){
		/* meaning handle address of label -> check label NodeList ... (TODO)*/
		/* Decided to handle it in the second scan and not halfass it!(TODO) */
	}else{
		/*Getting 1 Register and then Immed Pos/Neg number and then another Register*/
		/* fill the registers inside regArr , if error occured then i == -1*/
		i = registerHandlerArrSpot(line,regArr,i,0);
		if(i != -1){
			/*Handle immed function - */
			currImmed = (int *)malloc(sizeof(int));
			i = immedHandler(line,&currImmed,i);
			immed = *currImmed;
			free(currImmed);
			currImmed = NULL;
			if(i != -1){
				i = registerHandlerArrSpot(line,regArr,i,1);
			}
		}
	}
	if(i == -1 || immed == -1){
		/*printf("Line: %d Invaild structure of I cmd\n",lineNumber);*/
		return -1; /* Invaild structure of I cmd */
	}
	else if(letterType(line[i]) != eof){
		while(letterType(line[i]) != eof){
			if(letterType(line[i]) != blankLetter){
				lineError = true;
				printf("Line: %d Too much args!\n",lineNumber);
				return -1; /* Too much args! */
			}
		}
	}
	/* Handle the binary Transformation of I cmd: */
	numberToBinary(cmd->opCode,&retVal,26,31); /* opCode */	
	numberToBinary(regArr[0],&retVal,21,25); /* rs */
	/*printf("val of regArr[0]: %d\n",regArr[2]);*/
	numberToBinary(regArr[1],&retVal,16,20); /* rt */
	/*printf("val of regArr[1]: %d\n",regArr[1]);*/

	if(immed >= 0){
		numberToBinary(immed,&retVal,0,15); /* immed */
	}
	else {
		/*This mean that i have a negative immed: */
		immed = (-1)*immed;
		negNumberToBinary(immed,&retVal,0,15); /* immed */
		/*printf("val of immed: %d\n",immed);*/
	}
	
	printBinary(&retVal,0,31);

	return retVal;
}


/*
* This function will get a file pointer and the array of posible commands and will execute the first scan of the assembler.
* *file - pointer to the file needed to be transformed.
* **arrCmd - array of all the possible commands.
* **labelList - list of all the current labels in the file.
* **binLineList - list of all the binary lines in the file that i create.
*/
void firstScan(FILE *file, Command ** arrCmd, Label **labelList, BinaryLine **binLineList){
	int i = 0,startSpot = -1,endSpot = -1, argsSpot = -1;
	char *line = NULL,*firstWord = NULL,*secWord = NULL;
	Boolean isFirstWord = true, isSecWord = false, isCommentLine = false,isEmptyLine = false, isArgs = false, isCmd = false;
	CommandName cmdName = None;
	doStatement currDoState = NotStatement;

	BinaryLine *currBinLine = NULL;

	long signed int currCmdBinary = 0;

	while((line = getLine(file))){
		i = 0;
		while(letterType(line[i]) != eof && isCommentLine != true && isArgs != true){
			if(letterType(line[i]) == blankLetter){
				if(startSpot != -1){
					if(isFirstWord == true){
						firstWord = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
						strncpy(firstWord,&(line[startSpot]),(endSpot - startSpot + 1));
						firstWord[endSpot - startSpot + 1] = '\0';
						isFirstWord = false;
						isSecWord = true;
						argsSpot = endSpot + 1;
						startSpot = -1;
						endSpot = -1;
					}
					else if(isSecWord == true){
						secWord = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
						strncpy(secWord,&(line[startSpot]),(endSpot - startSpot + 1));
						secWord[endSpot - startSpot + 1] = '\0';
						isSecWord = false;
						argsSpot = endSpot + 1;
					}
				}
			}
			if(letterType(line[i]) == commentLine && startSpot == -1){
				isCommentLine = true;
			}
			else if(letterType(line[i]) == registerSign){
				argsSpot = i;
				isArgs = true;
			}
			else if(letterType(line[i]) != blankLetter && (isFirstWord == true || isSecWord == true) && startSpot == -1){
				startSpot = i;
			}
			/*printf("%c",line[i]);*/
			endSpot = i;
			i++;
		}
		if(firstWord == NULL && secWord == NULL){
			isEmptyLine = true;
		}
		/*printf("\n");*/
		if(isCommentLine != true && isEmptyLine != true){
			if(secWord == NULL && startSpot != -1){
				secWord = (char *)malloc((endSpot - startSpot + 2) * sizeof(char));
				strncpy(secWord,&(line[startSpot]),(endSpot - startSpot + 1));
				secWord[endSpot - startSpot + 1] = '\0';
				isSecWord = false;
			}

			if(firstWord != NULL){
				if((cmdName = CmdType(firstWord)) != None){				
					/*There is a cmd but not a cmd! */
					if(rCmdType(firstWord) != None){
						currCmdBinary = RcmdHandler(&line[argsSpot],&(*arrCmd)[cmdName]);
						if(lineError != true){
							isCmd = true;
						}
					}
					else if(iCmdType(firstWord) != None){
						currCmdBinary = IcmdHandler(&line[argsSpot],&(*arrCmd)[cmdName]);
						if(lineError != true){
							isCmd = true;
						}
					}
				}
				else if((currDoState = doStatementType(firstWord)) != NotStatement){
					/*Make the BinLines in the function: */
					doStatementHandler(&line[argsSpot],currDoState,binLineList);
				}
			}
			/* If we enter here we need to handle our label: */
			if(secWord != NULL){
				if((cmdName = CmdType(secWord)) != None){
					if(rCmdType(secWord) != None){
						currCmdBinary = RcmdHandler(&line[argsSpot],&(*arrCmd)[cmdName]);
						if(lineError != true){
							labelHandle(firstWord,labelList,code);
							isCmd = true;
						}
					}
					else if(iCmdType(secWord) != None){
						currCmdBinary = IcmdHandler(&line[argsSpot],&(*arrCmd)[cmdName]);
						if(lineError != true){
							labelHandle(firstWord,labelList,code);
							isCmd = true;
						}
					}
				}
				else if((currDoState = doStatementType(secWord)) != NotStatement){
					/*Make the BinLines in the function: */
					doStatementHandler(&line[argsSpot],currDoState,binLineList);
					if(lineError != true){
						labelHandle(firstWord,labelList,data);
					}
				}
			}
			else if((firstWord != NULL || secWord != NULL) && startSpot != -1){
				lineError = true;
				printf("Line: %d Syntax error, the command don't have a legal command!\n",lineNumber);
			}
			if(lineError != true){	
				if((*binLineList)->secondScan == NULL){					
					if(isCmd == true){
						currBinLine = (BinaryLine *)malloc(sizeof(BinaryLine));
						currBinLine->address = IC;
						currBinLine->addressType = ICType;
						currBinLine->dataType = FourByte;
						IC = IC + 4;
						currBinLine->binary = currCmdBinary;
						currBinLine->secondScan = NULL;
						currBinLine->isDone = true;
						currBinLine->next = NULL;
						/*Adding the New BinaryLine to the list: */
						/*printf("Line %d addLine!\n",lineNumber);*/
						connectNewBinaryLine(binLineList,&currBinLine);
					}			
				}
				else if(strcmp((*binLineList)->secondScan,"empty") == 0){
					if(isCmd == true){
						(*binLineList)->address = IC;
						(*binLineList)->addressType = ICType;
						(*binLineList)->dataType = FourByte;
						IC = IC + 4;
						(*binLineList)->binary = currCmdBinary;
						(*binLineList)->secondScan = NULL;
						(*binLineList)->isDone = true;
						(*binLineList)->next = NULL;
						/*printf("Line %d addLine!\n",lineNumber);*/
					}
				}
			}	
		}
		if(firstWord != NULL){
			free(firstWord);
		}
		if(secWord != NULL){
			free(secWord);
		}
		firstWord = NULL;
		secWord = NULL;
		isFirstWord = true;
		isSecWord = false;
		isCommentLine = false;
		isEmptyLine = false;
		isArgs = false;
		isCmd = false;
		startSpot = -1;
		endSpot = -1;
		free(line);

		if(lineError == true && isFileVaild == true){
			isFileVaild = false;
		}
		lineError = false;
		lineNumber++;
	}
}
