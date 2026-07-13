CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -Icore -IAPI -IJSON -IJSON/cjson_import
LIBS = -lcurl

TARGET = cweather

SRCS = core/main.c \
       core/printing.c \
       API/api.c \
       JSON/cjson_import/cJSON.c \
       JSON/json.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)