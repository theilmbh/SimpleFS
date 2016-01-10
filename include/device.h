/* device.h    */
#ifndef DEVICE_H
#define DEVICE_H

#include "sfs_types.h"

/* Block Device Definitions */

#define NR_DEVS 16 /* Max num of open devices */
#define DEV_MAJOR 8
#define BYTESPERBLOCK 1024
#define NR_BLOCKS 1024

/* Define dev_t */
typedef struct sfs_dev_t {
	int major;
	int minor;
}	sfs_dev_t;

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