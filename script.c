#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "script.h";

typedef struct __Choice {
	int transition;
	char choice[100];
	char afterChoice[100];
} Choice;

FILE* fp;
char c;
int next = 1;
Choice choices[100];
char endings[5][1000] = {
	"��â�� ���� ����� �������� �������̿��� ����� 2D�� ���� 3D�� �����ϰ� �Ǿ����ϴ�.\nâ�찡 ��� �����ϴ� ���ڰ� ����ٴ� ����ε���, ���ڸ� ���� ������ �մϴ�\n���ϸ��� ������ ������ �Ϸ����� �� ��� ������ ���ٴ� ����ε�,\n2D�� �����ϴ� �ͺ��ٴ� �����Ű���?\n[ENDING 1: HAPPY END]",
	"��â�� ���� ����� �������� �������̿��� ����� 2D�� ���� 3D�� �����ϰ� �Ǿ����ϴ�.\n�׷��� ��â�찡 ��ſ��� ����� �մϴ�\n\"�ʸ� �����ϰ� �Ǿ��� ���� ��;���\"\n\n��ħ �޻��� ���� �����ϴ� ��\n\"�� ���?\"\n���� �ߴ� ��â�찡 ������ �� ���� ���´�\n�׷� �̰Ÿ� �Ȱ��� ���� �ູ�ϴ� \n[ENDING 2: BED END]",
	"â��� ������ ���� ������ �ʴ� ����Դϴ�. �͸��� Į���� ���԰ŵ��\n[ENDING 3: BAD END]"
};
int ei = 0;
int choicesI = -1;
int intimacy = 0;

int hasNext() {
	return next;
}
void loadScript() {
	fp = fopen("script.txt", "r");
}
void cleanUpScript() {
	fclose(fp);
}
int _isEmptyLine(char* str) {
	return strcmp(str, "\n") == 0;
}
void _printStr(char* str) {
	int kr_flag = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		printf("%c", str[i]);
		if (!kr_flag && str[i] < 0) {
			kr_flag = 1;
			continue;
		}
		if (kr_flag) kr_flag = 0;
		Sleep(33);
	}
}
void _choiceRegister(Choice* c, char* str) {
	int isInBracket = 0;
	char choice[100];
	int ci = 0;
	int transition = 1;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '(') {
			isInBracket = 1;
			continue;
		}
		if (str[i] == ')') {
			isInBracket = 0;
			continue;
		}
		if (str[i] == '>') continue;
		if (i > 0 && str[i - 1] == '>' && str[i] == ' ') continue;

		if (isInBracket) {
			if (str[i] == '-') transition = -1;
			if (str[i] >= '0' && str[i] <= '9') {
				transition *= str[i] - '0';
			}
			continue;
		}
		if (str[i] == '\n') continue;
		choice[ci++] = str[i];
	}

	choice[ci] = '\0';
	strcpy(c->choice, choice);
	c->transition = transition;
}
void _afterChoiceRegister(Choice* c, char* str) {
	char afterChoice[100];
	int ci = 0;
	int flag = 1;
	for (int i = 0; str[i] != '\0'; i++) {
		if (flag && (str[i] == ' ' || str[i] == '\t')) {
			continue;
		}
		else {
			flag = 0;
		}
		if (str[i] == '\n') continue;
		afterChoice[ci++] = str[i];
	}
	afterChoice[ci] = '\0';
	strcpy(c->afterChoice, afterChoice);
}
void scriptNext() {
	int break_flag = 0;
	Choice c;

	char str[100];
	choicesI = -1;
	while (next) {
		if (feof(fp)) {
			next = 0;
			break;
		}

		fgets(str, 100, fp);
		if (_isEmptyLine(str)) {
			break;
		}
		if (str[0] == '>') {
			if (choicesI != -1) {
				choices[choicesI] = c;
			}
			strcpy(c.afterChoice, "");
			choicesI++;

			_choiceRegister(&c, str);
			continue;
		}
		if ((str[0] == ' ' && str[1] == ' ') || str[0] == '\t') {
			_afterChoiceRegister(&c, str);
			continue;
		}
		_printStr(str);
	}
	if (choicesI != -1) {
		choices[choicesI] = c;
		choicesI++;
	}
}
int printChoices() {
	if (choicesI == -1) {
		return 0;
	}
	int i;
	for (i = 0; i < choicesI; i++) {
		printf("%d. %s\n", i+1, choices[i].choice);
	}
	printf("\n");
	int flag = 1;
	while (flag) {
		char c = getch();
		if (c < '1' || c > '9') {
			continue;
		}
		if (c - '0' > i) {
			continue;
		}
		flag = 0;
		Choice ci = choices[c - '0' - 1];
		if (strcmp(ci.afterChoice, ""))
			printf("\"%s\"\n\n", ci.afterChoice);
		
		intimacy += ci.transition;
		if (ci.transition > 0) {
			printf("ģ�е��� %d ����߽��ϴ�.", ci.transition);
		}
		else if (ci.transition < 0) {
			printf("ģ�е��� %d �϶��߽��ϴ�.", ci.transition * -1);
		}
		else {
			printf("ģ�е��� �״�� �����˴ϴ�.");
		}
		printf("\n���� ģ�е�: %d", intimacy);
		printf("\n\n");
	}
	return 1;
}
void playEnding() {
	int end = 0;
	if (intimacy >= 15) {
		end = 1;
	}
	else if (intimacy <= 6) {
		end = 2;
	}

	int kr_flag = 0;
	for (int i = 0; endings[end][i] != '\0'; i++) {
		char c = endings[end][i];
		printf("%c", c);
		if (c < 0 && !kr_flag) {
			kr_flag = 1;
			continue;
		}
		if (kr_flag) kr_flag = 0;
		if (c == '\n') getch();
		Sleep(33);
	}
}