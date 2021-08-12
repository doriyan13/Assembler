#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandsHandler.h"
#include "binaryHandler.h"
#include "utilities.h"

/*The number of line in the file i'm in, for each file i reset the size of line*/
int lineNumber = 1;
/* Validation for errors in file and if there is a entry or a external doStatement- */
extern Boolean isFileVaild, isEntry, isExtern;
/* The addresses types counter- */
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
					/* Reset the memory spots for each file- */	
					lineNumber = 1;
					IC = 100;
					DC = 0;
					currLineAddress = 100;
					/* Giving dynamic memory allocation for labelList: */
					labelList = (Label *)malloc(sizeof(Label));
					labelList->name = "empty";
					labelList->next = NULL;

					/* Giving dynamic memory allocation for BinaryLine: */
					binLineList = (BinaryLine *)malloc(sizeof(BinaryLine));
					binLineList->secondScan = "empty"; /* to notify that this is the first node in the list! */
					binLineList->next = NULL;

					firstScan(file,&cmdArr,&labelList,&binLineList);

					secondScan(&labelList,&binLineList);

					if(isFileVaild == true){
						/* If the file hold only vaild syntex then the assembler will create the .ob and .entry and .extern files*/
						/* Handle the entry & external files: */
						if(isEntry == true || isExtern == true){
							if(isEntry == true){
								entFileName = concat(tempFileName,".ent\0");
								if(entFileName == NULL || (fent = fopen(entFileName,"w")) == NULL){
									printf("Error: could not create output files to: %s\n",tempFileName);
									if(cmdArr != NULL){
										free(cmdArr);
									}
									exit(0);
								}
							}
							if(isExtern == true){
								extFileName = concat(tempFileName,".ext\0");
								if(extFileName == NULL || (fext = fopen(extFileName,"w")) == NULL){
									printf("Error: could not create output files to: %s\n",tempFileName);
									if(cmdArr != NULL){
										free(cmdArr);
									}
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
						/* Handle the obj file: */
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
									while(letterType(tempHexData[hexIndex]) != eof){
										if(letterType(tempHexData[hexIndex]) == blankLetter){
											lineSizeCounter++;
											fprintf(fobj," ");
										}									
										if(lineSizeCounter == 4){
											/* Handle the display of address in the obj file*/
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
									if(tempHexData != NULL){
										free(tempHexData);
										tempHexData = NULL;
									}
									hexIndex = 0;
									tempBinLine = tempBinLine->next;
								}
							}
							if(fobj != NULL){
								fclose(fobj);	
							}
							if(fent != NULL){						
								fclose(fent);
							}
							if(fext != NULL){
								fclose(fext);
							}
						}
						else{
							printf("Error: could not create output files to: %s\n",tempFileName);
							if(cmdArr != NULL){
								free(cmdArr);
							}
							exit(0);
						}
					}

					#if DEBUG
						printLabelList(&labelList);
					#endif
					/* Free all the labels of the current file - (can be done after creating entry and extern file if needed)*/
					if(labelList != NULL){
						freeLabelList(&labelList);
						labelList = NULL;
					}

					#if DEBUG
						printBinaryLineList(&binLineList);
					#endif
					/* Free all the Binary lines of the current file - (can be done after creating entry and extern file and the hex file if needed)*/
					if(binLineList != NULL){
						freeBinaryList(&binLineList);
						binLineList = NULL;
					}
					fclose(file);
				}
				else{
					printf("Error: The file %s.as dose not exists.\n", argv[i] );
					free(cmdArr);
					exit(0);
				}

				isFileVaild = true;	/* Before going to the next file restart the check*/	
				if(tempFileName != NULL){
				free(tempFileName);
					tempFileName = NULL;
				}
				if(objFileName != NULL){
					free(objFileName);
					objFileName = NULL;
				}
				if(entFileName != NULL){
					free(entFileName);
					entFileName = NULL;
				}
				if(extFileName != NULL){
					free(extFileName);
					extFileName = NULL;
				}
				isEntry = false;
				isExtern = false;
				lineSizeCounter = 0;
				hexIndex = 0;
			}
		}
		else{
			printf("Input error: couldn't open: %s\n", argv[i]);
		}
	}
	/*Free the memory i gave arr*/
	free(cmdArr);
	return 0;
}
