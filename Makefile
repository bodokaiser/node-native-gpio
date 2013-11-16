MOCHA 	 = node_modules/.bin/mocha
NODE_GYP = node_modules/.bin/node-gyp

MOCHA_FLAGS = \
		--reporter spec

test: test-src

test-src:
	$(MOCHA) $(MOCHA_FLAGS) \
		test/src/gpio

build:
	$(NODE_GYP) configure \
	$(NODE_GYP) rebuild

clean:
	@ rm -rf ./build src/*.o

.PHONY: test
