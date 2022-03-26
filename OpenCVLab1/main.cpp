//
//  main.cpp
//  OpenCVLab1
//
//  Created by RaaziaT on 09/03/2022.
//

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include "task2.h"

using namespace std;
using namespace cv;

int MAX_KERNEL_LENGTH = 31;
int histSize = 256;


class Lab1 {
public:
    void task1and2(cv::Mat img, cv::Mat img2) {
        cv::namedWindow("Normal Image");
        cv::namedWindow("Grayscale Image");
        cv::imshow("Normal Image", img);
        cv::imshow("Grayscale Image", img2);
        
        std::cout<<"\n Here is the key";
        char key = (char) cv::waitKey(0);
        std::cout<<key;
    }
    
    void task3a(bool horizonatalGradient) {
        cv::Mat imMat(256, 256, CV_8U);
        
        for (int i = 0; i < imMat.cols; i++) {
            for (int j = 0; j < imMat.rows; j++) {
                if(horizonatalGradient)
                    imMat.at<unsigned char> (i, j) = j+2;
                else imMat.at<unsigned char> (i, j) = i+2;
            }
        }
        
        if(horizonatalGradient){
            namedWindow("Horizontal Gradient");
            imshow ("Horizontal Gradient", imMat);}
        else {
            namedWindow("Vertical Gradient");
            imshow ("Vertical Gradient", imMat);}
        
        cv::waitKey(0);
        
    }
    
    void task3b(int chessBoxSize) {
        
        if(chessBoxSize>0 && chessBoxSize<=300) {
            cv::Mat imMat3 = cv::Mat(300, 300, CV_8UC1);
            
            int colorOfCB = 0;
            int startingColorOfCB = 0;
            
            for (int i = 0; i < imMat3.cols; i++) {
                colorOfCB = startingColorOfCB;
                for (int j = 0; j < imMat3.rows; j++) {
                    imMat3.at<unsigned char> (i, j) = colorOfCB;
                    if(j + 1 == imMat3.cols) break;
                    else if((j + 1) % chessBoxSize == 0 && colorOfCB == 0) colorOfCB = 255;
                    else if((j + 1) % chessBoxSize == 0 && colorOfCB == 255) colorOfCB = 0;
                }
                
                if((i + 1) % chessBoxSize == 0 && startingColorOfCB == 0) startingColorOfCB = 255;
                else if((i + 1) % chessBoxSize == 0 && startingColorOfCB == 255) startingColorOfCB = 0;
            }
            
            namedWindow("Chessboard with box size : " + to_string(chessBoxSize));
            imshow ("Chessboard with box size : " + to_string(chessBoxSize), imMat3);
            
            cv::waitKey(0);
        }
    }
    
    void task4(int value, cv::Mat img) {
        
        if(img.channels() == 3){
            for (int i = 0; i < img.cols; i++) {
                for (int j = 0; j < img.rows; j++) {
                    img.at<Vec3b>(i, j).val[value] = 0;
                }
            }
            cv::namedWindow("Setting value of channel : " + to_string(value+1) + " to zero");
            cv::imshow("Setting value of channel : " + to_string(value+1) + " to zero", img);
            cv::waitKey(0);
        }
    }
    
    void task5(cv::Mat img) {
        
        if(img.channels() == 3) {
            
            cv::Mat channel1(img.cols, img.rows, CV_8U);
            cv::Mat channel2(img.cols, img.rows, CV_8U);
            cv::Mat channel3(img.cols, img.rows, CV_8U);
            
            for (int i = 0; i < img.cols; i++) {
                for (int j = 0; j < img.rows; j++) {
                    channel1.at<unsigned char> (i, j) = img.at<Vec3b>(i, j).val[0];
                    channel2.at<unsigned char> (i, j) = img.at<Vec3b>(i, j).val[1];
                    channel3.at<unsigned char> (i, j) = img.at<Vec3b>(i, j).val[2];
                }
            }
            
            namedWindow("channel1");
            imshow ("channel1", channel1);
            
            namedWindow("channel2");
            imshow ("channel2", channel2);
            
            namedWindow("channel3");
            imshow ("channel3", channel3);
            
            cv::waitKey(0);
        }
    }
    
