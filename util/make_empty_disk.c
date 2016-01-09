/* Make an empty disk */
/* Brad Theilman 010916 */

/* make_empty_disk BYTESPERBLOCK NBLOCKS */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if(argc != 3) {
		printf("Usage: make_empty_disk bytes_per_block nblocks\n");
		return 0;
	}

	/* get bytesperblock */
	int bytes_per_block = atoi(argv[1]);
	int nblocks = atoi(argv[2]);

	FILE *dev_fd = fopen("./disk.sfs", "w");
	int i;
	for(i=0; i<nblocks*bytes_per_block; i++) {
		fputc(0, dev_fd);
	}

	fclose(dev_fd);
	return 0;
}