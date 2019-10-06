

//Variables for the anemometer
byte ReadByteANO = 0;
int startANO = 0; //Start a new NMEA sentence for the Anemometer
int indexANO = 0; //Index of the char array for the Anemometer
int cutANO = 0;
int finANO = 0; //Finish NMEA sentence for the Anemometer
char dataANO[300];
//---------------------------------------------------------------

//Variables for the echolot
byte ReadByteECHO = 0;
int startECHO = 0; //Start a new NMEA sentence for the GPS Device
int cutECHO = 0;
int indexECHO = 0; //Index of the char array for the GPS device
int finECHO = 0; //Finish NMEA sentence for the GPS device
char dataECHO[300];
//---------------------------------------------------------------


boolean sdcardinit = false;
int layer = 0; //The variable layer indicates the current layer of the Graphical-User-Interface
int pinCS = 53;
float volt, celc;//The variables for the temperature

boolean sendbluethooth = true;
boolean currentdata = false;
int sec = 1;

//Variables for the output data
String outputData;//The combined data from the echolot and anemometer is stored here
String quickinfo; //This string contains informtion regarding wind direction and speed for the touchscreen
String windinfo; //This string contains the NMEA 0183 sentence for the anemometer device
String echoinfo; //This string contains the NMEA 0183 sentence for the echolot device
//---------------------------------------------------------------

//Variables for detecting an error regarding the NMEA 0183 devices
int errorECHO = 0;
int errorANO = 0;
//---------------------------------------------------------------


void combineNMEAData() {
  /*
     This function combines the NMEA data and builds
     a new string of information for each transmitting device
  */
  String combinedata;
  String anemometerdata;
  String echolotdata;
  String currentval;

  int len = sizeof(dataANO);
  char copy_data[len];
  memcpy(copy_data, dataANO, sizeof(dataANO));
  char* nmealine = strtok(copy_data, "\n");
  if (strstr(nmealine, "MWV")) {
    int l = strlen(nmealine);
    nmealine[l] = (char)0;
    nmealine = strtok(nmealine, ",");
    currentval += "Windrichtung: ";
    nmealine = strtok(0, ",");
    currentval += nmealine;
    nmealine = strtok(0, ",");
    nmealine = strtok(0, ",");
    currentval += " Grad\n\n\n";
    currentval += " Geschwind.:   ";
    currentval += nmealine;
    currentval += " Knoten";
    quickinfo = currentval;
  }
  dataANO[indexANO] = (char)0;
  dataECHO[indexECHO] = (char)0;
  anemometerdata = dataANO;
  echolotdata = dataECHO;
  combinedata = anemometerdata + echolotdata;
  if (echolotdata != "") {
    echoinfo = echolotdata;
  }
  if (anemometerdata != "") {
    windinfo = anemometerdata;
  }
  if ((anemometerdata != "") && (echolotdata != "") && (finANO == 1) && (finECHO == 1)) {
    outputData = combinedata;
  }
}

void setup()   {
  /*
     Setting up the serial ports and the pins for receiving
     and transmitting the nmea data
  */
  pinMode(5, INPUT);//Digital input from Echolot...
  pinMode(6, OUTPUT);//...where the output is connected to Serial1
  pinMode(7, INPUT);//Digital input from Anemometer...
  pinMode(8, OUTPUT);//where the output is connected to Serial2
  Serial.begin(4800); //Output to PC
  //Serial1.begin(4800); //Output from Anemometer
  
}

void loop()   {
  /*
     Data from the devices is stored in char arrays
     After completion the char array will be checked
     and decoded
  */

  if (digitalRead(7) == LOW)  {
    digitalWrite(8, HIGH);
  }
  else
  {
    digitalWrite(8, LOW);
  }
  
  if (Serial.available())  { //Serial port 1 receives the data from the Anemometer device
    ReadByteANO = Serial.read();
    Serial.write(ReadByteANO);
  }
 
}
