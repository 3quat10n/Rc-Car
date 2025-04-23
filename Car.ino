#include <WiFi.h>

// Define the SSID and password for the Access Point
const char *ssid = "ESP32-Rc-CAR";
const char *password = "123456789";

//struct type for motors
struct Motor{
    int a;
    int b;
};

const struct Motor MOTOR_A = {13,12};
const struct Motor MOTOR_B = {15,14};

// Define the TCP server port (use any port number, e.g., 12345)
const int tcpPort = 4444;

WiFiServer server(tcpPort);

void driveMotor(struct Motor motor,int x, int y){
    digitalWrite(motor.a, x);
    digitalWrite(motor.b, y);
} 

void FORWARD(){
    driveMotor(MOTOR_A,1,0);
    driveMotor(MOTOR_B,1,0);
}
void BACKWARD(){
    driveMotor(MOTOR_A,0,1);
    driveMotor(MOTOR_B,0,1);
}
void LEFT(){
    driveMotor(MOTOR_A,1,0);
    driveMotor(MOTOR_B,0,0);
}
void RIGHT(){
    driveMotor(MOTOR_A,0,0);
    driveMotor(MOTOR_B,1,0);
}
void ROTATE_LEFT(){
    driveMotor(MOTOR_A,1,0);
    driveMotor(MOTOR_B,0,1);
}
void ROTATE_RIGHT(){
    driveMotor(MOTOR_A,0,1);
    driveMotor(MOTOR_B,1,0);
}
void STOP(){
    driveMotor(MOTOR_A,0,0);
    driveMotor(MOTOR_B,0,0);
}

void setup() {

  WiFi.softAP(ssid, password);

  // Start the TCP server
  server.begin();

  pinMode(MOTOR_A.a, OUTPUT);
  pinMode(MOTOR_A.b, OUTPUT);

  pinMode(MOTOR_B.a, OUTPUT);
  pinMode(MOTOR_B.b, OUTPUT);
}

void loop() {
  // Check for new client connections
  WiFiClient client = server.available();

  if (client) {
    // Read incoming data from the client

    while (client.connected()) {

      if (client.available()) {

        char data = client.read();  // Read a byte of data from the client

        switch (data) {

            case 'z':
                FORWARD();
                break;

            case 'q':
                LEFT();
                break;
            
            case 'd':
                RIGHT();
                break;

            case 's':
                BACKWARD();
                break;

            case 'a':
                ROTATE_LEFT();
                break;

            case 'e':
                ROTATE_RIGHT();
                break;

            default:
                STOP();                
        }
      }
    }
    // Client disconnected
    client.stop();
  }
}
