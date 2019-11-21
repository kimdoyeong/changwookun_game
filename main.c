#include <stdio.h>
#include "script.h"
#include "ending.h"

 int main() {
	 loadScript();
	 //initEnding();
	 while (hasNext()) {
		 system("cls");
		 scriptNext();
		 printChoices();
		 getch();
		 
	 }
}