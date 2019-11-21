#include <stdio.h>
#include "ending.h";

FILE* fp;
void initEnding() {
	fp = fopen("ending.txt", "r");
}
int isEndingTrigged() { return 1; }
void playEnd() {}