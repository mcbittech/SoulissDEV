/**********************************************************************************/
/* Thermistore -- EPCOS 10k Thermistor in circuit like this:              		  */
/*  Tested with EPCOS NTC B57703M0103G040                                         */
/*   http://www.epcos.com/inf/50/db/ntc_09/ProbeAss__B57703__M703.pdf  			  */
/*                                                                                */
/*		(Ground) ---- (10k-Resister) -------|------- (Thermistor) ---- (+5v)	  */
/*                                          |									  */
/*                                      Analog Pin								  */
/*																				  */
/*								www.mcbittech.it								  */
/*								mcbittech@mcbittech.it  						  */
/**********************************************************************************/

/* ======================================================== */

#include "Arduino.h"
#include "Termistore.h"

//--------------------------
Termistore::Termistore(int pin) {
  _pin = pin;
}

//--------------------------
float Termistore::getTemp() {
 // Nominal resitance for the thermistor (ohm value)
 #define K_Termistore 10000
 // Nominal temperature depicted on the datasheet @nominal resistance
 #define T_Termistore 25
 // Number of samples
 #define N_Campioni 25
 // Beta value of Thermistor
 #define Bvalue 3988
 // Value of the series resistor
 #define K_Serie 10000

 int mostra[N_Campioni];
 int i;
	 float media;

	 for (i=0; i< N_Campioni; i++) {
		 mostra[i] = analogRead(_pin);
		 delay(1);
	 }

	 media = 0;
	 for (i=0; i< N_Campioni; i++) {
		 media += mostra[i];
	 }
	 media /= N_Campioni;
	 // Thermal value to resistance
	 media = 1023 / media - 1;
	 media = K_Serie / media;

	 //Beta Factor equation
	 float Temp;
	 Temp = media / K_Termistore;                    // (R/Ro)
	 Temp = log(Temp);                               // ln(R/Ro)
	 Temp /= Bvalue;                                 // 1/B * ln(R/Ro)
	 Temp += 1.0 / (T_Termistore + 273.15);          // + (1/To)
	 Temp = 1.0 / Temp;                              // Inversion of value
	 Temp -= 273.15;                                 // Celsius Conversion


  return Temp;  // Return the Temperature
}

/* ======================================================== */