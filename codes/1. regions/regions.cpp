#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char** argv){
  cv::Mat image;
  cv::Vec3b val;
  int x1,x2;
  int y1,y2;

  image= cv::imread(argv[1],cv::IMREAD_COLOR);
  if(!image.data)
    std::cout << "nao abriu a imagem." << std::endl;

  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

  std::cout<<"Insira a coordenada do ponto 1:"<< std::endl;
  std::cin>>x1>>y1;
  std::cout<<"Insira a coordenada do ponto 2:"<< std::endl;
  std::cin>>x2>>y2;

  for(int i=x1;i<x2;i++){ //150 to 300
    for(int j=y1;j<y2;j++){ //250 to 1300
      image.at<uchar>(i,j)= 255 - image.at<uchar>(i,j);
    }
  }


  cv::imshow("janela", image);  
  cv::imwrite("negative.png", image);
  cv::waitKey();
  return 0;
}
