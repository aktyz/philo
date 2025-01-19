# My assumptions for this project
1. Any of the program arguments cannot be zero, as it is impractical to sleep, eat or think for no time. Also I am reserving zero to check for errors from my ft_atoi function.
2. I keep philosphers and forks in two tables, both of the same size,
- for the first philospher (philos[0]) - first fork will be the left one (forks[0]), second fork will be the right one (forks[n-1])
- for the second philosoper (philos[1] - odd) - first fork will be the right one (forks[0] - even), second fork will be the left one (forks[1] - odd)
- for the third philosoper (philos[2] - even) - first fork will be the left one (fork[2] - even), second fork will be the right one (fork[1] - odd)
- for the fourth philosoper (philos[3] - odd) - first fork will be the right one (forks[2] - even), second fork will be left one (forks[3] - odd)

p[0]: f[0], f[n-1]
p[1]: f[0], f[1]
p[2]: f[2], f[1]
p[3]: f[2], f[3]
p[4]: f[4], f[3]

# Nice README.md
Time to learn creating proper README files... Once the project is done...

# External functions you can use
## pthread.h(7POSIX)
pthread_create<br>
pthread_detach<br>
pthread_join<br>
pthread_mutex_init<br>
pthread_mutex_destroy<br>
pthread_mutex_lock<br>
pthread_mutex_unlock<br>
## stdio.h
printf
## stdlib.h
malloc
free
## string.h
memset
## sys/time.h
gettimeofday
## unistd.h
usleep<br>
write<br>

# Usefull resources:
https://nafuka11.github.io/philosophers-visualizer/
