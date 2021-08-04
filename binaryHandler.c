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
		if(space_counter == 6 || space_counter == 11 || space_counter == 16 || space_counter == 21 || space_counter == 26){ /*currently works for R command, need to custom it for all the three types, maybe make one for each!*/
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
