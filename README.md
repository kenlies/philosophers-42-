# philosophers-42-
## My hive (42) school philosophers project [BONUSES]
- A synchronized simulation of the dining philosophers problem

This project was all about learning to use threads & mutexes for the mandatory part to achieve a synchronized simulation of the dining philosophers problem, where no dataraces (or leaks ofc) were tolerated.
For the bonus section we had to use processes and semaphores for achieving pretty much the same goal, although this time all of the forks were put on the middle of the table. So any philo could pickup any fork, but there still needed to be, like in the mandatory part, the same amount of forks as philos.

If you are not familiar of the dining philosophers problem, then I suggest to read about it online. And I have included the subject.

This implementation passed both mandatory and bonus sections of this project, which I am quite happy about. The mandatory part should not have any dataraces or leaks when compiled with -fsanitize=thread/address respectively.

The bonus section however, if you compile it with the thread sanitizer, it will show some dataraces. I figured, after some tinkering, research and peer questioniong, that those are warnings are false; the lines where that supposed datarace is occuring, is protected with a sem_wait() call and a subsequent sem_post() call to increment the semaphore. 

I don't see where & how it can possibly lead to a datarace. The thread sanitizer is intended for threads & mutexes, not for semaphores.

use:


     ./philo [philo count] [time to die] [time to eat] [time to sleep] {times philos have to eat} <-- last argument is optional
     ./philo_bonus [philo count] [time to die] [time to eat] [time to sleep] {times philos have to eat} <-- last argument is optional
example:
      
      
     ./philo 5 800 200 200 7

<img width="622" alt="Screen Shot 2023-06-11 at 1 38 45 PM" src="https://github.com/kenlies/philosophers-42-/assets/97135325/2eefe29d-c944-41c3-8a10-1b2c3bac8717">
