#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	char buf[20];
	int fd;
	fd = open("/dev/test", O_RDWR);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}

	read(fd, buf, 20);
	printf("<app>[%s]\n", buf);


	write(fd, (const void*)(0), 20);
	//write(fd, buf, 20);

	close(fd);
	return 0;
}

