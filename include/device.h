/* device.h    */
#ifndef DEVICE_H
#define DEVICE_H

/* Block Device Definitions */

#define NR_DEVS 16 /* Max num of open devices */

/* Define dev_t */
typedef struct dev_t {
	int major;
	int minor;
}	dev_t;

struct dev_table {
	dev_t device;
	int fd;
}	dev_table[NR_DEVS];

FILE dev_fd;