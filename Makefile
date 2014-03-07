object=main.o GetAccessToken.o Blog.o
CFLAGS=$(shell pkg-config --libs libcurl gtk+-3.0 --cflags gtk+-3.0)
xiaonei-gtk:$(object)
	gcc -o xiaonei-gtk $(object) $(CFLAGS) -g
main.o: AccessToken.h Blog.h
GetAccessToken.o:GetAccessToken.h
Blog.o:Blog.h AccessToken.h
clean:
	rm *.o;rm *~;rm xiaonei-gtk;rm result.html;rm blog_info.json person_one_blog
