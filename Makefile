g:
	gcc client.c my_protocol.c -o client -lwayland-client
k:
	gcc server.c my_protocol.c -o server -lwayland-server