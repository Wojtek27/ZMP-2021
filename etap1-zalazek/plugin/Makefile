

__start__: obj __lines_for_space__ ../libs/libInterp4Move.so ../libs/libInterp4Set.so
	@echo "  Tworzenie wtyczki zakonczone."
	@echo

obj:
	mkdir obj

CPPFLAGS=-Wall -fPIC -pedantic -std=c++17 -iquote inc -iquote ../inc
LDFLAGS=-Wall -shared

__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo

../libs/libInterp4Move.so: obj/Interp4Move.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Move.so obj/Interp4Move.o
	@echo
	@echo "  Wtyczka dla polecenia 'Move' zostala utworzona."
	@echo


obj/Interp4Move.o: src/Interp4Move.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Move.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Move.o src/Interp4Move.cpp

../libs/libInterp4Set.so: obj/Interp4Set.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Set.so obj/Interp4Set.o
	@echo
	@echo "  Wtyczka dla polecenia 'Set' zostala utworzona."
	@echo

obj/Interp4Set.o: src/Interp4Set.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Set.hh 
	g++ -c ${CPPFLAGS} -o obj/Interp4Set.o src/Interp4Set.cpp


clean:
	rm -f obj/*

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
