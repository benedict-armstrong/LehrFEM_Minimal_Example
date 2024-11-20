#include "lf/geometry/geometry.h"

#include <lf/mesh/mesh.h>
#include <lf/refinement/refinement.h>

#include <Eigen/Eigen>
#include <iostream>

#include "lf/mesh/hybrid2d/hybrid2d.h"
#include "lf/mesh/test_utils/test_meshes.h"
#include "lf/mesh/utils/utils.h"

int main(int argc, const char *argv[]) {
  auto mesh = lf::mesh::test_utils::GenerateHybrid2DTestMesh(1);

  // Get entity pointer by index
  auto entity = mesh->EntityByIndex(0, 0);
  auto entity2 = mesh->EntityByIndex(0, 1);

  // Get the geometry of the entity
  auto geometry = entity2->Geometry();

  // Get the Volume of an entity
  double v = lf::geometry::Volume(*geometry);

  // Get the corners of an entity
  auto corners = lf::geometry::Corners(*geometry);

  // Geometry mappings can be composed
  //   auto geometry2 = entity2->Geometry();
  //   auto composed_geo = lf::geometry::Compose(geometry, geometry2);

  // print entity reference element
  std::cout << entity2->RefEl() << std::endl;

  /* Jacobian etc. */
  auto points = Eigen::MatrixXd(2, 3);
  points << 0.0, 1.0, 0.3, 0.0, 0.5, 0.5;
  auto jacobian = geometry->Jacobian(points);

  std::cout << jacobian << std::endl;

  return 0;
}
