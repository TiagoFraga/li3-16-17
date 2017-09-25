CC = gcc
CFLAGS = -Wall -std=c11 -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0` 	
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`

program: avlRevisoes avlContribuidores avlArtigos parser interface 
		$(CC) $(CFLAGS) program.c -o program avlRevisoes.o avlArtigos.o avlContribuidores.o parser.o interface.o $(LIBS) 


interface: 
	$(CC) $(CFLAGS) -c interface.c 

#modulo parser

parser: 
	$(CC) $(CFLAGS) -c parser.c  

	
#modulo avlArtigos

avlArtigos: 
	$(CC) $(CFLAGS) -c avlArtigos.c 


#modulo avlContribuidores

avlContribuidores: 
	$(CC) $(CFLAGS) -c avlContribuidores.c 

#modulo avlRevisoes

avlRevisoes: 
	$(CC) $(CFLAGS) -c avlRevisoes.c 	


clean:
		rm -f program *.o
