all:
	$(CC) -g -o cloud_device cloud_device.c ./lib/http.c ./lib/xml.c  -I./lib
	$(CC) -g -o cloud_user cloud_user.c ./lib/http.c ./lib/xml.c  -I./lib

clean:
	-rm cloud_device
	-rm cloud_user
	find ./ -name \*~ | xargs rm -f

