CC = gcc
CFLAGS = -Wall -pedantic -o MFO-matcher
TARGET = MFO-matcher
TESTS = allTests
CUTEST = CuTest
$(TARGET).exe: $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c $(TESTS).c $(CUTEST).c