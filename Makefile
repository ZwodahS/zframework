
WARNING= -Wextra -Wno-switch -Wno-sign-compare -Wno-missing-braces -Wno-unused-parameter
OBJDIR=obj

CXX=clang++ ${WARNING} -std=c++11 ${OPTIMIZE}

ZF_TERM=obj/zf_term.o
ZF_SPRITESHEET=obj/zf_spritesheet.o
ZF_STRING=obj/zf_string.o
ZF_CONVERSION=obj/zf_conversion.o
ZF_RECT=obj/zf_rect.o
ZF_SPRITE=obj/zf_sprite.o
ZF_DIRECTIOn=obj/zf_direction.o

all: $(ZF_TERM) $(ZF_SPRITESHEET) $(ZF_STRING) $(ZF_CONVERSION) $(ZF_RECT) $(ZF_SPRITE) $(ZF_DIRECTION)
 
# probably want to generate the dependency object

$(ZF_TERM) : zf_term.cpp zf_term.hpp zf_spritesheet.hpp zf_rect.hpp zf_sprite.hpp
	$(CXX) -c -o $@ $<

$(ZF_SPRITESHEET) : zf_spritesheet.cpp zf_spritesheet.hpp
	$(CXX) -c -o $@ $<

$(ZF_STRING) : zf_strings.cpp zf_strings.hpp 
	$(CXX) -c -o $@ $<

$(ZF_CONVERSION) : zf_conversion.cpp zf_conversion.hpp
	$(CXX) -c -o $@ $<

$(ZF_RECT) : zf_rect.cpp zf_rect.hpp
	$(CXX) -c -o $@ $<

$(ZF_SPRITE) : zf_sprite.cpp zf_sprite.hpp 
	$(CXX) -c -o $@ $<

$(ZF_DIRECTION) : zf_direction.cpp zf_direction.hpp
	$(CXX) -c -o $@ $<

clean:
	rm obj/*.o

remake:
	make clean
	make all

.PHONY: clean remake debug
