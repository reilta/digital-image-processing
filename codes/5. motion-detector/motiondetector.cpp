#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>


int main(int argc, char** argv){
  cv::Mat image, gray;
  int width, height;
  int camera;
  cv::VideoCapture cap;
  std::vector<cv::Mat> planes;
  cv::Mat histC, histL;
  int nbins = 64;
  float range[] = {0, 255};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;
  int key;
  double compare;
  double limit = 0.99;

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
  cv::Mat histImg(histh, histw, CV_8UC3, cv::Scalar(0,0,0));
  
  // Obtem a primeira imagem e cria o histograma inicial
    cap >> image;
    split(image, planes);
    if (image.empty()) return -1;
    cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::calcHist(&planes[0], 1, 0, cv::Mat(), histL, 1, &nbins, &histrange, uniform, acummulate);
    cv::normalize(histL, histL, 0, histImg.rows, cv::NORM_MINMAX, -1, cv::Mat());

  while(1){
    cap >> image;
    
    split(image, planes);

    cv::calcHist(&planes[0], 1, 0, cv::Mat(), histC, 1, &nbins, &histrange, uniform, acummulate);
    cv::normalize(histC, histC, 0, histImg.rows, cv::NORM_MINMAX, -1, cv::Mat());

    histImg.setTo(cv::Scalar(0));

    
    compare = cv::compareHist(histL, histC, cv::HISTCMP_CORREL);
    std::cout << "Comparação: " << compare << std::endl;

     if (compare < limit) {
            cv::putText(image, "Motion Detected", cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
    }

    for(int i=0; i<nbins; i++){
      line(histImg,
               cv::Point(i, histh),
               cv::Point(i, histh-cvRound(histC.at<float>(i))),
               cv::Scalar(255, 255, 255), 1, 8, 0);
    }

    
    cv::imshow("Live", image);
    
    key = cv::waitKey(30);
    if(key == 27) break;
    histC.copyTo(histL);  // Atualiza o histograma anterior
  }
  return 0;
}

