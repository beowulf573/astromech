#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define SHARED_FB "shared_fb"

int main(int argc, char **argv) 
{
    void *shm_buf;
    int shm_fd = shm_open(SHARED_FB, O_RDWR, S_IRUSR | S_IWUSR);
    if(shm_fd > 0) {
        shm_buf = mmap(NULL, 320*200*3, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, (off_t)0);
        if(shm_buf == MAP_FAILED) {
            fprintf(stderr, "mmap failed: %s\n", strerror(errno));
            shm_buf = NULL;
            return 1;
        }
    }
    else {
        fprintf(stderr, "shm_open failed: %s\n", strerror(errno));
        return 1;
    }
 
    unsigned char *fb = (unsigned char *)shm_buf;

    int color = 0;
    while(1) {
        color += 8;
        color = color % 255;
        sleep(1);

        unsigned char *data = fb;
        for(int y = 0; y < 200; y++) {
            for(int x = 0; x < 320; x++) {
                *data++ = color;
                *data++ = color;
                *data++ = color;
            }
        }

    }

    munmap(shm_buf, 320*200*3);
    close(shm_fd);
    return 0;
}
