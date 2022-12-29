all: main.o read_sentence.o read_text.o delete_double.o replace.o replace_text.o find_dates.o delete_same_words.o is_happened.o
	gcc -o program main.o read_sentence.o read_text.o delete_double.o replace.o replace_text.o find_dates.o delete_same_words.o is_happened.o

main.o: main.c structs.h read_sentence.h read_text.h delete_double.h replace.h find_dates.h delete_same_words.h is_happened.h
	gcc -c main.c

read_sentence.o: read_sentence.c read_sentence.h structs.h
	gcc -c read_sentence.c

read_text.o: read_text.c read_text.h read_sentence.h
	gcc -c read_text.c 

delete_double.o: delete_double.c delete_double.h 
	gcc -c delete_double.c 

replace.o: replace.c replace.h 
	gcc -c replace.c

replace_text.o: replace_text.c replace_text.h 
	gcc -c replace_text.c
	
find_dates.o: find_dates.c find_dates.h 
	gcc -c find_dates.c

delete_same_words.o: delete_same_words.c delete_same_words.h 
	gcc -c delete_same_words.c

is_happened.o: is_happened.c is_happened.h replace.h
	gcc -c is_happened.c

clean:
	rm -rf *.o
	
