/*@author: Shruti Singh
* 
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <wait.h>

using namespace cv;
using namespace std;

Mat stdfilt(Mat I);//, Mat NHOOD=Mat(3, 3, CV_8UC3,Scalar(1,1,1)) );
Mat stdfilt(Mat I, Mat NHOOD);


// int main(int argc, char** argv )
// {

//     if ( argc != 2 )
//     {
//         printf("usage: DisplayImage.out <Image_Path>\n");
//         return -1;
//     }

//     Mat image;
//     image = imread( argv[1], 1 );

//     if ( !image.data )
//     {
//         printf("No image data \n");
//         return -1;
//     }

//     //Display the image befor stdfilt() and after appplying the function

//     imshow("before", image);

//     Mat J=stdfilt(image, Mat(11,11,CV_8UC3));       // standard deviation of a 11x11 neighbourhood
//                                                     // for default values of neighbourhood=3x3, omit the 2nd argument, i.e. J=stdfilt(image)

//     imshow("after", J);

//     waitKey(0);
//     return 0;

// }


/* Determine the number of channels in the image(eg 3 for RGB images).
*  For each channel, calculate the mean, then variance and finally standard deviation and write to that particular channel of that pixel.
*/

Mat stdfilt(Mat img){

    int channels=img.channels();
    
    int count=0;
    long int w, z, y, x, tempx, tempy;
    double mean[channels], variance[channels];

    int NHOODSizeY=1;
    int NHOODSizeX=1;

    for(y=0;y<img.rows;y++)
    {

            for(x=0;x<img.cols;x++)
            {
                           
                    count=0;
                    while(count<channels)
                    {
                        variance[count]=0;
                        mean[count]=0;
                        ++count;
                    }

                    for(w=(y-NHOODSizeY);w<=(y+NHOODSizeY);++w)
                    {
                            for(z=(x-NHOODSizeX);z<=(x+NHOODSizeX);++z)
                            {
                                    tempy=w;
                                    tempx=z;
                                    if(w>=img.rows)
                                        tempy=2*(img.rows-1)-w;
                                    if(z>=img.cols)
                                        tempx=2*(img.cols-1)-z;

                                    count=0;
                                    while(count<channels)
                                    {

                                        mean[count]+=img.data[channels*(img.cols*abs(tempy) + abs(tempx)) + count];
                                        ++count;
                                    }            
                            }
                    }

                    count=0;
                    while(count<channels)
                    {
                            mean[count]=mean[count]/((NHOODSizeY*2+1)*(NHOODSizeX*2+1));
                            ++count;
                    }
                    for(w=(y-NHOODSizeY);w<=(y+NHOODSizeY);++w)
                    {
                            for(z=(x-NHOODSizeX);z<=(x+NHOODSizeX);++z)
                            {
                                    count=0;
                                    while(count<channels)
                                    {
                                            tempy=w;
                                            tempx=z;
                                            if(w>=img.rows)
                                                    tempy=2*(img.rows-1)-w;
                                            if(z>=img.cols)
                                                    tempx=2*(img.cols-1)-z;
                                        
                                            variance[count]+=pow((img.data[channels*(img.cols*abs(tempy) + abs(tempx) ) + count]-mean[count]),2);
                                            ++count;
                                    }            
                            }
                    }

                    count=0;
                    while(count<channels)
                    {
                                variance[count]=variance[count]/((NHOODSizeY*2+1)*(NHOODSizeX*2+1));
                                img.data[channels*(img.cols*y + x) + count]=sqrt(variance[count]);
                                ++count;
                    }

                    
            }
   }

    //imshow("after", img);
    return img;

}

Mat stdfilt(Mat img, Mat NHOOD ){

    Mat J;
    imshow("before", img);
    int channels=img.channels();

    int count=0;
    long int w, z, y, x, tempx, tempy;
    double mean[channels], variance[channels];

    int NHOODSizeY=(NHOOD.rows)/2;
    int NHOODSizeX=(NHOOD.cols)/2;

    for(y=0;y<img.rows;y++)
    {

            for(x=0;x<img.cols;x++)
            {
                           
                    count=0;
                    while(count<channels)
                    {
                        variance[count]=0;
                        mean[count]=0;
                        ++count;
                    }

                    for(w=(y-NHOODSizeY);w<=(y+NHOODSizeY);++w)
                    {
                            for(z=(x-NHOODSizeX);z<=(x+NHOODSizeX);++z)
                            {
                                    tempy=w;
                                    tempx=z;
                                    if(w>=img.rows)
                                        tempy=2*(img.rows-1)-w;
                                    if(z>=img.cols)
                                        tempx=2*(img.cols-1)-z;
                                    count=0;
                                    while(count<channels)
                                    {

                                        mean[count]+=img.data[channels*(img.cols*abs(tempy) + abs(tempx)) + count];
                                        ++count;
                                    }            
                            }
                    }

                    count=0;
                    while(count<channels)
                    {
                            mean[count]=mean[count]/((NHOODSizeY*2+1)*(NHOODSizeX*2+1));
                            ++count;
                    }
                    for(w=(y-NHOODSizeY);w<=(y+NHOODSizeY);++w)
                    {
                            for(z=(x-NHOODSizeX);z<=(x+NHOODSizeX);++z)
                            {
                                    count=0;
                                    while(count<channels)
                                    {
                                            tempy=w;
                                            tempx=z;
                                            if(w>=img.rows)
                                                    tempy=2*(img.rows-1)-w;
                                            if(z>=img.cols)
                                                    tempx=2*(img.cols-1)-z;
                                        
                                            variance[count]+=pow((img.data[channels*(img.cols*abs(tempy) + abs(tempx) ) + count]-mean[count]),2);
                                            ++count;
                                    }            
                            }
                    }

                    count=0;
                    while(count<channels)
                    {
                                variance[count]=variance[count]/((NHOODSizeY*2+1)*(NHOODSizeX*2+1));
                                img.data[channels*(img.cols*y + x) + count]=sqrt(variance[count]);
                                ++count;
                    }

                    
            }
   }

   //imshow("after", img);
   return img;

}

