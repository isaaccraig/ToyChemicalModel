
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void write_data( Matrix *M ) {
  // matrix is time by x by y by z by concentration
  string tab = "   ";
  string filename;
  string file_location = "data/";
  string filename_base = "dataset_";
  string filename_end = ".txt";
  ofstream fid;

  int Nt = M.Nt;
  int Nx = M.Nx;
  int Ny = M.Ny;
  int Nz = M.Nz;

  for (int t=0; t<Nt; t++)

      filename = file_location + filename_base + to_string(t) + filename_end;
      fid.open(filename);

      for (int x=0; x<Nx; x++)
          for (int y=0; y<Ny; y++)
              for (int z=0; z<Nz; z++)
                  double value = M[t][x][y][z];
                  fid << x << tab << y << tab << z << value << endl;

      fid.close();

  return 0;

}
