#include <stdio.h>
#include "script.h"

 int main() {
	 loadScript();

	 while (hasNext()) {
		 system("cls");
		 scriptNext();
		 printChoices();
		 getch();
	 }
	 cleanUpScript();
	 playEnding();

	 return 0;
}