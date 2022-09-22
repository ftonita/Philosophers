# Philosophers

## This project is about the basics of threading a process
##
 ## "I never thought philosophy would be so deadly" ##

 <img src="https://i.makeagif.com/media/9-08-2018/T-4nH1.gif"></img>

##

### Common
  - Philosophers can think, eat and sleep
  - If philo exist without a meal so long, he dies
  - Number of Philos = Number of forks
  - To eat, each philosopher need 2 forks

### Mandatory Part
  - Each philosopher is a thread
  - Forks are mutexes

### Bonus Part
  - Each philosopher is a process
  - Using semaphores to lock forks (cause both philos must be eaten, but not in the same time)
  
  
### Launch
  - ~ git clone
  - ~ make
  - ~ ./philosophers 5 800 200 200 (number of philos, time to die, time to eat, time to sleep, * time in ms)
  
