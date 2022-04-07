#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct variable {
	char type;
	int integer;
	float floatval;
	char* string;
};

struct statement {
	int opcode;
	int memory;
	struct variable constant;
};

struct variable typeprocess(char* input) {
	struct variable trt;
	switch (input[0]) {
		case 'i':
			trt.integer = atoi(input+2);
			trt.type = 'i';
			break;
		case 'f':
			trt.floatval = atof(input+2);
			trt.type = 'f';
			break;
		case 's':
			trt.string = (char*) calloc(sizeof(input),sizeof(char));
			trt.string = input+2;
			trt.type = 's';
			break;
	}
	return trt;
}

int uwutoindex(char* uwutc) {
	if (strcmp(uwutc,"uwu")==0) {
		return 0;
	} else if (strcmp(uwutc,"Uwu")==0) {
		return 1;
	} else if (strcmp(uwutc,"uWu")==0) {
		return 2;
	} else if (strcmp(uwutc,"UWu")==0) {
		return 3;
	} else if (strcmp(uwutc,"uwU")==0) {
		return 4;
	} else if (strcmp(uwutc,"UwU")==0) {
		return 5;	
	} else if (strcmp(uwutc,"uWU")==0) {
		return 6;
	} else if (strcmp(uwutc,"UWU")==0) {
		return 7;
	}
}

int main(void) {
	char* code;
	char filebuffer[255];
	FILE* codefile;
	unsigned long filesize;
	
	codefile = fopen("./input.owol","r");

	if(codefile == NULL) {
	    printf("File missing!\n");   
		exit(1);             
	}

	fseek(codefile, 0L, SEEK_END);
	filesize = ftell(codefile)+1;
	rewind(codefile);
	
	code = (char*) calloc(filesize,sizeof(char));

	while (fgets(&filebuffer,255,codefile)!=NULL) {
		strcat(code, filebuffer);
	}
	
	// end of file reading section
	// statement processing time

	int statementcount = 1;
	int statementindex = 0;
	char* statementbuffer;
	
	for (int i=0;i<filesize;i++){
		if (code[i]==10) {
			statementcount++;
		}
	}
	
	char* stringstatements[statementcount];
	struct statement statements[statementcount];
	
	statementbuffer = strtok(code, "\n");
	
	while( statementbuffer != NULL ) {
		stringstatements[statementindex] = (char*) calloc(statementcount,sizeof(char));
		strcpy(stringstatements[statementindex],statementbuffer);
	    statementbuffer = strtok(NULL, "\n");
		statementindex++;
	}
	
	for (int i=0;i<statementcount;i++) {
		statementindex = 0;
		statements[i].constant = typeprocess(stringstatements[i]+8);
		statementbuffer = strtok(stringstatements[i]," ");
		while (statementbuffer != NULL&&statementindex<2) {
			switch (statementindex) {
				case 0:
					if (strcmp(statementbuffer,"owo")==0) {
						statements[i].opcode = 0;
					} else if (strcmp(statementbuffer,"Owo")==0) {
						statements[i].opcode = 1;
					} else if (strcmp(statementbuffer,"oWo")==0) {
						statements[i].opcode = 2;
					} else if (strcmp(statementbuffer,"OWo")==0) {
						statements[i].opcode = 3;
					} else if (strcmp(statementbuffer,"owO")==0) {
						statements[i].opcode = 4;
					} else if (strcmp(statementbuffer,"OwO")==0) {
						statements[i].opcode = 5;	
					} else if (strcmp(statementbuffer,"oWO")==0) {
						statements[i].opcode = 6;
					} else if (strcmp(statementbuffer,"OWO")==0) {
						statements[i].opcode = 7;
					}
					break;
				case 1:
					statements[i].memory = uwutoindex(statementbuffer);
					break;
			}
	    	statementbuffer = strtok(NULL, " ");
			statementindex++;
		}
	}

	// statement parsing done here, now time for the interpreter

	struct variable memory[8];
	
	for (int programcount = 0; programcount < statementcount; programcount++) {
		struct statement statement = statements[programcount];
		switch (statement.opcode) {
			case 0:
				memory[statement.memory] = statement.constant;
				break;
			case 1:
				switch (statement.constant.type) {
					case 'i':
						memory[statement.memory].integer = memory[statement.memory].integer + statement.constant.integer;
					case 'f':
						memory[statement.memory].floatval = memory[statement.memory].floatval + statement.constant.floatval;
				}
				break;
			case 2:
				switch (statement.constant.type) {
					case 'i':
						memory[statement.memory].integer = memory[statement.memory].integer - statement.constant.integer;
					case 'f':
						memory[statement.memory].floatval = memory[statement.memory].floatval - statement.constant.floatval;
				}
				break;
			case 3:
				switch (statement.constant.type) {
					case 'i':
						memory[statement.memory].integer = memory[statement.memory].integer * statement.constant.integer;
					case 'f':
						memory[statement.memory].floatval = memory[statement.memory].floatval * statement.constant.floatval;
				}
				break;
			case 4:
				switch (statement.constant.type) {
					case 'i':
						memory[statement.memory].integer = memory[statement.memory].integer / statement.constant.integer;
					case 'f':
						memory[statement.memory].floatval = memory[statement.memory].floatval / statement.constant.floatval;
				}
				break;
			case 5:
				switch (statement.constant.type) {
					case 'i':
						memory[statement.memory].integer = pow(memory[statement.memory].integer, statement.constant.integer);
					case 'f':
						memory[statement.memory].floatval = pow(memory[statement.memory].floatval,statement.constant.floatval);
				}
				break;
			case 6:
				switch (memory[statement.memory].type) {
					case 'i':
						printf("%i\n",memory[statement.memory].integer);
						break;
					case 'f':
						printf("%f\n",memory[statement.memory].floatval);
						break;
					case 's':
						printf("%s\n",memory[statement.memory].string);
						break;
				}
				break;
			case 7:
				printf("CONDJUMP");
				break;
		}
	}
	
	//cleanup
	
	fclose(codefile);
	return 0;
}
