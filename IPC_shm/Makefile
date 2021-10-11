all:shm_read shm_write
shm_read:shm_read.c
	gcc $^ -o $@
shm_write:shm_write.c
	gcc $^ -o $@
.PHONY:clean
clean:
	rm -f shm_read shm_write
