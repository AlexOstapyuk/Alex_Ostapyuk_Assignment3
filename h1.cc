//Alex Ostapyuk
//h1
//Computer Vision

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
using namespace ComputerVisionProjects;



 
//The convolution function applies Sobel's Mask in order to detect the edges of the image
void convolution(Image &an_image) {
    //The new values after Sobel's mask will be stored to convo
    vector<vector<int>> convo(an_image.num_rows(), vector<int>(an_image.num_columns(), 0)); 
    
    //the mask used to convolute the horizontal side
    vector<vector<int>> v_side = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    //the mask used to convolute the vertical side
    vector<vector<int>> h_side = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

    int up_left, up_mid, up_right, mid_left, mid_mid, mid_right, bottom_left, bottom_mid, bottom_right, total_x, total_y, gradient;

    for (int i = 1; i < an_image.num_rows() - 1; ++i) {
        for (int j = 1; j < an_image.num_columns() - 1; ++j) {

            // Calculation of the current pixel with surrounding pixels to determin the edge for the vertical side
            up_left = v_side[0][0] * an_image.GetPixel(i - 1, j - 1);
            up_mid = v_side[0][1] * an_image.GetPixel(i - 1, j);
            up_right = v_side[0][2] * an_image.GetPixel(i - 1, j + 1);
            mid_left = v_side[1][0] * an_image.GetPixel(i, j - 1);
            mid_mid = v_side[1][1] * an_image.GetPixel(i, j);
            mid_right = v_side[1][2] * an_image.GetPixel(i, j + 1);
            bottom_left = v_side[2][0] * an_image.GetPixel(i + 1, j - 1);
            bottom_mid = v_side[2][1] * an_image.GetPixel(i + 1, j);
            bottom_right = v_side[2][2] * an_image.GetPixel(i + 1, j + 1);

            total_x = (up_left + up_mid + up_right + mid_left + mid_mid + mid_right + bottom_left + bottom_mid + bottom_right);

            // Calculation of the current pixel with surrounding pixels to determine the edge for the horizontal side
            up_left = h_side[0][0] * an_image.GetPixel(i - 1, j - 1);
            up_mid = h_side[0][1] * an_image.GetPixel(i - 1, j);
            up_right = h_side[0][2] * an_image.GetPixel(i - 1, j + 1);
            mid_left = h_side[1][0] * an_image.GetPixel(i, j - 1);
            mid_mid = h_side[1][1] * an_image.GetPixel(i, j);
            mid_right = h_side[1][2] * an_image.GetPixel(i, j + 1);
            bottom_left = h_side[2][0] * an_image.GetPixel(i + 1, j - 1);
            bottom_mid = h_side[2][1] * an_image.GetPixel(i + 1, j);
            bottom_right = h_side[2][2] * an_image.GetPixel(i + 1, j + 1);

            total_y = (up_left + up_mid + up_right + mid_left + mid_mid + mid_right + bottom_left + bottom_mid + bottom_right);

            //Apply the squared gradient so we can combine both the horizontal and vertical edges
            gradient = sqrt(total_x * total_x + total_y * total_y);

            //make sure that the gradient is not greater than the highest RGB
            gradient = min(255, gradient);



            //Place the edge values into the temporary 2D vector convo
            convo[i][j] = gradient;
        }
    }

    //Set the pixel of the image to the edge values that we got for convo
    for (int i = 0; i < an_image.num_rows(); ++i) {
        for (int j = 0; j < an_image.num_columns(); ++j) {
            an_image.SetPixel(i, j, convo[i][j]);
        }
    }
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

  convolution(an_image);
  
  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}