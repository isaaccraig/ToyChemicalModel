#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

  string str = "gnuplot ";

  if (argc <= 1) {
    str.append("animate.gnu");
  } else {
    str.append(argv[1]);
  }

  const char * command_line = str.c_str();

  system(command_line);
  return 0;

}
