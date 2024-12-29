#include <stdio.h>        
#include <sys/types.h>    
#include <sys/stat.h>     
#include <stdlib.h>       
#include "permissions.h"


void changePermissions(const char *path, mode_t mode) {
    if (chmod(path, mode) == -1) {
        perror("chmod error");  
    } else {
        printf("Permissions changed successfully.\n");     }
}
