# mks65-finalproject
# Computer Orchestra

Kevin Cai, Eric Chen, Qiong Huang

Our project is to create a computer orchestra. A user will feed a piece of “sheet music” into our program. Then, the program will tell each computer to play certain notes. 

1. User creates the sheet music as a text file
2. User connects main computer to other computers
3. User chooses instruments for each computer
4. The main computer reads the sheet music, and tells each other computer what notes to play and when 

## Working With Files:
- The program will read and parse each piece of sheet music using read().  
### Processes
- The aplay command will be used to play each note. For each call of aplay, a new child process will be forked. 
### Signals
- Signals will be used to stop to manage the aplay command
### Networking
- The program will use networking to connect to other computers to tell them what notes to play
- Each computer will be able to pause the music by telling the main computer to stop

## User Interface:
A user creates a text file to serve as the sheet music
letters together = chord
Chords

## Examples of sheet music: 
### Cmaj
```
/piano
c4-e4-g4
```

### Hot Cross Buns
```
/piano
b4 a4 g4 r
/marimba
b4 a4 g4 r
g4 g4 g4 g4 
a4 a4 a4 a4
b4 a4 g4 r
```

## Data structures:
Each text file will be converted into a list of notes. 

## Timeline:
##### January 6: 
- Qiong: Research networking and get computers connected
- Kevin: Handle where to store notes/ general structure of the structs
- Eric: Handle aplay and processes
##### January 10
- Qiong: Send notes and begin implementing semaphore system
- Kevin: Integrate data structure of notes with aplay
- Eric: Complete filehandler 
##### January 13: System Integration 
- Qiong: Finish semaphore system to play chords
- Kevin: Integrate filehandler with aplay
- Eric: Integrate aplay with networking
##### January 15
- Final draft deadline
- Bug fixes
##### January 17
- Project submission deadline
