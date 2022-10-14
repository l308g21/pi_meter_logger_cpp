include config/deploy.conf

TARGET 			= $(lastword $(subst /, ,$(CURDIR)))
REMOTE_LOCATION	= code/$(TARGET)


CC     = g++
CFLAGS = -g -Wall

SRC	= src/
BLD = build/
BIN = bin/

all: clean mkdir app

mkdir:
	mkdir -p $(BLD) $(BIN)

$(BLD)datalogger.o: $(SRC)datalogger.cpp $(SRC)datalogger.h $(BLD)db.o
	$(CC) $(CFLAGS) -lpigpio -o $@ -c $<

$(BLD)db.o: $(SRC)db.cpp $(SRC)db.h
	$(CC) $(CFLAGS) -o $@ -c $<

app: $(SRC)main.cpp $(BLD)db.o $(BLD)datalogger.o
	$(CC) $(CFLAGS) -lpigpio -o $(BIN)$(TARGET) $^




deploy: clean zip
	./deploy.sh $(USER) $(MACHINE) $(TARGET) $(REMOTE_LOCATION)

zip:
	zip -r $(TARGET).zip .

clean:
	rm -rf *.zip *.o $(BLD) $(BIN)