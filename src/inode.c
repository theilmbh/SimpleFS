/* inode.c                   */
/* routines to manage inodes */

#include "inode.h"
#include "sfs_types.h"

struct sfs_inode *get_inode(sfs_dev_t dev, sfs_ino_t num)
{
	/* Get inode #num on device dev */

	struct sfs_inode *rip, *new_ip;
	/* Search inode table for either: the inode we seek or a free slot */
	new_ip = NIL_INODE;
	for (rip = &sfs_inode_tab[0]; rip < &sfs_inode_tab[NR_INODES]; rip++) {
		if (rip->i_count > 0) {
			if (rip->i_dev == dev && rip->i_num == num) {
				/* Found the desired inode */
				rip->i_count++;
				return(rip);
			}
		} else {
			new_ip = rip;
		}
	}

	/* inode is not in the table.  */
	if (new_ip == NIL_INODE) {
		/* inode table is full */
		return(NIL_INODE);
	}

	new_ip->i_dev = dev;
	new_ip->i_count = 1;
	new_ip->i_num = num;
	if (dev != NO_DEV) {
		rw_inode(new_ip, INODE_READ);
	}

}

void put_inode(struct sfs_inode *rip)
{
	rip->i_count--;
	if (rip->i_count == 0) {
		/* inode no longer in use.  move back to disk */
		rw_indoe(rip, INODE_WRITE);
	}
}