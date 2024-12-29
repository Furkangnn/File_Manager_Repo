#include <stdio.h>
#include <string.h>
#include <sys/types.h>   // mode_t için
#include <stdlib.h>       // strtol için
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"

void executeCommand(char *command) {
    if (strncmp(command, "slist", 5) == 0) {
        // Dizin listeleme komutu
        listDirectory(command + 6);
    } else if (strncmp(command, "scopy", 5) == 0) {
        // Dosya kopyalama komutu
        char *source = strtok(command + 6, " ");
        char *destination = strtok(NULL, " ");
        copyFile(source, destination);
    } else if (strncmp(command, "sremove", 7) == 0) {
        // Dosya silme komutu
        removeFile(command + 8);
    } else if (strncmp(command, "sdircreate", 10) == 0) {
        // Dizin oluşturma komutu
        createDirectory(command + 11);
    } else if (strncmp(command, "sdirremove", 10) == 0) {
        // Dizin silme komutu
        removeDirectory(command + 11);
    } else if (strncmp(command, "sperm", 5) == 0) {
        // İzin değiştirme komutu
        char *path = strtok(command + 6, " ");
        mode_t mode = strtol(strtok(NULL, " "), NULL, 8);
        changePermissions(path, mode);
    } else if (strncmp(command, "sdisplay", 8) == 0) {
        // Dosya gösterme komutu
        displayFile(command + 9);
    } else if (strncmp(command, "ssearch", 7) == 0) {
        // Dosya arama komutu
        char *dir = strtok(command + 8, " ");
        char *filename = strtok(NULL, " ");
        searchFile(dir, filename);
    } 
    else if (strncmp(command, "sopen", 5) == 0) {
        // Dizin açma komutu
        openDirectory(command + 6);
    }
    else if (strncmp(command, "sstat", 5) == 0) {
    // Dosya/dizin istatistik bilgisi komutu
    getStatInfo(command + 6);
   } 
   else if (strncmp(command, "screate", 7) == 0) {
        // Dosya oluşturma komutu
        createFile(command + 8);
   }
   else if (strncmp(command, "srename", 7) == 0) {
        // Dosya veya dizin adı değiştirme komutu
        char *oldPath = strtok(command + 8, " ");  // Eski dosya veya dizin yolu
        char *newPath = strtok(NULL, " ");         // Yeni dosya veya dizin yolu
        
        if (oldPath && newPath) {
            renameFileOrDirectory(oldPath, newPath);  // Dosya veya dizin adını değiştirme fonksiyonunu çağır
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

        // Yeni satır karakterini kaldır
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break;
        }

        executeCommand(command);
    }

    return 0;
}

