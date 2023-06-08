#include <armadillo>

class Weighting {
public:
  virtual arma::vec get_weight_vector(Document & doc);
};
