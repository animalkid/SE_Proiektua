main: clock_h.c timer_h.c sched_h.c process_gen_h.c main.c	
	gcc-9 -o main p_array.c linked_l.c clock_h.c timer_h.c sched_h.c process_gen_h.c main.c -pthread
