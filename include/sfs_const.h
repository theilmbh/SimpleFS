/* sfs_const.h */
/* constants for sfs */

#ifndef SFS_CONST_H
#define SFS_CONST_H

#define NR_INODES 128 /* number of inodes in inode table */
#define NR_I_BLOCK 8 /* Number of direct block addrs in inode */


/* Block Device Definitions */

#define NR_DEVS 16 /* Max num of open devices */
#define DEV_MAJOR 8
#define BYTESPERBLOCK 1024
#define NR_BLOCKS 1024 

#define NR_BUF_HASH 256
#define NR_BUFS 256

#endif