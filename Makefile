all: rssk8r

WARNINGS = -Wall
DEBUG = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O2

rssk8r: Makefile rssk8r.c
	$(CC) -o $@ $(WARNINGS) $(DEBUG) $(OPTIMIZE) rssk8r.c

clean:
	rm -f rssk8r

# Builder will call this to install the application before running.
install:
	echo "Installing is not supported"

# Builder uses this target to run your application.
run:
	echo "1\n2\n3\n4\n5\nbutts<item>butts\n6\n7\n8\n9\n10" #> test.xml #use this if you need a bare minimum test file
	./rssk8r test.xml #uncomment to autoload test file

