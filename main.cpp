#include "raylib.h"
#include<iostream>
#include <iostream>
#include <random>
#include <cmath>


const int screenWidth = 600;
const int screenHeight = 600;

struct vector2 { float x, y; };

// this is a pseudo random gradient generator
// will give same output for the same input

vector2 randomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;

    b ^= a << s | a >> w - s;
    b *= 1911520717;

    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    vector2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}


//compute the dot product of ditance vector and gradient vector
// the int data is used to find the nearest gradient at the point 
// the float is the actual cordinates of the point

float dotGridGradient(int ix, int iy, float x, float y)
{
	vector2 gradient = randomGradient(ix, iy);
       //computing the distance vector
    float dx = x - ix;
    float dy = y - iy;

    return(dx * gradient.x + dy *gradient.y);


}



// combinibn values ina more mathematical way
float interpolate(float a0, float a1, float w)
{
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;

}


float perlinNoise(float x, float y) //  actual cordinates of the point
{	
	int x0 = (int)x;  // we get the crrent cell 
	int y0 = (int)y;  //  by arranging them we get the all the cordinates of 
	int x1 = x0 + 1;  //  4 adjacent corner
	int y1 = y0 + 1;

    

	float xf = x - (float)x0;   // this is the cordinates of the point with respect to the cell
	float yf = y - (float)y0;   //also used  as intepoalation weights



    //computing the dotproduct gradient and position
    float n0 = dotGridGradient(x0, y0, x, y);  //top left corner  (my left)
    float n1 = dotGridGradient(x1, y0, x, y); //tor right corner (my right)
   
    //interpolating 
    float ix0 = interpolate(n0, n1, xf);



    //computing the dotproduct gradient and position
    n0 = dotGridGradient(x0, y1, x, y); //botton  left corner  (my left)
    n1 = dotGridGradient(x1, y1, x, y); //bottom  right corner (my right)
    
    //interpolating 
    float ix1 = interpolate(n0, n1, xf);


    float value = interpolate(ix0, ix1, yf);
    return value;


}
