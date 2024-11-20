#include <lf/mesh/mesh.h>
#include <lf/refinement/refinement.h>

#include <Eigen/Eigen>
#include <iostream>
#include <vector>

#include "lf/io/io.h"
#include "lf/mesh/hybrid2d/hybrid2d.h"
#include "lf/mesh/test_utils/test_meshes.h"
#include "lf/mesh/utils/utils.h"

int main(int argc, const char* argv[]) {
  // auto mesh = lf::mesh::test_utils::GenerateHybrid2DTestMesh(1);

  std::unique_ptr<lf::mesh::hybrid2d::MeshFactory> mesh_factory =
      std::make_unique<lf::mesh::hybrid2d::MeshFactory>(2);
  lf::io::GmshReader gmsh_reader =
      lf::io::GmshReader(std::move(mesh_factory), "triangle.msh");
  std::shared_ptr<lf::mesh::Mesh> mesh = gmsh_reader.mesh();

  // Access number of cells
  unsigned num_entities = mesh->NumEntities(0);

  // Access number of edges
  unsigned num_nodes = mesh->NumEntities(1);

  const lf::mesh::Entity* entity = mesh->EntityByIndex(0, 0);

  // Iterate over all cells (const lf::mesh::Entity *cell)
  for (const lf::mesh::Entity* cell : mesh->Entities(0)) {
    // Do something with entity e.g.: print index of cell
    std::cout << mesh->Index(*cell) << std::endl;
  }

  // Get the co-dimension of the entity
  unsigned codim = entity->Codim();

  // Get the geometry of the entity, more details can be found
  // in the Geometry Quick reference
  const lf::geometry::Geometry* geometry = entity->Geometry();

  // Get the reference element of the entity (e.g. the unit triangle for a
  // general triangle)
  lf::base::RefEl ref_el = entity->RefEl();

  std::span<const lf::mesh::Entity* const> sub_entities =
      entity->SubEntities(1);

  std::vector<const lf::mesh::Entity*> sub_entities_vec{
      entity->SubEntities(1).begin(), entity->SubEntities(1).end()};

  lf::mesh::utils::AllCodimMeshDataSet<bool> bd_flags{
      lf::mesh::utils::flagEntitiesOnBoundary(mesh)};

  // Create a mesh data set storing boolean values for each entity of the mesh
  lf::mesh::utils::AllCodimMeshDataSet<bool> mesh_data_set =
      lf::mesh::utils::AllCodimMeshDataSet<bool>(mesh);

  // Create a mesh data set storing boolean values for each edge of the mesh
  lf::mesh::utils::CodimMeshDataSet<bool> mesh_data_set_edges =
      lf::mesh::utils::CodimMeshDataSet<bool>(mesh, 1);

  // Mesh data sets can be initialized with a default value (false in this case)
  lf::mesh::utils::AllCodimMeshDataSet<bool> mesh_data_set_2 =
      lf::mesh::utils::AllCodimMeshDataSet<bool>(mesh, false);

  /* Entities */

  // Get entity pointer by index
  const lf::mesh::Entity* entity_1 = mesh->EntityByIndex(0, 0);

  bool value = mesh_data_set(*entity);

  // Get the co-dimension of the entity
  auto codim_1 = entity->Codim();

  // Return all sub entities of this entity that have the given codimension
  // (w.r.t. this entity!) For example, for a cell, the sub-entities of codim 1
  // are the edges of the cell.
  auto sub_entities_1 = entity->SubEntities(1);

  // Get the geometry of the entity, more details can be found in the @ref
  // quick_reference_geometry
  auto geometry_1 = entity->Geometry();

  std::span<const lf::mesh::Orientation> orientations =
      entity->RelativeOrientations();

  std::vector<lf::mesh::Orientation> orientations_vec{
      entity->RelativeOrientations().begin(),
      entity->RelativeOrientations().end()};

  // Get the reference element of the entity (e.g. the unit triangle for a
  // general triangle)
  auto ref_el_1 = entity->RefEl();

  std::cout << ref_el << std::endl;

  /* Mesh refinement */

  std::shared_ptr<lf::refinement::MeshHierarchy> multi_mesh_p =
      lf::refinement::GenerateMeshHierarchyByUniformRefinemnt(mesh, 3);

  auto mesh_level_3 = multi_mesh_p->getMesh(3);

  std::cout << mesh_level_3->NumEntities(0) << std::endl;

  auto L = multi_mesh_p->NumLevels();

  std::cout << L << std::endl;

  multi_mesh_p->RefineRegular();

  std::cout << multi_mesh_p->NumLevels() << std::endl;

  auto mesh_level_4 = multi_mesh_p->getMesh(4);

  std::cout << mesh_level_4->NumEntities(0) << std::endl;

  /* Mesh Factory */

  // Create a mesh factory
  //   std::shared_ptr<lf::mesh::hybrid2d::MeshFactory> mesh_factory =
  //       std::make_shared<lf::mesh::hybrid2d::MeshFactory>(2);

  // // Add a points to the mesh factory
  // mesh_factory->AddPoint(Eigen::Vector2d{0.0, 0.0});
  // mesh_factory->AddPoint(Eigen::Vector2d{1.0, 0.0});

  // auto mesh = mesh_factory->Build();

  // /* Mesh Functions */

  auto alpha = [](Eigen::Vector2d x) -> double { return 0.5 * x.norm(); };

  // // Wrap the lambda function in a MeshFunctionGlobal object
  lf::mesh::utils::MeshFunctionGlobal mesh_function =
      lf::mesh::utils::MeshFunctionGlobal(alpha);

  // // Evaluate the mesh function on a cell
  const lf::mesh::Entity* cell = mesh->EntityByIndex(0, 0);
  std::vector<double> values = mesh_function(*cell, Eigen::Vector2d{0.5, 0.5});

  // // We only asked for one point, so the vector has only one entry
  std::cout << "Value: " << values[0] << std::endl;

  return 0;
}
