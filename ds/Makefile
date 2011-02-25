CC=gcc -g
TREE=bst
BASETREE=$(TREE)tree
EXT=.o
BASETREEOBJ=$(BASETREE)$(EXT)
all: $(BASETREE) test
$(BASETREE):$(BASETREEOBJ)
	
test:$(BASETREE) test.o
	$(CC) test.o $(BASETREEOBJ) -o test
.c.o:
	$(CC) -c -D$(TREE) $<
clean:
	rm -rf test *.o

