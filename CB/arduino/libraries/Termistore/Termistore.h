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

#ifndef Termistore_h
#define Termistore_h

#include "Arduino.h"
#include "math.h"


class Termistore {
	public:
		Termistore(int pin);
		float getTemp();
	private:
		int _pin;
};

#endif