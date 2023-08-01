/*
#########################################################################################
futari.ino
                          #############################
                          # CopyRight to Min Sup Kim  #
                          #############################

[Purpose]
Forbid to ride kickboard over two guys

[Hardware]
We would use 8 pressure sensors, so we need to have at least 8 pins

[Software]
Step on over two specific foot-shaped stickers, think of over two guys ride kickboard
--> send signal to stop

[Fuctions]
pin_setup(): Set up analog pins
print_db(): Show information pressure sensor's resistance data on Serial Monitor
over_two(): Judge over two guys riding on kickboard
#########################################################################################
*/


/* Measure the voltage at 5V and resistance of your 3.3k resistor, and enter */
const double VCC = 4.98; // Measured voltage of Ardunio 5V line
const double R_DIV = 3230.0; // Measured resistance of 3.3k resistor


/* Sensor Pin Setting */
const int pin_length = 6;
const int pin_arr[pin_length] = {A0, A1, A2, A3, A4, A5};


/* Delay time */
const int delay_time = 500;


/* Function Prototype */
void pin_setup(const int, const int&); // Set up initial pin settings
void print_db(const double); // Show information about pressure sensors
const bool over_two(const double); // Judge over two guys riding on kickboard




void setup()
{
  // Open serial monitor
  Serial.begin(9600);
  // pin setting
  pin_setup(pin_arr, pin_length);
}




void loop() 
{
  // Read db from analogPins
  int ADC_arr[pin_length];
  int sum{0};
  for (int i = 0; i < pin_length; i++)
  {
    int tmp = analogRead(pin_arr[i]);
    ADC_arr[i] = tmp;
    sum += tmp;
  }
  
  
  // If the FSR has no pressure, the resistance will be near infinite. 
  // So the voltage should be near 0.
  if (sum) // If the analog reading is non-zero
  {
    double voltage_arr[pin_length];
    // Use ADC reading to calculate voltage:
    for (int i = 0; i < pin_length; i++)
      voltage_arr[i] = ADC_arr[i] * VCC / 1023.0;

    // Use voltage and static resistor value to calculate FSR resistance:
    double resistance_arr[pin_length];
    for (int i = 0; i < pin_length; i++)
      resistance_arr[i] = R_DIV * (VCC / voltage_arr[i] - 1.0);

    print_db(resistance_arr);
  }
}




/*
Turn on every sensors'pin
analog pin: 6, digital pin: 2
*/
void pin_setup(const int pin_arr[], const int& pin_length)
{
  // Turn on pressure sensors
  for (int i = 0; i < pin_length; i++)
    pinMode(pin_arr[i], INPUT);
}


/* Print all pressure sensors data */
void print_db(const double resistance_arr[])
{
  Serial.println("===========================");
  for (int i = 0; i < pin_length; i++)
    Serial.println("Resistance" + String(i) + ": " + String(resistance_arr[i]) + " ohms");
  delay(delay_time);
}


/*
Judge how many guys ride kickboard 
If over two --> true
not --> false
*/
const bool over_two(const double resistance_arr[])
{

}