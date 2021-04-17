#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h> 
//Libraries for our elements to work

LiquidCrystal lcd(13,12, 11, 10, 9, 8);
const byte rows = 4;
const byte columns= 4;
char buttons[rows][columns]=
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'}, 
{'*', '0', '#', 'D'} 
};
byte rowsPins [rows] = {2,3,4,5};
//Connect to the row pinouts of the keypad 
byte columnPins[columns]= {A3,A2,A0,A1}; 
//Connect to the column pinouts of the keypad
Keypad keypad= Keypad(makeKeymap(buttons), rowsPins, columnPins, rows,
columns);
//Create Keypad object
//By the method makeKeymap we create a map for our keypad

int lock = HIGH;
Servo servo;
String inputPassword = "";
String password = "1234";
//Define begin password

void setup()
{ 
 lcd.begin(16, 2);
 lcd.print("Lcd is Working");
 delay(1000);
 lcd.clear();
 servo.attach(7);
 servo.write(0);
}
void loop()
{
 char button = keypad.getKey();
  //Get clicked button from the keypad
  /*getKey() Reports the ASCII value of a key being 
  pressed or released on an attached USB keyboard*/
  
 if (button != NO_KEY)
 {
   /*Returns the keycode of the pressed key,
   or NO_KEY if no key is pressed.
   The keycode is retrieved from the keymap array.*/
   
   switch(button)
   {
     case '*': //Click '*' when we want to lock the safebox
       lcd.clear();
       inputPassword = "";
       servo.write(0); //Micro Servo turns to 0 degrees
       lcd.setCursor(0,1);
       lcd.write("Locking");
       delay(1000);
       lcd.clear();
       lock = HIGH;
     break;

     case 'A':  //Click A when we want to change password
       lcd.setCursor(0,1);
       if (!lock) // When lock is 0(LOW) then works
       {
         lcd.write("Changing password...");
         password = inputPassword; 
       }
       else
       {
         lcd.write("Password not changed.");
       }
       inputPassword="";
       delay(1000);
       lcd.clear();
       break;
     case '#':
       lcd.setCursor(0,1);

       if(inputPassword == password) 
       {
         servo.write(90); //Micro Servo turns 90 degrees
         lcd.write("Locking");
         lock=LOW;
       }
       else
       {
         lcd.write("Invalid Password"); 
       }
       delay(1000);
       inputPassword = "";
       lcd.clear();
       break;

       default: //Works when we don't choose any of cases
         lcd.write(button);
         inputPassword+=button;
         break;
   }
 }
}
