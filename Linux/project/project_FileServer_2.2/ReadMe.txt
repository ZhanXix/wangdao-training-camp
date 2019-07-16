by zhanxix

****************************************
*注意事项*
1.客户端上传和下载的文件都必须在客户端的files文件夹里面，服务器端亦然。
2.由于文件夹和文件信息都是用数据库记录的，所以无法操作数据库未记录的内容，保证安全性。
3.客户端和服务器端的ip、端口、最大线程数等配置都写在conf文件夹配置文件里，写好配置文件后，直接运行程序即可，不需要添加其他参数。
****************************************
*更新日志*

【1.0】--2019/7/15
完成第一期所有功能
*功能概述：
编写服务器端，服务器端启动，然后启动客户端，通过客户端可以输入以下命令操作：
1.cd dir 进入对应目录dir，文件夹名可多层嵌套；..表示上一层文件
2.ls 列出当前目录文件
3.puts file 将本地文件file上传至服务器
4.gets file 下载服务器文件file到本地
5.remove file 删除服务器上文件file
6.pwd 显示目前所在路径
7.exit 退出
8.help 显示帮助
9.其他命令会提示命令错误

【2.0】--2019/7/15
修改：
1.修改了一些bug
2.整理了server端的程序结构，将头文件移到include文件夹中，将Makefile和可执行文件移到bin文件夹中
3.合并了thread_pool和work_queue文件
4.修改了help命令输出的功能
添加功能：
1.mkdir dir 在当前目录添加文件夹dir
2.rmdir dir 在当前目录删除文件夹dir（文件夹需要为空）
3.服务器端断开时，客户端也会断开

【2.1】--2019/7/15
2017/7/15
添加功能：
1.密码验证（使用数据库表user_list存储加密密码）
修改：
1.修改了大部分线程command系列函数，使用户只能操作自己名下的文件

【2.2】--2019/7/15-16
修改：
1.用md5存储文件名，文件目录使用虚拟目录,实现极速秒传
2.不再另起子进程下载和上传文件，直接采用原子线程
添加功能：
1.日志记录(在conf文件夹下的log.txt，待以后改成数据库记录)

【2.3]计划中
3.断点续传
4.mmap


****************************************
*数据库初始配置*
create database file_server_info;
use file_server_info;

*文件信息*

create table file_list(
	code int auto_increment NOT NULL,
	precode int NOT NULL,
	filename varchar(40) NOT NULL,
	filesize int NOT NULL,
	filetype char(1) NOT NULL,
	MD5 char(100),
	owner varchar(20) NOT NULL,
	PRIMARY KEY(code)
	);

*用户信息*
create table user_list(
	ID int auto_increment NOT NULL,
	username varchar(40) NOT NULL,
	salt char(12) NOT NULL,
	passwd char(100) NOT NULL,
	PRIMARY KEY(ID)
	);
    
****************************************

用户名	密码
test	test
xiaoming	123