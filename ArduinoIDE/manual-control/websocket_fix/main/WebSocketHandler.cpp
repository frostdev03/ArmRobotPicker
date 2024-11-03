// WebSocketHandler.cpp
#include "WebSocketHandler.h"

// Definisikan WebSocket pada port 81
WebSocketsServer webSocket = WebSocketsServer(81);

void initWebSocket() {
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

// Fungsi untuk menangani event WebSocket
void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
    if (type == WStype_TEXT) {
        String message = String((char*)payload);

        // Parsing pesan dari WebSocket (contoh: "1:90" berarti Servo 1, sudut 90 derajat)
        int servoIndex = message.substring(0, message.indexOf(':')).toInt();
        int angle = message.substring(message.indexOf(':') + 1).toInt();

        // Kontrol servo sesuai dengan pesan yang diterima
        switch (servoIndex) {
            case 1:
                servo1.write(angle);
                servo1b.write(180 - angle);
                break;
            case 2:
                servo2.write(angle);
                break;
            case 3:
                servo3.write(angle);
                break;
            case 4:
                servo4.write(angle);
                break;
            case 5:
                servo5.write(angle);
                break;
            case 6:
                servo6.write(angle);
                break;
            case 7:
                if (angle != stepper.currentPosition()) {
                    stepper.moveTo(angle * (stepper.maxSpeed() / 360));  // Hanya bergerak jika ada perubahan posisi
                }
                break;
        }
    }
}
