// Buzzer setup
#include "Buzzers.h"

// Music setup
#include "pitches.h"
#include <toneAC.h>
#define OCTAVE_OFFSET 0
#define isdigit(n) (n >= '0' && n <= '9')

Buzzers buzzers;
Buzzer teacherBuzzer(A2);

int notes[] = { 
  0,
  NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
  NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
  NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
  NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};

char *missionImpossible = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
char *pacman = "pacman:d=4,o=5,b=112:32b,32p,32b6,32p,32f#6,32p,32d#6,32p,32b6,32f#6,16p,16d#6,16p,32c6,32p,32c7,32p,32g6,32p,32e6,32p,32c7,32g6,16p,16e6,16p,32b,32p,32b6,32p,32f#6,32p,32d#6,32p,32b6,32f#6,16p,16d#6,16p,32d#6,32e6,32f6,32p,32f6,32f#6,32g6,32p,32g6,32g#6,32a6,32p,32b.6";
char *batman = "wwtbam1:d=4,o=5,b=140:16g,16c6,16d#6,16g6,16c7,16g6,16d#6,16c6,16g,16c6,16d#6,16g6,16c7,16g6,16d#6,16c6,16g#,16c6,16d#6,16g#6,16c7,16g#6,16d#6,16c6,16g#,16c6,16d#6,16g#6,16c7,16g#6,16d#6,16c6,16f#,16c6,16d#6,16f#6,16c7,16f#6,16d#6,16c6,16f#,16c6,16d#6,16f#6,16c7,16f#6,16d#6,16c6,16g,16b,16d6,16g6,16b6,16g6,16d6,16b,16g,16b,16d6,16g6,16b6,16g6,16d6,16b";
char *barbie = "Barbie girl:d=4,o=5,b=125:8g#,8e,8g#,8c#6,a,p,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#";
char *knightRider = "KnightRider:d=4,o=5,b=63:16e,32f,32e,8b,16e6,32f6,32e6,8b,16e,32f,32e,16b,16e6,d6,8p,p,16e,32f,32e,8b,16e6,32f6,32e6,8b,16e,32f,32e,16b,16e6,f6,p";
char *pinkPanther = "PinkPanther:d=4,o=5,b=160:8d#,8e,2p,8f#,8g,2p,8d#,8e,16p,8f#,8g,16p,8c6,8b,16p,8d#,8e,16p,8b,2a#,2p,16a,16g,16e,16d,2e";
char *axelF = "axelf:d=4,o=5,b=160:f#,8a.,8f#,16f#,8a#,8f#,8e,f#,8c.6,8f#,16f#,8d6,8c#6,8a,8f#,8c#6,8f#6,16f#,8e,16e,8c#,8g#,f#";
char *XFiles = "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b";
char *YMCA = "YMCA:d=4,o=5,b=160:8c#6,8a#,2p,8a#,8g#,8f#,8g#,8a#,c#6,8a#,c#6,8d#6,8a#,2p,8a#,8g#,8f#,8g#,8a#,c#6,8a#,c#6,8d#6,8b,2p,8b,8a#,8g#,8a#,8b,d#6,8f#6,d#6,f.6,d#.6,c#.6,b.,a#,g#";

char *buzzerAxelF = "axelf:d=4,o=5,b=160:f#,8a.";//,8f#,16f#,8a#,8f#,8e,f#,8c.6,8f#,16f#,8d6,8c#6,8a,8f#,8c#6,8f#6,16f#,8e,16e,8c#,8g#,f#";


// game mechanics
enum GameState {
  ASK_QUESTION,
  WAIT_FOR_ANSWER,
  STUDENT_BUZZES  
};

GameState gameState;
int buzzedIn = -1;

void setup() { 

  Serial.begin(9600); 

  teacherBuzzer.init();
  buzzers.initAll();

  startup();

  gameState = ASK_QUESTION;
  buzzers.allOn();

}

// the loop routine runs over and over again forever:
void loop() {


  if(gameState == ASK_QUESTION){
    Serial.println("ASK_QUESTION");
    
    // Lock out early birds
    for(int i = 0; i < buzzers.getNumBuzzers(); i++){
      if(buzzers.poll(i) == 1){
        buzzers.lock(i);
        buzzers.off(i);
      }
    }
    
    // Question over - move to Wait for answer
    if(teacherBuzzer.poll() == 1){
      teacherBuzzer.timelock();
      gameState = WAIT_FOR_ANSWER;
      buzzers.allOff();
    }
  }
    
  else if(gameState == WAIT_FOR_ANSWER){
    Serial.println("WAIT_FOR_ANSWER");
    
    // Student buzzes in
    for(int i = 0; i < buzzers.getNumBuzzers(); i++){
      if(buzzers.poll(i) == 1){
        play_rtttl(buzzerAxelF);
        toneAC();
        buzzers.on(i);        
        gameState = STUDENT_BUZZES;
      }
    }
  
    // No one answered, teacher resets
    if(teacherBuzzer.poll() == 1){     
      teacherBuzzer.timelock();
      gameState = ASK_QUESTION;
      buzzers.unlockAll();
      buzzers.allOn();            
    }
  }
    
  else{ // STUDENT_BUZZES:
    Serial.println("STUDENT_BUZZES");
    
    // Question answered, teacher resets
    if(teacherBuzzer.poll() == 1){     
      teacherBuzzer.timelock();
      gameState = ASK_QUESTION;
      buzzers.unlockAll();
      buzzers.allOn();      
    }
  
  }    
 
}


void startup(){

  for(int i = 0; i < buzzers.getNumBuzzers(); i++){
    buzzers.on(i);
    delay(100);   
  }
  
  play_rtttl(pacman);
  toneAC();

  for(int i = 0; i < buzzers.getNumBuzzers(); i++){
    buzzers.off(i);
    delay(100);   
  }

}

void play_rtttl(char *p)
{
  // Absolutely no error checking in here on arduino segway clone
  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while(*p != ':') p++;    // ignore name
  p++;                     // skip ':'

  // get default duration
  if(*p == 'd')
  {
    p++; 
    p++;              // skip "d="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   // skip comma
  }

  // get default octave
  if(*p == 'o')
  {
    p++; 
    p++;              // skip "o="
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }

  // get BPM
  if(*p == 'b')
  {
    p++; 
    p++;              // skip "b="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

  // now begin note loop
  while(*p)
  {
    // first, get note duration, if available
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }

    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

      // now get the note
    note = 0;

    switch(*p)
    {
    case 'c':
      note = 1;
      break;
    case 'd':
      note = 3;
      break;
    case 'e':
      note = 5;
      break;
    case 'f':
      note = 6;
      break;
    case 'g':
      note = 8;
      break;
    case 'a':
      note = 10;
      break;
    case 'b':
      note = 12;
      break;
    case 'p':
    default:
      note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if(*p == '#')
    {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if(*p == '.')
    {
      duration += duration/2;
      p++;
    }

    // now, get scale
    if(isdigit(*p))
    {
      scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if(*p == ',')
      p++;       // skip comma for next note (or we may be at the end)

    // now play the note
    if(note)
    {
      toneAC(notes[(scale - 4) * 12 + note], 10, duration, true);
      delay(duration);
      toneAC();
    }
    else
    {
      delay(duration);
    }
  }
}
