#include "defines.h"
#include "serial.h"
#include "lib.h"

volatile int value = 10;
int value3;

static int init(void)
{
	extern int erodata;
	extern int data_start,edata;
	extern int bss_start,ebss;

	memcpy(&data_start,&erodata,(long)&edata - (long)&data_start);
	memset(&bss_start,0,(long)&ebss - (long)&bss_start);
	
	serial_init(SERIAL_DEFAULT_DEVICE);

	return 0;
}

int main(void)
{
	init();

	int value2 = 30;

	puts("Hello Kozos\n");
	
	putxval(value,0);
	puts("\n");

	value = 20;

	putxval(value,0);
	puts("\n");

	putxval(value2,0);
	puts("\n");
	
	value2 = 40;

	putxval(value2,0);
	puts("\n");
	
	putxval(value3,0);
	puts("\n");

	value3 = 50;

	putxval(value3,0);
	puts("\n");


	while(1)
		;

	return 0;
}

