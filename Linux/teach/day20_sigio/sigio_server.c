#include "head.h"
#define QUESIZE  16         /* 队列大小 */ 
#define BUFSIZE  512
 
struct request {                /* client request string */ 
	char *reqstr; 
	size_t reqlen;             /* client request string len */ 
	struct sockaddr_in *peer;    /* client sending this request */ 
	socklen_t sklen; 
}; 

static struct request req_queue[QUESIZE]; 

static int idx_in; 
static int idx_out; 
static int nqueue; 

int s;                          /* 服务器端套接字 */ 
struct sockaddr_in peer_addr;      /* 客户端internet地址 */ 
static socklen_t socklen = sizeof(peer_addr); 

static void bail(const char *on_what){ 
	fputs(strerror(errno), stderr); 
	fputs(": ", stderr); 
	fputs(on_what, stderr); 
	fputc('\n', stderr); 
	exit(-1); 
} 

/* SIGIO信号处理函数*/ 
void do_sigio (int signum) 
{ 
	int z; 
	struct request *p_req; 
	char buf[BUFSIZE]; 
	printf("data is coming\n");
	for(;;){ 
		/* 保存下一个客户端请求数据报的位置索引 */ 
		p_req = &req_queue[idx_in]; 

		if(nqueue >= QUESIZE){ 
			write(STDOUT_FILENO, "request queue is full!/n", 23); 
			return; 
			         } 

		z = recvfrom(s,             /* 服务器套接字 */ 
				p_req->reqstr,          /* 接收缓存位置指针 */ 
				BUFSIZE, 
				0, 
				(struct sockaddr *)p_req->peer, /* 客户端地址指针 */ 
				&socklen); 

		if(z < 0) { 
			             /* 设置服务器套接字于非阻塞模式，因此当无新数据 
						   * 可读时，recvfrom立刻返回，并且错误代码设置为 
						   *  EWOULDBLOCK 
						   */ 
				if(errno == EWOULDBLOCK) 
					break; 
				else{ 
					write (STDOUT_FILENO, "recvfrom error!/n", 16); 
					exit(1); 
				} 
		} 
		p_req->reqstr[z]=0; 
		p_req->reqlen = z; 
		nqueue++; 

		if(++idx_in >= QUESIZE) 
			idx_in = 0; 
	} 
} 
void init_queue() 
{ 
	for(int i = 0; i < QUESIZE; i++){ 
		if((req_queue[i].reqstr = malloc(BUFSIZE)) == NULL || 
				(req_queue[i].peer = malloc(socklen)) == NULL ) 
			bail("init_queue"); 
		req_queue[i].sklen = socklen; 
	} 

	idx_in = idx_out = nqueue = 0; 
} 

/* 注册SIGIO信号处理程序 */ 
static void install_sigio() 
{ 
	struct sigaction sigio_action; 

	memset(&sigio_action, 0, sizeof(sigio_action)); 
	sigio_action.sa_flags = 0; 

	sigio_action.sa_handler = do_sigio; 

	   if (sigaction(SIGIO, &sigio_action, NULL) == -1) 
		perror("Failed to set SIGIO"); 
} 

/* 设置套接字为信号驱动I/O和非阻塞模式 */ 
void set_sockopt(int s, int flags) 
{ 
	fcntl(s, F_SETOWN, getpid()); 
	if((flags = fcntl(s, F_GETFL, 0)) < 0) 
		bail("F_GETFL error"); 
	flags |= O_ASYNC | O_NONBLOCK; 
	if(fcntl(s, F_SETFL, flags) < 0) 
		bail("F_SETFL error"); 
} 

int main(int argc, char **argv){ 
	int z; 
	char * srvr_addr = NULL; 
	int len_inet; 
	int portnumber; 
	int flags; 

	struct sockaddr_in srvaddr;    /* 服务器internet地址 */           
	char dtfmt[BUFSIZE];        /* 日期-时间结果 */ 
	time_t td;                    /* 当前时间和日期 */ 
	struct tm tv;                    /* 日期时间结构体 */ 
	sigset_t zeromask, newmask, oldmask; 
	struct request *p_req; 

	/* 
	 * 若命令行提供了作为服务器地址和端口的参数，则使用参数 
	 0      * 作为地址和端口，否则使用缺省的地址和端口 
	 */ 
	if(argc > 2){ 
		srvr_addr = argv[1]; 

		if((portnumber = atoi(argv[2]))<0){ 
			fprintf(stderr, "Usage: %s portnumber/a/n", argv[0]); 
			exit(1); 
		} 
	}else{ 
		srvr_addr = "0"; 
		portnumber = 9000; 
	} 

	/* 创建数据报套接字 */ 
	s = socket(AF_INET, SOCK_DGRAM, 0); 
	if(s == -1) 
		bail("socket()"); 

	init_queue();   /* 初始化应用数据报接收队列 */ 
	install_sigio();  /* 注册SIGIO信号处理程序 */ 
	set_sockopt(s, flags); /* 设置非阻塞和SIGIO驱动I/O模式 */ 

	/* 初始化套接字地址 */ 
	memset(&srvaddr, 0, sizeof srvaddr); 
	srvaddr.sin_family = PF_INET; 
	srvaddr.sin_port = htons(portnumber); 
	if(!inet_aton(srvr_addr, &srvaddr.sin_addr)) 
		bail("bad address."); 

	     len_inet = sizeof(srvaddr); 

	/* 
	 * 绑定套接字到指定地址和端口，于是客户端可以连接 
	 * 到该服务器 
	 */ 
	z = bind(s, (struct sockaddr *)&srvaddr, len_inet); 
	if(z == -1) 
		bail("bind()"); 

	sigemptyset(&zeromask); 
	sigemptyset(&newmask); 
	sigemptyset(&oldmask); 
	sigaddset(&newmask, SIGIO); 

	sigprocmask(SIG_BLOCK, &newmask, &oldmask); 
	for(;;) { 
		while(nqueue == 0) 
			/* unblock all and waiting for any signal */ 
			sigsuspend(&zeromask); 
		
		        /* 尽可能早解除对SIGIO 的阻塞 */ 
		        sigprocmask(SIG_SETMASK, &oldmask, NULL); 
		
		        if(idx_out > QUESIZE) 
		            idx_out = 0; 
		
		        p_req = &req_queue[idx_out++]; 
		    /* 获得当前日期和时间 */ 
		        time(&td); 
		    tv =*localtime(&td); 

		/* 
		 * 根据获得的日期时间格式字符串要求，获得当前日期 
		 * 和时间并格式化结果 
		 */ 
		strftime(dtfmt,  /* formatted result */ 
				sizeof dtfmt, 
				p_req->reqstr,      /* 输入的日期时间格式串 */ 
				&tv); 

		/* 将格式化结果返回给客户端 */ 
		z = sendto(s,            /* 服务器套接字 */ 
				dtfmt,             /* 返回结果 */ 
				strlen(dtfmt), 
				0, 
				(struct sockaddr *)(p_req->peer),   /* 对方地址 */ 
				p_req->sklen); 

		if(z < 0) 
			bail("sendto()"); 

		/* 更新临界变量，必须阻塞SIGIO信号 */ 
		sigprocmask(SIG_BLOCK, &newmask, &oldmask); 
		nqueue--; 
	} 

	close(s); 
	return 0; 
} 
