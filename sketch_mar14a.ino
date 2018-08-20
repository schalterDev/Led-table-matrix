/*************************************************
 * Public Constants
 *************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define PAUSE    0


int buzzer = 5;
boolean DEBUG = true;


void setup()
{

  pinMode(buzzer, OUTPUT);

  if(DEBUG) {
    Serial.begin(9600);
  }
}


int imperialMarchTuneTpt1[] = {
  // line 1
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5, 
  NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4, 
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_C5, 
  NOTE_GS4, NOTE_F4, NOTE_C5, NOTE_A4,
  // line 2
  NOTE_A5, NOTE_A4, NOTE_A4, NOTE_A5, NOTE_GS5, NOTE_G5, 
  NOTE_FS5, NOTE_F5, NOTE_FS5, PAUSE, NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_CS5, 
  NOTE_C5, NOTE_B4, NOTE_C5, PAUSE, NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_A4, 
  NOTE_C5, NOTE_A4, NOTE_C5, NOTE_E5,
  // line 3
  NOTE_A5, NOTE_A4, NOTE_A4, NOTE_A5, NOTE_GS5, NOTE_G5, 
  NOTE_FS5, NOTE_F5, NOTE_FS5, PAUSE, NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_CS5, 
  NOTE_C5, NOTE_B4, NOTE_C5, PAUSE, NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_C5, 
  NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
  // line 4
  PAUSE,
  PAUSE,
  NOTE_A4, PAUSE, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5,
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_C6,
  // line 5
  PAUSE,
  PAUSE,
  PAUSE,
  PAUSE,
  PAUSE,
  // line 6
  PAUSE,
  PAUSE,
  PAUSE,
  PAUSE,
  PAUSE,
  // line 7
  PAUSE,
  PAUSE,
  PAUSE,
  PAUSE,
  PAUSE,
  // line 8
  PAUSE,
  NOTE_C5, NOTE_C4, PAUSE, NOTE_C4, NOTE_E5, NOTE_B4, NOTE_AS4,
  NOTE_A4, NOTE_GS4, NOTE_A4, PAUSE, NOTE_CS4, NOTE_FS4,
  NOTE_FS4, NOTE_FS4, PAUSE, NOTE_F4, NOTE_E4,
  NOTE_DS4, NOTE_D4, NOTE_DS4, PAUSE, NOTE_GS3, NOTE_B3,
  // line 9
  NOTE_B3, PAUSE, NOTE_GS3, NOTE_DS4, 
  NOTE_C4, PAUSE, NOTE_GS3, NOTE_DS4, NOTE_C4,
  NOTE_C4, NOTE_C4, PAUSE,
  PAUSE,
  PAUSE,
  // line 10
  PAUSE,
  PAUSE,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5,
  NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
  // line 11
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_C5,
  NOTE_GS4, NOTE_F4, NOTE_C5, NOTE_A4,
  NOTE_A5, NOTE_A4, NOTE_A4, NOTE_A5, NOTE_GS5, NOTE_G5,
  NOTE_FS5, NOTE_F5, NOTE_FS5, PAUSE, NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_CS5,
  // line 12
  NOTE_C5, NOTE_B4, NOTE_C5, PAUSE, NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_GS4,
  NOTE_C5, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A5, NOTE_A4, NOTE_A4, NOTE_A5, NOTE_GS5, NOTE_G5,
  NOTE_FS5, NOTE_F5, NOTE_FS5, PAUSE, NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_CS5,
  // line 13
  NOTE_C5, NOTE_B4, NOTE_C5, PAUSE, NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_C5,
  NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5, 
  NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
  // line 14
  NOTE_C5, NOTE_B4, NOTE_C5, PAUSE, NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_C5,
  NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5, 
  NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
  // line 15
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_C5,
  NOTE_GS4, NOTE_F4, NOTE_C5, NOTE_A4,
  NOTE_A5, NOTE_A4, NOTE_A4, NOTE_A5, NOTE_GS5, NOTE_G5,
  NOTE_FS5, NOTE_F5, NOTE_FS5, PAUSE, NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_CS5,
  // line 16
  NOTE_C5, NOTE_B4, NOTE_C5, PAUSE, NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_C5,
  NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
  PAUSE,
  PAUSE,
  // line 17
  PAUSE,
  PAUSE,
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_F5, NOTE_C6, 
  NOTE_A5, NOTE_F5, NOTE_C6, NOTE_A5, NOTE_F5, NOTE_C6,
  // line 18
  NOTE_A5, PAUSE, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5,
  NOTE_A5, PAUSE, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5,
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, PAUSE, PAUSE,
  // line 19
  NOTE_A5, PAUSE, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_A5, PAUSE, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_A5, PAUSE, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_A5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, PAUSE,
  // end 
};

/* TEMPOS
 *
 * Binary
 * 1 = round
 * 2 = white
 * 3 = black + dot
 * 4 = black
 * 6 = quaver + dot
 * 8 = quaver
 * 12 = half quaver + dot
 * 16 = half quaver
 * 24 = fusa + dot
 * 32 = fusa
 *
 * Ternary
 * 3 = white (3 white = 1 round)
 * 6 = black (3 black = 1 white)
 * 12 = quaver (3 quaver = 1 black)
 * 24 = half quaver (3 half quaver = 1 quaver)
 * 48 = fusa (3 fusa = 1 half quaver)
 *
 * Attached notes are written separately but with 1000 more on their tempo value
 * ex: two black notes attached have tempos like 1004, 1004
 */
