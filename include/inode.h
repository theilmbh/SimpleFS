/* inode.h 	*/
/* Definitions of inode data structure and inode table */
/* Brad Theilman 011016 */

#ifndef SFS_INODE_H
#define SFS_INODE_H

#include "sfs_types.h"

/* inode definition */

/* inode table */
struct sfs_inode {
	sfs_mode_t i_mode;
	sfs_uid_t i_uid;
	f_size_t i_size;
	block_num_t i_block[NR_I_BLOCK];

	/* in-memory fields */
	sfs_dev_t i_dev;
	sfs_ino_t i_num;
	int i_count; /* 0 if this entry is free */
	int i_ndblock;
	int i_nindirs;
	char i_dirt;
	char i_seek
} sfs_inode_tab[NR_INODES];

/* The disk version of the inode */
struct __attribute__ ((__packed__)) sfs_disk_inode {
	sfs_mode_t i_mode;
	sfs_uid_t i_uid;
	sfs_f_size_t i_size;
	sfs_block_num_t i_block[NR_I_BLOCK];
};

#define NIL_INODE ((struct sfs_inode *) 0)

#endif