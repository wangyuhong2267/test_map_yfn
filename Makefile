CC = g++ -std=c++11


INC=../nghttp2/lib/includes
LIB=../nghttp2/lib/.libs

INC2=/usr/local/openssl/include
LIB2=/usr/lib64/


#CFLAGS=-Wall -O2 -lpthread -I/usr/include -I$(INC) $(LIB)/libnghttp2.a -Bstatic  -Wl,-Bdynamic -lssl -lcrypto


CFLAGS=-Wall -Wextra -Wno-unused-parameter -I$(INC) -I$(INC2)
LDFLAGS= -L$(LIB)   -Wl,-Bstatic  -lnghttp2 -Wl,-Bdynamic -lssl -lcrypto -lpthread




TARGET = main

SRCS := $(wildcard *.cpp)

OBJS := $(patsubst %cpp, %o, $(SRCS) $(LIB)/libnghttp2.a)

all: $(TARGET)

$(TARGET): $(OBJS)
#$(CC)    -o  $@ $^ $(LDFLAGS)
	$(CC)    -o  $@ $^ $(LDFLAGS)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $<


$(LIB)/libnghttp2.a:
clean:
	rm -f *.o $(TARGET)
