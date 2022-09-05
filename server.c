#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>
#define MAX 5
#define key1 123
#define key2 456

typedef struct Dict{
	char PL[256];
	char EN[256];
}Dict;

typedef struct Stat{
	long type;
	char data[256];
}Stat;

Dict dictionary[MAX] = {
	{"Tak", "Yes"},
	{"Nie", "No"},
	{"Dzieki", "Thanks"},
	{"Prosze", "Please"},
	{"Moze", "Maybe"}
};

char* translate(char*);
void showDict();

int main(){

	//delete queues
	msgctl(key1, IPC_RMID, 0);
	msgctl(key2, IPC_RMID, 0);

	showDict();
	
	Stat statement;
	int que1, que2;
	
	//create queues	
	que1 = msgget(key1, 0777|IPC_CREAT);
	que2 = msgget(key2, 0777|IPC_CREAT);

	while(1){
		//sleep(5);
		msgrcv(que1, &statement, 256 * sizeof(char), 0, 0); //any type
		printf("PID(%ld), data: %s\n", statement.type, statement.data);
		//sleep(5);
		strcpy(statement.data, translate(statement.data));
		msgsnd(que2, &statement, 256 * sizeof(char), 0);
	}

	return 0;
}

char* translate(char* word){
	for(int i = 0; i < MAX; i++){
		if((strcmp(word, dictionary[i].PL)) == 0){
			return dictionary[i].EN;
		}
	}
	return "I dont know that word";
}

void showDict(){
	for(int i = 0; i < MAX; i++){
		printf("PL: %12s -> EN: %-12s\n", dictionary[i].PL, dictionary[i].EN);
	}
}
