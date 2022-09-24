#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int printable_chars[98] = {
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
    0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,
    0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,
    0x75,0x76,0x77,0x78,0x79,0x7a,0x41,0x42,0x43,0x44,
    0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,
    0x4f,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,
    0x59,0x5a,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
    0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x3a,0x3b,0x3c,
    0x3d,0x3e,0x3f,0x40,0x5b,0x5c,0x5d,0x5e,0x5f,0x60,
    0x7b,0x7c,0x7d,0x7e,0x20,0x9,0xa,0xd
};

// returns 0 if isAuthorized, -1 if not
int isAuthorized(char c) {
    for (int i = 0; i < sizeof(printable_chars); i++) {
        if (printable_chars[i] == c) {
            return 1;
        }
    }
    return 0;
}

int clean_buffer(char * buffer, int buffer_size) {
    int char_index = 0;
    while (char_index != buffer_size) {
        if (! isAuthorized(buffer[char_index])) {
            buffer[char_index] = '.';
        } else if (buffer[char_index] == '\0') {
            buffer[char_index] = '.';
        }
        char_index++;
    }
    return 0;
}

int hexcat_reader(int in_fd, int out_fd) {
    char buffer[4096];
    ssize_t nbytes;
    while ((nbytes = read(in_fd, buffer, sizeof(buffer))) > 0) {
        clean_buffer(buffer, sizeof(buffer));
        if (write(out_fd, buffer, nbytes) != nbytes) {
            return -1;
        }
    }
    return (nbytes < 0) ? -1 : 0;
}


int main(int argc, char const *argv[]) {
    if (argc == 1) {
        if (hexcat_reader(0, 1) != 0) {
            fprintf(stderr, "[warn] failed to copy stdin.\n");
        }
    } else {
        for (int i = 1; i < argc; i++) {
            int fd = open(argv[i], O_RDONLY);
            if (fd < 0) {
                fprintf(stderr, "[warn] failed to open %s for reading\n", argv[i]);
            } else {
                if (hexcat_reader(fd, 1) != 0) {
                    fprintf(stderr, "[warn] failed to copy %s to stdout.\n", argv[i]);
                }
                close(fd);
            }
        }
    }
    return 0;
}
