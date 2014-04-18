/*
Program Name: dog.c
14S CS 50 Lab 3
@Author: Paul Champeau

Inputs: See the README/TESTING/help function

*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGTH 1000

void help(void){
	fprintf(stderr, "dog.c Help:\n"
		"Switch options are as follows:\n\n"
		"-n: place line numbers at the front of each output line\n\n"
		"-m [Mapfile]: lightly encrypt the output based on the Mapfile\n"
		"note** the map file must direcly follow the -m\n\n"
		"-M [Mapfile]: decrypt an input based on the mapfile\n\n"
		"Input format:(Formatting must strictly follow this example)\n"
		"./dog.o [-n] [-m] Mapfile [-M] Mapfile [list of target files]\n\n"
		"Note**: the [-n] switch must be right after the function call,\n"
		"other switches after that, followed by their corresponding files,\n"
		"and then lastly the target file.\n\n");

}

int main(int argc, char* argv[]){

	char temp[MAX_LENGTH];
	int file = 1;
	int line_number = 0;
	int map = 0;
	int un_map = 0;
	char encrypt[5];
	int counter = 1;
	FILE *afile, *ofile;
	int i,j;
	//if there is only a single argument then jump to echo text mode
	if(argc == 1){
		while (1){
			fgets(temp, sizeof temp, stdin);
			fprintf(stdout, "%s\n", temp);
		}
	}

	//check for various switches, if found flip the corresponding boolean from false to true
	for(j=1; j<argc; j++){
		for(i=0; i<strlen(argv[j]); i++){
			if(argv[j][i] == '-' && argv[j][i+1] == 'n')
				line_number = 1;
			else if(argv[j][i] == '-' && argv[j][i+1] == 'm')
				map = 1;
			else if(argv[j][i] == '-' && argv[j][i+1] == 'M')
				un_map = 1;
			else if (argv[j][i] == '-' && argv[j][i+1] == '-'){
				help();
				return 0;
			}
		}
	}
	//check to see if the user wishes to "dog" a file 
	//or just text from stdin
	if(((map || un_map)) && ((argc == 3)))
		file = 0;
	else if(line_number && (argc == 2))
		file = 0;

	fprintf(stderr, "-n: %d\n", line_number);
	fprintf(stderr, "file: %d\n", file );
	fprintf(stderr, "map: %d\n", map);
	fprintf(stderr, "un_map: %d\n", un_map);
	//check to file boolean which is set in the code above

	//If you encrypting and numbering lines from stdin
	if(map && line_number && (argc == 4)){
		afile = fopen(argv[3],"r");
		if(afile == NULL){
			fprintf(stderr, "File %s does not exist\n", argv[2]);
			return 1;
		}

		while(1){
			fgets(temp, sizeof temp, stdin);
			for(i=0; i<sizeof temp; ++i){
				while (fgets(encrypt, sizeof encrypt, afile) != NULL){
					if(encrypt[0] == temp[i]){
						temp[i] = encrypt[2];
						break;
					}
				}
				rewind(afile);
			}
			fprintf(stdout, "%d ",counter);
			fprintf(stdout, "%s", temp);
			counter++;
		}
	}

	//If you are decrpyting and numbering lines from stdin
	else if(un_map && line_number && (argc == 4)) {
		afile = fopen(argv[3],"r");
		if(afile == NULL){
			fprintf(stderr, "File %s does not exist\n", argv[2]);
			return 1;
		}

		while(1){
			fgets(temp, sizeof temp, stdin);
			for(i=0; i<sizeof temp; ++i){
				while (fgets(encrypt, sizeof encrypt, afile) != NULL){
					if(encrypt[2] == temp[i]){
						temp[i] = encrypt[0];
						break;
					}
				}
				rewind(afile);
			}
			fprintf(stdout, "%d ", counter);
			fprintf(stdout, "%s", temp);
			counter++;
		}
	}
	//if you are mapping and numbing lines from a file
	else if(map && file && line_number){
		for(j=4; j<argc; j++){
			afile = fopen(argv[3],"r");
			ofile = fopen(argv[j], "r");
			if(afile == NULL){
				fprintf(stderr, "File %s does not exist\n", argv[2]);
				return 1;
			}
			else if(ofile == NULL){
				fprintf(stderr, "File %s does not exist\n", argv[3]);
				return 1;
			}

			while(fgets(temp, sizeof temp, ofile) != NULL){
				for(i=0; i<sizeof temp; ++i){
					while (fgets(encrypt, sizeof encrypt, afile) != NULL){
						if(encrypt[0] == temp[i]){
							temp[i] = encrypt[2];
							break;
						}
					}
					rewind(afile);
				}
				fprintf(stdout, "%d ", counter);
				fprintf(stdout, "%s", temp);
				counter++;
			}
			fclose(afile);
			fclose(ofile);
			counter = 1;
		}
	}

	//if you are decrypting and numbering lines from a file
	else if(un_map && file && line_number){
		for(j=4; j<argc; j++){
			afile = fopen(argv[3],"r");
			ofile = fopen(argv[j], "r");
			if(afile == NULL){
				fprintf(stderr, "File %s does not exist\n", argv[2]);
				return 1;
			}
			else if(ofile == NULL){
				fprintf(stderr, "File %s does not exist\n", argv[3]);
				return 1;
			}

			while(fgets(temp, sizeof temp, ofile) != NULL){
				for(i=0; i<sizeof temp; ++i){
					while (fgets(encrypt, sizeof encrypt, afile) != NULL){
						if(encrypt[2] == temp[i]){
							temp[i] = encrypt[0];
							break;
						}
					}
					rewind(afile);
				}
				fprintf(stdout, "%d ", counter);
				fprintf(stdout, "%s", temp);
				counter++;
			}
			fclose(afile);
			fclose(ofile);
			counter = 1;
		}
	}

	//If you are just numbering lines from a file
	else if(file && line_number && !map && !un_map){

		for(i=2; i<argc; i++){
			afile = fopen(argv[i], "r");

		//check for existence of the file
			if(afile == NULL){
				fprintf(stderr,"File %s does not exist\n", argv[i]);
				return 1;
			}

			while(fgets(temp, sizeof temp, afile) != NULL){	
				fprintf(stdout, "%d ", counter);
				fputs(temp, stdout);
				counter++;
			}

			fclose(afile);
			counter = 1;
		}
		fprintf(stdout, "\n"); //formatting
		return 0;
	}
    
    //if you are just reading lines from a file
	else if(file && !map && !line_number && !un_map){
		for(i=1; i<argc; i++){
			afile = fopen(argv[i], "r");

		//check for existence of the file
			if(afile == NULL){
				fprintf(stderr,"File %s does not exist\n", argv[i]);
				return 1;
			}

			while(fgets(temp, sizeof temp, afile) != NULL){	
				fputs(temp, stdout);
			}

			fclose(afile);
		}
		fprintf(stdout, "\n"); //formatting
		return 0;
	}

	//if both the -m and -M switches are thrown
	else if(map && un_map){
		fprintf(stderr, "Invalid Switches: both -m and -M cannot be called\n");
		return 1;
	}

	//if you are encrypting lines from a file without number lines
	else if(map && file){
		for(j=3; j<argc; j++){
			afile = fopen(argv[2],"r");
			ofile = fopen(argv[j], "r");
			if(afile == NULL){
				fprintf(stderr, "File %s does not exist\n", argv[2]);
				return 1;
			}
			else if(ofile == NULL){
				fprintf(stderr, "File %s does not exist\n", argv[3]);
				return 1;
			}

			while(fgets(temp, sizeof temp, ofile) != NULL){
				for(i=0; i<sizeof temp; ++i){
					while (fgets(encrypt, sizeof encrypt, afile) != NULL){
						if(encrypt[0] == temp[i]){
							temp[i] = encrypt[2];
							break;
						}
					}
					rewind(afile);
				}
				fprintf(stdout, "%s", temp);
			}
			fclose(afile);
			fclose(ofile);
		}
	}

	//if you are decrypting lines from a file without number lines
	else if(un_map && file){
		for(j=3; j<argc; j++){
			afile = fopen(argv[2],"r");
			ofile = fopen(argv[j], "r");
			if(afile == NULL){
				fprintf(stderr, "File %s does not exist\n", argv[2]);
				return 1;
			}
			else if(ofile == NULL){
				fprintf(stderr, "File %s does not exist\n", argv[3]);
				return 1;
			}

			while(fgets(temp, sizeof temp, ofile) != NULL){
				for(i=0; i<sizeof temp; ++i){
					while (fgets(encrypt, sizeof encrypt, afile) != NULL){
						if(encrypt[2] == temp[i]){
							temp[i] = encrypt[0];
							break;
						}
					}
					rewind(afile);
				}
				fprintf(stdout, "%s", temp);
			}
			fclose(afile);
			fclose(ofile);
		}
	}

	//if you are just encrypting lines from stdin
	else if(map){
		afile = fopen(argv[2],"r");
		if(afile == NULL){
			fprintf(stderr, "File %s does not exist\n", argv[2]);
			return 1;
		}

		while(1){
			fgets(temp, sizeof temp, stdin);
			for(i=0; i<sizeof temp; ++i){
				while (fgets(encrypt, sizeof encrypt, afile) != NULL){
					if(encrypt[0] == temp[i]){
						temp[i] = encrypt[2];
						break;
					}
				}
				rewind(afile);
			}
			fprintf(stdout, "%s", temp);
		}
	}

	//if you are just decrypting lines from stdin
	else if(un_map){
		afile = fopen(argv[2],"r");
		if(afile == NULL){
			fprintf(stderr, "File %s does not exist\n", argv[2]);
			return 1;
		}

		while(1){
			fgets(temp, sizeof temp, stdin);
			for(i=0; i<sizeof temp; ++i){
				while (fgets(encrypt, sizeof encrypt, afile) != NULL){
					if(encrypt[2] == temp[i]){
						temp[i] = encrypt[0];
						break;
					}
				}
				rewind(afile);
			}
			fprintf(stdout, "%s", temp);
		}
	}
	//if you are just numbering lines from stdin
	else if(line_number){
		i = 1;
		while (1){
			fgets(temp, sizeof temp, stdin);
			fprintf(stdout, "%d %s\n", i, temp);
			i++;
		}
	}

	return 0;
}
