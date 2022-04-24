#pragma once

#include "ICommunication.hpp"

class SerialCommunication : public ICommunication {
  private:
    bool m_isOpen;

  public:
    SerialCommunication() {
      m_isOpen = false;
    }

    bool isOpen(){
      return m_isOpen;
    }

    void start(){
      Serial.setTimeout(1);
      Serial.begin(SERIAL_BAUD_RATE);
      m_isOpen = true;
    }

    void output(char* data){
      Serial.print(data);
      Serial.flush();
    }

    bool hasData() {
      return Serial.available() > 0;
    }

    bool readData(char* input, size_t buffer_size){
      size_t size = Serial.readBytesUntil('\n', input, buffer_size);
      input[size] = NULL;
      return size > 0;
    }
};
