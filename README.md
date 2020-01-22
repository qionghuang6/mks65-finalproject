# mks65-finalproject
# Computer Orchestra

Kevin Cai, Eric Chen, Qiong Huang

### How to Run
- Use make server and make client to compile.
- Run server using:
./server
- Run each client using:
./client [ip of server]
- Play and Pause using Ctrl + C (Note this only works on the server), not being able to pause and play on the client is a bug

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
- Signals will be used to stop to manage the aplay command. It is also used to play and pause the program
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
C4-E4-G4
```

### Hot Cross Buns
```
/piano
B4 A4 G4 r
/marimba
B4 A4 G4 r
G4 G4 G4 G4 
A4 A4 A4 A4
B4 A4 G4 r
```

## Data structures:
Each text file will be converted into a list of notes. 

## Devlog
### Qiong:
 * Tuesday: Played with networking code and got basic one way communication between server and client
 * Thursday: Began working on multi threads with select
 * Monday: Finished multi threads and using signals to play and pause
### Eric:
 * Tuesday: Found mp3 files online for instruments, converted to wav file to use with aplay
 * Thursday: Wrote code for aplaying and execing the music files 
 * Monday: Implemented aplay and exec code into client
### Kevin
 * Tuesday: Wrote parser for music text files
 * Thursday-Friday: Wrote structs for holding notes and chords 
 * Monday/Tuesday(20-21): Implemented structs and finished connection between server and client. Debugging
