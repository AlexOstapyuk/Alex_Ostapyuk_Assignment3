//Alex Ostapyuk
//h3
//Computer Vision

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;

/*
thoughts on how to use Hough Transformation
first- take the input image, and the output image as parameters (potentially will need a third parameter to store the array values, aka txt file)
second-create a 2D vector accumulator that will store 'labeled edges' values (size of the vector I am still unsure of)
third- traverse through the input image until an edge is detected; then do r= x cos(theta) + y sin(theta) where the r will be the row and theta will be the col for accumulator
fourth- store the accumulator into the output image and have a for loop to store the accumulator values to the txt file

I think this is enough?


*/

/*
In h3, we will use Hough Transformation in order to get the accumulator array for the image
*/
void h3(Image &an_image) {
    
    // Get the value of the diagonal
    int diagonal = round(sqrt(pow(an_image.num_rows(),2) + pow(an_image.num_columns(),2)));
    
    //create a 2D vector that will store the accumulator (we use diagonal * 2 to include the negative side, although images do not have negative pixels, 
    //lines can go a negative direction)
    vector<vector<int>> accumulator(diagonal * 2, vector<int>(180, 0)); 


    //variables needed for calculation
    double radian = 0; //to compute theta to radian
    double r = 0; //rho
    int total = 0; //the total rho after applying the xcos(theta) + ysin(theta)
    int maxValue = 0; //the maximum label that we have

    // Go through the threshold image
    for (int i = 0; i < an_image.num_rows(); ++i) {
        for (int j = 0; j < an_image.num_columns(); ++j) {
            //if it is not an edge, continue to next pixel
            if (an_image.GetPixel(i, j) != 255) { 
                continue;
            }
            //for loop to test all theta variables
            for (int h = 0; h < 180; ++h) {
                radian = h * 3.14159265 / 180;  // Convert degree to radian
                r = i * cos(radian) + j * sin(radian);
                total = round(r) + diagonal; 

                if (total >= 0 && total < diagonal * 2) { 
                    accumulator[total][h]++;
                    maxValue = max(accumulator[total][h], maxValue);
                }
            }
        }
    }

    //make the image have the size of accumulator as we need to output accumulator lines
    an_image.AllocateSpaceAndSetSize(180, diagonal * 2);

    //variables needed for setting image
    int value = 0;
    int scaledValue = 0;

    //Set the new image
    for (int i = 0; i < diagonal * 2; ++i) {
        for (int j = 0; j < 180; ++j) {
            value = accumulator[i][j];

            //make sure that the color will be within range for setting the pixel
            scaledValue = (255 * value / maxValue); 
            an_image.SetPixel(j,i,scaledValue); 
        }
    }
}



int main(int argc, char **argv){
    if (argc != 4) {
        printf("Usage: %s file1 file2 txt_file\n", argv[0]);
        return 0;
    }
    const string input_file(argv[1]);
    const string output_file(argv[2]);
    const char* output_txt(argv[3]);


    Image an_image;
    if (!ReadImage(input_file, &an_image)) {
        cout << "Can't open file " << input_file << endl;
        return 0;
    }

    Image hough;
    h3(an_image);

    //open the txt file
    std::ofstream txt_file(output_txt);

    //put the accumulated image values to the txt file
    //simply put the pixel and move on
    for(int i=0; i<an_image.num_rows(); ++i){
        for(int j=0; j<an_image.num_columns(); ++j){
            txt_file << an_image.GetPixel(i,j) << " ";
        }
        txt_file << std::endl;
    }
    txt_file.close();

    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
}
}