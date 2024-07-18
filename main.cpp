

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
