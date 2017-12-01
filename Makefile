CXX         = clang++
LIBARYFLAGS = -lncurses
CXXFLAGS    = -std=c++1z -Wall -Wextra -Wparentheses -g $(SANS)
HPPS        = $(wildcard *.hpp)
OBJECTS     = $(HPPS:.hpp=.o)

all: format tags mains clean
seg: msan

msan:
	make all SANS=-fsanitize=address

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
format:
	find|egrep '.*[.](cpp|cxx|cc|c++|c|tpp|txx)$$'|sed 's/[] ()'\''\\[&;]/\\&/g'|xargs clang-format -i
