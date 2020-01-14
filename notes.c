struct Note {
    char * note;
    char * directory;
};
struct Instrument{
    struct Note * notes[90];
    int ind;
};
struct MusicInterface {
  struct Instrument * piano;
  struct Instrument * guitar;
};
struct MusicInterface* setup(){
  struct MusicInterface* out = malloc(sizeof(struct MusicInterface));
  out->piano = malloc(sizeof(struct Instrument));
  out->guitar = malloc(sizeof(struct Instrument));
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
void addNotes(struct MusicInterface * player){
  addNote(player, 0, "E", "");
  addNote(player, 0, "F", "");
  addNote(player, 0, "G", "");
}
void addNote(struct MusicInterface* player, int instID, char * note, char * dir){
  struct Instrument * inst = cvtIDtoInst(player, instID);
  struct Note * tmp = malloc(sizeof(struct Note));
  tmp->note = malloc(strlen(note) * sizeof(char *));
  strcpy(tmp->note,note);
  tmp->directory = malloc(strlen(dir) * sizeof(char *));
  strcpy(tmp->directory,dir);
  inst->notes[inst->ind] = tmp;
  inst->ind++;
}
char * getDirectory(struct MusicInterface* player, char* note, int instID){
  struct Instrument * inst = cvtIDtoInst(player,instID);
  struct Note * notes = inst->notes;
  for(;notes != 0; ++notes){
    if(strcmp(notes->note,note) == 0){
      return notes->directory;
    }
  }
  return '\0';
}

void freeNote(struct Note * note){
  free(note->note);
  free(note->directory);
  free(note);
}
void freeInst(struct Instrument * inst){
  const int numNotes = inst->ind;
  int i;
  for(i = 0; i < numNotes; ++i){
    freeNote(inst->notes[i]);
  }
  free(inst);
}
void freeEverything(struct MusicInterface* player){
  freeInst(player->piano);
  freeInst(player->guitar);
  free(player);
}
