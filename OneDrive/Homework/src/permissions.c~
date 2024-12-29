#include <stdio.h>        // perror ve printf için
#include <sys/types.h>    // mode_t için
#include <sys/stat.h>     // chmod fonksiyonu için
#include <stdlib.h>       // strtol için
#include "permissions.h"

// İzin değiştirme fonksiyonu
void changePermissions(const char *path, mode_t mode) {
    if (chmod(path, mode) == -1) {
        perror("chmod error");  // Hata mesajı yazdır
    } else {
        printf("Permissions changed successfully.\n");  // Başarı mesajı yazdır
    }
}

