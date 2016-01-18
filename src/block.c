/* block.c - routines for managing the block cache */
/* Brad Theilman 01/2016 */

#include "block.h"

struct sfs_block_buf *sfs_get_block(sfs_dev_t dev, sfs_block_num_t block_num)
{
	/* Check to see if requested block is in the block cache.  If so, return its pointer
	 * If not, evict some other block and fetch the requested block 
	 */
	int b;
	struct sfs_block_buf *bp, *prev_ptr;

	if (dev != NO_DEV) {
		b = (int) block_num & HASH_MASK;
		bp = sfs_buf_hash[b];
		while (bp != NIL_BUF) {
			if (bp->b_blocknum == block_num && bp->b_dev == dev) {
	 			/* Found the right block */
	 			if (bp->b_count == 0) rm_lru(bp);
	 			bp->b_count++;
	 			return(bp);
	 		} else {
	 			bp = bp->b_hash;
	 		}
	 	}
	}

	 /* Take the oldest block */
	bp = front;
	rm_lru(bp);

	 /* Remove the block just taken from hash chain */
	b = (int) bp->b_blocknum & HASH_MASK;
	prev_ptr = sfs_buf_hash[b];
	if (prev_ptr == bp) {
		buf_hash[b] = bp->b_hash;
	} else {
		while (prev_ptr->b_hash != NIL_BUF) {
			if (prev_ptr->b_hash == bp) {
	 			prev_ptr->b_hash = bp->b_hash;	/* found the block! */
	 			break;
	 		} else {
	 			prev_ptr = prev_ptr->b_hash;	/* Move on */
	 		}
	 	}
	}

	/* Check to see if block taken is dirty.  
	 * If it is, flush all blocks from device
	 */
	if (bp->b_dev != NO_DEV) {
		if (bp->b_dirty == DIRTY) flushall(bp->b_dev);
	}

	/* fill in block details, then go get the block data from the disk */
	bp->b_dev = dev;
	bp->b_blocknum = block_num;
	bp->b_count++;
	b = (int) block_num & HASH_MASK;
	bp->b_hash = sfs_buf_hash[b]
	sfs_buf_hash[b] = bp;

	if (dev != NO_DEV) {
		rw_block(bp, BLOCK_READ);
	}
} 

void sfs_put_block(struct sfs_block_buf *bp, int block_type)
{

}

int rw_bock(struct sfs_block_buf *bp, int rw_flag)
{
	
}