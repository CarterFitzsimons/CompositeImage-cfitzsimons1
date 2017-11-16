//Author: Carter Fitzsimons
#include <iostream>
#include "bitmap.h"
#include <string>
#include <vector>

using namespace std;

string userInput; //holds the users input

int numPhotos = 0; //number of photos added

Pixel rgb; //pixel 1 
Pixel gbr; //holds a second pixel so the information from one can be transfered to the other.
Bitmap photo; //holds the currently used photo
vector <Bitmap> allImages; //vector that holds the bitmap of every image inputted by the user
vector <vector <Pixel> > current; //holds the currently used pixel map whos values are being pulled out
vector <vector <Pixel> > merged; //holds the pixel map that will become a final merged image,

int x = 0; // X value of resolution of final, merged image
int y = 0; // Y value of resolution of final, merged image, 




void getUserImages(){
	bool isFinished = false; //will be used to determine whether to loop again or finish the function
	
	int tx; // X value of the resolution of current image
	int ty; // Y value of resolution of current image
	
	while (isFinished == false){
		
		cout << "Please enter a valid .bmp file. If you are finsihed, input DONE" << endl;
		cin >> userInput; // enters the file name of the current image
		
		if (userInput == "DONE"){  //if DONE is inputted the getUserImages function ends
			isFinished = true; // this value will be checked when the loop checks its condition. the loop will end.
			continue;
		}
		if (numPhotos >= 10){
			continue;
		}
		photo.open(userInput);
		
		if (photo.isImage() == true){  //checks to see if it is a valid .bmp file
			
			current = photo.toPixelMatrix();
			tx = current.size();
			ty = current[tx].size();
			
			if(x == tx){  
				if(y == ty){   //nested loops check the images resolution before adding the image to the allImages vector
					allImages.push_back (photo);
					cout << "Got it." << endl;
				}
			}
			
			if(x == 0){ //only the first inputted image goes through this if statement as no non-zero x value exists
				
				merged = current; //sets the final photo to have the same resolution as the first one inputted, rgb values will be reset later
				x = current.size(); //X value of resolution, setting this value 
				y = current[x].size(); //Y value of resolution
				allImages.push_back(photo); 
				cout << "Got it." << endl;
			}
			
			if(x != tx || y != ty) { //checks to see if the new files resolutions don't match and outputs a warning if so
				cout << "The images must be the same resolution." << endl;
				continue;
			}
			numPhotos += 1;
		}
	}
}

void setToZero(){ //sets the pixels rgb values to 0

for(int tx = 0; tx < x - 1; tx++)  //important note: the tx and ty here are entirely seperate from the tx and ty in the getUserImages() function
	{
		for(int ty = 0; ty < merged[tx].size() - 1; ty++){ //nested for loops go through each pixel and change its value to 0
			rgb = merged[tx][ty]; //selects pixel 
			rgb.blue = 0;
			rgb.red = 0;     //changes color values to 0
			rgb.green = 0;
			
			merged[tx][ty] = rgb; //puts pixel back in
		}
	}
photo.fromPixelMatrix(merged); //saves 
}

void addAnImage(const vector< vector <Pixel> > &current){ // divides the R, G, and B values of each pixel in an image by the # of images and adds it into merged bmp

for(int tx = 0; tx <= x - 1 ; tx++)  //important note: the tx and ty here are entirely seperate from the tx and ty in the getUserImages() function
	{
		for(int ty = 0; ty <= y - 1 ; ty++){ //nested for loops go through each pixel and change its value to 0
			rgb = merged[tx][ty]; //selects pixel to be added to
			gbr = current[tx][ty]; //selects pixel to add
			
			rgb.blue += (gbr.blue / numPhotos - 1);
			rgb.red += (gbr.red / numPhotos - 1);
			rgb.green += (gbr.green / numPhotos - 1);
			
			merged[tx][ty] = rgb; //puts pixel back in
		}
	}
photo.fromPixelMatrix(merged); //saves 
}

int main(){
	cout << "Enter up to 10 photos and a composite photo will be made for you." << endl;
	
	getUserImages(); //gets all of the photo file names from the user and stores them in a vector of bitmaps for later
	
	setToZero(); //sets a vector of vector of pixels (named merged) with the correct resolution to have all its RGB values equal to 0 so we have a clean slate to work with
	
	for(int i = 0; i <= numPhotos - 1 ; i++){
		photo = allImages[i];
		current = photo.toPixelMatrix();
		cout << "Image " << i + 1 << " of " << numPhotos << "." << endl;
		addAnImage(current);
	}
	
	photo.save("composite-cfitzsimons1.bmp");
}
	



