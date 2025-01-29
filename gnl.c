#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100
#endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    static int bytes_read = 0;
    static int index = 0;
    char *line = NULL;
    int line_len = 0;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    while (1) {
        if (index >= bytes_read) {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read <= 0)
                break;
            index = 0;
        }
        while (index < bytes_read) {
            if (buffer[index] == '\n') {
                line = realloc(line, line_len + 1);
                if (!line)
                    return NULL;
                line[line_len] = '\0';
                index++;
                return line;
            }
            line = realloc(line, line_len + 1);
            if (!line)
                return NULL;
            line[line_len++] = buffer[index++];
        }
    }
    if (line_len > 0) {
        line = realloc(line, line_len + 1);
        if (!line)
            return NULL;
        line[line_len] = '\0';
        return line;
    }
    free(line);
    return NULL;
}
