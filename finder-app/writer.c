#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    openlog("writer", LOG_PID, LOG_USER);
    if (argc != 3) {
        syslog(LOG_ERR, "Expected a file path and a string");
        fprintf(stderr, "Usage: %s writefile writestr\n", argv[0]);
        closelog();
        return 1;
    }
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        syslog(LOG_ERR, "Cannot open %s: %s", argv[1], strerror(errno));
        closelog();
        return 1;
    }
    const char *cursor = argv[2];
    size_t remaining = strlen(cursor);
    while (remaining) {
        ssize_t count = write(fd, cursor, remaining);
        if (count < 0 && errno == EINTR) continue;
        if (count <= 0) {
            syslog(LOG_ERR, "Cannot write %s: %s", argv[1], count < 0 ? strerror(errno) : "zero-byte write");
            close(fd);
            closelog();
            return 1;
        }
        cursor += count;
        remaining -= (size_t)count;
    }
    if (close(fd) == -1) {
        syslog(LOG_ERR, "Cannot close %s: %s", argv[1], strerror(errno));
        closelog();
        return 1;
    }
    syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);
    closelog();
    return 0;
}
