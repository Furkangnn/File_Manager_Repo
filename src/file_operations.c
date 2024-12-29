#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>  // mkdir fonksiyonu için
#include <errno.h>      // errno için
#include "file_operations.h"


void removeFile(const char *path) {
    if (unlink(path) == 0) {
        logOperation("Remove File", "Success");
        printf("File '%s' successfully removed.\n", path);
    } else {
        logOperation("Remove File", "Error");
        perror("Error removing file");
    }
}

void copyFile(const char *source, const char *destination) {
    FILE *srcFile = fopen(source, "rb");
    if (srcFile == NULL) {
        perror("Error opening source file");
        return;
    }

    FILE *dstFile = fopen(destination, "wb");
    if (dstFile == NULL) {
        perror("Error opening destination file");
        fclose(srcFile);
        return;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        fwrite(buffer, 1, bytesRead, dstFile);
    }

    fclose(srcFile);
    fclose(dstFile);
    logOperation("Copy File", "Success");
    printf("File copied from '%s' to '%s'.\n", source, destination);
}

void displayFile(const char *path) {
    // Dosyayı okuma modunda açıyoruz
    FILE *file = fopen(path, "r");
    
    // Dosya açılmadıysa hata mesajı basıyoruz
    if (file == NULL) {
        perror("Error opening file");
        printf("Failed to open file: %s\n", path);  // Hata hakkında daha fazla bilgi
        return;
    }

    // Dosya içeriğini okuma ve ekrana yazdırma
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);  // Dosyadaki her karakteri ekrana yazdırıyoruz
    }

    fclose(file);  // Dosyayı kapatıyoruz
    logOperation("Display File", "Success");  // İşlem kaydını tutuyoruz
}


void searchFile(const char *dir, const char *filename) {
    DIR *d;
    struct dirent *dirEntry;
    int found = 0; // Dosyanın bulunup bulunmadığını takip eden bayrak

    // Dizin açılıyor
    d = opendir(dir);
    if (d == NULL) {
        perror("Error opening directory");
        return;
    }

    printf("Searching for '%s' in directory '%s'...\n", filename, dir);

    // Dizin içeriğini okuma
    while ((dirEntry = readdir(d)) != NULL) {
        // Dosya adı tam olarak eşleşiyor mu kontrol et
        if (strcmp(dirEntry->d_name, filename) == 0) {
            printf("Found: %s/%s\n", dir, dirEntry->d_name);
            found = 1; // Dosya bulundu
            break;     // Tam eşleşme bulunduysa döngüden çık
        }
    }

    // Eğer hiçbir dosya bulunmadıysa "Not Found" mesajı yazdırılır
    if (!found) {
        printf("Not Found\n");
    }

    // Dizin kapatılıyor
    closedir(d);
}

// Dosya oluşturma fonksiyonu
void createFile(const char *filepath) {
    // Dosyanın bulunduğu dizin var mı kontrol et
    char dir[256];
    strncpy(dir, filepath, sizeof(dir));

    // Dosya adını almak için son '/' karakterinden sonrasını at
    char *lastSlash = strrchr(dir, '/');
    if (lastSlash != NULL) {
        *lastSlash = '\0';  // Dizin yolunu elde etmek için '/' karakterinden sonrasını sıfırla

        // Dizin mevcut mu kontrol et, değilse oluştur
        if (mkdir(dir, 0777) == -1 && errno != EEXIST) {
            perror("Error creating directory");
            return;
        }
    }

    // Dosyayı oluştur
    FILE *file = fopen(filepath, "w");  // "w" mode'u, dosya yoksa oluşturur
    if (file == NULL) {
        perror("Error creating file");
    } else {
        printf("File '%s' created successfully.\n", filepath);
        fclose(file);
    }
}

