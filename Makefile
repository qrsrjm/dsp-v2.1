
CC=mipsel-linux-gcc
#CC=gcc 
 

SRCS= TAS3xxxDownload.c DSP.c I2C.c UserMath.c DataStg.c TAS3xxx.c dataToString.c dspArchive.c g_variable.c repDsp.c 
OBJS=$(patsubst %.c,%.o,$(SRCS) ) 

%.o:%.c 
	$(CC) -fPIC -c  $< -o $@  -std=c99

.PHONY:all clean
all:libDsp.so

libDsp.so:$(OBJS)
	$(CC) -shared -fPIC -o libDsp.so $(OBJS) -L libnvram-0.9.28.so -lm -std=c99
	
#all:test
#test:$(OBJS)
#	$(CC) -fPIC -o test $(OBJS) -lm -std=c99
	
clean:
	rm *.o *.so -rf


      



