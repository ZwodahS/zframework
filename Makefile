
WARNING= -Wextra -Wno-switch -Wno-sign-compare -Wno-missing-braces -Wno-unused-parameter
OBJDIR=obj

CXX=clang++ ${WARNING} -std=c++11 ${OPTIMIZE}

ZF_TERM=obj/zf_term.o
ZF_SPRITESHEET=obj/zf_spritesheet.o
ZF_STRING=obj/zf_string.o

all: $(ZF_TERM) $(ZF_SPRITESHEET) $(ZF_STRING)
 
# probably want to generate the dependency object

$(ZF_TERM) : zf_term.hpp zf_term.cpp zf_spritesheet.hpp
	$(CXX) -c -o $@ zf_term.cpp

$(ZF_SPRITESHEET) : zf_spritesheet.hpp zf_spritesheet.cpp
	$(CXX) -c -o $@ zf_spritesheet.cpp

$(ZF_STRING) : zf_strings.hpp zf_strings.cpp
	$(CXX) -c -o $@ zf_strings.cpp

clean:
	rm obj/*.o

remake:
	make clean
	make all

.PHONY: clean remake debug
