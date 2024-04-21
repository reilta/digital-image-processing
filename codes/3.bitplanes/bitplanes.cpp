#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char**argv) {
  cv::Mat imagemPortadora, imagemOriginal, imagemDecodificada;
  cv::Vec3b valPortadora, valEscondida, valOriginal;
  int nbits = 3;

  imagemPortadora = cv::imread(argv[1], cv::IMREAD_COLOR);

  if (imagemPortadora.empty()) {
    std::cout << "imagem nao carregou corretamente" << std::endl;
    return (-1);
  }

  imagemDecodificada = imagemPortadora.clone();
  imagemOriginal = imagemPortadora.clone();

  for (int i = 0; i < imagemPortadora.rows; i++) {
    for (int j = 0; j < imagemPortadora.cols; j++) {
      valPortadora = imagemPortadora.at<cv::Vec3b>(i, j);

      valOriginal[0] = valPortadora[0] >> nbits << nbits;
      valOriginal[1] = valPortadora[1] >> nbits << nbits;
      valOriginal[2] = valPortadora[2] >> nbits << nbits;

      valEscondida[0] = valPortadora[0] << (8 - nbits);
      valEscondida[1] = valPortadora[1] << (8 - nbits);
      valEscondida[2] = valPortadora[2] << (8 - nbits);

      imagemDecodificada.at<cv::Vec3b>(i, j) = valEscondida;
      imagemOriginal.at<cv::Vec3b>(i,j) = valOriginal;
    }
  }
  imwrite("decodificada.png", imagemDecodificada);
  imwrite("original.png", imagemOriginal);
  return 0;
}
