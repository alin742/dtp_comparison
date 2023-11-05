BOARD = "esp32:esp32:nodemcu-32s"
PORT = /dev/ttyUSB0

server:
	chmod a+rw $(PORT)
	pio run --target upload -d ./Server

client:
	gcc -o Client/Client.exe Client/main.c

all: Client Server
