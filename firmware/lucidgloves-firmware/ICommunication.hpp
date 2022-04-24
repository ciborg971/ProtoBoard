#pragma once

//Interface for communication
struct ICommunication {
  virtual bool isOpen() = 0;
  virtual void start() = 0;
  virtual void output(char* data) = 0;
  virtual bool hasData() = 0;
  virtual bool readData(char* input, size_t buffer_size) = 0;
};
