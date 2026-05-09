CC=qcc

CFLAGS=-Vgcc_ntoaarch64le -Wall

all:
	$(CC) $(CFLAGS) -o monitor_process src/monitor_process.c src/utility.c
	$(CC) $(CFLAGS) -o primary_app src/primary_app.c src/utility.c
	$(CC) $(CFLAGS) -o ghost_app src/ghost_app.c src/utility.c
	$(CC) $(CFLAGS) -o media_app src/media_app.c src/utility.c
	$(CC) $(CFLAGS) -o guardian_app src/guardian_app.c src/utility.c
	$(CC) $(CFLAGS) -o controller_app src/controller_app.c src/utility.c
	$(CC) $(CFLAGS) -o critical_core_hog src/critical_core_hog.c src/utility.c
	$(CC) $(CFLAGS) -o noncritical_core_hog src/noncritical_core_hog.c src/utility.c

clean:
	rm -f monitor_process
	rm -f primary_app
	rm -f ghost_app
	rm -f media_app
	rm -f guardian_app
	rm -f controller_app
	rm -f critical_core_hog
	rm -f noncritical_core_hog