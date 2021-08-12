#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commandsHandler.h"
#include "binaryHandler.h"

#define SetBit(x,spot)     ( x |= (1lu << ((spot)%32)) )
#define ClearBit(x,spot)   ( x &= ~(1lu << ((spot)%32)) )
#define TestBit(x,spot)    ( x & (1lu << ((spot)%32)) )

/* Fill the Bin needed.
* input - the number that i need to transform to binary.
* cmdBin - the command pointer i need to fill his Binary.
* start_spot - the spot to start update the Binary.
* end_spot - the spot to end the update of the Binary.
*/
void numberToBinary(signed long int input, signed long int * cmdBin, int start_spot, int end_spot){

	while(start_spot <= end_spot){
		if(input % 2 == 1){
			SetBit((*cmdBin),start_spot);
		}
		input >>= 1;
		start_spot++;
	}
}

/* Fill the Bin needed for negative numbers.
* input - the number that i need to transform to binary.
* cmdBin - the command pointer i need to fill his Binary.
* start_spot - the spot to start update the Binary.
* end_spot - the spot to end the update of the Binary.
*/
void negNumberToBinary(signed long int input, signed long int * cmdBin, int start_spot, int end_spot){

	while(start_spot <= end_spot){
		if(input % 2 != 1){
			SetBit((*cmdBin),start_spot);
		}
		input >>= 1;
		start_spot++;
	}
	(*cmdBin) += 1;
}

/* This function getting binary command and print the block of the command wanted.
* cmdBin - the command pointer i need to print his Binary.
* start_spot - the spot to start update the Binary.
* end_spot - the spot to end the update of the Binary.
*/
void printBinary(signed long int * cmdBin, int start_spot, int end_spot){

	short int space_counter = 0;

	while(end_spot >= start_spot){
		if(space_counter == 6 || space_counter == 11 || space_counter == 16 || space_counter == 21 || space_counter == 26){ 
			putchar(' ');
		}
		if(TestBit((*cmdBin),end_spot) > 0){
			printf("1");
		}
		else {
			printf("0");
		}
		end_spot--;
		space_counter++;
	}
	printf("\n");
}

/*
* This function get a long signed BinaryLine and transform it to little edian Hex and return it.
* binaryVal - a binary line value.
* size - the amout of byte that this binary line suppose to have.
* Return - the display of hex little edian of the binary value.
*/
char *binaryToHex(long signed int binaryVal,int size){
	int multi = 1, currSpot = 0,index = 0,tempFirstDigit = 0,tempSecDigit = 0;
	char *hexVal = NULL,tempChar[1];

	Boolean isFirst = true, isSec = false;

	hexVal = (char *)malloc((2 * size) * sizeof(char) + (size-1) * sizeof(char)); /*adding size - 1 to add the needed spaces*/

	while(currSpot <= (size * 8)){
		if(currSpot != 0 && currSpot % 4 == 0){
			if(isFirst == true && isSec == false){
				isFirst = false;
				isSec = true;
				multi = 1;
			}
			else if(isFirst != true && isSec == true){
				switch(tempSecDigit){
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
					case 9:
						sprintf(tempChar, "%d", tempSecDigit);
						hexVal[index] = tempChar[0];
						break;
					case 10:
						hexVal[index] = 'A';
						break;
					case 11:
						hexVal[index] = 'B';
						break;
					case 12:
						hexVal[index] = 'C';
						break;
					case 13:
						hexVal[index] = 'D';
						break;
					case 14:
						hexVal[index] = 'E';
						break;
					case 15:
						hexVal[index] = 'F';
						break;
				}
				/*moving to the next figure*/
				index++;

				switch(tempFirstDigit){
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
					case 9:
						sprintf(tempChar, "%d", tempFirstDigit);
						hexVal[index] = tempChar[0];
						break;
					case 10:
						hexVal[index] = 'A';
						break;
					case 11:
						hexVal[index] = 'B';
						break;
					case 12:
						hexVal[index] = 'C';
						break;
					case 13:
						hexVal[index] = 'D';
						break;
					case 14:
						hexVal[index] = 'E';
						break;
					case 15:
						hexVal[index] = 'F';
						break;
				}
				/*moving to the next figure*/
				index++;

				if((currSpot + 1) < (size * 8)){
					hexVal[index] = ' ';
					index++;
				}		
				
				isFirst = true;
				isSec = false;
				tempFirstDigit = 0;
				tempSecDigit = 0;
				multi = 1;
			}
			hexVal[index] = '\0';
		}
		if(isFirst == true && isSec == false){
			if(TestBit(binaryVal,currSpot) > 0){
				tempFirstDigit = tempFirstDigit + 1 * multi; 			
			}
		}
		else if(isSec == true && isFirst == false){
			if(TestBit(binaryVal,currSpot) > 0){
				tempSecDigit = tempSecDigit + 1 * multi; 			
			}
		}
		multi = multi * 2;
		currSpot++;
	}
	return hexVal;
}
