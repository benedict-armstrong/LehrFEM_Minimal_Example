#include "lf/quad/quad.h"

#include <Eigen/Eigen>
#include <iostream>
#include <vector>

#include "lf/base/base.h"

int main(int argc, const char *argv[]) {
  auto ref_tria = lf::base::RefEl::kTria();

  lf::quad::QuadRule qr = lf::quad::make_QuadRule(ref_tria, 2);

  auto points = qr.Points();
  auto weights = qr.Weights();
  int degree = 2;

  std::cout << "Points:" << std::endl;
  std::cout << points << std::endl;

  std::cout << "Weights:" << std::endl;
  std::cout << weights << std::endl;

  std::cout << "Degree:" << std::endl;
  std::cout << qr.Degree() << std::endl;

  Eigen::MatrixXd points2(2, 3);
  points2 << 0.166667, 0.666667, 0.166667, 0.166667, 0.166667, 0.666667;

  Eigen::Vector3d weights2;
  weights2 << 0.166667, 0.166667, 0.166667;

  auto qr2 = lf::quad::QuadRule(ref_tria, points2, weights2, 2);

  return 0;
}
