#include<opencv2/opencv.hpp>
#include<iostream>
#include<dest/dest.h>
#include<dest/face/face_detector.h>
using namespace std;
using namespace cv;
using namespace dest;
using namespace dest::face;

Point p1,p2;
int coun1t=0;
Mat templ,templ1;

Mat src,thresh,bg,fg,element,result_a,result_b;

int LH=0,LS=0,LV=0,HH=180,HS=255,HV=255;
vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  //vector<vector<int> > hulli;
int main(int argc, char **argv)
{
	namedWindow("original", WINDOW_NORMAL);

	namedWindow("hsv", WINDOW_NORMAL);
	VideoCapture cap(1);

		createTrackbar("LH","original",0,180);
		createTrackbar("LS","original",0,255);
		createTrackbar("LV","original",0,255);
		createTrackbar("HH","original",0,180);
		createTrackbar("HS","original",0,255);
		createTrackbar("HV","original",0,255);

	//cap.read(src);
	while(1)
	{
		cap>>src;
		HH= getTrackbarPos("HH","original");
		HV= getTrackbarPos("HS","original");
		HS= getTrackbarPos("HV","original");
		LH= getTrackbarPos("LH","original");
		LV= getTrackbarPos("LS","original");
		LS= getTrackbarPos("LV","original");
		
		cvtColor(src,thresh,CV_BGR2HSV);
		inRange(thresh,Scalar(0,135,81),Scalar(21,255,255),thresh);

		erode(thresh,thresh,getStructuringElement(MORPH_RECT,Size(5,5)));
	//	erode(thresh,thresh,getStructuringElement(MORPH_RECT,Size(3,3)));
		dilate(thresh,thresh,getStructuringElement(MORPH_RECT,Size(5,5)));
		dilate(thresh,thresh,getStructuringElement(MORPH_RECT,Size(5,5)));

		findContours(thresh,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

			 //drawContours(src,contours,-1,Scalar(255,0,0));
		int area=0,imax=0,max=0;
		if(contours.size()!=0)
		{
			for(int i=0;i<contours.size();i++)
			{
				area=contourArea(contours[i]);
				if(max<area)
				{
					max=area;
					i=imax;
				}
			}
			
			RotatedRect rect;
			rect=minAreaRect(Mat(contours[imax]));
			// drawContours(src,contours,imax,Scalar(255,0,0));
			 Point2f rect_points[4]; 
			 rect.points( rect_points );
			 Point2f x1,x2;
			 x1.x=10000;
	       for( int j = 0; j < 4; j++ )
		   {
				line( src, rect_points[j], rect_points[(j+1)%4], Scalar(255,0,0), 4, 8 );
				/*if(x1.x<rect_points[j].x)
				{
					x2=x1;
					x1=rect_points[j];
				}*/
				x1=rect_points[1];
				x2=rect_points[2];
				cout<<x1.x<<" "<<x1.y<<endl;
				cout<<x2.x<<" "<<x2.y<<endl;
		   }
		   cout<<"angle= " <<atan((x1.y-x2.y)/(x1.x-x2.x))*180/M_PI<<endl;
		   cout<<endl;
		}
		


/*
       Point2f rect_points[4]; rect.points( rect_points );
       for( int j = 0; j < 4; j++ )
		  line( src, rect_points[j], rect_points[(j+1)%4], Scalar(255,0,0), 1, 8 );
*/
		imshow("original",src);
		imshow("hsv",thresh);

	//	while(1)
			if((char)waitKey(30)=='q')break;
	}	
	cvDestroyAllWindows();
	return 0;
}
	
