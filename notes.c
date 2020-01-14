struct Note {
    char * note;
    char * directory;
};
struct Instrument{
    const struct Note * notes[90];
    int ind;
};
struct MusicInterface {
  struct Instrument * piano;
  struct Instrument * guitar;
};
struct MusicInterface* setup(){
  return malloc(sizeof(struct MusicInterface));
}
void addNotes(struct MusicInterface * player){

}
void addNote(int instID, char * note, char * dir){
  struct Instrument * inst = cvtIDtoInst(instID);
  inst->notes[inst->ind] = {note, dir};
}
char * getDirectory(char* note, int instID){
  struct Instrument * inst = cvtIDtoInst(instID);
  struct Note[300] * notes = inst->notes;
  const int numNotes = inst->ind;
  int i;
  for(i = 0; i < numNotes; ++i){
    if(strcmp(notes[i]->note,note) == 0){
      return notes[i]->dir;
    }
  }
  return '\0';
}
struct Instrument * cvtIDtoInst(struct MusicInterface* player, int instID){
  struct Instrument * inst = 0;
  if(instID == 0){
    inst = player->piano;
  } else if (instID == 1){
    inst = player->guitar;
  }
  return inst;

}
