/*
 * main.c
 *
 *  Created on: 5 Oct 2015
 *      Author: embedded fab
 *      This project used to communicate with blue tooth terminal app to turn on or off Relay
 */

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "HAL/Bluetooth.h"

int main()
{
	char incoming_data[50]          = {0};
	char Turn_on_array[20]          = "turn on lamb\r\n";
	char Turn_off_array[20]         = "turn off lamb\r\n";


	EF_void_BLUETOOTH_Init();
	EF_B_DIO_InitPin('D',4,OUTPUT);                          // init Relay as Output which connected to the lamb
	EF_S8_DIO_ClearPin('D',4);                               //Make the lamb off

	EF_Void_BLUETOOTH_Send_String("Start\r\n");              //send start to blue tooth terminal to check connection



	while(1)
	{

		memset(incoming_data, 0,50*sizeof(char));                           //Clear the Buffer before receiving new Data

		EF_Void_BLUETOOTH_ReadArray_untill_NewLine(incoming_data,50);       //Read the data from blue tooth terminal until new line found


		if(strcmp(incoming_data,Turn_on_array)==0)                          //check if the incoming data = turn on lamb
		{
			EF_S8_DIO_SetPin('D',4); 									    //turn on Relay
		}


		else if(strcmp(incoming_data,Turn_off_array)==0)                    //check if the incoming data = turn OFF lamb
		{
			EF_S8_DIO_ClearPin('D',4);   									//turn OFF Relay
		}


		EF_Void_BLUETOOTH_Send_String(incoming_data);

	}


	return 0;
}


