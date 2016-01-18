/* device.h    */
#ifndef DEVICE_H
#define DEVICE_H

#include "sfs_types.h"
#include "sfs_const.h"


struct sfs_dev_table {
	sfs_dev_t device;
	int fd;
}	dev_table[NR_DEVS];

FILE *dev_fd;

/* Function Prototypes */
int dev_open(sfs_dev_t device);
int dev_close(sfs_dev_t device);
int dev_read(sfs_dev_t device, sfs_block_num_t block_num, char *buf);
int dev_write(sfs_dev_t device, sfs_block_num_t block_num, char *buf);
long int block_num_to_offset(sfs_block_num_t block_num);
int check_if_valid_block(sfs_block_num_t block_num);

#endif