#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
  gmsh::initialize();

  gmsh::model::add("t2");

  double lc = 1e-2;
  gmsh::model::geo::addPoint(0, 0, 0, lc, 1);
  gmsh::model::geo::addPoint(.1, 0, 0, lc, 2);
  gmsh::model::geo::addPoint(.1, .1, 0, lc, 3);
  gmsh::model::geo::addPoint(0, .1, 0, lc, 4);
  gmsh::model::geo::addPoint(0, 0, .1, lc, 5);
  gmsh::model::geo::addPoint(.1, 0, .1, lc, 6);
  gmsh::model::geo::addPoint(.1, .1, .1, lc, 7);
  gmsh::model::geo::addPoint(0, .1, .1, lc, 8);

  gmsh::model::geo::addLine(1, 2, 1);
  gmsh::model::geo::addLine(2, 3, 2);
  gmsh::model::geo::addLine(3, 4, 3);
  gmsh::model::geo::addLine(4, 1, 4);
  gmsh::model::geo::addLine(5, 6, 5);
  gmsh::model::geo::addLine(6, 7, 6);
  gmsh::model::geo::addLine(7, 8, 7);
  gmsh::model::geo::addLine(8, 5, 8);

  for(int i = 0; i < 4; i++)
    gmsh::model::geo::addLine(i + 1, i + 5, i + 9);

  gmsh::model::geo::addCurveLoop({1, 2, 3, 4}, 1);
  gmsh::model::geo::addPlaneSurface({1}, 1);

  gmsh::model::geo::addCurveLoop({1, 10, -5, -9}, 2);
  gmsh::model::geo::addPlaneSurface({2}, 2);

  gmsh::model::geo::addCurveLoop({2, 11, -6, -10}, 3);
  gmsh::model::geo::addPlaneSurface({3}, 3);

  gmsh::model::geo::addCurveLoop({3, 12, -7, -11}, 4);
  gmsh::model::geo::addPlaneSurface({4}, 4);

  gmsh::model::geo::addCurveLoop({4, 9, -8, -12}, 5);
  gmsh::model::geo::addPlaneSurface({5}, 5);

  gmsh::model::geo::addCurveLoop({5, 6, 7, 8}, 6);
  gmsh::model::geo::addPlaneSurface({6}, 6);

  gmsh::model::geo::addSurfaceLoop({1, 2, 3, 4, 5, 6}, 1);
  gmsh::model::geo::addVolume({1});

  gmsh::model::geo::synchronize();

  gmsh::model::mesh::generate(3);

  gmsh::write("t2.msh");

  std::set<std::string> args(argv, argv + argc);
  if(!args.count("-nopopup")) gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}

