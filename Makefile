 CC=gcc
CFLAGS=
INCLUDE=-Iso_files
LDFLAGS=
SOFLAGS=
PATHS=so_files/
DEBUG=
COMPILE=$(CC) $(DEBUG) $(INCLUDE) $(CFLAGS)
LINK=$(CC) $(DEBUG) $(CFLAGS) $(LDFLAGS)
LINKSO=$(CC) $(DEBUG) $(SOFLAGS)

.c.o:
	$(COMPILE) -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

allFunctions: $(PATHS)allFunctions.c $(PATHS)allFunctions.h
	$(LINK) $(PATHS)allFunctions.c -o $(PATHS)$@

allFunctions.so: $(PATHS)allFunctions.o
	$(LINKSO) -shared -fpic $(PATHS)allFunctions.o -o $(PATHS)$@

run_c: main.c
	$(LINK) main.c -o $@

charArrayCounter: run_c.o $(PATHS)allFunctions.so
	$(LINK) run_c.o $(PATHS)allFunctions.so -o $@

all: \
	allFunctions.so \
	charArrayCounter

run_all_tests:
	./charArrayCounter test_files/test_1 test_files/test_2 test_files/test_3 test_files/test_4

run_test_1:
	./charArrayCounter test_files/test_1

run_test_2:
	./charArrayCounter test_files/test_2

run_test_3:
	./charArrayCounter test_files/test_3

run_test_4:
	./charArrayCounter test_files/test_4

clean:
	rm -f *.o *.s $(PATHS)*.o $(PATHS)*.s $(PATHS)*.so charArrayCounter


