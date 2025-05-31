SANFLAGS = -fsanitize=address
CXX = g++
CXXFLAGS = -std=c++17 -O2 # $(SANFLAGS) -O2
DEPS = utils/node.h utils/parse_tsp.h utils/distance_matrix.h utils/distance_matrix.cpp

eval:	eval.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) main eval