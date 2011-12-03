#include <string>
#include <ostream>
#include <iostream>
#include <string>
#include "Instance.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

// testing dijkstra, using graph I from wikipedia entry on Dijkstra's algorithm.

int main(int argc, char *argv[])
{
    Ptr<Instance::Manager> manager = shippingInstanceManager();

    if (manager == NULL) {
        cerr << "Unexpected NULL manager." << endl;
        return 1;
    }

    Ptr<Instance> stats = manager->instanceNew("myStats", "Stats");

    if (stats == NULL) {
        cerr << "Unexpected NULL stats." << endl;
        return 1;
    }

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");

    if (fleet == NULL) {
        cerr << "Unexpected NULL." << endl;
        return 1;
    }

    fleet->attributeIs("Boat, speed", "60");
    fleet->attributeIs("Truck, capacity", "50");
    fleet->attributeIs("Plane, cost", "20");

    // --- Create instances
    // -- Locations
    // customers
    Ptr<Instance> customerA = manager->instanceNew("customerA", "Customer");
    Ptr<Instance> customerB = manager->instanceNew("customerB", "Customer");
    Ptr<Instance> customerC = manager->instanceNew("customerC", "Customer");
    Ptr<Instance> customerD = manager->instanceNew("customerD", "Customer");
    Ptr<Instance> customerE = manager->instanceNew("customerE", "Customer");
    // ports
    Ptr<Instance> port = manager->instanceNew("port", "Port");

    // -- Segments
    // boat
    Ptr<Instance> boatSegAB = manager->instanceNew("boatSegAB", "Boat segment");
    Ptr<Instance> boatSegBA = manager->instanceNew("boatSegBA", "Boat segment");
    boatSegAB->attributeIs("source", "customerA");
    boatSegBA->attributeIs("source", "customerB");
    boatSegAB->attributeIs("length","14");
    boatSegBA->attributeIs("length","14");
    boatSegAB->attributeIs("return segment", "boatSegBA");

    Ptr<Instance> boatSegAE = manager->instanceNew("boatSegAE", "Boat segment");
    Ptr<Instance> boatSegEA = manager->instanceNew("boatSegEA", "Boat segment");
    boatSegAE->attributeIs("source", "customerA");
    boatSegEA->attributeIs("source", "customerE");
    boatSegAE->attributeIs("length","7");
    boatSegEA->attributeIs("length","7");
    boatSegAE->attributeIs("return segment", "boatSegEA");

    Ptr<Instance> boatSegDE = manager->instanceNew("boatSegDE", "Boat segment");
    Ptr<Instance> boatSegED = manager->instanceNew("boatSegED", "Boat segment");
    boatSegDE->attributeIs("source", "customerD");
    boatSegED->attributeIs("source", "customerE");
    boatSegDE->attributeIs("length","15");
    boatSegED->attributeIs("length","15");
    boatSegDE->attributeIs("return segment", "boatSegED");

    Ptr<Instance> boatSegPE = manager->instanceNew("boatSegPE", "Boat segment");
    Ptr<Instance> boatSegEP = manager->instanceNew("boatSegEP", "Boat segment");
    boatSegPE->attributeIs("source", "port");
    boatSegEP->attributeIs("source", "customerE");
    boatSegPE->attributeIs("length","10");
    boatSegEP->attributeIs("length","10");
    boatSegPE->attributeIs("return segment", "boatSegEP");

    Ptr<Instance> boatSegPA = manager->instanceNew("boatSegPA", "Boat segment");
    Ptr<Instance> boatSegAP = manager->instanceNew("boatSegAP", "Boat segment");
    boatSegPA->attributeIs("source", "port");
    boatSegAP->attributeIs("source", "customerA");
    boatSegPA->attributeIs("length","9");
    boatSegAP->attributeIs("length","9");
    boatSegPA->attributeIs("return segment", "boatSegAP");

    Ptr<Instance> boatSegPB = manager->instanceNew("boatSegPB", "Boat segment");
    Ptr<Instance> boatSegBP = manager->instanceNew("boatSegBP", "Boat segment");
    boatSegPB->attributeIs("source", "port");
    boatSegBP->attributeIs("source", "customerB");
    boatSegPB->attributeIs("length","2");
    boatSegBP->attributeIs("length","2");
    boatSegPB->attributeIs("return segment", "boatSegBP");

    Ptr<Instance> boatSegPD = manager->instanceNew("boatSegPD", "Boat segment");
    Ptr<Instance> boatSegDP = manager->instanceNew("boatSegDP", "Boat segment");
    boatSegPD->attributeIs("source", "port");
    boatSegDP->attributeIs("source", "customerD");
    boatSegPD->attributeIs("length","11");
    boatSegDP->attributeIs("length","11");
    boatSegPD->attributeIs("return segment", "boatSegDP");

    Ptr<Instance> boatSegCB = manager->instanceNew("boatSegCB", "Boat segment");
    Ptr<Instance> boatSegBC = manager->instanceNew("boatSegBC", "Boat segment");
    boatSegCB->attributeIs("source", "customerC");
    boatSegBC->attributeIs("source", "customerB");
    boatSegCB->attributeIs("length","9");
    boatSegBC->attributeIs("length","9");
    boatSegCB->attributeIs("return segment", "boatSegBC");

    Ptr<Instance> boatSegCD = manager->instanceNew("boatSegCD", "Boat segment");
    Ptr<Instance> boatSegDC = manager->instanceNew("boatSegDC", "Boat segment");
    boatSegCD->attributeIs("source", "customerC");
    boatSegDC->attributeIs("source", "customerD");
    boatSegCD->attributeIs("length","6");
    boatSegDC->attributeIs("length","6");
    boatSegCD->attributeIs("return segment", "boatSegDC");

    Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");
    //conn->attributeIs("routing algorithm", "Dijkstra"); 
    conn->attributeIs("routing algorithm", "BFS"); 

    // print the routing tables of each location
    manager->printTables();
    

    // -- Statistics queries
    cout << "===== Stats attributes =====" << endl;
    cout << " --- Segments --- " << endl;
    cout << "# Truck segments : " << stats->attribute("Truck segment") << endl;
    cout << "Expediting %     : " << stats->attribute("expedite percentage") << endl;
    cout << " --- Terminals --- " << endl;
    cout << "# Plane terminals: " << stats->attribute("Plane terminal") << endl;
    cout << " --- Ports and customers --- " << endl;
    cout << "# Ports          : " << stats->attribute("Port") << endl;

    cerr << "Done!" << endl;

    return 0;

}
