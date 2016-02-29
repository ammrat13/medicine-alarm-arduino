/*                        
 * MedicineAlarm.ino
 * By: Tanya Ratnani
 * 
 * This program will keep time from its startup and will sound an alarm 
 * at certain times of day.
 * 
 * Hardware:
 *   * Lithium Ion Rechargeable Battery with USB outlet for phones
 *   * Piezo Buzzer (We used https://www.sparkfun.com/products/7950)
 *   
 * Notes:
 *   * At NO POINT should the battery run out of power. The Arduino 
 * 		 can't keep track of time while off
 *     
 * Function Structure:
 *   setTime( hours, minutes, seconds, days, months, years )
 *     * Sets the time
 *     * Hours are 0-23
 *     * Years are 4 digit
 *   Alarm.alarmRepeat( hours, minutes, seconds, callback )
 *     * Sets an alarm to repeat once daily
 *     * Hours are 0-23
 *     * Callback is a function and must be declared
 *     * Callback parameter is written without parenthesis 
 *       (eg. "func" instead of "func()")
 *   Alarm.delay( milliseconds )
 *     * Like the delay function, but allows for alarms to check if they 
 *       are triggered
 *     * For this reason, DO NOT, UNDER ANY CIRCUMSTANCES, USE delay()
 *   tone( pin#, frequency, duration )
 *     * Frequency in hertz
 *     * Duration in milliseconds
 *   noTone( pin# )
 *     * Stops playing the tone on the pin number
 *   Serial.write( data )
 *     * Sends data over the USB if connected to a computer
*/

//https://www.pjrc.com/teensy/td_libs_Time.html
//Required for the Time Alarms library
#include <Time.h>

//https://www.pjrc.com/teensy/td_libs_TimeAlarms.html
#include <TimeAlarms.h>

//Function called once at the very start
void setup() {

  //For debugging.
  Serial.begin(9600);
  
  //Set the current time and required alarms.
  //CHANGE ALL OF THIS AS NEEDED!!!!!!!!!!!!!!!!!!!!!!

  //CHANGE THIS TO CURRENT TIME!!!!!!!!!!!!!!!!!!!!!!!
  setTime(20, 3, 0, 1, 1, 2016);                 //08:57:00 PM 1 Jan 2016
                                                 //Time of activation
                                                 //CHANGE THIS!!!!!!!!

  Alarm.alarmOnce(20, 3,15, onAlarmTrigger); //08:57:00 PM Once
  
  Alarm.alarmRepeat(16, 0, 0, onAlarmTrigger); //04:00:00 PM Daily
  Alarm.alarmRepeat(21, 0, 0, onAlarmTrigger); //09:00:00 PM Daily
  
}

//Function to be run over and over again after "setup()"
void loop() {

  //For debugging
  //Print the current time to serial.
  printTime();
  
  Alarm.delay(1000);  //DO NOT, UNDER ANY CIRCUMSTANCES, USE delay()
}

//Function to be called when an alarm goes off
void onAlarmTrigger(){

  Serial.println("\nTriggered");
  printTime();
  Serial.println("Doing...");
  
  //Generate a tone on the pin with the speaker
  tone(12, 1000, 5000);
  delay(5000); //This is the one time we can use delay() as we don't 
							 //want alarm going off while we play our tone
  noTone(12);

  Serial.println("Done\n");
  
}

//Prints the time to USB
void printTime(){
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.println(second());
}
