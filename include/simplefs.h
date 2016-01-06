/* Simple filesystem implementation */
/* Brad Theilman 2015 */

#define NR_FDS 128
#define BYTESPERBLOCK 256
#define NBLOCKSININODE 11

/* Define data structures */

/* superblock */
typedef struct sfs_superblock_t
{
	char magic;
	unsigned int n_inodes;
	unsigned int first_free_inode;
	
}sfs_superblock_t;

/* inode */
typedef struct sfs_inode_t
{

	char mode;
	unsigned int fsize;
	char in_use;
	unsigned int next_free;
	unsigned int prev_free;
	unsigned int blocks[NBLOCKSININODE];
	unsigned int direct_block;
	unsigned int indirect_block;
	char padding[6];
	
}sfs_inode_t;
