CXX=g++
FLAGS= -std=c++17 -Wall -Wextra -Werror
GTEST= -lgtest -lgtest_main -pthread
GCOV= -fprofile-arcs -ftest-coverage
TARGETS= model/model.cc test/test.cc


all: gcov_report

test: clean
	$(CXX) $(FLAGS) -o testss $(TARGETS) $(GTEST) $(GCOV)
	./testss

install: clean uninstall
	mkdir build
	cd build && cmake ../Kalculator/CMakeLists.txt && make
	cp -rf build/Kalculator.app $(HOME)/Desktop/Calculator.app

uninstall: clean
	rm -rf build
	rm -rf $(HOME)/Desktop/Calculator.app

gcov_report: clean add_coverage test
	mkdir report
	gcovr --html-details -o report/coverage.html
	open ./report/coverage.html

dist: clean uninstall install
	mkdir ../dist
	cp -r $(HOME)/Desktop/Calculator.app ../dist/.
	cp ../README.md ../dist
	tar -czvf dist.tar.gz ../dist
	rm -rf ../dist

dvi:
	doxygen Doxyfile
	open ./html/index.html/

clean:
	rm -rf *.o gcov_report *.a *.gcda *.gcno testss testss.info -r report

add_coverage:
	$(eval FLAGS += --coverage)

.PHONY: test install uninstall gcov_report dist clean add_coverage dvi
