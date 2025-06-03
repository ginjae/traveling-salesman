SANFLAGS = -fsanitize=address
CXX = g++
CXXFLAGS = -std=c++17 -O2 # $(SANFLAGS) -O2
DEPS = utils/node.h utils/parse_tsp.h algorithms/tsp_solver.h algorithms/mst_based.h algorithms/mst_based.cpp	\
		algorithms/held_karp.h algorithms/held_karp.cpp algorithms/jam.h algorithms/jam.cpp

eval:	eval.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) main eval
