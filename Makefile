test: test-addon test-node

install: configure rebuild

configure: 
	./node_modules/.bin/node-gyp configure

build: 
	./node_modules/.bin/node-gyp build

rebuild: 
	./node_modules/.bin/node-gyp rebuild

test-addon:
	$(CC) -o test/gpio.o test/gpio.c && ./test/gpio.o

test-node:
	./node_modules/.bin/mocha test/*.js

clean:
	rm -rf ./build test/gpio.o

.PHONY: test install configure build rebuild clean
