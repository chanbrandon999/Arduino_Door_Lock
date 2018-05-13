#include <Servo.h>

#include<Keypad.h>

Servo servo1;

int angle = 0;

char password[4] = {'2', '3', '5', '7'};
char inputKeys[4];
char key_pressed = 0;
const byte rows = 4;
const byte columns = 4;
char hexaKeys[rows][columns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte row_pins[rows] = {A5, A4, A3, A2};
byte column_pins[columns] = {A1, A0, 3, 6};

bool toggleLight = true;
bool isLocked = true;
char pressedKey  = ' ';
int whichLight = -1;
unsigned long pastTime = 0;

Keypad keypad_key = Keypad(makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);




void light()
{
  if (toggleLight == false)
  {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }
  else
  {
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
  }
  toggleLight = !toggleLight;
}

void light(bool whichOne)
{
  if (whichOne == false)
  {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }
  else
  {
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
  }
  toggleLight = !toggleLight;
}

void flash()
{
  for (int i = 0; i < 30; i++)
  {
    light();
    delay(20);
  }
}

char wait4Press()
{
  char waitKeyPressed = NO_KEY;

  //return keypad_key.waitForKey();
  while (waitKeyPressed == NO_KEY && digitalRead(0) == HIGH)
  {
    waitKeyPressed = keypad_key.getKey(); 
    delay(5);
  }
  
  return waitKeyPressed;
}


void setup() {

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  light();

  servo1.attach(2);      // attach the signal pin of servo to pin9 of arduino
  servo1.write(200);
  delay(2000);
  servo1.detach();
  
  delay(2000);

  pinMode(0, INPUT_PULLUP);
  //digitalWrite(0, HIGH);
}


void loop() {

  //Arduino will always continue in this loop as long as the correct password has not been entered
  while (isLocked == true && digitalRead(0) == HIGH)
  {
    for (int i = 0; i < 4 && digitalRead(0) == HIGH; i++)
    {
      inputKeys[i] = wait4Press();
  
    }

    for (int k = 0; k < 4 && isLocked == true && digitalRead(0) == HIGH; k++)
    {  
      if (inputKeys[k] != password[k])
      {
        isLocked = true;
        
        //Show error
        flash();
        break;
      }
      else if (k = 3)
      {
        isLocked = false;
      }
    }
  }

  pressedKey = ' ';

  light(true);
  
  flash();
  //Unlock
  servo1.attach(2);
  servo1.write(0);
  delay(2000);
  servo1.detach();
  delay(200);



  wait4Press();
  light(false);
//Lock 
  flash();
  isLocked = true;
  servo1.attach(2);
  servo1.write(180);
  delay(400);
  servo1.detach();
  delay(200);


}



