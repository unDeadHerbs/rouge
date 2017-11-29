CXX         = clang++
LIBARYFLAGS = -lncurses
CXXFLAGS    = -std=c++1z -Wall -Wextra -Wparentheses -g
HPPS        = $(wildcard *.hpp)
OBJECTS     = $(HPPS:.hpp=.o)

all: tags mains clean

mains: $(OBJECTS)
	-for f in `ls *.*` ; do \
		etags $$f -o - | grep "int main(" - > /dev/null && echo $$f | sed -e 's/[.][^.]*$$/.bin/' -e 's/.*/make &/' |sh; \
	done

%.bin: $(OBJECTS) %.o
	$(CXX) $(CXXFLAGS) $(LIBARYFLAGS) -o $@ $?

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

check-syntax: csyntax

csyntax:
	$(CXX) $(CXXFLAGS) -c ${CHK_SOURCES} -o /dev/null

tags:
	rm -f TAGS
	ls|grep "pp$$"|xargs -r etags -a

clean:
	rm -f $(OBJECTS) $(EXEC).o

cleanwarn:
	rm -f warnings.log
