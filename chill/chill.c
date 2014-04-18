/*
Program name: Chill.c
14S CS 50 Lab 3
@Author: Paul Champeau
Inputs: this program accepts two numerical inputs: temperature and wind velocity
Output: The wind chill is then outputted to stdout

**See README and TESTING for more information
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>

//This Function creates a temperature chart for when no arguments are passed to chill.c
void temperature_chart (void){
	float temp, wind, wind_chill;
	temp = -10;
	wind = 5;
	fprintf(stdout, "Temp    Wind    Chill\n");
	fprintf(stdout, "_____   ____    _____\n");
	while (temp <= 40){
		while (wind <= 15){
		wind_chill = 35.74 + (.6215*temp) - (35.75 * pow(wind, .16)) + ((.4275*temp)*pow(wind, .16));
		fprintf(stdout, "%5.1f  %5.1f   %5.1f\n",temp, wind, wind_chill);
		wind += 5;
		}
		temp += 10;
		wind = 5;
	}
	
}

int main(int argc, char* argv[]){
	
	float wind_chill, temp, wind;
	int i, j;

	//check to make sure that only numbers have been passed in as arguments
	for(j=1; j<argc; j++){
	for(i=0; i<strlen(argv[j]); i++){
		if(!(isdigit((int)argv[j][i]))){
			if(argv[j][i] == '.')
				continue;
			fprintf(stderr, "Invalid Argument: Arguments must be strictly numberical values\n");
			return 1;
		}
	}
	}

	//Case 1: check for no arguments
	if(argc == 1){
		temperature_chart();
		return 0;
	}
	//Case 2: check for a single argument
	if (argc == 2){
		temp = atof(argv[1]);
		//If the value is out of bounds alert the user
		if(temp >= 50){
			fprintf(stderr, "Arguments out of bounds: Temperature must be greater than 50 degrees "
			 "and wind velocity must be greater than .5 MPH\n");
			return 1;
		}
		wind = 5;
		fprintf(stdout, "Temp    Wind    Chill\n");
		fprintf(stdout, "_____   ____    _____\n");
		while(wind <= 15){
			wind_chill = 35.74 + (.6215*temp) - (35.75 * pow(wind, .16)) + ((.4275*temp)*pow(wind, .16));
			fprintf(stdout, "%5.1f  %5.1f   %5.1f\n",temp, wind, wind_chill);
			wind += 5;
		}
		return 0;
	}
	//Case 3: check to make sure both arguments are within the bounds
	temp = atof(argv[1]);
	wind = atof(argv[2]);
		if(temp < 50 && wind > .5){
			wind_chill = 35.74 + (.6215*temp) - (35.75 * pow(wind, .16)) + ((.4275*temp)*pow(wind, .16));
			fprintf(stdout, "Temp    Wind    Chill\n");
			fprintf(stdout, "_____   ____    _____\n");
			fprintf(stdout, "%.1f    %.1f    %.1f\n",temp, wind, wind_chill);
		}
		//if not then alert ths user.
		else{
			fprintf(stderr, "Arguments out of bounds: Temperature must be greater than 50 degrees "
			 "and wind velocity must be greater than .5 MPH\n");
			return 1;
		}

	return 0;
}
