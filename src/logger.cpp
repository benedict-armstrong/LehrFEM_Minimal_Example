/** @file main.cc
 * Demo for outputting information about reference elements
 */

#include <Eigen/Eigen>
#include <iostream>

#include "lf/assemble/assemble.h"
#include "lf/base/base.h"
#include "lf/mesh/test_utils/test_meshes.h"
#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

void stopwatch_example() {
  auto logger = spdlog::get("lf::mesh::hybrid2d::Mesh::Logger");

  spdlog::stopwatch sw;
  logger->info("Elapsed {}s", sw);
  logger->info("Elapsed {:.3}s", sw);
}

int main() {
  Eigen::MatrixXd matrix(2, 2);
  matrix << 1, 2, 3, 4;

  fmt::print("{}", matrix);

  auto logger = lf::base::InitLogger("test");

  logger->info("Hello, World!");
  logger->warn("This is a warning!");
  logger->error("This is an error!");

  // define an Eigen matrix
  Eigen::MatrixXd A(2, 2);
  A << 1, 2, 3, 4;

  // output the matrix using the spdlog logger
  logger->info(A);

  // Node
  auto re_node = lf::base::RefEl::kPoint();
  std::cout << "Information about node: \n" << re_node << '\n';

  // Segment
  auto re_seg = lf::base::RefEl::kSegment();
  std::cout << "\nInformation about segment: \n" << re_seg << '\n';

  // Triangle
  auto re_tria = lf::base::RefEl::kTria();
  std::cout << "\nInformation about triangle: \n" << re_tria << '\n';

  // Qaud
  auto re_quad = lf::base::RefEl::kQuad();
  std::cout << "\nInformation about quad: \n" << re_quad << '\n';

  stopwatch_example();

  return 0;
}
