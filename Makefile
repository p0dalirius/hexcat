.PHONY:clean compile

OUTBINARY := hexcat

CC := gcc
CCFLAGS := -Wall

all : clean compile

compile :
	@if [ ! -d "bin/" ]; then mkdir -p "bin/"; fi;
	$(CC) $(CCFLAGS) "src/hexcat.c" -o "bin/${OUTBINARY}"
clean :
	@if [ -f "bin/${OUTBINARY}" ]; then rm "bin/${OUTBINARY}"; fi;
