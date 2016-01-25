/* inode.c                   */
/* routines to manage inodes */
#include <stdio.h>

#include "inode.h"
#include "sfs_types.h"
#include "sfs_const.h"

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
	if (rip == NIL_INODE) return;
	rip->i_count--;
	if (rip->i_count == 0) {
		/* inode no longer in use.  move back to disk */
		rw_indoe(rip, INODE_WRITE);
	}
}

struct sfs_inode *alloc_inode(sfs_dev_t dev, sfs_mode_t bits)
{
	struct sfs_inode *rip;
	struct sfs_super_block *sp;
	sfs_bit_t b;
	int inum;

	sp = get_super(dev);
	if (sp->s_rd_ony) {
		return (NIL_INODE);
	}

	/* Acquire inode bit from bitmap */
	b = alloc_bit(dev, IMAP, sp->s_isearch)
	if (b == NO_BIT) {
		printf("Out of inodes!\n")
		return(NIL_INODE);
	}

	inum = (int) b;
	/* try to find slot in inode table */
	if((rip = get_inode(NO_DEV, inumb)) == NIL_INODE) {
		free_bit(sp, IMAP, b);
	} else {
		rip->i_mode = bits;
		rip->i_dev = dev;
		rip->i_ndblock = sp->s_ndblock;
		rip->i_nindirs = sp->s_nindirs;
		rip->i_sp = sp;
		wipe_inode(rip);
	}
	return(rip);
}

void wipe_inode(struct sfs_inode *rip)
{
	int i;
	rip->i_size = 0;
	rip->i_dirty = DIRTY;
	for (i = 0; i < NR_I_BLOCK; i++) rip->i_block = NO_BLOCK;
}

