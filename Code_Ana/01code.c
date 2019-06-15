#include <stdio.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define CONFIG_sys_COMPILER 0

int main (void) {

#ifndef CONFIG_sys_COMPILER
	printf("CONFIG_sys_COMPILER is not defined!\n");
#else
	printf("CONFIG_sys_COMPILER is defined!\n");

#endif

	return 0;
}
