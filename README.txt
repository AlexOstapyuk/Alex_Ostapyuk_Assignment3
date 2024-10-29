#Alex Ostapyuk Computer Vision HW3

#Completed Parts
h1
h2
h3

#Half Completed Part
h4

#Comments on the code

h1 - In h1, I used Sobel's Mask in order to get the horizontal and vertical edges and then used the squared gradient in order to combine these two together. In this, I notice there are slight
pixel mismatches compared to the original, but it is extremely small mismatches

h2- I thresholded the image, same way I did for the previous assignment(I used threshold 22)

h3 - In h3, I used Hough Transformation to get the accumulator array. I managed to get the same shape, however I did not manage to get the same color as the results given, mine is a little
darker but seems to be overall correct. For the txt, I decided to save it as the "image" that will simply store the voting number
the txt file is kinda like this format if the image is 3 x 3
0 9 0
2 5 5
9 0 2

h4 - I attempted to get the accumulator from the txt file, but looking back maybe it would have been better to store the labeled values with the coordinates so I would not have to loop
and maybe it would have been able to run it better. I tried to run it with my current function, but I get the same result as the output. I am unsure what my error is, but with what I have
written I believe I should have had some lines. Since the output is not the same, the threshold does not really matter but I would also try 21 at first if it did work

#How to run it
(For Linux)
make all 
./h1.o {input image} {output image}
./h2.o {input image} {21} {output image}
./h3.o {input image} {output image} {txt file}
./h4.o {input image} {input txt} {threshold} {output image}