int imperialMarchTempoTpt1[] = {
  // line 1
  4, 4, 4, 6, 16, 
  4, 6, 16, 2, 
  4, 4, 4, 6, 16, 
  4, 6, 16, 2, 
  // line 2
  4, 6, 16, 4, 6, 16, 
  16, 16, 8, 8, 8, 4, 6, 16, 
  16, 16, 8, 8, 8, 4, 6, 16, 
  4, 6, 16, 2,
  // line 3
  4, 6, 16, 4, 6, 16, 
  16, 16, 8, 8, 8, 4, 6, 16, 
  16, 16, 8, 8, 8, 4, 6, 16, 
  4, 6, 16, 2,
  // line 4
  1,
  1,
  6, 16, 8, 24, 24, 24, 8, 24, 24, 24, 24, 24, 24, 8,
  8, 24, 24, 24, 24, 24, 24, 8, 8, 24, 24, 24, 24, 24, 24, 8,
  // line 5
  1,
  1,
  1,
  1,
  1,
  // line 6
  1,
  1,
  1,
  1,
  2,
  // line 7
  1,
  1,
  1,
  2,
  1,
  // line 8
  1,
  4, 16, 8, 16, 4, 6, 16,
  16, 16, 8, 8, 8, 1002, 
  1002, 1008, 8, 6, 16,
  16, 16, 8, 8, 8, 1002,
  // line 9
  1003, 8, 4, 4,
  6, 16, 8, 16, 1004,
  1003, 1001.5, 1008, 8,
  1,
  1,
  // line 10
  1,
  1,
  4, 4, 4, 6, 16,
  4, 6, 16, 2,
  // line 11
  4, 4, 4, 6, 16,
  4, 6, 16, 2,
  4, 6, 16, 4, 6, 16,
  16, 16, 8, 8, 4, 6, 16,
  // line 12
  16, 16, 8, 8, 8, 4, 6, 16,
  4, 6, 16, 2,
  4, 6, 16, 4, 6, 16,
  16, 16, 8, 8, 8, 4, 6, 16,
  // line 13
  16, 16, 8, 8, 8, 4, 6, 16,
  4, 6, 16, 2,
  4, 4, 4, 6, 16,
  4, 6, 16, 2,
  // line 14
  16, 16, 8, 8, 8, 4, 6, 16,
  4, 6, 16, 2,
  4, 4, 4, 6, 16,
  4, 6, 16, 2,
  // line 15
  4, 4, 4, 6, 16,
  4, 6, 16, 2,
  4, 6, 16, 4, 6, 16,
  16, 16, 8, 8, 8, 4, 6, 16,
  // line 16
  16, 16, 8, 8, 8, 4, 6, 16,
  4, 6, 16, 2,
  1,
  1,
  // line 17
  1,
  1,
  4, 4, 4, 6, 16,
  4, 6, 16, 4, 6, 16,
  // line 18
  8,  8, 8, 24, 24, 24, 8, 24, 24, 24, 24, 24, 24, 8,
  8,  8, 8, 24, 24, 24, 8, 24, 24, 24, 24, 24, 24, 8,
  24, 24, 24, 8, 4, 2,
  // line 19
  1,
  8, 8, 8, 24, 24, 24, 24, 24, 24, 8, 8, 24, 24, 24,
  24, 24, 24, 8, 8, 24, 24, 24, 8, 24, 24, 24, 8, 8,
  // end
};

int tuneLength = sizeof(imperialMarchTuneTpt1) / 2;

void playMelody(char title[], int tune[], int tempo[], int tuneLength, int buzzPin)
{
  if(DEBUG) {
    Serial.println();
    Serial.println(title);
    Serial.println();
  }
    
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < tuneLength; thisNote++)
  {
    boolean notAttached = (tempo[thisNote] < 1000) ? true : false;
    
    // dealing with notes attached
    int noteTempo = (notAttached) ? tempo[thisNote] : tempo[thisNote] - 1000;

    noteTempo *= 1.5;

    if(DEBUG) {
      if(!(thisNote % 8)) {
        Serial.println();
      }
      Serial.print(tune[thisNote]);
            Serial.print(" ");
            Serial.print(noteTempo);
            if(!notAttached) {
        Serial.print(" attached!");
            }
            Serial.print(", ");
    }

    // set noteDuration
    int noteDuration = 2800 / noteTempo;

    // playNote
    tone(buzzPin, tune[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = (notAttached) ? noteDuration * 1.30 : noteDuration;
    delay(pauseBetweenNotes);
    
    // stop the tone playing:
    noTone(buzzPin);
  }
}

void loop()
{
  playMelody("Star Wars - Imperial March", imperialMarchTuneTpt1, imperialMarchTempoTpt1, tuneLength, buzzer);
}
