#include "md5.h"
#include "file_server.h"

#define READ_DATA_SIZE	1024
#define MD5_SIZE		16
#define MD5_STR_LEN		(MD5_SIZE * 2)

// function declare
int Compute_string_md5(unsigned char *dest_str, unsigned int dest_len, char *md5_str);
int Compute_file_md5(const char *file_path, char *md5_str);

/************** main test **************/
void  md5Sum(char *md5sum,char *filename)
{
	int ret;
	char md5_str[MD5_STR_LEN + 1];
	// test file md5
	ret = Compute_file_md5(filename ,md5_str);
	if (0 == ret)
	{
		memcpy(md5sum,md5_str,strlen(md5_str));
	}
}

/**
 * compute the value of a file
 * @param  file_path
 * @param  md5_str
 * @return 0: ok, -1: fail
 */
int Compute_file_md5(const char *file_path, char *md5_str)
{
	int i;
	int fd;
	int ret;
	unsigned char data[READ_DATA_SIZE];
	unsigned char md5_value[MD5_SIZE];
	MD5_CTX md5;

	fd = open(file_path, O_RDONLY);
	if (-1 == fd)
	{
		perror("open");
		return -1;
	}

	// init md5
	MD5Init(&md5);

	while (1)
	{
		ret = read(fd, data, READ_DATA_SIZE);
		if (-1 == ret)
		{
			perror("read");
			close(fd);
			return -1;
		}

		MD5Update(&md5, data, ret);

		if (0 == ret || ret < READ_DATA_SIZE)
		{
			break;
		}
	}

	close(fd);

	MD5Final(&md5, md5_value);

	// convert md5 value to md5 string
	for(i = 0; i < MD5_SIZE; i++)
	{
		snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
	}

	return 0;
}

