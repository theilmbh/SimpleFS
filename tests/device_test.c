/* device_test.c 					   			*/
/* To test virtual block device in/out 			*/
/*												*/
/*  open a block device 						*/
/* 	open a device that does not exists			*/
/*  read an arbitrary block						*/	
/*  read a block that does not exists			*/
/*  write an arbitrary block					*/
/* 	write an arbitary block that does not exist */

#include "device.h"

#define TEST_SUCCESS 1
#define TEST_FAIL 0

void open_block_device_test() {
	
	char *test_name = "Open Block Device";
	dev_t device;
	device.major = 8;
	device.minor = 0;

	int return_code = dev_open(device);
	if(!return_code) {
		report_test(test_name, TEST_SUCCESS);
	}
	else {
		report_test(test_name, TEST_FAILURE);
	}

}

void report_test(char* name, bool outcome) {
	if(outcome) {
		printf("Test was success\n");
	}
	else {
		printf("Test was fail\n");
	}
}