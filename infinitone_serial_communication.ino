
#// Receive with start- and end-markers combined with parsing

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use by strtok() function

      // variables to hold the parsed data

int servo1 = 0;
int servo2 = 0;
int servo3 = 0;
int servo4 = 0;
int servo5 = 0;


boolean newData = false;

//============

void setup() {
    Serial.begin(115200);
    Serial.println("Ready");
    
}

//============

void loop() {
    recvWithStartEndMarkers();
    if (newData == true) { 
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() replaces the commas with \0
        parseData(); 
        servos();
        newData = false;
    }
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {

      // split the data into its parts
    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,"/");      // get the first part - the string
    servo1 = atoi(strtokIndx); // copy it to servo1
  
    strtokIndx = strtok(NULL, "/"); // this continues where the previous call left off
    servo2 = atoi(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, "/");
    servo3 = atoi(strtokIndx);

    strtokIndx = strtok(NULL, "/");
    servo4 = atoi(strtokIndx);

    strtokIndx = strtok(NULL, "/");
    servo5 = atoi(strtokIndx);

}

//============

void servos() {
    Serial.print("servo1 ");
    Serial.println(servo1);
    Serial.print("servo2 ");
    Serial.println(servo2);
    Serial.print("servo3 ");
    Serial.println(servo3);
    Serial.print("servo4 ");
    Serial.println(servo4);
    Serial.print("servo5 ");
    Serial.println(servo5);

    analogWriteResolution(12);
          analogWrite(2,servo1);
          analogWrite(3,servo2);
          analogWrite(4,servo3);
          analogWrite(5,servo4);
          analogWrite(6,servo5);


    
    
}
