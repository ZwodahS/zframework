# game code.
vpath %.cpp z_framework/
vpath %.hpp z_framework/
vpath %.o obj/

WARNING= -Wextra -Wno-switch -Wno-sign-compare -Wno-missing-braces -Wno-unused-parameter
OPTIMIZE= -fno-exceptions
TARGETFDR=bin
TARGET=example
SFML=-framework sfml-graphics -framework sfml-system -framework sfml-window
OBJDIR=obj

CXX=clang++ ${WARNING} -std=c++11 ${OPTIMIZE}

cppfiles=$(shell find . -name "*.cpp" -exec basename {} \;)
hppfiles=$(shell find . -name "*.hpp" -exec basename {} \;)
objs=$(patsubst %, $(OBJDIR)/%, $(cppfiles:.cpp=.o))

all: $(TARGETFDR)/$(TARGET)

$(TARGETFDR)/$(TARGET) : $(objs)
	$(CXX) -o $(TARGETFDR)/$(TARGET) $(OBJDIR)/*.o $(SFML) 

$(OBJDIR)/%.o : %.cpp ${hppfiles}
	$(CXX) -c -o $@ $<

clean:
	rm -f obj/*.o
	rm -f $(TARGETFDR)/*

remake:
	make clean
	make all

debug :
	@echo $(cppfiles)
	@echo $(hppfiles)

.PHONY: clean remake debug
