#include <iostream>
#include <armadillo>

int main() {
  std::cout << "Olá" << std::endl;
  std::cout << "Armadillo version: " << arma::arma_version::as_string() << std::endl;
  arma::mat A(4, 5, arma::fill::randu);
  arma::mat B(4, 5, arma::fill::randu);

  std::cout << A*B.t() << std::endl;
  return 0;
}
