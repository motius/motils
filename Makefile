all:
	/home/plam/.platformio/penv/bin/pio run

install:
	/home/plam/.platformio/penv/bin/pio run --target upload

run:
	picocom /dev/ttyUSB0 --baud 115200

clean:
	/home/plam/.platformio/penv/bin/pio run --target clean
