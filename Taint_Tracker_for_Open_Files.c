#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

// Structure to represent tainted file data
typedef struct {
    FILE *filePointer;
    char fileName[MAX_FILENAME_LENGTH];
    int tainted;  // 1 if tainted, 0 if not tainted
} TaintedFile;

// Function prototypes
void displayMenu();
void taintFile(TaintedFile *taintedFile);
void readFile(TaintedFile *taintedFile);
void writeFile(TaintedFile *taintedFile);
void exitTool();

// Function to simulate tainting a file
void taintFile(TaintedFile *taintedFile) {
    if (taintedFile->tainted == 1) {
        printf("Warning: The file %s is tainted. Any operations on it will be considered tainted.\n", taintedFile->fileName);
    } else {
        printf("Marking file %s as tainted.\n", taintedFile->fileName);
        taintedFile->tainted = 1;
    }
}

// Function to read the tainted file
void readFile(TaintedFile *taintedFile) {
    if (taintedFile->tainted == 1) {
        printf("Reading from tainted file %s...\n", taintedFile->fileName);
        char ch;
        fseek(taintedFile->filePointer, 0, SEEK_SET);  // Reset to the beginning of the file
        while ((ch = fgetc(taintedFile->filePointer)) != EOF) {
            putchar(ch);  // Output content to the console
        }
        printf("\nThe file data has been read.\n");
    } else {
        printf("File %s is not tainted. No taint detected when reading.\n", taintedFile->fileName);
    }
}

// Function to write to the tainted file
void writeFile(TaintedFile *taintedFile) {
    if (taintedFile->tainted == 1) {
        printf("Writing to tainted file %s...\n", taintedFile->fileName);
        fseek(taintedFile->filePointer, 0, SEEK_END);  // Move to the end of the file
        fprintf(taintedFile->filePointer, "Tainted Data\n");
        printf("Data has been written to the tainted file.\n");
    } else {
        printf("File %s is not tainted. No taint detected when writing.\n", taintedFile->fileName);
    }
}

// Function to display the main menu
void displayMenu() {
    int userChoice;
    TaintedFile taintedFile;

    printf("\nFile Taint Tracker\n");
    printf("1. Open and Taint a File\n");
    printf("2. Read from a File\n");
    printf("3. Write to a File\n");
    printf("4. Exit\n");

    printf("Enter your choice:");
    scanf("%d", &userChoice);
    getchar();  // Consume newline character

    switch (userChoice) {
        case 1:
            printf("Enter the filename to open and taint:");
            fgets(taintedFile.fileName, sizeof(taintedFile.fileName), stdin);
            taintedFile.fileName[strcspn(taintedFile.fileName, "\n")] = 0;  // Remove newline character

            taintedFile.filePointer = fopen(taintedFile.fileName, "r+");
            if (taintedFile.filePointer == NULL) {
                printf("Error: Could not open file %s\n", taintedFile.fileName);
                break;
            }
            taintedFile.tainted = 0;  // Initially not tainted
            taintFile(&taintedFile);
            break;

        case 2:
            if (taintedFile.filePointer != NULL) {
                readFile(&taintedFile);
            } else {
                printf("No file opened. Please open a file first.\n");
            }
            break;

        case 3:
            if (taintedFile.filePointer != NULL) {
                writeFile(&taintedFile);
            } else {
                printf("No file opened. Please open a file first.\n");
            }
            break;

        case 4:
            exitTool();
            break;

        default:
            printf("Invalid choice. Please try again.\n");
    }
}

// Exit the program
void exitTool() {
    printf("Exiting the File Taint Tracker. Goodbye!\n");
    exit(0);
}

// Main program loop
int main() {
    printf("Welcome to the File Taint Tracker\n");

    // Main program loop
    while (1) {
        displayMenu();
    }

    return 0;
}
