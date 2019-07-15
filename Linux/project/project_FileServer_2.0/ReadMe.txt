by程玄 

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
1.一些bug
2.整理了程序结构
3.help命令输出的功能
添加功能：
1.mkdir dir 在当前目录添加文件夹dir
2.rmdir dir 在当前目录删除文件夹dir（文件夹需要为空）
3.服务器端断开时，客户端退出机制

【2.1】--2019/7/15
2017/7/15
第二期要求：
1.密码验证
2.日志记录
3.断点续传
4.mmap


****************************************
*注意事项*
1.客户端上传和下载的文件都必须在客户端的files文件夹里面，服务器端亦然。
2.由于文件夹和文件信息都是用数据库记录的，所以无法操作数据库未记录的内容，保证安全性。
3.客户端和服务器端的ip、端口、最大线程数等配置都写在conf文件夹配置文件里，写好配置文件后，直接运行程序即可，不需要添加其他参数。

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