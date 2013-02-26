all:
	utils/embedify res/class05.mod include/modfiles.h
	gcc -std=c99 -c src/Player_Channel.c -Iinclude -o obj/Player_Channel.o -g
	gcc -std=c99 -c src/Player.c -Iinclude -o obj/Player.o -g
	gcc -std=c99 -c src/MOD.c -Iinclude -o obj/MOD.o -g
	gcc -std=c99 -c src/MOD_Sample.c -Iinclude -o obj/MOD_Sample.o -g
	gcc -std=c99 -c src/MOD_Pattern.c -Iinclude -o obj/MOD_Pattern.o -g
	gcc -std=c99 -c src/MOD_PatternDivision.c -Iinclude -o obj/MOD_PatternDivision.o -g
	gcc -std=c99 -c src/MOD_Channel.c -Iinclude -o obj/MOD_Channel.o -g
	gcc -std=c99 -c src/utils.c -Iinclude -o obj/utils.o -g
	ar rcs lib/libmodam.a obj/*.o

test: all
	gcc -std=c99 tests/test.c -o bin/test -Iinclude -Llib -lmodam -g -lm


play: all test
	bin/test | aplay -r44100 -f S16_LE

clean:
	rm bin/*
	rm lib/*
	rm obj/*
