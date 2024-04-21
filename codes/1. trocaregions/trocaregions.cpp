#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char** argv){
  cv::Mat image;
  cv::Mat reg1, reg2, reg3, reg4;

  image= cv::imread(argv[1],cv::IMREAD_COLOR);
  if(!image.data)
    std::cout << "nao abriu a imagem." << std::endl;

  cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
  
  cv::imshow("original", image);  
  cv::waitKey();

  reg1 = image(cv::Rect(0,0,image.rows/2,image.cols/2));
  reg2 = image(cv::Rect(image.rows/2,0,image.rows/2,image.cols/2));
  reg3 = image(cv::Rect(0,image.cols/2,image.rows/2,image.cols/2));
  reg4 = image(cv::Rect(image.rows/2,image.cols/2,image.rows/2,image.cols/2));

  cv::Mat inverted(image.rows,image.cols,image.type());

  reg4.copyTo(inverted(cv::Rect(0,0,image.rows/2,image.cols/2)));
  reg3.copyTo(inverted(cv::Rect(image.rows/2,0,image.rows/2,image.cols/2)));
  reg2.copyTo(inverted(cv::Rect(0,image.cols/2,image.rows/2,image.cols/2)));
  reg1.copyTo(inverted(cv::Rect(image.rows/2,image.cols/2,image.rows/2,image.cols/2)));
  
  
  cv::imshow("inverted regions", inverted);  
  cv::imwrite("inverted.png", inverted);
  cv::waitKey();
  return 0;
}
