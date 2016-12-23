#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define SHARED_FB "shared_fb"

int my_fb_open() 
{
    int shm_fd = shm_open(SHARED_FB, O_RDWR, S_IRUSR | S_IWUSR);
    return shm_fd;
}

void  *my_fb_map(int shm_fd) {
    void *shm_buf;

    if(shm_fd > 0) {
        shm_buf = mmap(NULL, 320*200*3, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, (off_t)0);
        if(shm_buf == MAP_FAILED) {
            fprintf(stderr, "mmap failed: %s\n", strerror(errno));
            shm_buf = NULL;
        }
    }
    else {
        fprintf(stderr, "shm_open failed: %s\n", strerror(errno));
    }
    return shm_buf;
}

void my_fb_unmap(void *shm_buf) { 
    munmap(shm_buf, 320*200*3);
}

void my_fb_close(int shm_fd) {
    close(shm_fd);
}
