object=main.o GetAccessToken.o
CFLAGS=$(shell pkg-config --libs libcurl gtk+-3.0 --cflags gtk+-3.0)
application:$(object)
	gcc -o application $(object) $(CFLAGS)
main.o:main.c GetAccessToken.c
GetAccessToken.o:GetAccessToken.c
clean:
	rm *.o;rm *~;rm application;rm result.html