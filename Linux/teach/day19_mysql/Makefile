con_mysql:query.c delete.c insert.c update.c
	gcc query.c -o query_mysql -I /usr/include/mysql/ -lmysqlclient
	gcc delete.c -o delete_mysql -I /usr/include/mysql/ -lmysqlclient
	gcc insert.c -o insert_mysql -I /usr/include/mysql/ -lmysqlclient
	gcc update.c -o update_mysql -I /usr/include/mysql/ -lmysqlclient
clean:
	rm query_mysql delete_mysql insert_mysql update_mysql
