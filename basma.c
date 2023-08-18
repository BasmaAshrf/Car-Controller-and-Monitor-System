/*
 * basma.c
 *
 *  Created on: Aug 17, 2023
 *      Author: basma ashraf
 */
//*************************************************************
//*************************link section************************
//*************************************************************
#include<stdio.h>
#include<stdlib.h>
//*************************************************************
//************************main section*************************
//*************************************************************
#define WITH_ENGINE_TEMP_CONTROLLER 1
typedef enum aircond{ OFF_A , ON_A } aircond;
typedef enum ENG_TEMP_CONT {OFF_E , ON_E}ENG_TEMP_CONT;
void system_func (char *character_system_state);//to display the state of the system
void sensors_menu(char *sensor);//to display the sensors set menu
void traffic_light(int *speed);//to get the traffic light
void room_temp_func(float *temp , aircond *AC); //to get the room temp.
void Engine_temp_func(float *temp , ENG_TEMP_CONT *ETC);//to get the engine temp
/* to display the data of the system */
void show_data(char *sensor , float *room_temp , aircond *AC , int *speed , ENG_TEMP_CONT *ETC , float *engin_temp);
int main()
{
	setvbuf(stdout,NULL,_IONBF,0);
	setvbuf(stderr,NULL,_IONBF,0);
	//start initialization
	char character_system_state , sensor;
	aircond AC = OFF_A;
	ENG_TEMP_CONT ETC = OFF_A;
	int speed =0;
	float room_temp=30 , engin_temp=90;
	//end initialization
	do{
		system_func(&character_system_state);//calling the system state function
		//condation to check the user wants to exit program
		if(character_system_state=='c'){
			printf("Exit program\n");
			return 0;
		}
		do{
			sensors_menu(&sensor);//calling the sensors set menu function
			/*check the selected sensor*/
			if(sensor=='b'){
				traffic_light(&speed);//calling the traffic light function
			}
			else if(sensor=='c'){
				room_temp_func(&room_temp , &AC);//calling the room temp function
			}
			else if(WITH_ENGINE_TEMP_CONTROLLER){ //condition to validate the engine temp controller displayed data
				if(sensor == 'd'){
					Engine_temp_func(&engin_temp , &ETC );//calling the engine temp. data function
				}
			}

			if((!WITH_ENGINE_TEMP_CONTROLLER) &&  sensor == 'd'){//if the user selected d it must be invalid
				continue;
			}
			if(speed==30){
				AC = ON_A;
				room_temp= ((5.0/4)*room_temp) + 1;
				ETC = ON_A;
				engin_temp= ((5.0/4)*room_temp) + 1;
			}
			show_data(&sensor , &room_temp , &AC ,&speed , &ETC , &engin_temp );
		}while(sensor !='a');
	}while(sensor =='a');
}
void system_func(char *character_system_state){
	do{
		printf("select system state\n");
		printf("a.Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c.Quit the system\n");
		printf("your answer:");
		scanf(" %c" , character_system_state);
		printf("\n==============================\n");
		//to be sure the selected character in system state menu
		if(!(*character_system_state >= 'a' && *character_system_state <= 'c')){
			printf("\nSorry! please enter on of 3 option from system menu\n");
		}
		if(*character_system_state=='b')
			printf("Turn off the vehicle engine\n");
	}while((*character_system_state=='b')||!(*character_system_state >= 'a' && *character_system_state <= 'c'));
}
void sensors_menu(char *sensor){
	do{
		printf("sensor set menu\n");
		printf("a. Turn off the engine\n");
		printf("b. Set the traffic light color\n");
		printf("c. Set the room temperature\n");
		if(WITH_ENGINE_TEMP_CONTROLLER){//condition to validate the engine temp controller sensor
			printf("d. Set the engine temperature\n");}
		printf("d. Set the engine temperature\n");
		printf("your answer:");
		scanf(" %c" , sensor);
		printf("\n==============================\n");
		if((!WITH_ENGINE_TEMP_CONTROLLER) &&  *sensor == 'd'){
			printf("This option is not valid now because ENGINE_TEMP_CONTROLLER is invalid ");
			printf("\n==============================\n");
		}
	}while( !(*sensor >= 'a' && *sensor <= 'd'));
}
void traffic_light(int *speed)
{
	char light;

	do{
		printf("enter the current traffic light: ");
		scanf(" %c",&light);
		printf("\n==============================\n");
		if ( light =='G')
		{
			*speed=100;
		}
		else if( light =='O')
		{
			*speed=30;
		}
		else if( light =='R')
		{
			*speed=0;
		}

	}while(light!='G' && light!='O' && light!='R');
}
void room_temp_func(float *room_temp , aircond *AC){
	printf("the current room temperture:\n");
	scanf("%f" , room_temp);//get the room temp. from the user
	printf("\n==============================\n");
	if((*room_temp < 10 ) || (*room_temp > 30)){
		*AC = ON_A;
		*room_temp = 20;}
	else{
		*AC = OFF_A;
	}

}
void Engine_temp_func(float *engin_temp , ENG_TEMP_CONT *ETC ){
	printf(" Engine temperature:\n");
	scanf("%f" , engin_temp);//get the engine temp. from the user
	printf("\n==============================\n");
	if((*engin_temp < 100 ) || (*engin_temp > 150)){
		*ETC = ON_E;
		*engin_temp = 125;}
	else{
		*ETC =OFF_E;
	}

}
void show_data(char *sensor , float *room_temp , aircond *AC , int *speed , ENG_TEMP_CONT *ETC , float *engin_temp){
	printf("\nThe current vehicle state:");
	if(*sensor == 'a')
		printf(" OFF\n");
	else
		printf(" ON\n");
	printf("Engine state:");
	if(*sensor == 'a')
		printf(" OFF\n");
	else
		printf(" ON\n");
	printf("AC:");
	if( *AC == ON_A)
		printf(" ON\n");
	else
		printf(" OFF\n");
	printf("Vehicle Speed: %d\n" , *speed);
	printf("Room Temperature: %f\n" , *room_temp );
	printf("Engine Temperature Controller State:");
	if(*ETC == ON_E)
		printf(" ON\n");
	else
		printf(" OFF\n");
	printf("Engine Temperature:%f\n\n" , *engin_temp);

	printf("\n==============================\n");
}

