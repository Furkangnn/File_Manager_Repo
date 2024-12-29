#include <stdio.h>
#include <string.h>
#include <sys/types.h>   
#include <stdlib.h>       
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"

void executeCommand(char *command) {
    if (strncmp(command, "slist", 5) == 0) {

        listDirectory(command + 6);
    } else if (strncmp(command, "scopy", 5) == 0) {

        char *source = strtok(command + 6, " ");
        char *destination = strtok(NULL, " ");
        copyFile(source, destination);
    } else if (strncmp(command, "sremove", 7) == 0) {

        removeFile(command + 8);
    } else if (strncmp(command, "sdircreate", 10) == 0) {

        createDirectory(command + 11);
    } else if (strncmp(command, "sdirremove", 10) == 0) {

        removeDirectory(command + 11);
    } else if (strncmp(command, "sperm", 5) == 0) {

        char *path = strtok(command + 6, " ");
        mode_t mode = strtol(strtok(NULL, " "), NULL, 8);
        changePermissions(path, mode);
    } else if (strncmp(command, "sdisplay", 8) == 0) {

        displayFile(command + 9);
    } else if (strncmp(command, "ssearch", 7) == 0) {

        char *dir = strtok(command + 8, " ");
        char *filename = strtok(NULL, " ");
        searchFile(dir, filename);
    }
    else if (strncmp(command, "sstat", 5) == 0) {

    getStatInfo(command + 6);
   } 
   else if (strncmp(command, "screate", 7) == 0) {

        createFile(command + 8);
   }
   else if (strncmp(command, "srename", 7) == 0) {

        char *oldPath = strtok(command + 8, " ");  
        char *newPath = strtok(NULL, " ");         
        
        if (oldPath && newPath) {
            renameFileOrDirectory(oldPath, newPath);  
        } else {
            printf("Invalid command format. Usage: srename <old_path> <new_path>\n");
        }
    }
  
   else {
        printf("Unknown command!\n");
    }
}


int main() {
    char command[256];

    while (1) {
        printf("Enter command: ");
        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break;
        }

        executeCommand(command);
    }

    return 0;
}