    void task6(cv::Mat img) {
        
        if(img.channels() == 3) {
            Point2f srcTri[3];
            srcTri[0] = Point2f( 0.f, 0.f );
            srcTri[1] = Point2f( img.cols - 1.f, 0.f );
            srcTri[2] = Point2f( 0.f, img.rows - 1.f );
            
            Point2f dstTri[3];
            dstTri[0] = Point2f( 0.f, img.rows*0.33f );
            dstTri[1] = Point2f( img.cols*0.85f, img.rows*0.25f );
            dstTri[2] = Point2f( img.cols*0.15f, img.rows*0.7f );
            
            Mat warp_mat = getAffineTransform( srcTri, dstTri );
            Mat warp_dst = Mat::zeros( img.rows, img.cols, img.type());
            
            warpAffine( img, warp_dst, warp_mat, warp_dst.size());
            
            Point center = Point(warp_dst.cols/2, warp_dst.rows/2);
            
            double angle = -50.0;
            double scale = 0.6;
            
            Mat rot_mat = getRotationMatrix2D(center, angle, scale );
            Mat warp_rotate_dst;
            
            warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());
            
            imshow( "Source image", img );
            imshow( "Warp", warp_dst );
            imshow( "Warp + Rotate", warp_rotate_dst );
            
            cv::waitKey(0);
        }
    }
};

class Lab2 {
public: void task1(cv::Mat img){
    cv::Mat gray(img.cols, img.rows, CV_8U);
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    imwrite("/Users/apple/Desktop/image_grayscale.jpg", gray);
    imshow( "Source image", img );
    imshow( "Source image in gray", gray);
    cv::waitKey(0);
}
    
public:void task2A(cv::Mat img){
    cv::Mat img6 = MaxFilter(img, 5);
    cv::imwrite("/Users/apple/Desktop/image_max.jpg", img6);
    cv::waitKey(0);
}
    
public:void task2B(cv::Mat img){
    cv::Mat img6 = MinFilter(img, 5);
    cv::imwrite("/Users/apple/Desktop/image_min.jpg", img6);
    cv::waitKey(0);
}
    
public:void task3(cv::Mat src){
    Mat dst = src.clone();
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ) {
        GaussianBlur( src, dst, Size( i, i ), 0, 0 );
    }
    cv::imwrite("/Users/apple/Desktop/GaussianBlur.jpg", dst);
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ) {
        medianBlur ( src, dst, i );
    }
    cv::imwrite("/Users/apple/Desktop/medianBlur.jpg", dst);
    cv::waitKey(0);
}
    
    
    
    void drawHistogram(cv::Mat src) {
        vector<Mat> bgr_planes;
        split(src, bgr_planes );
        int histSize = 256;
        float range[] = { 0, 255 }; //the upper boundary is exclusive
        const float* histRange[] = { range };
        bool uniform = true, accumulate = false;
        Mat b_hist, g_hist, r_hist;
        calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate );
        calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate );
        calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate );
        int hist_w = 512, hist_h = 400;
        int bin_w = cvRound( (double) hist_w/histSize );
        Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
        normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        for( int i = 1; i < histSize; i++ )
        {
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
                 Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                 Scalar( 255, 0, 0), 2, 8, 0  );
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
                 Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                 Scalar( 0, 255, 0), 2, 8, 0  );
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
                 Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                 Scalar( 0, 0, 255), 2, 8, 0  );
        }
        imshow("Source image", src );
        imshow("calcHist Demo", histImage );
        waitKey();
    }
    void task5(cv::Mat src){
        cvtColor( src, src, COLOR_BGR2GRAY );
        Mat dst;
        equalizeHist( src, dst );
        imshow( "Source image", src );
        imshow( "Equalized Image", dst );
        waitKey();
        
    }
};

int main(int argc, char** argv) {
    cv::Mat img = cv::imread(argv[1]);
    cv::Mat img2 = cv::imread(argv[2]);
    cv::Mat image = cv::imread(argv[3]);
    
    Lab2 lab2;
    lab2.task5(image);
    
    
    return 0;
}
