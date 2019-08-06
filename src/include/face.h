//
// Created by jack on 2019/8/5.
//

#ifndef FILTER_FACE_H
#define FILTER_FACE_H

#include "ldmarkmodel.h"
#include "opencv2/opencv.hpp"

using namespace std;


class Face {

public:
    static int init(string modelFilePath);
    static int formatLandMarks(cv::Mat& marksMat, std::vector<cv::Point>& landmarks);
    static int detect(cv::Mat& src, vector<cv::Rect>& faceRects, vector<cv::Mat>& landmarkMats);
    static int buffing(const cv::Mat& src, const cv::Rect& faceRect, const std::vector<cv::Point>& landmarks, cv::Mat& dst);

private:
    static ldmarkmodel* markModel;
};


#endif //FILTER_FACE_H
