CXX=g++ 
CXXFLAGS= -Wall -std=c++11 
LDFLAGS=
EXEC_FILES=tests affichage
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< $(LDFLAGS)
	
tests: test.o coord.o fourmis.o colonie.o places.o grille.o simulation2.o graphique.o
	$(CXX) -o $@ $^ $(LDFLAGS)
affichage: test.o coord.o fourmis.o colonie.o places.o grille.o simulation2.o graphique.o
	$(CXX) -o $@ $^ $(LDFLAGS)
	./affichage
	convert -scale 300 -delay 10 img*.ppm movie.gif
	rm -f *.ppm
	rm -f *.o

coord.o: coord.hpp 
fourmis.o: coord.hpp fourmis.hpp
colonie.o: coord.hpp fourmis.hpp colonie.hpp
places.o: coord.hpp fourmis.hpp colonie.hpp places.hpp
grille.o: coord.hpp fourmis.hpp colonie.hpp places.hpp grille.hpp 
simulation2.o: coord.hpp fourmis.hpp colonie.hpp places.hpp grille.hpp simulation2.hpp
graphique.o: coord.hpp fourmis.hpp colonie.hpp places.hpp grille.hpp simulation2.hpp graphique.hpp
test.o: coord.hpp fourmis.hpp places.hpp grille.hpp simulation2.hpp 
affichage.o: coord.hpp fourmis.hpp places.hpp grille.hpp simulation2.hpp graphique.hpp


clean:
	rm -f *.o $(EXEC_FILES) 
	rm -f movie.gif
	rm img*

check: tests
	./tests
	
	
