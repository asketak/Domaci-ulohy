all:
	g++ cviceni1/A.cpp -lcairo -o 1A
	g++ cviceni1/B.cpp -lutil -lboost_iostreams -lboost_system -lboost_filesystem -std=c++11 -o 1B
	g++ cviceni1/C.cpp -lutil -lboost_iostreams -lboost_system -lboost_filesystem -lcairo -std=c++11 -o 1C
	g++ cviceni2/A.cpp cviceni2/testA.cpp -lcairo -o 2A
	g++ cviceni2/B.cpp -lutil -lboost_iostreams -lboost_system -lboost_filesystem -lcairo -std=c++11 -o 2B
