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

using namespace std;
using namespace cv;

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

int main(int argc, char** argv) {
    cv::Mat img = cv::imread(argv[1]);
    cv::Mat img2 = cv::imread(argv[2]);
    
    Lab1 lab1;
    //    lab1.task1and2(img, img2);
    //    lab1.task3a(true);
    //    lab1.task3a(false);
    //    lab1.task3b(20);
    //    lab1.task3b(50);
    //    lab1.task4(0, img);
    //    lab1.task4(1, img);
    lab1.task4(2, img);
    //    lab1.task5(img);
    //    lab1.task6(img);
    return 0;
}
