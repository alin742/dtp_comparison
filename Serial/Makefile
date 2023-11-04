BOARD = "esp32:esp32:nodemcu-32s"
PORT = /dev/ttyUSB0

server:
	arduino-cli compile --fqbn $(BOARD) Server
	# arduino-cli upload -p $(PORT) --fqbn $(BOARD) Server

client:
	gcc -o Client/Client.exe Client/main.c

all: Client Server
