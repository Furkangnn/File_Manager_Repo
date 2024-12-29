#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h> // snprintf için
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
        // Gizli dosyaları hariç tut ('.' ile başlayanlar)
        if (entry->d_name[0] == '.') {
            continue;
        }

        // Tam dosya yolunu oluştur ve yazdır
        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", dir, entry->d_name);
        printf("%s\n", fullPath);
    }

    closedir(d);

    // İşlem başarıyla tamamlandı, log kaydı oluştur
    logOperation("List Directory", "Success");
}

void getStatInfo(const char *path) {
    struct stat fileStat;
    
    // Dosya/dizin hakkında bilgi al
    if (stat(path, &fileStat) == 0) {
        printf("File/Directory: %s\n", path);
        
        // Dosya tipi
        if (S_ISDIR(fileStat.st_mode)) {
            printf("Type: Directory\n");
        } else if (S_ISREG(fileStat.st_mode)) {
            printf("Type: Regular file\n");
        } else if (S_ISLNK(fileStat.st_mode)) {
            printf("Type: Symbolic link\n");
        } else {
            printf("Type: Other\n");
        }
        
        // Dosyanın boyutu
        printf("Size: %ld bytes\n", fileStat.st_size);
        
        // Dosyanın son erişim zamanı
        printf("Last accessed: %ld\n", fileStat.st_atime);
        
        // Dosyanın son yazma zamanı
        printf("Last modified: %ld\n", fileStat.st_mtime);
        
        // Dosyanın izinleri
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



// Dizin açma fonksiyonu
void openDirectory(const char *dir) {
    // Dizin açılıyor
    DIR *d = opendir(dir);
    if (d == NULL) {
        // Dizin açılamazsa hata mesajı
        perror("Error opening directory");
        return;
    }

    printf("Directory '%s' opened successfully.\n", dir);

    // Dizin içeriğini okuma
    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        // Dosya adını ekrana yazdır
        // (Gizli dosyalar hariç)
        if (entry->d_name[0] != '.') {
            printf("%s\n", entry->d_name);
        }
    }

    // Dizin kapatılıyor
    closedir(d);
}


void renameFileOrDirectory(const char *oldName, const char *newName) {
    // rename fonksiyonu ile dosya veya dizin adı değiştirme işlemi yapılır
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

