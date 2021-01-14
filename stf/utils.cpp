#include "utils.hpp"

#include <termios.h>
#include <fcntl.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <err.h>

winsize stf::getws()
{
    winsize ws;
    int fd;

    fd = open("/dev/tty", O_RDWR);
    if (fd < 0) err(1, "/dev/tty");

    if (ioctl(fd, TIOCGWINSZ, &ws) < 0) err(1, "/dev/tty");

    close(fd);
    return ws;
}

char *stf::itostr(int n, char* b)
{
    int i = 10, t = n, g = 0;
    if (n == 0)
    {
        b[0] = '0';
        b[1] = 0;
        return b;
    }
    while(t) 
    { 
        t /= i;
        g++; 
    }
    if (n < 0)
    {
        b[0] = '-';
        n = -n;
        g++;
    }
    b[g] = 0;
    while(n) 
    { 
        b[--g] = n % i + '0'; 
        n /= i; 
    }
    return b;
}

char *stf::ftostr(const double n, char *b)
{
    itostr((int)n, b);
    int d = 0;
    while (b[++d] != 0);
    
    b[d] = '.';
    
    double z = double((double)n - (int)n);
    if (z < 0.0) z = -z;
    
    while ((float)z - (int)z > 0.001f)
    {
        z *= 10.f;
        b[++d] = ((int)z == 0) ? '0' : (int)z % 10 + '0';
    }
    
    b[d] = 0;
    return b;
}

void stf::set_mode(int want_key)
{
	static struct termios old, newt;
	if (!want_key) {
		tcsetattr(STDIN_FILENO, TCSANOW, &old);
		return;
	}
    
	tcgetattr(STDIN_FILENO, &old);
	newt = old;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

int stf::get_key()
{
	int c = 0;
	struct timeval tv;
	fd_set fs;
	tv.tv_usec = tv.tv_sec = 0;
	FD_ZERO(&fs);
	FD_SET(STDIN_FILENO, &fs);
	select(STDIN_FILENO + 1, &fs, 0, 0, &tv);
    
	if (FD_ISSET(STDIN_FILENO, &fs)) {
		c = getchar();
		set_mode(0);
	}
	return c;
}