#include <string.h>
#include <cmath>
#include <stdio.h>

#include "car_controller.h"
#include "gflags.h"
#include "glog/logging.h"

CarController::CarController() {
  command.resize(10);
  memset(command.data(), 0, command.size());
  command[0] = 0xff;
  command[1] = 0xfe;
  command[2] = ControlMode::CoordinateMode;
}

void CarController::SetMoveParam(int x, int y, int z) {
  int x_flag = (x >= 0 ? 0 : 1);
  int y_flag = (y >= 0 ? 0 : 1);
  int z_flag = (z >= 0 ? 0 : 1);
  x = abs(x);
  y = abs(y);
  z = abs(z);
  if (x > FLAGS_SpeedLimit) x = FLAGS_SpeedLimit;
  if (y > FLAGS_SpeedLimit) y = FLAGS_SpeedLimit;
  if (z > FLAGS_SpeedLimit) z = FLAGS_SpeedLimit;
  command[3] = x / 256;
  command[4] = x % 256;
  command[5] = y / 256;
  command[6] = y % 256;
  command[7] = z / 256;
  command[8] = z % 256;
  command[9] = x_flag << 2 | y_flag << 1 | z_flag;
  std::string x_sign = ""; if(x_flag != 0) x_sign = "-";
  std::string y_sign = ""; if(y_flag != 0) y_sign = "-";
  std::string z_sign = ""; if(z_flag != 0) z_sign = "-";
  LOG(INFO) << "x=" << x_sign.c_str() << x << ", y=" << y_sign.c_str() << y << ", z=" << z_sign.c_str() << z;
}
