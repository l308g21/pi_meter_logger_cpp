include config/deploy.conf

TARGET 			= $(lastword $(subst /, ,$(CURDIR)))
REMOTE_LOCATION	= code/$(TARGET)


CC     = g++
CFLAGS = -g -Wall -pthread

SRC	= src/
BLD = build/
BIN = bin/

all: clean mkdir app

mkdir:
	mkdir -p $(BLD) $(BIN)

$(BLD)tool.o: $(SRC)tool.cpp $(SRC)tool.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(BLD)config.o: $(SRC)config.cpp $(SRC)config.h $(BLD)tool.o
	$(CC) $(CFLAGS) -o $@ -c $<

# might need $(BLD)config.o dependency also - my late night guess is that it's implicitly included via db.o
$(BLD)datalogger.o: $(SRC)datalogger.cpp $(SRC)datalogger.h $(BLD)db.o
	$(CC) $(CFLAGS) -o $@ -c $<

$(BLD)db.o: $(SRC)db.cpp $(SRC)db.h $(BLD)config.o
	$(CC) $(CFLAGS) -o $@ -c $<

app: $(SRC)main.cpp $(BLD)db.o $(BLD)datalogger.o
	$(CC) $(CFLAGS) -o $(BIN)$(TARGET) $^ -lmariadb -lpigpio


test_config: clean mkdir $(BLD)config.o

deploy: clean zip
	./deploy.sh $(REMOTE_USER) $(MACHINE) $(TARGET) $(REMOTE_LOCATION)

zip:
	zip -r  $(TARGET).zip Makefile config/ sql/ src/

clean:
	rm -rf *.zip *.o $(BLD) $(BIN)