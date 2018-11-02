ACCI_OBJS = acType.o acRand.o acArray.o acCrease.o acci.o acHash.o

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -fPIC -c $<
	
all: $(ACCI_OBJS)
	@ $(LD) -o $(OBJ_ACC)  $^ -r -X 
	 
	 
.PHONY : clean	 
clean:
	@ $(RM) -f *.o