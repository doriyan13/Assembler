#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandsHandler.h"
#include "binaryHandler.h"
#include "utilities.h"

/*The number of line in the file i'm in, for each file i reset the size of line*/
int lineNumber = 1;
extern Boolean isFileVaild, isEntry, isExtern;
extern long int IC, DC;

int main(int argc, char const *argv[])
{	
	int i, lineSizeCounter = 0, hexIndex = 0;
	long unsigned int currLineAddress = 100;
	/*char *fullFileName = NULL;*/	
	FILE *file, *fobj, *fent, *fext;

	/* Define char* to hold the Hex data and the name of the relavent files*/
	char *tempHexData = NULL,*tempFileName = NULL, *objFileName = NULL, *entFileName = NULL, *extFileName = NULL;

	/*cmdArr - will hold the array of commands: */
	Command *cmdArr = NULL;
	/*labelList - will hold the list of labels: */
	Label *labelList = NULL, *tempLabelLine = NULL;
	/*binLineList - will hold the list of all the binary lines in the file to write in the file*/
	BinaryLine *binLineList = NULL, *tempBinLine = NULL;

	/* Giving dynamic memory allocation for cmdArr -*/
	cmdArr =  malloc(sizeof(Command) * 27); 
	initCommandsList(&cmdArr); /* fill the array with all the relavent commands*/

	/* Giving dynamic memory allocation for labelList: */
	labelList = (Label *)malloc(sizeof(Label));
	labelList->name = "empty";
	labelList->next = NULL;

	/* Giving dynamic memory allocation for BinaryLine: */
	binLineList = (BinaryLine *)malloc(sizeof(BinaryLine));
	binLineList->secondScan = "empty"; /* to notify that this is the first node in the list! */
	binLineList->next = NULL;

	/*tempHexData = binaryToHex(97,1);
	free(tempHexData);*/

	if(argc <= 1){
		printf("No File were typed.\n");
		exit(0);
	}
	for	(i=1; i<argc; i++)
	{	
		if(argv[i]){	
			tempFileName = getFileName(argv[i]);			
			if(tempFileName != NULL){

				file = fopen(argv[i], "r");
				if (file){	
					lineNumber = 1;
					firstScan(file,&cmdArr,&labelList,&binLineList);
				   	fclose(file);

					secondScan(&labelList,&binLineList);

					if(isFileVaild == true){
						/* If the file hold only vaild syntex then the assembler will create the .ob and .entry and .extern files*/
						if(isEntry == true || isExtern == true){
							if(isEntry == true){
								entFileName = concat(tempFileName,".ent\0");
								if(entFileName == NULL || (fent = fopen(entFileName,"w")) == NULL){
									printf("Error: could not create output files to: %s\n",tempFileName);
									free(cmdArr);
									exit(0);
								}
							}
							if(isExtern == true){
								extFileName = concat(tempFileName,".ext\0");
								if(extFileName == NULL || (fext = fopen(extFileName,"w")) == NULL){
									printf("Error: could not create output files to: %s\n",tempFileName);
									free(cmdArr);
									exit(0);
								}
							}
							/*Start Scanning my LabelList: */
							tempLabelLine = labelList;

							if(tempLabelLine != NULL){
								while(tempLabelLine != NULL){
									if(isEntry == true && tempLabelLine->attributes[entry] == 1){
										if(tempLabelLine->value != 0 && tempLabelLine->value < 1000){
											fprintf(fent,"%s 0%ld\n",tempLabelLine->name,tempLabelLine->value);
										}
										else{
											fprintf(fent,"%s %ld\n",tempLabelLine->name,tempLabelLine->value);
										}
									}
									tempLabelLine = tempLabelLine->next;
								}
							}
						}

						objFileName = concat(tempFileName,".ob\0");
						if(objFileName != NULL && (fobj = fopen(objFileName,"w")) != NULL){
							fprintf(fobj,"      %ld %ld",(IC-100),(DC));
							tempBinLine = binLineList;
							if(tempBinLine != NULL){
								while(tempBinLine != NULL){
									if(tempBinLine->secondScan != NULL){
										tempLabelLine = getLabelFromList((tempBinLine->secondScan),&labelList);
										if(isExtern == true && tempLabelLine->attributes[external] == 1){
											if(tempLabelLine->value != 0 && tempLabelLine->value < 1000){
												fprintf(fext,"%s 0%ld\n",tempBinLine->secondScan,tempBinLine->address);
											}
											else{
												fprintf(fext,"%s %ld\n",tempBinLine->secondScan,tempBinLine->address);
											}
										}
									}
									if(lineSizeCounter == 0 || lineSizeCounter == 4){
										if(currLineAddress != 0 && currLineAddress < 1000){
											fprintf(fobj,"\n0%ld  ",currLineAddress);
										}
										else{
											fprintf(fobj,"\n%ld  ",currLineAddress);
										}
										currLineAddress = currLineAddress + 4;
										lineSizeCounter = 0;
									}
									
									if(tempBinLine->dataType == FourByte){
										tempHexData = binaryToHex(tempBinLine->binary,4);
									}
									else if(tempBinLine->dataType == TwoByte){
										tempHexData = binaryToHex(tempBinLine->binary,2);
									}
									else if(tempBinLine->dataType == OneByte){
										tempHexData = binaryToHex(tempBinLine->binary,1);
									}
									else {
										/*TODO:Error!*/
									}
									/*printf("handle: |%s|\n",tempHexData);*/
									while(letterType(tempHexData[hexIndex]) != eof){
										if(letterType(tempHexData[hexIndex]) == blankLetter){
											lineSizeCounter++;
											fprintf(fobj," ");
										}				
										/*printf(" lineSize: %d\n",lineSizeCounter);*/						
										if(lineSizeCounter == 4){
											/**/
											if(currLineAddress != 0 && currLineAddress < 1000){
												fprintf(fobj,"\n0%ld  ",currLineAddress);
											}
											else{
												fprintf(fobj,"\n%ld  ",currLineAddress);
											}
											currLineAddress = currLineAddress + 4;
											lineSizeCounter = 0;
										}
										else {
											fprintf(fobj,"%c",tempHexData[hexIndex]);
										}
										hexIndex++;
									}
									lineSizeCounter++;
									if(lineSizeCounter < 4 && tempBinLine->next != NULL){
										fprintf(fobj,"  ");
									}
									free(tempHexData);
									tempHexData = NULL;
									hexIndex = 0;
									tempBinLine = tempBinLine->next;
								}
							}
							fclose(fobj);							
							fclose(fent);
							fclose(fext);
						}
						else{
							printf("Error: could not create output files to: %s\n",tempFileName);
							free(cmdArr);
							exit(0);
						}

						
					}

					/*TODO: DEBUG! */
					printLabelList(&labelList);
					/* Free all the labels of the current file - (can be done after creating entry and extern file if needed)*/
					freeLabelList(&labelList);

					/*TODO: DEBUG*/
					printBinaryLineList(&binLineList);
					/* Free all the Binary lines of the current file - (can be done after creating entry and extern file and the hex file if needed)*/
					freeBinaryList(&binLineList);
				}
				else{
					printf("Error: The file %s.as dose not exists.\n", argv[i] );
					free(cmdArr);
					exit(0);
				}

				isFileVaild = true;	/* Before going to the next file restart the check*/	
				free(tempFileName);
				free(objFileName);
				free(entFileName);
				free(extFileName);
				tempFileName = NULL;
				isEntry = false;
				isExtern = false;
			}
		}
		else{
			/*printf("Dynamic allocation error: couldn't create file: %s\n", argv[i]);*/
		}
	}
	/*Free the memory i gave arr*/
	free(cmdArr);

	return 0;
}
