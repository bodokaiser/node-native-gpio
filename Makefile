test:
	./node_modules/.bin/mocha test/*.js

install: configure rebuild

configure: 
	./node_modules/.bin/node-gyp configure

build: 
	./node_modules/.bin/node-gyp build

rebuild: 
	./node_modules/.bin/node-gyp rebuild

clean:
	rm -rf ./build

.PHONY: test install configure build rebuild clean
