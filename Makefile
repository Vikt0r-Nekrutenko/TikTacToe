all:
	clang++ -fpic -shared stf/*.cpp -o ~/libstf.so
	clang++ ~/libstf.so main.cpp -o ~/main
	~/main