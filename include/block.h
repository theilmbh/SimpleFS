/* block.h - definitions for block buffer */
/* Brad Theilman 01/2016 */


#include "sfs_const.h"
#include "sfs_types.h"

/* Block Buffer*/
struct sfs_block_buf_t {
	/* Data portion */
	union {
		char b_data[BYTESPERBLOCK];
		struct sfs_directory b_dir[NR_DIR_ENTRIES];
		struct sfs_inode b_inode[INODES_PER_BLOCK];
		sfs_bitchunk_t b_bitmap[BITMAP_CHUNKS];
	} b;

	/* Header portion */
	struct sfs_block_buf *b_next;
	struct sfs_block_buf *b_prev;
	struct sfs_block_buf *b_hash;
	sfs_block_num_t b_blocknum;
	sfs_dev_t b_dev;
	char b_dirty;
	char b_count;
}	sfs_block_buf[NR_BUFS];

struct sfs_block_buf *sfs_buf_hash[NR_BUF_HASH];

#define NIL_BUF ((struct sfs_block_buf *) 0)

struct sfs_block_buf *front;
struct sfs_block_buf *rear;
int bufs_in_use;

#define HASH_MASK (NR_BUF_HASH - 1)
#define	BLOCK_READ 1
#define BLOCK_WRITE 0