#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>
#define key1 123
#define key2 456

typedef struct Stat{
	long type;
	char data[256];
}Stat;

int main(){

	Stat statement;
	int que1, que2;
	char word[256];

	que1 = msgget(key1, 0777);
	que2 = msgget(key2, 0777);

	scanf("%s", word);
	strcpy(statement.data, word);
	statement.type = getpid();

	msgsnd(que1, &statement, 256 * sizeof(char), 0);

	msgrcv(que2, &statement, 256 * sizeof(char), getpid(), 0);
	
	printf("PL: %s -> EN: %s\n", word, statement.data);

	return 0;
}
