#include <set>
#include <gmsh.h>

int main(int argc, char **argv)
{
    gmsh::initialize();

    gmsh::model::add("tor");

    try {
        gmsh::merge("../../src/tor.stl");
    } catch(...) {
        gmsh::logger::write("Could not load STL mesh: bye!");
        gmsh::finalize();
        return 0;
    }

    double angle = 15;
    bool forceParametrizablePatches = false;
    bool includeBoundary = true;
    double curveAngle = 180;

    gmsh::model::mesh::classifySurfaces(angle * M_PI / 180., includeBoundary,
                                          forceParametrizablePatches,
                                          curveAngle * M_PI / 180.);

    gmsh::model::mesh::createGeometry();

    std::vector<std::pair<int, int> > s;
    gmsh::model::getEntities(s, 2);
    std::vector<int> sl;
    for(auto surf : s) sl.push_back(surf.second);
    int l = gmsh::model::geo::addSurfaceLoop(sl);
    gmsh::model::geo::addVolume({l});

    gmsh::model::geo::synchronize();

    int f = gmsh::model::mesh::field::add("MathEval");

    gmsh::model::mesh::field::setString(f, "F", "4");
    gmsh::model::mesh::field::setAsBackgroundMesh(f);

    gmsh::model::mesh::generate(3);

    gmsh::write("tor.msh");

    // Launch the GUI to see the results:
    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();
    return 0;
}