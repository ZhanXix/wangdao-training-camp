程玄 2017/7/15
****************************************
*注意事项*
1.客户端上传和下载的文件都必须在客户端的files文件夹里面，服务器端亦然。
2.由于文件夹和文件信息都是用数据库记录的，所以无法操作数据库未记录的内容，保证安全性。
3.md5的相关函数由于不是第一期内容，所以直接套用了网上的代码，待以后重写。
4.无法上传文件夹，也无法在服务器端创建文件夹。如果试图下载文件夹，会直接报错“没有该文件”，待以后添加mkdir和rmdir功能。
5.客户端和服务器端的ip、端口、最大线程数等配置都写在配置文件里，所以运行时直接启动可执行文件即可，不需要添加其他参数。

****************************************
*数据库初始配置*

create database file_server_info;
use file_server_info;

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
    
****************************************
*更新日志*

2019/7/15
完成第一版所有功能
*功能概述：
编写服务器端，服务器端启动，然后启动客户端，通过客户端可以输入以下命令操作：
1.cd dir 进入对应目录dir，文件夹名可多层嵌套；..表示上一层文件
2.ls 列出相应目录文件
3.puts file 将本地文件file上传至服务器
4.gets file 下载服务器文件file到本地
5.remove file 删除服务器上文件file
6.pwd 显示目前所在路径
7.exit 退出
8.help 显示帮助
9.其他命令会提示命令错误
