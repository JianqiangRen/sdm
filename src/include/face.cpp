//
// Created by jack on 2019/8/5.
//

#include "face.h"
ldmarkmodel Face::markModel;

int Face::init(const string modelFilePath)
{
    Face::markModel = new ldmarkmodel();
    if(load_ldmarkmodel(modelFilePath,  Face::markModel))
    {
		std::cout<<"load model success"<<endl;
        return 0;
    } else
	{
		std::cout<<"load model error"<<endl;
        return 1;
     }
}

int Face::detect(cv::Mat& src, cv::Rect& faceRect, cv::Mat& landmarkMat)
{
    int ret =  Face::markModel.track(src,landmarkMat);
    std::cout<<"ret1:"<<ret<<std::endl;
    if(ret < 400)
        return 0;
    return ret;
}

int Face::detect(cv::Mat& src, std::vector<cv::Rect>& faceRects, std::vector<cv::Mat>& landmarkMats)
{
    int ret =  Face::markModel.track(src,faceRects,landmarkMats);
    std::cout<<"ret2:"<<ret<<std::endl;
    if(ret < 400)
        return 0;
    return ret;
}


int Face::formatLandMarks(cv::Mat &marksMat, std::vector<cv::Point>& landmarks)
{
    int numLandmarks = marksMat.cols/2;
    landmarks.clear();
    landmarks.resize(numLandmarks);

    for(int j=0; j<numLandmarks; j++){
        int x = marksMat.at<float>(j);
        int y = marksMat.at<float>(j + numLandmarks);
        landmarks[j] = cv::Point(x,y);
    }
    return 0;
}


int Face::buffing(const cv::Mat &src,
                  const cv::Rect& faceRect,
                  const std::vector<cv::Point>& landmarks,
                  cv::Mat &dst)
{

    cv::Mat roi = src(faceRect);

    cv::Mat mask = cv::Mat::zeros(roi.size(), CV_32F);

    vector<cv::Point> allPoints, leftEyePoints, rightEyePoints, mouthPoints, nosePoints;

    allPoints.insert(allPoints.end(), landmarks.begin()+3, landmarks.begin()+13);
    allPoints.insert(allPoints.end(), landmarks.begin()+17, landmarks.begin()+26);

    leftEyePoints.insert(leftEyePoints.end(), landmarks.begin()+36, landmarks.begin()+41);
    leftEyePoints.insert(leftEyePoints.end(), landmarks.begin()+17, landmarks.begin()+21);

    rightEyePoints.insert(rightEyePoints.end(), landmarks.begin()+42, landmarks.begin()+47);
    rightEyePoints.insert(rightEyePoints.end(), landmarks.begin()+22, landmarks.begin()+26);


    mouthPoints.insert(mouthPoints.end(), landmarks.begin()+48, landmarks.end());

    nosePoints.insert(nosePoints.end(), landmarks.begin()+27, landmarks.begin()+35);

    cv::fillConvexPoly(mask,allPoints,255);
    cv::fillConvexPoly(mask,leftEyePoints,0);
    cv::fillConvexPoly(mask,rightEyePoints,0);
    cv::fillConvexPoly(mask,mouthPoints,0);
    cv::fillConvexPoly(mask,nosePoints,0);

    int blur_amount =0.6 *(cv::norm(landmarks[36]-landmarks[42]));
    if(blur_amount%2 ==0)
        blur_amount +=1;

    cv::GaussianBlur(mask,mask,cv::Size(blur_amount,blur_amount), 0);

    return 0;
}
