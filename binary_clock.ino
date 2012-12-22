/* Arduino binary clock*

 ************************************************************************************
 * Use instructions                                                                 *
 * ######################                                                           *
 * Connect LED's in consecutive order                                               *
 * --> Minute LED's start from PIN2 and end at 7, PIN2 being the binary value of 1, *
 *         PIN3 being the binary value of 2 etc.                                    *
 *     Hour LED's start from pin 8 and end at 12, 8 being the binary value of 1.    *
 *                                                                                  *
 *     set 'minutes' and 'hours' to the appropiate values                           *
 ************************************************************************************
 *                                                                                  *
 *  Developed by Antonis Kalou (kalouantonis@gmail.com) and Anthony Clays           *
 *  under the GPL v3 Licence                                                        *
 ************************************************************************************

 */

 

int minutes = 59;
int hours = 23;

unsigned long lastUpdate; // variables used to correct minor timing errors
unsigned long waitTime;
const unsigned long M60 = 60000000; // 60 million microsenconds = 1 minute

 
void setup()
{

  /* Initialise pins -- set to output*/

  for(int i = 2; i < 13; i++){
    pinMode(i, OUTPUT);
  }  
  minutes--;

  hour_loop(hours);

}

 

void loop()
{
  lastUpdate = micros();

  if(++minutes > 59)
  {
  
    minutes = 0;

    for(int i = 2; i < 8; i++)
      digitalWrite(i, LOW);
      
    if(++hours > 23)
    {
      hours = 0;
      
      for(int j = 8; j < 13; j++)
        digitalWrite(j, LOW);
    }
    else
      hour_loop(hours);
  }

  else
    minute_loop(minutes);
    
  //determine how long to wait before next loop.

  if(lastUpdate > micros()) // micros() loops back to 0 after 70 mins or so
    lastUpdate = 0;

  waitTime = M60 - micros() + lastUpdate;

  delay(waitTime / 1000);

}

 

void minute_loop(int mins)
{

  /* Move minutes to corresponding LED Pin(s) */
  
  boolean current; // should the current pin be ON?

  for(int i = 2; i < 8; i++)
  {
    current = ((mins % 2) == 1);

    digitalWrite(i, current);

    if(current)
      mins--;

    if(mins == 0)
      break;
      
    mins /= 2;
  }
}

 

void hour_loop(int hs)
{

  /* Move hours to corresponding LED pin(s) */

  boolean current;
  
  for(int i = 8; i < 13; i++)
  {
    current = ((hs % 2) == 1);

    digitalWrite(i, current);

    if(current)
      hs--;

    if(hs == 0)
      break;
      
    hs /= 2;

  }
}
