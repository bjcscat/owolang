#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct variable {
	char type;
	float number;
	char* string;
};

struct statement {
	int opcode;
	int memory;
	struct variable constant;
};

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
	codefile = fopen("./input.omar","r");

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
		char* constant_proc = stringstatements[i]+8;

		statementindex = 0;
		
		switch (constant_proc[0]) {
			case 'n':
				statements[i].constant.type = 'n';
				statements[i].constant.number = atof(constant_proc+2);
				break;
			case 's':
				statements[i].constant.string = (char*) calloc(sizeof(constant_proc),sizeof(char*));
				strcpy(statements[i].constant.string,constant_proc+2);
				statements[i].constant.type = 's';
				break;
			case 'r':
				statements[i].constant.string = (char*) calloc(sizeof(constant_proc),sizeof(char*));
				strcpy(statements[i].constant.string,constant_proc+2);
				statements[i].constant.type = 'r';
				break;
		}
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
		if (statement.constant.type=='r') {
			struct variable referenced = memory[uwutoindex(statement.constant.string)];
			statement.constant = referenced;
		}
		switch (statement.opcode) {
			case 0:
				memory[statement.memory] = statement.constant;
				break;
			case 1:
				memory[statement.memory].number = memory[statement.memory].number + statement.constant.number;
				break;
			case 2:
				memory[statement.memory].number = memory[statement.memory].number - statement.constant.number;
				break;
			case 3:
				memory[statement.memory].number = memory[statement.memory].number * statement.constant.number;
				break;
			case 4:
				memory[statement.memory].number = memory[statement.memory].number / statement.constant.number;
				break;
			case 5:
				memory[statement.memory].number = pow(memory[statement.memory].number, statement.constant.number);
				break;
			case 6:
				
				switch (memory[statement.memory].type) {
					case 'n':
						printf("%g\n",memory[statement.memory].number);
						break;
					case 's':
						printf("%s\n",memory[statement.memory].string);
						break;
				}
				break;
			case 7:
				switch (memory[statement.memory].type) {
					case 'n':
						if (memory[statement.memory].number!=0.0) {
							programcount = statement.constant.number-2;
						}
						break;
					case 's':
						if (memory[statement.memory].string!="") {
							programcount = statement.constant.number-2;
						}
						break;
				}
				break;
		}
	}
	
	//cleanup
	
	fclose(codefile);
	return 0;
}
