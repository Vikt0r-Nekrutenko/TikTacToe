all:
	#clang++ -fpic -shared stf/*.cpp -o ~/libstf.so
	clang++ ~/libstf.so tik_tac_toe/*.cpp main.cpp -o ~/main
	~/main