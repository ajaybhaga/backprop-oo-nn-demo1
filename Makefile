all:    backprop_ex1

ui:
	g++ -g -I/usr/include/SDL2 -D_REENTRANT -I/usr/include/SDL2_image -I/usr/include/SDL2_ttf -Wall -c /home/osboxes/dev/oo-nn/backprop/src/main.cpp -o obj/Debug/main.o
	g++ -o bin/Debug/backprop obj/Debug/main.o -lSDL2 -lSDL2_image -lSDL2_ttf

adaline1:
	g++ src/adaline/ex1.cpp -o bin/adaline1

adaline2:
	g++ src/adaline/ex2.cpp -o bin/adaline2


backprop_ex1:
	g++ src/backprop/backprop_ex1.cpp -o bin/backprop_ex1

329:
	g++ src/329/main.cpp -o bin/329

git:
	git add -A
	git commit -m "$(msg)"
	git push

