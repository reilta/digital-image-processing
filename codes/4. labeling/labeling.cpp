#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {
  cv::Mat image, realce;
  int width, height;
  int nobjects, nholes;

  cv::Point p;
  image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

  if (!image.data) {
    std::cout << "imagem nao carregou corretamente\n";
    return (-1);
  }

  width = image.cols;
  height = image.rows;
  std::cout << width << "x" << height << std::endl;

  p.x = 0;
  p.y = 0;

  //objetos da borda
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      if(image.at<uchar>(i,j) == 255 && (i == 0 | j == width-1 || j == 0 || i == height-1)){
        p.x = j;
        p.y = i;
        floodFill(image,p,0);
      }    
    }
  }

  cv::imwrite("bordas-removidas.png", image);
  cv::imshow("objetos da bordas removidos", image);
  cv::waitKey();

  p.x = 0;
  p.y = 0;
  cv::floodFill(image,p,100);
  cv::imwrite("background-pintado.png", image);
  cv::imshow("cor do background alterada", image);
  cv::waitKey();

  // busca objetos presentes
  nobjects = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (image.at<uchar>(i, j) == 255) {
        // achou um objeto
        nobjects++;
        // para o floodfill as coordenadas
        // x e y são trocadas.
        p.x = j;
        p.y = i;
        // preenche o objeto com o contador
        cv::floodFill(image, p, nobjects);
      }
    }
  }

  cv::imwrite("objetos-contados.png",image);
  cv::imshow("objetos contados", image);
  cv::waitKey();

  nholes = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (image.at<uchar>(i, j) == 0) {
        // achou um buraco
        nholes++;
        // para o floodfill as coordenadas
        // x e y são trocadas.
        p.x = j;
        p.y = i;
        // preenche o objeto com o contador
        cv::floodFill(image, p, 255);
      }
    }
  }

  cv::imwrite("buracos-contados.png", image);
  cv::imshow("buracos contados", image);
  cv::waitKey();
  
  
  std::cout << "a figura tem " << nobjects << " bolhas\n";
  std::cout<<" sendo "<< nobjects - nholes<< " bolhas completas e "<< nholes<< " bolhas com buracos\n"; 
  return 0;
}
