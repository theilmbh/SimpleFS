/* sfs_types.h */

#ifndef SFS_TYPES_H
#define SFS_TYPES_H

typedef char sfs_mode_t;
typedef char sfs_uid_t;
typedef unsigned int sfs_f_size_t;
typedef unsigned int sfs_block_num_t;
typedef unsigned int sfs_ino_t;
typedef unsigned int sfs_bit_t


/* Define dev_t */
typedef struct sfs_dev_t {
	int major;
	int minor;
}	sfs_dev_t;


#endif
