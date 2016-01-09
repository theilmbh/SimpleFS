/* device.c 						   */
/* Interface to a virtual block device */
#include <stdlib.h>
#include <stdio.h>

#include "device.h"

#define DEV_MAJOR 8
#define BYTESPERBLOCK 1024
#define NR_BLOCKS 1024

/* Open a block device */
int dev_open(sfs_dev_t device)
{
	/* First check major number is correct */
	if(device.major != DEV_MAJOR) {
		return -1;
	}

	/* Try to open disk file */
	dev_fd = fopen("disk.sfs", "w");
	if(dev_fd == NULL) {
		return -1;
	}

	return 0;
}

/* Close a block device */
int dev_close(sfs_dev_t device)
{
	fclose(dev_fd);
	return 0;
}

/* Read a block from a block device */
int dev_read(sfs_dev_t device, long int block_num, char *buf)
{
	/* Check if block_num is sane */
	if(block_num < 0 | block_num > NR_BLOCKS) {
		printf("DEVICE: 'block_num' does not make sense. 'block_num'=%d", block_num);
	}
	/* Convert block num to file offset */
	long int offset = block_num_to_offset(block_num);

	/* seek to file position */
	fseek(dev_fd, offset, SEEK_SET);

	/* Read in block */
	size_t n = fread(buf, sizeof(char), BYTESPERBLOCK, dev_fd);
	if(n != BYTESPERBLOCK){
		printf("Unable to read block-sized chunk from the disk file\n");
		return -1;
	}
	return 0;
}

/* Write a block from a block device */
int dev_write(sfs_dev_t device, long int block_num, char *buf)
{
	printf("DEVICE: 'write' not implemented\n");
	return 0;
}

long int block_num_to_offset(long int block_num) {
	return block_num*BYTESPERBLOCK;
}