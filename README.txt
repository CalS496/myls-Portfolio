To compile:
	gcc -o myls myls.c
To run
	./myls ls ("-ai1" / "-ail1") [thing]

*Just to note, the program can also run without being directed
to a specific file or directory with [thing]

This code is not as optimized as I hoped it would have been due
to personal time constraints. I also wasn't able to figure out certain 
details like how to get user id or group id printed out

Please note that the ls flags have to be very specific,
	like "-ai1" or "-ail1"
	not "-a1i" (e.g)

this was also a hardcoded implementation

Please let me know if there is any issue 