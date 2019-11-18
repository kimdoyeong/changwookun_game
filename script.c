#include <stdio.h>
#include <Windows.h>
#include "script.h";

FILE* fp;
char speacker[20];

void loadScript() {
	fp = fopen("script.txt", "r");
}
char* getSpeaker() {
	return speacker;
}
void scriptNext() {
	char c;
	int cnt = 0;
	
	int kr_flag = 0;
	while (1) {
		fread(&c, sizeof(char), 1, fp);
		if (c == '_') {
			printf("\n");
			break;
		}

		printf("%c", c);
		
		if (c == '\n') {
			Sleep(100);
			continue;
		}
		if (!kr_flag && c < 0) {
			kr_flag = 1;
		}
		else {
			kr_flag = 0;
			Sleep(50);
		}
	}
}