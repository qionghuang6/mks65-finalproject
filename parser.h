int NUM_INSTRUMENTS;
struct Instruments{
  char * inst[3];
};
struct Instruction {
    char ** chord;
};
struct Song{
  struct Instruction ** data;
};
char * parse_note(char * note, char * start, char * end);
struct Instruction* parse_chord(char * chord);
struct Song* parse_song(char * song);
struct Song ** parse_file(char * song);
struct Song ** parseIn(char* dir);
