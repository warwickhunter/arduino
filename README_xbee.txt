How to connect to the XBee module attached to the desktop machine via USB

minicom -D /dev/ttyUSB0 -b 9600 -o

How to set the baud rate, which is 9600 for the XBee modules

stty -F /dev/ttyUSB1 speed 9600

Another way to just listen on the serial port

cat /dev/ttyUSB1
