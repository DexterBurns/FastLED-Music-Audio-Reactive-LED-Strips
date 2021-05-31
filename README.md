# FastLED-Music-Audio-Reactive-LED-Strips
This project is about creating LED strips that react to music. I'm using the FastLED Library. 
Circuit Diagrams will be included soon, along with IC data sheets.
feel free to email: dexter.burns456@gmail.com should you require any further information on project details.

This Code contains the full functionality of the audio reactive LED strips.
It requires individually addressible LED strips (NEOPIXELS) to be used properly.
Microcontroller used is the Arduino Uno, but this can be used with any other uController given there are enough GPIO pins to accomodate.
Used the MSGEQ7 IC to separate the audio signal into 7 Bands(in Hz), 63, 160, 400, 1000, 2500, 6250, 16000

The LED strip is be able to react to each frequency band of the incoming audio signal and the intensity of the signal in each band will be shown 
in groups of 15 LED's that are different individual colors (15 is arbitrarily chosen, any number can be picked here, i just thought 15 looked nice)


*NOTE*: Circuit Diagrams and physical drawings will be provided in the future. If there's something you want to know, feel free to send a message or email. 

*****
NOTE: Super Important, make sure you're using a power supply with enough supply current to power the LEDs. Max power ratings should come with the LED strip you've bought. If you dont have a suitable powersupply, there are brightness functions within the FastLed Library that you can use to lower the brightness and save on needed current to operate. This should work as a fix if the LED's start blinking erratically from not having enough current.
*****
