#include <set>
#include <gmsh.h>
int main(int argc, char **argv)
{
    gmsh::initialize();
    gmsh::model::add("round.msh");

    double lc = 1e-2;
    int center = gmsh::model::geo::addPoint(0, 0, 0, lc);
    int p1 = gmsh::model::geo::addPoint(0, .1, 0, lc);
    int p2 = gmsh::model::geo::addPoint(0, -.1, 0, lc);

    gmsh::model::geo::addCircleArc(p1, center, p2, 1);
    gmsh::model::geo::addCircleArc(p2, center, p1, 2);

    gmsh::model::geo::addCurveLoop({1, 2}, 1);

    gmsh::model::geo::addPlaneSurface({1}, 1);

    gmsh::model::geo::synchronize();

    gmsh::model::mesh::generate(2);

    gmsh::write("round.msh");

    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();

    return 0;
}
