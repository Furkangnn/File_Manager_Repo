#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h> 
#include "directory_ops.h"
#include <sys/stat.h>

void listDirectory(const char *dir) {
    DIR *d = opendir(dir);
    if (d == NULL) {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }

        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", dir, entry->d_name);
        printf("%s\n", fullPath);
    }

    closedir(d);

    logOperation("List Directory", "Success");
}

void getStatInfo(const char *path) {
    struct stat fileStat;
    
    if (stat(path, &fileStat) == 0) {
        printf("File/Directory: %s\n", path);
        
        if (S_ISDIR(fileStat.st_mode)) {
            printf("Type: Directory\n");
        } else if (S_ISREG(fileStat.st_mode)) {
            printf("Type: Regular file\n");
        } else if (S_ISLNK(fileStat.st_mode)) {
            printf("Type: Symbolic link\n");
        } else {
            printf("Type: Other\n");
        }
        
        printf("Size: %ld bytes\n", fileStat.st_size);
        
        printf("Last accessed: %ld\n", fileStat.st_atime);
        
        printf("Last modified: %ld\n", fileStat.st_mtime);
        
        printf("Permissions: %o\n", fileStat.st_mode & 0777);
    } else {
        perror("stat error");
    }
}


void createDirectory(const char *dir) {
    if (mkdir(dir, 0755) == 0) {
        logOperation("Create Directory", "Success");
        printf("Directory '%s' created.\n", dir);
    } else {
        logOperation("Create Directory", "Error");
        perror("Error creating directory");
    }
}



void openDirectory(const char *dir) {
    DIR *d = opendir(dir);
    if (d == NULL) {
        perror("Error opening directory");
        return;
    }

    printf("Directory '%s' opened successfully.\n", dir);

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        if (entry->d_name[0] != '.') {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(d);
}


void renameFileOrDirectory(const char *oldName, const char *newName) {
    if (rename(oldName, newName) == 0) {
        printf("Successfully renamed '%s' to '%s'.\n", oldName, newName);
    } else {
        perror("Error renaming file or directory");
    }
}

void removeDirectory(const char *dir) {
    if (rmdir(dir) == 0) {
        logOperation("Remove Directory", "Success");
        printf("Directory '%s' removed.\n", dir);
    } else {
        logOperation("Remove Directory", "Error");
        perror("Error removing directory");
    }
}

