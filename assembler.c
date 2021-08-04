#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandsHandler.h"
#include "binaryHandler.h"
#include "utilities.h"

/*The number of line in the file i'm in, for each file i reset the size of line*/
int lineNumber = 1;
extern int isFileVaild;

int main(int argc, char const *argv[])
{	
	int i;
	/*char *fullFileName = NULL;*/	
	FILE * file;

	/*cmdArr - will hold the array of commands: */
	Command *cmdArr = NULL;
	/*labelList - will hold the list of labels: */
	Label *labelList = NULL;
	/*binLineList - will hold the list of all the binary lines in the file to write in the file*/
	BinaryLine *binLineList = NULL;

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

	if(argc <= 1)
	{
		printf("No File were typed.\n");
		exit(0);
	}
	
	for	(i=1; i<argc; i++)
	{			
		if(argv[i]) /*Need to add a check if the ending of the file name is .as if not it's invaild file!*/
		{
			file = fopen(argv[i], "r");
			if (file)
			{	
				lineNumber = 1;
				firstScan(file,&cmdArr,&labelList,&binLineList);
			   	fclose(file);

				/*TODO: DEBUG! */
				printLabelList(&labelList);
				/* Free all the labels of the current file - (can be done after creating entry and extern file if needed)*/
				freeLabelList(&labelList);

				/*TODO: DEBUG*/
				printBinaryLineList(&binLineList);
				/* Free all the Binary lines of the current file - (can be done after creating entry and extern file and the hex file if needed)*/
				freeBinaryList(&binLineList);
			}else{
				printf("Error: The file %s.as dose not exists.\n", argv[i] );
				exit(0);
			}
			isFileVaild = true;	/* Before going to the next file restart the check*/		
		}
		else
		{
			printf("Dynamic allocation error: couldn't create file: %s\n", argv[i]);
		}
	}
	/*Free the memory i gave arr*/
	free(cmdArr);

	return 0;
}
