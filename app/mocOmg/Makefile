OMG_OBJS = mocOmgCmd.o mocOmgPort.o mocOmgVlan.o

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -fPIC -c $<
	#$(CC) $(IFLAGS) -c -o build/$@ $< 
	
all: $(OMG_OBJS)
	@ $(LD) $(LDFLAGS) -o $(OBJ_OMG)  $^
	 
	 
.PHONY : clean	 
clean:
	@ $(RM) -f *.o