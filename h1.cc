// Sample test file for the image class.
// Reads a given pgm image, draws a line, and saves it to
// another pgm image.
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
using namespace ComputerVisionProjects;


void convolution(Image &an_image) {
    vector<vector<int>> convo(an_image.num_rows(), vector<int>(an_image.num_columns(), 0)); // Create an empty 2D space for convoluted image
    for (int i = 0; i < an_image.num_rows(); ++i) {
        for (int j = 0; j < an_image.num_columns(); ++j) {
            convo[i][j] = an_image.GetPixel(i, j);
        }
    }

    vector<vector<int>> x_side = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    vector<vector<int>> y_side = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

    int up_left, up_mid, up_right, mid_left, mid_mid, mid_right, bottom_left, bottom_mid, bottom_right, total_x, total_y, gradient;

    for (int i = 1; i < an_image.num_rows() - 1; ++i) {
        for (int j = 1; j < an_image.num_columns() - 1; ++j) {
            // Sobel X convolution (horizontal edge detection)
            up_left = x_side[0][0] * an_image.GetPixel(i - 1, j - 1);
            up_mid = x_side[0][1] * an_image.GetPixel(i - 1, j);
            up_right = x_side[0][2] * an_image.GetPixel(i - 1, j + 1);
            mid_left = x_side[1][0] * an_image.GetPixel(i, j - 1);
            mid_mid = x_side[1][1] * an_image.GetPixel(i, j);
            mid_right = x_side[1][2] * an_image.GetPixel(i, j + 1);
            bottom_left = x_side[2][0] * an_image.GetPixel(i + 1, j - 1);
            bottom_mid = x_side[2][1] * an_image.GetPixel(i + 1, j);
            bottom_right = x_side[2][2] * an_image.GetPixel(i + 1, j + 1);

            total_x = (up_left + up_mid + up_right + mid_left + mid_mid + mid_right + bottom_left + bottom_mid + bottom_right) / (54);

            // // Sobel Y convolution (vertical edge detection)
            up_left = y_side[0][0] * an_image.GetPixel(i - 1, j - 1);
            up_mid = y_side[0][1] * an_image.GetPixel(i - 1, j);
            up_right = y_side[0][2] * an_image.GetPixel(i - 1, j + 1);
            mid_left = y_side[1][0] * an_image.GetPixel(i, j - 1);
            mid_mid = y_side[1][1] * an_image.GetPixel(i, j);
            mid_right = y_side[1][2] * an_image.GetPixel(i, j + 1);
            bottom_left = y_side[2][0] * an_image.GetPixel(i + 1, j - 1);
            bottom_mid = y_side[2][1] * an_image.GetPixel(i + 1, j);
            bottom_right = y_side[2][2] * an_image.GetPixel(i + 1, j + 1);

            total_y = (up_left + up_mid + up_right + mid_left + mid_mid + mid_right + bottom_left + bottom_mid + bottom_right) / 54;

            // Compute the gradient magnitude (Pythagoras theorem)
            gradient = sqrt(total_x * total_x + total_y * total_y);

            // Clip values between 0 and 255
            gradient = max(0, min(255, gradient));



            // Store the result
            convo[i][j] = gradient;
        }
    }

    for (int i = 0; i < an_image.num_rows(); ++i) {
        for (int j = 0; j < an_image.num_columns(); ++j) {
            an_image.SetPixel(i, j, convo[i][j]);
        }
    }
}

void h1(Image *an_image, Image *edge){
  //ignore edge of image (start at i=1, j=1 and end at i=size-2, j=size-2 so we can do a 3 by 3 check)

  double dx,dy;
  
  for(int i=1; i<an_image->num_rows()-1; i++){
    for(int j=1; j<an_image->num_columns()-1; j++){
        dx = (an_image->GetPixel(i,j+1) - an_image->GetPixel(i,j-1)) / 2.0;

        dy = (an_image->GetPixel(i+1,j) - an_image->GetPixel(i-1,j)) / 2.0;

        edge->SetPixel(i,j,sqrt((dx*dx)+(dy*dy)));
    }
  }

  //can also try convolution, then do gradient

  
}

int
main(int argc, char **argv){
  
  if (argc!=3) {
    printf("Usage: %s file1 file2\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string output_file(argv[2]);

  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }
  Image edge_image = an_image;
  //h1(&an_image, &edge_image);
  convolution(an_image);
  
  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}
