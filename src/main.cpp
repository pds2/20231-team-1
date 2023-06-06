#include <iostream>
#include <armadillo>

int main() {
  std::cout << "Olá" << std::endl;
  std::cout << "Armadillo version: " << arma::arma_version::as_string() << std::endl;
  return 0;
}
