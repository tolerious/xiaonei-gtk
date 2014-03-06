object=main.o GetAccessToken.o
CFLAGS=$(shell pkg-config --libs libcurl gtk+-3.0 --cflags gtk+-3.0)
xiaonei-gtk:$(object)
	gcc -o xiaonei-gtk $(object) $(CFLAGS)
main.o:main.c GetAccessToken.c AccessToken.h
GetAccessToken.o:GetAccessToken.c
clean:
	rm *.o;rm *~;rm xiaonei-gtk;rm result.html
