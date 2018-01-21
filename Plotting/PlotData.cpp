
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> // for random data
using namespace std;

#define NT 10
#define NX 5
#define NY 5
#define NZ 5

/**
  Writes data for GNU functions from a given matrix
**/

void write_data( double (* Matrix)[NT][NX][NY][NZ] ) {

  double value = 0;
  string tab = "   ";
  string filename;
  string file_location = "data/";
  string filename_base = "dataset_";
  string filename_end = ".txt";
  ofstream fid;

  for (int t=0; t<NT; t++) {
      filename = file_location + filename_base + to_string(t) + filename_end;

      fid.open(filename);

      for (int x=0; x<NX; x++) {
          for (int y=0; y<NY; y++) {
              for (int z=0; z<NZ; z++) {
                  value = (*Matrix)[t][x][y][z];
                  fid << x << tab << y << tab << z << tab << value << endl;
              }
          }
      }
      fid.close();
  }
}

/**
  Calls GNU file animate.gnu
  which creates animated plot of the data created by write_data
**/

int callGNU() {

  string str = "gnuplot ";
  str.append("animate.gnu");

  const char * command_line = str.c_str();

  system(command_line);
  return 0;

}

/**
  Uses Filler Data (testing)
**/

int main(){

  double M[NT][NX][NY][NZ];

  for (int t=0; t<NT; t++) {
    for (int x=0; x<NX; x++) {
      for (int y=0; y<NY; y++) {
        for (int z=0; z<NZ; z++) {
          M[t][x][y][z] = rand() % 100 + 1; // random number
        }
      }
    }
  }

  write_data( &M );
  callGNU();

}
