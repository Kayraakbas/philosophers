Philosophers (Dining Philosophers Simulation with POSIX Threads)

# Project Overview
A C implementation of the classic Dining Philosophers concurrency problem. The program simulates philosophers alternating between thinking, eating, and sleeping while competing for shared fork resources (mutexes) with timing constraints and termination conditions.

# Features
- Precise millisecond timing with busy-wait calibrated sleep
- Deadlock avoidance via asymmetric fork acquisition
- Death monitoring thread detecting starvation
- Optional meals-to-eat termination condition
- Thread-safe logging with timestamped events
- Graceful resource cleanup (mutexes & heap memory)
- Input validation with overflow protection

# Tech Stack
- Language: C (C99)
- Concurrency: POSIX Threads (pthreads)
- Timing: gettimeofday
- Build: Makefile
- Platform: Unix-like (tested on macOS)
- Standard libraries: stdlib, stdio, unistd, sys/time, pthread, limits

# Architecture
- philo.c: Entry point (argument handling, initialization, thread orchestration)
- srcs/
  - arg_check_utils.c: Argument parsing & validation
  - philo_utils.c: Philosopher setup and thread start routine
  - philo_state_utils.c: State transitions (eat, sleep, think, fork handling)
  - monitor_thread_utils.c: Death and meal completion monitoring
  - safety_utils.c: Synchronized printing, timing, cleanup
  - ft_atoll.c / ft_isdigit.c: Utility conversion helpers
- includes/philo.h: Shared type and function declarations
- Core Data Structures:
  - t_args: Parsed CLI parameters
  - t_resources: Shared simulation context (timers, mutex arrays, global flags)
  - t_philo: Per-philosopher state (thread, fork refs, meal timing)

# Installation & Setup
1. Clone repository  
   git clone <https://github.com/Kayraakbas/philosophers> && cd philo
2. Build  
   make
3. (Optional) Clean builds  
   make clean / make fclean / make re
4. Verify binary  
   ls -l ./philo

# Usage
Basic run:  
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

Example:  
./philo 5 800 200 200  
./philo 5 800 200 200 7

Output format:  
<elapsed_ms> <philo_id> <event>

Events: has taken a fork | is eating | is sleeping | is thinking | died | meals finished

# API Endpoints / Core Functions (if applicable)
(Not a network API; core internal functions:)

Initialization:
- check_arguments(argc, argv)
- convert_args_to_int(argv, argc)
- init_resources(args)
- create_mutex_arr(n)
- create_philo_arr(n, resources)

Philosopher lifecycle:
- philo_starter(void*)
- acquire_forks(philo)
- release_forks(philo)
- time_to_eat / time_to_sleep / time_to_think

Monitoring:
- death_monitor(void*)
- time_monitor(philos_array)
- meal_monitor(philos_array)
- safe_check_philo_death(philo)
- safe_check_is_meal_finished(philo)

Safety & Utilities:
- safe_print(philo, msg)
- safe_sleep(ms)
- get_time_ms()
- is_sim_ended(philo)
- safe_free_all(resources)

Input utilities:
- ft_atoll(str)
- ft_isdigit(c)

# Configuration
Command-line parameters (all integers):
1. number_of_philosophers: > 0
2. time_to_die (ms)
3. time_to_eat (ms)
4. time_to_sleep (ms)
5. number_of_times_each_philosopher_must_eat (optional; if absent simulation ends only on death)

Constraints / Notes:
- All values must fit in int and be non-negative (add stricter checks if desired)
- No internal config file (placeholder if future expansion planned)
- Placeholder: Add environment variable overrides (TBD)

# Testing
Current Status:
- Manual runtime observation
- Edge case trials (1 philosopher, minimal times, large counts)
Planned / Placeholder:
- Add unit tests for parsing (ft_atoll, check_arguments)
- Add stress test script (shell) for large philosopher counts
- Add timing accuracy assertions (TBD)
Execution:
- make (build)
- Run multiple scenarios; capture output with: ./philo ... | tee run.log

# Contributing
1. Fork repository
2. Create feature branch: git checkout -b feature/your-feature
3. Commit with conventional messages
4. Run build & basic manual tests
5. Submit pull request with clear description
Style Guidelines:
- Follow existing formatting and naming conventions
- Keep functions short and cohesive
- Guard new shared data with mutexes

# License
This project is licensed under the MIT License.

# Credits / Acknowledgements
- 42 School project inspiration
- POSIX Threads documentation
- Original Dining Philosophers problem (Edsger Dijkstra)
- Placeholder: Additional contributors / reviewers

Feel free to replace placeholders with project-specific details.
