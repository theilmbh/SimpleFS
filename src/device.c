/* device.c 						   */
/* Interface to a virtual block device */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "device.h"
#include "sfs_types.h"



/* Open a block device */
int dev_open(sfs_dev_t device)
{
	/* First check major number is correct */
	if(device.major != DEV_MAJOR) {
		return -1;
	}

	/* Try to open disk file */
	dev_fd = fopen("disk.sfs", "r+");
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
int dev_read(sfs_dev_t device, sfs_block_num_t block_num, char *buf)
{
	/* Check if block_num is sane */
	if(!check_if_valid_block(block_num)) {
		return -1;
	}
	/* Convert block num to file offset */
	long int offset = block_num_to_offset(block_num);
	printf("offset = %d\n", offset);
	/* seek to file position */
	if(fseek(dev_fd, offset, SEEK_SET)) {
		printf("fseek fail\n");
	}

	/* Read in block */
	size_t n = fread(buf, sizeof(char), BYTESPERBLOCK, dev_fd);
	if(n != BYTESPERBLOCK){
		printf("Unable to read block-sized chunk from the disk file.\n");
		printf("N bytes read was: %d\n", n);
		printf("ERRNO: %d\n", errno);
		return -1;
	}
	return 0;
}

/* Write a block from a block device */
int dev_write(sfs_dev_t device, sfs_block_num_t block_num, char *buf)
{
	
	if(!check_if_valid_block(block_num)) {
		return -1;
	}

	long int offset = block_num_to_offset(block_num);

	if(fseek(dev_fd, offset, SEEK_SET)) {
		printf("fseek fail\n");
	}

	/* write */
	size_t n = fwrite(buf, sizeof(char), BYTESPERBLOCK, dev_fd);
	if(n != BYTESPERBLOCK) {
		printf("Unable to write block-sized chunk from the disk file\n");
		return -1;
	}
	fflush(dev_fd);
	return 0;
	
}

long int block_num_to_offset(sfs_block_num_t block_num) {
	return block_num*BYTESPERBLOCK;
}

int check_if_valid_block(sfs_block_num_t block_num)
{
		/* Check if block_num is sane */
	if(block_num < 0 | block_num > NR_BLOCKS) {
		printf("DEVICE: 'block_num' does not make sense. 'block_num'=%d", block_num);
		return 0;
	}
	else
	{
		return 1;
	}
}