#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
    gmsh::initialize();

    gmsh::model::add("tor.msh");

    double lc = 1e-2;
    int center = gmsh::model::geo::addPoint(0, 0, 0, lc, 17);
    int center_down = gmsh::model::geo::addPoint(0, 0, -.1, lc, 0);
    int center_up = gmsh::model::geo::addPoint(0, 0, .1, lc, 1);
    int center1 = gmsh::model::geo::addPoint(0, .2, 0, lc, 2);
    int center2 = gmsh::model::geo::addPoint(0, -.2, 0, lc, 3);
    gmsh::model::geo::addPoint(0, .2, .1, lc, 4);
    gmsh::model::geo::addPoint(0, .2, -.1, lc, 5);
    gmsh::model::geo::addPoint(0, -.2, .1, lc, 6);
    gmsh::model::geo::addPoint(0, -.2, -.1, lc, 7);
    gmsh::model::geo::addPoint(0, .3, 0, lc, 8);
    gmsh::model::geo::addPoint(0, .1, 0, lc, 9);
    gmsh::model::geo::addPoint(0, -.3, 0, lc, 10);
    gmsh::model::geo::addPoint(0, -.1, 0, lc, 11);

    gmsh::model::geo::addCircleArc(8, center1, 4, 1);
    gmsh::model::geo::addCircleArc(4, center1, 9, 2);
    gmsh::model::geo::addCircleArc(9, center1, 5, 3);
    gmsh::model::geo::addCircleArc(5, center1, 8, 4);

    gmsh::model::geo::addCircleArc(10, center2, 6, 5);
    gmsh::model::geo::addCircleArc(6, center2, 11, 6);
    gmsh::model::geo::addCircleArc(11, center2, 7, 7);
    gmsh::model::geo::addCircleArc(7, center2, 10, 8);

    gmsh::model::geo::addCircleArc(7, center_down, 5, 9);
    gmsh::model::geo::addCircleArc(5, center_down, 7, 10);
    gmsh::model::geo::addCircleArc(6, center_up, 4, 11);
    gmsh::model::geo::addCircleArc(4, center_up, 6 , 12);

    gmsh::model::geo::addCircleArc(11, center, 9, 13);
    gmsh::model::geo::addCircleArc(9, center, 11, 14);
    gmsh::model::geo::addCircleArc(10, center, 8, 15);
    gmsh::model::geo::addCircleArc(8, center, 10 , 16);

    gmsh::model::geo::addCurveLoop({2, 14, -6, -12}, 1);
    gmsh::model::geo::addSurfaceFilling({1}, 1);

    gmsh::model::geo::addCurveLoop({2, -13, -6, 11}, 2);
    gmsh::model::geo::addSurfaceFilling({2}, 2);

    gmsh::model::geo::addCurveLoop({3, -9, -7, 13}, 3);
    gmsh::model::geo::addSurfaceFilling({3}, 3);



    // gmsh::model::geo::addCurveLoop({-2, -1}, 2);
    // gmsh::model::geo::addCurveLoop({9}, 3);
    // gmsh::model::geo::addCurveLoop({10}, 4);
    //
    // gmsh::model::geo::addSurfaceFilling({1, 2, 3, 4}, 1);

    // gmsh::model::geo::addCurveLoop({4, 6, -2, -5}, 2);
    // gmsh::model::geo::addSurfaceFilling({2}, 2);
    //
    // gmsh::model::geo::addCurveLoop({3, -7, -1, 8}, 3);
    // gmsh::model::geo::addSurfaceFilling({3}, 3);
    //
    // gmsh::model::geo::addCurveLoop({4, -8, -2, 7}, 4);
    // gmsh::model::geo::addSurfaceFilling({4}, 4);

    gmsh::model::geo::synchronize();

    gmsh::model::mesh::generate(2);

    gmsh::write("tor.msh");

    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();

    return 0;
}

