
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdexcept>

#include "task2.h"

using namespace cv;
using namespace std;


cv::Mat MaxFilter(cv::Mat img, int kernel_size){
    if (kernel_size%2 == 0 ){
        throw std::invalid_argument("Alreay Graysccale image");
    }
    
    cv:Mat kernal(kernel_size , kernel_size, img.type());
    
    cv::Mat dst(img.rows, img.cols, CV_8UC1);
        
    for(int x = 0;x < img.rows - kernal.rows;x++){
        for(int y = 0; y < img.cols - kernal.cols;y++){
            //kernal application
            cv::Rect slidingWindow(y, x, kernal.cols,kernal.rows);
        cv::Mat tmp = img(slidingWindow);
            
            uchar cmax = 0;
            for(int i = 0; i < tmp.rows ; i++){
                for(int j = 0; j < tmp.cols ; j++){
                    //take min
                    if(cmax < tmp.at<uchar>(i,j)){
                        cmax = tmp.at<uchar>(i,j);
                    }
                    
                }
            }
            dst.at<uchar>(x,y) = cmax;
            
        }
    }
    return dst;
}

cv::Mat MinFilter(cv::Mat img, int kernel_size){
    if (kernel_size%2 == 0 ){
        throw std::invalid_argument("Alreay Graysccale image");
    }
    
    cv:Mat kernal(kernel_size , kernel_size, img.type());
    
    cv::Mat dst(img.rows, img.cols, CV_8UC1);
        
    for(int x = 0;x < img.rows - kernal.rows;x++){
        for(int y = 0; y < img.cols - kernal.cols;y++){
            //kernal application
            cv::Rect slidingWindow(y, x, kernal.cols,kernal.rows);
        cv::Mat tmp = img(slidingWindow);
            uchar cmin = 255;
            for(int i = 0; i < tmp.rows ; i++){
                for(int j = 0; j < tmp.cols ; j++){
                    //take min
                    if(tmp.at<uchar>(i,j)<cmin){
                        cmin = tmp.at<uchar>(i,j);
                    }
                    
                }
            }
            dst.at<uchar>(x,y) = cmin;
            
        }
    }
    return dst;
}

