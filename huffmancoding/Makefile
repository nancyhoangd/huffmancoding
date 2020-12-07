# Nancy Hoang ndh9tsj

CXXFLAGS = -Wall -O2 
CXX = clang++ $(CXXFLAGS)
DEBUG = -g

OBJECTSENC = huffmanenc.o huffmanNode.o heap.o
OBJECTSDEC = huffmandec.o huffmanNode.o 

huffman: encoder decoder

encoder: $(OBJECTSENC)
	$(CXX) $(DEBUG) $(OBJECTSENC) -o encoder
	@echo "encoder is ready"

decoder: $(OBJECTSDEC)
	$(CXX) $(DEBUG) $(OBJECTSDEC) -o decoder
	@echo "decoder is ready"


.PHONY: clean
clean:
	-rm -f *.o *a.out *~ encoder decoder

huffmanedec.o: huffmandec.cpp huffmanNode.h
	$(CXX) -c huffmandec.cpp


huffmanNode.o: huffmanNode.cpp huffmanNode.h
	$(CXX) -c huffmanNode.cpp

huffmanenc.o: huffmanenc.cpp heap.h huffmanNode.h
	$(CXX) -c huffmanenc.cpp

heap.o: heap.cpp heap.h huffmanNode.h
	$(CXX) -c heap.cpp



