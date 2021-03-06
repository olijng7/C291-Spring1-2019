/*
 * Heoliny Jung
 * C291
 * Prof. Adeel Bhutta
 * 2/26/2019
 * Assignment 6: Store Inventory
 */
 
/*
 * FILE RECORD FORMAT
 * idnum name quantity cost
 * idnum name ...
 */

#include<stdio.h>
#include<string.h>

//tool struct
typedef struct Tool{
        int idnum;
        char name[32];
        int quantity; //when == -1, tool has not been entered yet
        double cost;
}tool_t;

//tool array
static tool_t tools[100];

//function prototypes
void writeAllToFile(char*); //writes all tools in tools[] to file
void readAllFromFile(FILE*); //reads all tools to tools[]
void printTools(void); //prints all tools in tools[]
void printTool(int); //finds and prints one tool from tools[]
void initializeTools(void); //put -1 at all quantities in tools[]
void addTool(int id); //adds new tool at id of tools[]

int main(void){

	printf("Please input a file name:");
	char fileName[30];
	char * namePtr = fileName;
	scanf(" %29s",namePtr);
	FILE* inventoryF;

	int state = 0; //indicates read or write mode. 0 = read, 1 = write

	if((inventoryF = fopen(fileName,"a+"))==NULL){
		printf("File cannot be opened/created\n");
	}
	else{
		initializeTools();
		//readAllFromFile(inventoryF);
		while(!feof(inventoryF)){
                	int id;
                	char n[32];
                	double c;
                	int q;
                	fscanf(inventoryF,"%d %31s %d %lf \n",&id,n,&q,&c);
                	tools[id-1].idnum = id;
                	strcpy(tools[id-1].name,n);
                	tools[id-1].quantity = q;
                	tools[id-1].cost = c;
		}
        	fclose(inventoryF);
		int input = 0;
		int in;
		while(input!=4){
                    printf("Please select an option (enter a number):\n1. Display inventory\n2. Check a tool's inventory\n3. Add/modify a tool's inventory\n4. Exit\n");
                    scanf("%d",&input);
                    switch(input){
                                case 1:
                                        printTools();
                    break;
                                case 2:
                                        printf("Enter a tool ID number:");
                                        scanf("%d",&in);
                                        printTool(in);
                    break;
                                case 3:
                                        printf("Enter a tool ID number:");
                                        scanf("%d",&in);
                                        if(tools[in-1].quantity != -1)
                                                printTool(in);
					addTool(in);
                                        printTool(in);
                    break;
                                case 4: printf("Exiting...\n");
                    break;
                                default: printf("Not a valid input\n");
                        }
                }
		writeAllToFile(fileName);
                fclose(inventoryF);
        }
    return 0;
}

void initializeTools(void){
	int i;
        for(i = 0; i < 100; i++){
		tools[i].quantity = -1;
        }
}

void addTool(int id){
	tools[id-1].idnum = id;
	int q;
	double c;
	char n[32];
        printf("Enter new values:\n");
        printf("Name:");
        scanf(" %[^\n]31s",n);
        printf("Quantity:");
        scanf("%d",&q);
        printf("Cost:");
        scanf("%lf",&c);
	strcpy(tools[id-1].name,n);
	tools[id-1].quantity = q;
	tools[id-1].cost = c;
}

void readAllFromFile(FILE* filePtr){
        while(!feof(filePtr)){
		int id;
		char n[32];
		double c;
		int q;
                fscanf(filePtr,"%d %31s %d %lf \n",&id,n,&q,&c);
		tools[id-1].idnum = id;
		strcpy(tools[id-1].name,n);
		tools[id-1].quantity = q;
		tools[id-1].cost = c;
        }
	fclose(filePtr);
}

void printTools(void){
        int i;
        printf("ID  Name                            Quantity   Cost\n");
        for (i = 0; i < 100; i++){
                if(tools[i].quantity != -1){
                        printf("%03d %-31s %8d %6.2lf\n",tools[i].idnum,tools[i].name,tools[i].quantity,tools[i].cost);
		}
        }
}

void printTool(int id){
	if(tools[id-1].quantity != -1){
	        printf("ID  Name                            Quantity   Cost\n");
		printf("%03d %-31s %8d %6.2lf\n",tools[id-1].idnum,tools[id-1].name,tools[id-1].quantity,tools[id-1].cost);
	}
	else{
                printf("No tool assigned to that ID num\n");
        }
}

void writeAllToFile(char* fileName){
	FILE* filePtr;
	if((filePtr = fopen(fileName,"w"))==NULL){
		printf("File cannot be opened/created\n");
	}
	else{
		int i;
		for(i = 0; i < 100; i++){
			if(tools[i].quantity != -1)
				fprintf(filePtr,"%d %31s %d %lf\n",tools[i].idnum,tools[i].name,tools[i].quantity,tools[i].cost);
		}
	}
	fclose(filePtr);
}
