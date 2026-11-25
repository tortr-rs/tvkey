/* tvkey: runs a command when the ThinkVantage button is pressed. X never sees that key, its code (360) is past
 * the 255 X can hold, so this reads it from the ThinkPad's own input device. usage: tvkey CMD [ARG]... */
#include "c.h"

struct ev { long sec, usec; unsigned short type, code; int value; };

static int buttons(void)
{
    char p[64], name[64];
    int i, fd, n;
    for (i = 0; i < 32; i++) {
        snprintf(p, sizeof p, "/sys/class/input/event%d/device/name", i);
        if ((fd = open(p, O_RDONLY)) < 0) continue;
        n = read(fd, name, sizeof name - 1);
        close(fd);
        if (n <= 0) continue;
        name[n] = 0;
        if (!strncmp(name, "ThinkPad Extra Buttons", 22)) {
            snprintf(p, sizeof p, "/dev/input/event%d", i);
            return open(p, O_RDONLY);
        }
    }
    return -1;
}

int main(int argc, char **argv)
{
    struct ev e;
    int fd;
    if (argc < 2) { fputs("usage: tvkey CMD [ARG]...\n", stderr); return 2; }
    if ((fd = buttons()) < 0) { fputs("tvkey: no ThinkPad buttons to read (thinkpad_acpi, the input group?)\n", stderr); return 1; }
    signal(SIGCHLD, SIG_IGN);
    while (read(fd, &e, sizeof e) == sizeof e)
        if (e.type == 1 && e.code == 360 && e.value == 1 && !fork()) {
            setsid();
            execvp(argv[1], argv + 1);
            _exit(127);
        }
    return 1;
}
