### Using several filters, this program takes as input a photo in jpg format and the user chooses the action. It can choose between Grayscale, to make the photo black and white, Blu, which blurs the pixels of the entire photo or Detect edges, which blurs the edges of the objects in the photo, edges which are detected as an abrupt difference between the colours of the pixels. As output, it generates the filtered photo.

I used different alghoritms for each filter to implement the functions.
The actual functions for the filters are coded in helpers.c. Then, the filter.c program calls the functions from helpers.c and runs the program, ultimately giving the output photo.
