#include <iostream>
#include <opencv2/opencv.hpp>


int main(int argc, char** argv){
  cv::Mat image, gray, imageEqualize;
  int width, height;
  int camera;
  cv::VideoCapture cap;
  std::vector<cv::Mat> planes;
  cv::Mat histG, histE;
  int nbins = 64;
  float range[] = {0, 255};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;
  int key;

  cap.open(2);
  
  if(!cap.isOpened()){
    std::cout << "cameras indisponiveis";
    return -1;
  }
  
  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);  
  width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  std::cout << "largura = " << width << std::endl;
  std::cout << "altura  = " << height << std::endl;

  int histw = nbins, histh = nbins/2;
  cv::Mat histImg(histh, histw, CV_8UC1, cv::Scalar(0));
  cv::Mat histImgE(histh, histw, CV_8UC1, cv::Scalar(0));
  

  while(1){
    cap >> image;

    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    
    cv::equalizeHist(gray, imageEqualize);

    cv::calcHist(&gray, 1, 0, cv::Mat(), histG, 1,
                 &nbins, &histrange,
                 uniform, acummulate);
    cv::calcHist(&imageEqualize, 1, 0, cv::Mat(), histE, 1,
                 &nbins, &histrange,
                 uniform, acummulate);
    
    cv::normalize(histG, histG, 0, histImg.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(histE, histE, 0, histImgE.rows, cv::NORM_MINMAX, -1, cv::Mat());
        
    histImg.setTo(cv::Scalar(0));
    histImgE.setTo(cv::Scalar(0));
    
    
    for(int i=0; i<nbins; i++){
      cv::line(histImg,
               cv::Point(i, histh),
               cv::Point(i, histh-cvRound(histG.at<float>(i))),
               cv::Scalar(255), 1, 8, 0);
      cv::line(histImgE,
               cv::Point(i, histh),
               cv::Point(i, histh-cvRound(histE.at<float>(i))),
               cv::Scalar(255), 1, 8, 0);
    }
    histImg.copyTo(gray(cv::Rect(0, 0, nbins, histh)));
    histImgE.copyTo(imageEqualize(cv::Rect(0, histh,nbins, histh)));
    
    cv::imshow("gray image", gray);
    cv::imwrite("tenth-doc-and-the-tardis.png", gray);
    cv::imshow("equalized image", imageEqualize);
    cv::imwrite("tenth-doc-and-the-tardis-equalized.png", imageEqualize);

    key = cv::waitKey(30);
    if(key == 27) break;
  }
  return 0;
}

