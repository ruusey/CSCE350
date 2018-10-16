CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		intsort.o

LIBS =

TARGET =	intsort.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
