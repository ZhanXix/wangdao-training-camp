#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<aio.h>
#include<unistd.h>

#define BUFFER_SIZE 1024


void aio_completion_handler(sigval_t sigval)
{
	//用来获取读aiocb结构的指针
	struct aiocb *prd;
	int ret;

	prd = (struct aiocb *)sigval.sival_ptr;

	printf("hello\n");

	//判断请求是否成功
	if(aio_error(prd) == 0)
	{
		//获取返回值
		ret = aio_return(prd);
		printf("读返回值为:%d\n",ret);
	}
}

int main(int argc,char **argv)
{
	int fd,ret;
	struct aiocb rd;

	fd = open("test.txt",O_RDONLY);
	if(fd < 0)
	{
		perror("test.txt");
	}



	//填充aiocb的基本内容
	bzero(&rd,sizeof(rd));

	rd.aio_fildes = fd;
	rd.aio_buf = (char *)malloc(sizeof(BUFFER_SIZE + 1));
	rd.aio_nbytes = BUFFER_SIZE;
	rd.aio_offset = 0;

	//填充aiocb中有关回调通知的结构体sigevent
	rd.aio_sigevent.sigev_notify = SIGEV_THREAD;//使用线程回调通知
	rd.aio_sigevent.sigev_notify_function = aio_completion_handler;//设置回调函数
	rd.aio_sigevent.sigev_notify_attributes = NULL;//使用默认属性
	rd.aio_sigevent.sigev_value.sival_ptr = &rd;//在aiocb控制块中加入自己的引用

	//异步读取文件
	ret = aio_read(&rd);
	if(ret < 0)
	{
		perror("aio_read");
	}

	printf("异步读以开始\n");
	sleep(1);
	printf("异步读结束\n");



	return 0;
}
