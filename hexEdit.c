#include<stdio.h>
#include<string.h>
#include"hexEdit.h"

int main(int argc, char** argv) {
	char read[8], write[8], input[128], changed = 0;
	int result;
	long offset = 0;

	if (argc != 2) {
		printf("Usage: hexEdit [filename]\n");
		return -1;
	}

	FILE *fp = fopen(argv[1], "r+");
	if (fp == NULL) {
		printf("File not found %s\n", argv[1]);
	}

	result = readBytes(fp, read, 8);
	printBytes(read, result);
	
	// ask user for input
	// edit, goto, next, quit, help
	do {
		printf("Enter a command\n");
		fgets(input, sizeof(input), stdin); // read input
		input[strcspn(input, "\n")] = '\0'; // remove newline char
		
		if (strcmp(input, "edit") == 0) {
			// handle edit command
			printf("Not implemented yet. Sorry.\n");
		} else if (strcmp(input, "next") == 0) {
			// handle next command
			offset += 8;
			changed = 1;
			fseek(fp, offset, SEEK_SET);
		} else if (strcmp(input, "goto") == 0) {
			// handle goto command
			printf("Enter new byte offset from beginning of file: ");
			offset = getNewOffset();
			fseek(fp, offset, SEEK_SET);
			changed = 1;

		} else if (strcmp(input, "quit")) {
			// show help menu
			printHelp();
		}
		if (changed) {
			result = readBytes(fp, read, 8);
			printBytes(read, result);
			changed = 0;
		}

	} while (strcmp("quit", input));

	return 0;
}

int readBytes(FILE *ptr, char* buffer, int size) {
	int i = 0;
	int result;
	for (i; i < size; i++) {
		result = fread(&buffer[i], 1, 1, ptr); // returns 0 when no read completed
		if (!result) {
			i--; // reduce count since previous read was bad
			break; // stop reading. No more bytes to be found	
		}
	}
	return i;
}

int printBytes(char* buffer, int size) {
	for (int i = 0; i < size; i++) {
		printf("%x ", buffer[i]);
	}
	printf("| ");
	for (int i = 0; i < size; i++) {
		printf("%c ", buffer[i]);
	}
	printf("\n");
}

long getNewOffset() {
	char buffer[64];
	long newOffset;

	fgets(buffer, sizeof(buffer), stdin);
	if (!sscanf(buffer, "%d", &newOffset)) {
		printf("Unable to parse input.\n");
	}
	return newOffset;
}

void printHelp() {
	printf("Help Menu: \n");
	printf("Valid commands: edit - edit the current visible bytes\n next - show the next 8 bytes\n goto - manually enter an offset for bytes to show\n help - show this menu\n");
	printf("This menu will also show if a command is not recognized.\n");
}
