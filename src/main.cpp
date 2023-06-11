#include <iostream>
#include <Eigen/Core>

int main() {
  std::cout << "Olá" << std::endl;
  Eigen::Matrix<double, 4, 5> A = Eigen::MatrixXd::Random(4, 5);
  Eigen::Matrix<double, 4, 5> B = Eigen::MatrixXd::Random(4, 5);

  std::cout << A*B.transpose() << std::endl;
  return 0;
}
