#ifndef HEXEDIT
#define HEXEDIT
// helper function prototypes
int readBytes(FILE *ptr, char* buffer, int size);
int printBytes(char* buffer, int size);
long getNewOffset();
void printHelp();
#endif
