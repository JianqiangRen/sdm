#include <vector>
#include <iostream>
#include <fstream>


#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "face.h"
#define  TEST 
#ifdef NORMAL

using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
    std::string imgPath = argv[1];
    std::string outPath = argv[2];

    ldmarkmodel modelt;
    std::string modelFilePath = "roboman-landmark-model.bin";
    while(!load_ldmarkmodel(modelFilePath, modelt)){
        std::cout << "." << std::endl;
        std::cin >> modelFilePath;
    }


    cv::Mat Image = cv::imread(imgPath);
    cv::Mat current_shape;

    modelt.track(Image, current_shape);
    cv::Vec3d eav;
    modelt.EstimateHeadPose(current_shape, eav);
    modelt.drawPose(Image, current_shape, 50);

    int numLandmarks = current_shape.cols/2;
    for(int j=0; j<numLandmarks; j++){
        int x = current_shape.at<float>(j);
        int y = current_shape.at<float>(j + numLandmarks);
        std::stringstream ss;
        ss << j;
//            cv::putText(Image, ss.str(), cv::Point(x, y), 0.5, 0.5, cv::Scalar(0, 0, 255));
        cv::circle(Image, cv::Point(x, y), 2, cv::Scalar(0, 0, 255), -1);
    }
    cv::imwrite(outPath, Image);

    return 0;
}


#endif


#ifdef TEST



using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
    std::string testPath = argv[1];
    std::string outPath = argv[2];
    cv::Mat img = cv::imread(testPath);

    Face::init("../example/roboman-landmark-model.bin");

    cv::Rect faceRect;
    cv::Mat landmarkMat;
    Face::detect(img,faceRect, landmarkMat);

    int numLandmarks = landmarkMat.cols/2;
    for(int j=0; j<numLandmarks; j++){
        int x = landmarkMat.at<float>(j);
        int y =landmarkMat.at<float>(j + numLandmarks);
        std::stringstream ss;
        ss << j;
//            cv::putText(Image, ss.str(), cv::Point(x, y), 0.5, 0.5, cv::Scalar(0, 0, 255));
        cv::circle(img, cv::Point(x, y), 2, cv::Scalar(0, 0, 255), -1);
    }
    cv::imwrite("out1.png", img);

    img = cv::imread(testPath);

    vector<cv::Rect> faceRects;
    vector<cv::Mat> landmarkMats;
    Face::detect(img,faceRects, landmarkMats);
    cout<<"facerects size:"<<faceRects.size()<<endl;
    for(int i=0; i < faceRects.size(); ++i)
    {
        int numLandmarks = landmarkMats[i].cols/2;
        for(int j=0; j<numLandmarks; j++){
            int x = landmarkMats[i].at<float>(j);
            int y = landmarkMats[i].at<float>(j + numLandmarks);
            std::stringstream ss;
            ss << j;
//            cv::putText(Image, ss.str(), cv::Point(x, y), 0.5, 0.5, cv::Scalar(0, 0, 255));
            cv::circle(img, cv::Point(x, y), 2, cv::Scalar(0, 0, 255), -1);
        }
    }
    cv::imwrite(outPath, img);
    return 0;
}


#endif
















