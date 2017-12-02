CXX         = clang++
LIBARYFLAGS = -lncurses
CXXFLAGS    = -std=c++1z -Wall -Wextra -Wparentheses -g $(SANS)

# auto generate dependencies stolen from
# http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
DEPDIR      = .d
$(shell mkdir -p $(DEPDIR) > /dev/null)
DEPFLAGS    = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
COMPILECXX  = $(CXX) $(DEPFLAGS) $(CXXFLAGS)
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

all: format tags mains
seg: msan

msan:
	make all SANS=-fsanitize=address

mains:
	-for f in `ls *.*` ; do \
		etags $$f -o - | grep "int main(" - > /dev/null && echo $$f | sed -e 's/[.][^.]*$$/.bin/' -e 's/.*/make &/' |sh; \
	done

%.bin: %.o
	$(COMPILECXX) $(LIBARYFLAGS) -o $@ $?

%.o: %.cpp
%.o: %.cpp $(DEPDIR)/%.d
	$(COMPILECXX) -c $< -o $@
	$(POSTCOMPILE)

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

.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basemane $(SRCS))))
