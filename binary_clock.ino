/* Arduino binary clock*
 ************************************************************************************
 * Use instructions                                                                 *
 *######################                                                            *
 * Connect LED in consecutive order                                                 *
 * So ---> Minute LED's start from pin 1 and end at 6, 1 being the binary value of 32,*
 *         2 being the binary value of 16                                           *
 *          etc.                                                                    *
 *                                                                                  *    
 *         Hour LED's start from pin 7 and end at 10, 7 being the binary value of 8 *
 *                                                                                  *
 ************************************************************************************
 *                                                                                  *
 *      Developed by Antonis Kalou (kalouantonis@gmail.com) under the GPL v3 Licence*
 ************************************************************************************
 */

void setup()
{
  /* Initialise pins -- set to output*/
  int i;
  
  Serial.begin(9600); /* Initialise serial port*/
  
  for(i = 0; i < 10; i++)
    pinMode(i, OUTPUT);
}

int minute_loop(int minutes)
{
 /* Move minutes to corresponding LED Pin(s) */ 
  int i;
  int j = 0;
 for(i = 32; j < 6; i/2)
 { 
   int curr_led = 6 - j;
   if(minutes == 0)
     break;
   if(minutes >= i)
    {
      minutes -= i; digitalWrite(curr_led, HIGH);
    }
    else
      digitalWrite(curr_led, LOW);
    j++;
    
  }  
    
  return minutes; /* Check that minutes is 0*/
}

int hour_loop(int hours)
{
 /* Move hours to corresponding LED pin(s) */ 
 int i;
 int j = 0;
 for(i = 8; j < 4; i/2)
 { 
   int curr_led = 10 - j;
   if(hours == 0)
     break;
   if(hours >= i)
    {
      hours -= i; digitalWrite(curr_led, HIGH);
    }
    else
      digitalWrite(curr_led, LOW);
    j++;
    
  }  
  return hours; /* Check that hours is 0*/
  
}

void loop()
{
  int minutes = 0;
  int hours = 0;
  Serial.print("Enter minutes\n");
  minutes = Serial.read();
  Serial.print("Enter hours\n");
  hours = Serial.read();
  
  while(((minutes <= 60) || (minutes >= 0)) || ((hours <= 24) || (hours >= 0)))
  {
    int minute_val = minute_loop(minutes);
    int hour_val = hour_loop(hours);
    
    if((minute_val != 0) || (hour_val != 0)) /* Check validation of data*/
    { 
      Serial.print("Error in minute or hour calculation: Return value not 0\n");
      exit(1);
    }
    
    delay(6000); /* Wait one minute*/ 
    minutes++;
    if(minutes > 60)
      hours++; minutes = 0;
    if(hours > 24)
      hours = 0;
  }
  Serial.print("Invalid input: You must enter minutes between 0 and 60 and hours between 0 and 24\n");
  
}



