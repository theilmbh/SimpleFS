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
	/* Returns a block being used to the lru chain */

	if (bp == NIL_BUF) return;
	bp->b_count--; 
	if (bp->b_count != 0) return; /* Block is still in use */

	/* We (should) could check what kind of block this is, 
	 * to determine where to put it.  I'll skip that for now 
	 */
	bp->b_prev = rear;
	bp->b_next = NIL_BUF;
	if (rear == NIL_BUF) { /* block buf is empty */
		front = bp;
	} else {
		rear->b_next = bp;
	}
	rear = bp;

	/* TODO: CHECK TO SEE IF BLOCK IS 'IMPORTANT'.  IF SO, WRITE TO DISK */
	if ((block_type & SFS_WRITE_IMMED) && bp->b_dirty==DIRTY && bp->b_dev != NO_DEV) {
		rw_block(bp, BLOCK_WRITE)
	}

}

struct sfs_block_num_t alloc_block(sfs_dev_t dev, sfs_block_num_t block_num)
{
	sfs_super_block *sp;
	sfs_bit_t bit;

	sp = get_super(dev);

	bit = alloc_bit(sp, BMAP, (sfs_bit_t) block_num);
	if (bit == NO_BIT) {
		printf("No space on device!\n");
		return NO_BLOCK;
	}
	return (sfs_block_num_t) bit;
}

void free_block(sfs_dev_t dev, sfs_block_num_t block)
{
	/* Frees a block */
	sfs_super_block *sp;
	sp = get_super(dev);

	free_bit(sp, BMAP, (sfs_bit_t) block_num);

}

int rw_bock(struct sfs_block_buf *bp, int rw_flag)
{
	if (bp->b_dev != NO_DEV) {
		if (rw_flag == BLOCK_READ) {
			dev_read(bp->b_dev, bp->b_blocknum, bp->b.b_data);
		} else {
			dev_write(bp->b_dev, bp->b_blocknum, bp->b.b_data);
		}
	}

}

void rm_lru(struct sfs_block_buf *bp)
{
	struct sfs_block_buf *next_ptr, *prev_ptr;

	bufs_in_use++;
	next_ptr = bp->b_next;
	prev_ptr = bp->b_prev;

	if (prev_ptr != NIL_BUF) {
		prev_ptr->b_next = next_ptr;
	} else {
		front = next_ptr;
	}

	if (next_ptr != NIL_BUF) {
		next_ptr->b_prev = prev_ptr;
	} else {
		rear = prev_ptr;
	}
}

void flushall(sfs_dev_t dev)
{
	/* Write all dirty blocks to disk */
	struct sfs_block_buf_t *buf;
	for (buf = &sfs_block_buf[0]; buf <= &sfs_block_buf[NR_BUFS]; buf++) {
		
	}
}