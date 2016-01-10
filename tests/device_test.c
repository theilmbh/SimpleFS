/* device_test.c 					   			*/
/* To test virtual block device in/out 			*/
/*												*/
/*  open a block device 						*/
/* 	open a device that does not exists			*/
/*  read an arbitrary block						*/	
/*  read a block that does not exists			*/
/*  write an arbitrary block					*/
/* 	write an arbitary block that does not exist */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "device.h"

#define TEST_SUCCESS 1
#define TEST_FAIL 0

typedef int test_result_t;

void open_block_device_test();
void report_test(char* name, test_result_t outcome);

void open_block_device_test() {
	
	char *test_name = "Open Block Device";
	sfs_dev_t device;
	device.major = 8;
	device.minor = 0;

	int return_code = dev_open(device);
	if(!return_code) {
		report_test(test_name, TEST_SUCCESS);
	}
	else {
		report_test(test_name, TEST_FAIL);
	}
	dev_close(device);

}

void open_invalid_block_device_test() 
{

}

void rw_test_write(char* random_int_block, int block_num)
{
	sfs_dev_t device;
	device.major = 8;
	device.minor = 0;

	int return_code = dev_open(device);
	return_code = dev_write(device, block_num, (char*)random_int_block);
	dev_close(device);


}

void rw_test_read(char* random_int_block, int block_num)
{
	sfs_dev_t device;
	device.major = 8;
	device.minor = 0;

	int return_code = dev_open(device);

	char* read_buf = malloc(BYTESPERBLOCK*sizeof(char));
	return_code = dev_read(device, block_num, read_buf);
	dev_close(device);
	if(memcmp(read_buf, random_int_block, BYTESPERBLOCK)==0) {
		report_test("ReadWrite", TEST_SUCCESS);
	}

}

void report_test(char* name, test_result_t outcome) {
	printf(name);
	if(outcome) {
		printf(" Test was success\n");
	}
	else {
		printf(" Test was fail\n");
	}
}

char *generate_random_block()
{
	
	char *random_block = (char*)malloc(BYTESPERBLOCK);
	int i;
	for(i=0; i< BYTESPERBLOCK; i++) {
		random_block[i] = rand() % 128;
	}
	return random_block;
}

int main()
{
	srand(time(NULL));
	open_block_device_test();
	char* random_block = generate_random_block();
	int block_num = rand() % NR_BLOCKS;
	rw_test_write(random_block, block_num);
	rw_test_read(random_block, block_num);
	
	return 0;
}