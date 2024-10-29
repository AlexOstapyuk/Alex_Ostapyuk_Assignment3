//Alex Ostapyuk
//h2
//Computer Vision


#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

//same function as p1 from previous assignment
void h1(Image *an_image, const int threshold){
  if (an_image == nullptr) abort();

  for(int i=0; i<an_image->num_rows(); ++i){
    for(int j=0; j<an_image->num_columns(); ++j){
      if(an_image->GetPixel(i,j) >= threshold){
          an_image->SetPixel(i,j,255);
      }
      else{
        an_image->SetPixel(i,j,0);
      }
    }
  }
}

int
main(int argc, char **argv){
  
  if (argc!=4) {
    printf("Usage: %s file1 threshold file2\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const int threshold(stoi(argv[2]));
  const string output_file(argv[3]);

  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }

  h1(&an_image, threshold); 
  
  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}



