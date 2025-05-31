SANFLAGS = -fsanitize=address
CXX = g++
CXXFLAGS = -std=c++17 -O2 # $(SANFLAGS) -O2
DEPS = utils/tsp_parser.h utils/tsp_parser.cpp

eval:	eval.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) main eval