//Alex Ostapyuk
//h4
//Computer Vision

#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;
using namespace ComputerVisionProjects;



void loadFile(const std::string &filename, std::vector<std::vector<int>> &hough_space) {
    std::ifstream hough_input(filename);
    if (!hough_input.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(hough_input, line)) {
        std::istringstream iss(line);
        std::vector<int> row;
        int value;
        
        while (iss >> value) {
            row.push_back(value);
        }
        
        if (!row.empty()) {
            hough_space.push_back(row);
        }
    }

    hough_input.close();


    //test to check if the transfer from txt to 2D vector was good
    // for(int i=0; i<hough_space.size(); ++i){
    //     for(int j=0; j<hough_space[i].size(); ++j){
    //         std::cout << hough_space[i][j] << " ";
    //     }
    //     cout << endl;
    // }

}

void h4(const std::vector<std::vector<int>> &hough_space, int threshold, Image &image) {
    int row, col;
    double radian;
    for (int i = 0; i < hough_space.size(); ++i) { // theta
        radian = i * (3.14159265 / 180);
        for (int j = 0; j < hough_space[0].size(); ++j) { // rho
            if (hough_space[i][j] >= threshold) {
                for (int y = 0; y < image.num_columns(); ++y) {
                    row = round((j - (y * sin(radian))) / cos(radian));
                    if (row >= 0 && row < image.num_rows()) {
                        image.SetPixel(row, y, 255);
                    }
                }
                for (int x = 0; x < image.num_rows(); ++x) {
                    col = round((j - (x * cos(radian))) / sin(radian));
                    if (col >= 0 && col < image.num_columns()) {
                        image.SetPixel(x, col, 255);
                    }
                }  
            }
        }
    }
}

int
main(int argc, char **argv){
  
  if (argc!=5) {
    printf("Usage: %s file1 txt_file1 threshold file2\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string txt_file(argv[2]);
  const int threshold(stoi(argv[3]));
  const string output_file(argv[4]);

  vector<vector<int>> accumulator;
  
  //store the values from the txt file to the 2D vector accumulator
  loadFile(txt_file,accumulator);
  
  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }

  h4(accumulator, threshold, an_image);
  
  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}



