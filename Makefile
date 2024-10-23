build: 
	gcc main.c -o quadtree -std=c99

run:
	./quadtree

clean:
	rm -r quadtree