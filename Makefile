install: configure rebuild

test:
	./node_modules/.bin/mocha test/*.js

configure: 
	./node_modules/.bin/node-gyp configure

build: 
	./node_modules/.bin/node-gyp build

rebuild: 
	./node_modules/.bin/node-gyp rebuild

clean:
	rm -rf ./build src/test.o

.PHONY: test install configure build rebuild clean
