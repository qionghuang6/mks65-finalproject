int NUM_INSTRUMENTS;
struct Instruments{
  char * inst[3];
};
struct Instruction {
    char ** chord;
    int clen;
};
struct Song{
  struct Instruction ** data;
  int chlen;
};
char * parse_note(char* dt,char * note);
struct Instruction* parse_chord(char * chord);
struct Song* parse_song(char * song);
struct Song ** parseIn(char* dir);
