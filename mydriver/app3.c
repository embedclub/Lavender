#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	char buf[20];
	int fd, count;
	fd = open("/dev/test", O_RDWR);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}

	count = read(fd, buf, 20);
	printf("<app>buf is [%s]\n", buf);


	count = write(fd, (const void*)0, 20);
	if (count == -1)
	{
		perror("write");
	}

	close(fd);
	return 0;
}

