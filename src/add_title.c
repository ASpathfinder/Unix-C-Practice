#include "../include/apue.h"
#include "../include/apueerror.h"
#include <fcntl.h>

#define BUFFSIZE 4096

char * title = "HellO_WOrld\nawdawdwadwadwa dwa\n"; 
char read_buff[BUFFSIZE];

int get_file_size(int fd);

int main(int argv, char *argc[]) {
	char * title_ptr = malloc(strlen(title_ptr) + 1);
	strcpy(title_ptr, title);
	printf("%s\n", title_ptr);
	int fd = open(argc[1], O_RDONLY);
	if(fd == -1) {
		err_sys("打开文件失败\n");
	}
	int file_size = get_file_size(fd);
	printf("%s 文件大小为 %d Byte\n", argc[1], file_size);
	//printf("title_ptr's length: %d %s\n", strlen(title_ptr), title_ptr);
	//printf("title's length: %d\n", strlen(title));
	char * result_file_ptr = realloc(title_ptr, strlen(title_ptr) + 1 + file_size + BUFFSIZE);
	//printf("test_ptr长度为: %d\n", strlen(test_ptr));
	//printf("result_file_ptr: %s\n", result_file_ptr);
	lseek(fd, 0, SEEK_SET);
	char * file_start_loc = result_file_ptr + strlen(title);
	int read_size = BUFFSIZE, last_read_size = 0;
	int buff_size_before;
	int index = 0;
	while(read_size) {
		read_size = read(fd, read_buff, BUFFSIZE);
		if(read_size == -1) {
			err_sys("读取错误\n");
		}
		if(read_size == 0) {
			printf("Break Loop\n");
			break;
		}
		read_buff[read_size] = '\0';
		index++;
		buff_size_before = strlen(result_file_ptr);
		strcpy(file_start_loc + last_read_size, read_buff);
		last_read_size += read_size;
		printf("[%d] result_file_ptr size: %d + %d = %d\n", index, buff_size_before, read_size, strlen(result_file_ptr));
	}
	printf("\nlast buffer content: %s\n\n", read_buff);
	printf("result_file_ptr size: %d\n", strlen(result_file_ptr));

	int new_file_fd = creat(argc[2], FILE_MODE);
	if(new_file_fd == -1) {
		err_sys("创建文件失败\n");
	}
	int write_byte;
	write_byte = write(new_file_fd, result_file_ptr, strlen(result_file_ptr));
	printf("写入 %d 字节\n", write_byte);
	return 0;
}

int get_file_size(int fd) {
	int read_size;
	int file_size = 0;
	int i = 0;
	char buff[BUFFSIZE];
	do{
		read_size = read(fd, buff, BUFFSIZE);
		file_size += read_size;
		if(read_size == -1) {
			err_sys("读取错误\n");
		}
		buff[read_size] = '\0';
		//printf("buff[%d]: \n%s", ++i, buff);
	} while(read_size);
	return file_size;
}
