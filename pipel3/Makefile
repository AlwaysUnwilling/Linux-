all:fifo_write fifo_read
fifo_read:fifo_read.c
	gcc $^ -o $@
fifo_write:fifo_write.c
	gcc $^ -o $@
.PHONY:clean
clean:
	rm -f fifo_read fifo_write
