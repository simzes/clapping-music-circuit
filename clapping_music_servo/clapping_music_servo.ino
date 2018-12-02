/**
 * a program to play "clapping music" by steve reich
 * by driving two steppers/servos
 */

#include <Servo.h>

int basic[] = {1,1,1,0,1,1,0,1,0,1,1,0};
int beat_len = 164;
int high_len = 30;
int low_len = 134;
int between_plays = 10 * 1000;

int reps = 8;

int left_pin = 13;
int right_pin = 12;

int initial_position = 35;
int secondary_position = 0;

Servo servo1;
Servo servo2;

void setup() {
  pinMode(left_pin,OUTPUT);
  pinMode(right_pin,OUTPUT);

  servo1.attach(9);
  servo1.write(initial_position);

  servo2.attach(10);
  servo2.write(initial_position);
}

void loop() {
  // loop over both players 
  int cycle_count = sizeof(basic) / sizeof(int);

  int pos1 = initial_position;
  int pos2 = initial_position;

  // do the piece CYCLES number of times
  for (int i = 0; i < (cycle_count + 1); i++) {
    int shift = i % cycle_count;

    // do each cycle REPS number of times
    for (int j = 0; j < reps; j++) {

      // per rep, iterate over each beat (there are CYCLES many beats) and actuate the thing
      for (int k=0; k < cycle_count; k++) {
	int left = basic[k];
	int right = basic[(k + shift) % cycle_count];

	if (left == 1 || right == 1) { 
	  if (left == 1) {
	    // play the left beat
	    // flip to the other position
	    if (pos1 == secondary_position) {
	      pos1 = initial_position;
	    } else {
	      pos1 = secondary_position;
	    }
	    servo1.write(pos1);
	    digitalWrite(left_pin, HIGH);
	  }

	  if (right == 1) {
	    // play the left beat
	    // flip to the other position
	    if (pos2 == secondary_position) {
	      pos2 = initial_position;
	    } else {
	      pos2 = secondary_position;
	    }
	    servo2.write(pos2);
	    digitalWrite(right_pin, HIGH);
	  }

	  delay(high_len);

	  digitalWrite(right_pin, LOW);
	  digitalWrite(left_pin, LOW);

	  delay(low_len);
	} else {
	  // nobody's playing this beat, hang tight
	  delay(beat_len);
	}
      }
    }
  }

  delay(between_plays);
}
