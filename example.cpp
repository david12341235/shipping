#include <string>
#include <stdio.h>
#include <ostream>
#include <iostream>
#include <string>
#include "Instance.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int example0();
int example1();
int example2();

int main(int argc, char *argv[]) {
	return example0();
}

int example0() {
    Ptr<Instance::Manager> manager = shippingInstanceManager();

    if (!manager) {
        cerr << "Unexpected NULL manager." << endl;
        return 1;
    }

    Ptr<Instance> stats = manager->instanceNew("myStats", "Stats");

    if (!stats) {
        cerr << "Unexpected NULL stats." << endl;
        return 1;
    }

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");

    if (!fleet) {
        cerr << "Unexpected NULL." << endl;
        return 1;
    }

    fleet->attributeIs("Boat, speed", "60");
    fleet->attributeIs("Truck, capacity", "50");
    fleet->attributeIs("Plane, cost", "20");
    cout << "fleet->attribute('Boat, speed'): " << fleet->attribute("Boat, speed") << endl;

    // --- Create instances
    // -- Locations
    // customers
    Ptr<Instance> customer1 = manager->instanceNew("customer1", "Customer");  
    Ptr<Instance> customer2 = manager->instanceNew("customer2", "Customer");  
    // ports
    Ptr<Instance> port1 = manager->instanceNew("port1", "Port");  

    if (!customer1 || !customer2 || !port1) {
        cerr << "Unexpected NULL customer or port." << endl;
	return 1;
    }

    // -- Segments
    // boat
    Ptr<Instance> boatSeg1 = manager->instanceNew("boatSeg1", "Boat segment");  
    Ptr<Instance> boatSeg2 = manager->instanceNew("boatSeg2", "Boat segment");  
    // truck
    Ptr<Instance> truckSeg1 = manager->instanceNew("truckSeg1", "Truck segment");  
    Ptr<Instance> truckSeg2 = manager->instanceNew("truckSeg2", "Truck segment");  

    if (!boatSeg1 || !boatSeg2 || !truckSeg1 || !truckSeg2 ) {
        cerr << "Unexpected NULL segment." << endl;
        return 1;
    }

    // connections
    // customer1 <---> port1
    truckSeg1->attributeIs("source", "customer1");
    truckSeg2->attributeIs("source", "port1");
    truckSeg1->attributeIs("return segment", "truckSeg2");
    cout << "truckSeg1->attribute('source'): " << truckSeg1->attribute("source") << endl;
    
    // customer2 <---> port1
    boatSeg1->attributeIs("source", "customer2");
    boatSeg2->attributeIs("source", "port1");
    boatSeg1->attributeIs("return segment", "boatSeg2");
    cout << "boatSeg1->attribute('return segment'): " << boatSeg1->attribute("return segment") << endl;

    // -- Segment lengths
    boatSeg1->attributeIs("length", "400");
    boatSeg2->attributeIs("length", "400");
    truckSeg1->attributeIs("length", "900");
    truckSeg2->attributeIs("length", "900");

    // -- Segment difficulties
    boatSeg1->attributeIs("difficulty", "1");
    boatSeg2->attributeIs("difficulty", "1");
    truckSeg1->attributeIs("difficulty", "1");
    truckSeg2->attributeIs("difficulty", "1");
    
    // -- Segment expedite support
    boatSeg1->attributeIs("expedite support", "yes");
    boatSeg2->attributeIs("expedite support", "yes");
    truckSeg1->attributeIs("expedite support", "yes");
    truckSeg2->attributeIs("expedite support", "yes");

    // -- Connectivity queries
    Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");

    if (!conn) {
        cerr << "Unexpected NULL conn." << endl;
        return 1;
    }

    cout << "**** explore customer1 : distance 1500 ****" << endl;
    cout << conn->attribute("explore customer1 : distance 1500") << endl;
    cout << endl;

    cout << "*** connect customer2 : customer1 ****" << endl;
    cout << conn->attribute("connect customer2 : customer1") << endl;
    cout << endl;

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

int example1() {
	    Ptr<Instance::Manager> manager = shippingInstanceManager();

    if (!manager) {
        cerr << "Unexpected NULL manager." << endl;
        getchar();
        return 1;
    }

    Ptr<Instance> stats = manager->instanceNew("myStats", "Stats");

    if (!stats) {
        cerr << "Unexpected NULL stats." << endl;
        getchar();
        return 1;
    }

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");

    if (!fleet) {
        cerr << "Unexpected NULL." << endl;
        getchar();
        return 1;
    }
	
    Ptr<Instance> fleet2 = manager->instanceNew("myFleet", "Fleet");
    Ptr<Instance> borg = manager->instanceNew("myBorg", "Borg");

    fleet->attributeIs("Boat, speed", "60");
    fleet->attributeIs("Truck, capacity", "50");
    fleet->attributeIs("Plane, cost", "20");
    fleet->attributeIs("Hippogryph, cost", "50");
    fleet->attributeIs("Boat, speed", "-1");
    cout << "fleet->attribute('Boat, speed'): " << fleet->attribute("Boat, speed") << endl;

    // --- Create instances
    // -- Locations
    // customers
    Ptr<Instance> customer1 = manager->instanceNew("customer1", "Customer");  
    Ptr<Instance> customer2 = manager->instanceNew("customer2", "Customer");  
    // ports
    Ptr<Instance> port1 = manager->instanceNew("port1", "Port");  

    if (!(customer1 && customer2 && port1)) {
        cerr << "Unexpected NULL customer or port." << endl;
        getchar();
        return 1;
    }

    // -- Segments
    // boat
    Ptr<Instance> boatSeg1 = manager->instanceNew("boatSeg1", "Boat segment");  
    Ptr<Instance> boatSeg2 = manager->instanceNew("boatSeg2", "Boat segment");  
    // truck
    Ptr<Instance> truckSeg1 = manager->instanceNew("truckSeg1", "Truck segment");  
    Ptr<Instance> truckSeg2 = manager->instanceNew("truckSeg2", "Truck segment");

    if (!(boatSeg1 && boatSeg2 && truckSeg1 && truckSeg2)) {
        cerr << "Unexpected NULL segment." << endl;
        return 1;
    }

    // connections
    // customer1 <---> port1
    truckSeg1->attributeIs("source", "customer1");
    truckSeg2->attributeIs("source", "port1");
    truckSeg1->attributeIs("return segment", "truckSeg2");
    cout << "truckSeg1->attribute('source'): " << truckSeg1->attribute("source") << endl;
    
    // customer2 <---> port1
    boatSeg1->attributeIs("source", "customer2");
    boatSeg2->attributeIs("source", "port1");
    boatSeg1->attributeIs("return segment", "boatSeg2");
    cout << "boatSeg1->attribute('return segment'): " << boatSeg1->attribute("return segment") << endl;
	
    cout << "port1->attribute('segment1'): " << port1->attribute("segment1") << endl;
    cout << "port1->attribute('segment2'): " << port1->attribute("segment2") << endl;
    cout << "port1->attribute('segment3'): " << port1->attribute("segment3") << endl;

    // -- Segment lengths
    boatSeg1->attributeIs("length", "400");
    boatSeg2->attributeIs("length", "400");
    truckSeg1->attributeIs("length", "900");
    truckSeg2->attributeIs("length", "900");

    // -- Segment difficulties
    boatSeg1->attributeIs("difficulty", "1");
    boatSeg2->attributeIs("difficulty", "1");
    truckSeg1->attributeIs("difficulty", "1");
    truckSeg2->attributeIs("difficulty", "1");
    
    // -- Segment expedite support
    boatSeg1->attributeIs("expedite support", "yes");
    boatSeg2->attributeIs("expedite support", "yes");
    truckSeg1->attributeIs("expedite support", "yes");
    truckSeg2->attributeIs("expedite support", "yes");

    // -- Connectivity queries
    Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");

    if (!conn) {
        cerr << "Unexpected NULL conn." << endl;
        return 1;
    }

    cout << "**** explore customer1 : distance 1500 ****" << endl;
    cout << conn->attribute("explore customer1 : distance 1500") << endl;
    cout << endl;

    cout << "*** connect customer2 : customer1 ****" << endl;
    cout << conn->attribute("connect customer2 : customer1") << endl;
    cout << endl;

    // -- Statistics queries
    cout << "===== Stats attributes =====" << endl;
    cout << " --- Segments --- " << endl;
    cout << "# Truck segments : " << stats->attribute("Truck segment") << endl;
    cout << "# Plane segments : " << stats->attribute("Plane segment") << endl;
    cout << "# Boat segments : " << stats->attribute("Boat segment") << endl;
    cout << "Expediting %     : " << stats->attribute("expedite percentage") << endl;
    cout << " --- Terminals --- " << endl;
    cout << "# Plane terminals: " << stats->attribute("Plane terminal") << endl;
    cout << "# Boat terminals: " << stats->attribute("Boat terminal") << endl;
    cout << "# Truck terminals: " << stats->attribute("Truck terminal") << endl;
    cout << " --- Ports and customers --- " << endl;
    cout << "# Ports          : " << stats->attribute("Port") << endl;
    cout << "# Customers      : " << stats->attribute("Customer") << endl;

    cerr << "Done!" << endl;

    getchar();

    return 0;
}

int example2() {
	    Ptr<Instance::Manager> manager = shippingInstanceManager();

    if (!manager) {
        cerr << "Unexpected NULL manager." << endl;
        getchar();
        return 1;
    }

    Ptr<Instance> stats = manager->instanceNew("myStats", "Stats");

    if (!stats) {
        cerr << "Unexpected NULL stats." << endl;
        getchar();
        return 1;
    }

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");

    if (!fleet) {
        cerr << "Unexpected NULL." << endl;
        getchar();
        return 1;
    }
	
    fleet->attributeIs("Boat, speed", "60");
    fleet->attributeIs("Boat, capacity", "1000");
    fleet->attributeIs("Boat, cost", "200");
    fleet->attributeIs("Truck, speed", "55");
    fleet->attributeIs("Truck, capacity", "100");
    fleet->attributeIs("Truck, cost", "100");
    fleet->attributeIs("Plane, speed", "800");
    fleet->attributeIs("Plane, capacity", "400");
    fleet->attributeIs("Plane, cost", "150");

    // --- Create instances
    // -- Locations
    // customers
    Ptr<Instance> customer1 = manager->instanceNew("customer1", "Customer");  
    Ptr<Instance> customer2 = manager->instanceNew("customer2", "Customer");  
    Ptr<Instance> customer3 = manager->instanceNew("customer3", "Customer");  
    Ptr<Instance> customer4 = manager->instanceNew("customer4", "Customer");  
    Ptr<Instance> customer5 = manager->instanceNew("customer5", "Customer");  
    // ports
    Ptr<Instance> port1 = manager->instanceNew("port1", "Port");  
    Ptr<Instance> port2 = manager->instanceNew("port2", "Port");  
    Ptr<Instance> port3 = manager->instanceNew("port3", "Port");  
	// terminals
    Ptr<Instance> pt1 = manager->instanceNew("pt1", "Plane terminal");
    Ptr<Instance> tt1 = manager->instanceNew("tt1", "Truck terminal");
    Ptr<Instance> bt1 = manager->instanceNew("bt1", "Boat terminal");

    // -- Segments
    // boat
    Ptr<Instance> bs1 = manager->instanceNew("bs1", "Boat segment");
    Ptr<Instance> bs1r = manager->instanceNew("bs1r", "Boat segment");
    Ptr<Instance> bs2 = manager->instanceNew("bs2", "Boat segment");
    Ptr<Instance> bs2r = manager->instanceNew("bs2r", "Boat segment");
    Ptr<Instance> bs3 = manager->instanceNew("bs3", "Boat segment");
    Ptr<Instance> bs3r = manager->instanceNew("bs3r", "Boat segment");
    Ptr<Instance> bs4 = manager->instanceNew("bs4", "Boat segment");
    Ptr<Instance> bs4r = manager->instanceNew("bs4r", "Boat segment");
    // truck
    Ptr<Instance> ts1 = manager->instanceNew("ts1", "Truck segment");
    Ptr<Instance> ts1r = manager->instanceNew("ts1r", "Truck segment");
    Ptr<Instance> ts2 = manager->instanceNew("ts2", "Truck segment");
    Ptr<Instance> ts2r = manager->instanceNew("ts2r", "Truck segment");
    Ptr<Instance> ts3 = manager->instanceNew("ts3", "Truck segment");
    Ptr<Instance> ts3r = manager->instanceNew("ts3r", "Truck segment");
    Ptr<Instance> ts4 = manager->instanceNew("ts4", "Truck segment");
    Ptr<Instance> ts4r = manager->instanceNew("ts4r", "Truck segment");
    Ptr<Instance> ts5 = manager->instanceNew("ts5", "Truck segment");
    Ptr<Instance> ts5r = manager->instanceNew("ts5r", "Truck segment");
	// plane
    Ptr<Instance> ps1 = manager->instanceNew("ps1", "Plane segment");
    Ptr<Instance> ps1r = manager->instanceNew("ps1r", "Plane segment");
    Ptr<Instance> ps2 = manager->instanceNew("ps2", "Plane segment");
    Ptr<Instance> ps2r = manager->instanceNew("ps2r", "Plane segment");
    Ptr<Instance> ps3 = manager->instanceNew("ps3", "Plane segment");
    Ptr<Instance> ps3r = manager->instanceNew("ps3r", "Plane segment");
    Ptr<Instance> ps4 = manager->instanceNew("ps4", "Plane segment");
    Ptr<Instance> ps4r = manager->instanceNew("ps4r", "Plane segment");

    // connections
    ts1->attributeIs("source", "customer1");
    ts1r->attributeIs("source", "port1");
    ts1->attributeIs("return segment", "ts1r");
    ts2->attributeIs("source", "port2");
    ts2r->attributeIs("source", "customer5");
    ts2->attributeIs("return segment", "ts2r");
    ts3->attributeIs("source", "port3");
    ts3r->attributeIs("source", "tt1");
    ts3->attributeIs("return segment", "ts3r");
    ts4->attributeIs("source", "port1");
    ts4r->attributeIs("source", "tt1");
    ts4->attributeIs("return segment", "ts4r");
    ts5->attributeIs("source", "tt1");
    ts5r->attributeIs("source", "customer3");
    ts5->attributeIs("return segment", "ts5r");
	
    ps1->attributeIs("source", "port1");
    ps1r->attributeIs("source", "pt1");
    ps1->attributeIs("return segment", "ps1r");
    ps2->attributeIs("source", "pt1");
    ps2r->attributeIs("source", "customer2");
    ps2->attributeIs("return segment", "ps2r");
    ps3->attributeIs("source", "pt1");
    ps3r->attributeIs("source", "port2");
    ps3->attributeIs("return segment", "ps3r");
    ps4->attributeIs("source", "customer4");
    ps4r->attributeIs("source", "customer5");
    ps4->attributeIs("return segment", "ps4r");
	
    bs1->attributeIs("source", "port2");
    bs1r->attributeIs("source", "bt1");
    bs1->attributeIs("return segment", "bs1r");
    bs2->attributeIs("source", "bt1");
    bs2r->attributeIs("source", "customer5");
    bs2->attributeIs("return segment", "bs2r");
    bs3->attributeIs("source", "bt1");
    bs3r->attributeIs("source", "port3");
    bs3->attributeIs("return segment", "bs3r");
    bs4->attributeIs("source", "port3");
    bs4r->attributeIs("source", "customer4");
    bs4->attributeIs("return segment", "bs4r");
    // -- Segment lengths
    ts1->attributeIs("length", "400");
    ts1r->attributeIs("length", "400");
    ts2->attributeIs("length", "600");
    ts2r->attributeIs("length", "600");
    ts3->attributeIs("length", "500");
    ts3r->attributeIs("length", "500");
    ts4->attributeIs("length", "100");
    ts4r->attributeIs("length", "100");
    ts5->attributeIs("length", "900");
    ts5r->attributeIs("length", "900");
	
    bs1->attributeIs("length", "900");
    bs1r->attributeIs("length", "900");
    bs2->attributeIs("length", "200");
    bs2r->attributeIs("length", "200");
    bs3->attributeIs("length", "500");
    bs3r->attributeIs("length", "500");
    bs4->attributeIs("length", "100");
    bs4r->attributeIs("length", "100");
	
    ps1->attributeIs("length", "100");
    ps1r->attributeIs("length", "100");
    ps2->attributeIs("length", "200");
    ps2r->attributeIs("length", "200");
    ps3->attributeIs("length", "300");
    ps3r->attributeIs("length", "300");
    ps4->attributeIs("length", "900");
    ps4r->attributeIs("length", "900");

    // -- Segment difficulties
    ts1->attributeIs("difficulty", "1");
    ts1r->attributeIs("difficulty", "1");
    ts2->attributeIs("difficulty", "1");
    ts2r->attributeIs("difficulty", "1");
    ts3->attributeIs("difficulty", "1");
    ts3r->attributeIs("difficulty", "1");
    ts4->attributeIs("difficulty", "1");
    ts4r->attributeIs("difficulty", "1");
    ts5->attributeIs("difficulty", "1");
    ts5r->attributeIs("difficulty", "1");
    bs1->attributeIs("difficulty", "1");
    bs1r->attributeIs("difficulty", "1");
    bs2->attributeIs("difficulty", "1");
    bs2r->attributeIs("difficulty", "1");
    bs3->attributeIs("difficulty", "1");
    bs3r->attributeIs("difficulty", "1");
    bs4->attributeIs("difficulty", "1");
    bs4r->attributeIs("difficulty", "1");
    ps1->attributeIs("difficulty", "1");
    ps1r->attributeIs("difficulty", "1");
    ps2->attributeIs("difficulty", "1");
    ps2r->attributeIs("difficulty", "1");
    ps3->attributeIs("difficulty", "1");
    ps3r->attributeIs("difficulty", "1");
    ps4->attributeIs("difficulty", "1");
    ps4r->attributeIs("difficulty", "1");
    
    // -- Segment expedite support
	ts1->attributeIs("expedite support", "yes");
	ts4->attributeIs("expedite support", "yes");
	ts3->attributeIs("expedite support", "yes");
	bs4->attributeIs("expedite support", "yes");
	
    cout << "ts1r->attribute('return segment'): " << ts1r->attribute("return segment") << endl;
    cout << "ts1->attribute('expedite support'): " << ts1->attribute("expedite support") << endl;
    cout << "ts1r->attribute('expedite support'): " << ts1r->attribute("expedite support") << endl;

    // -- Connectivity queries
    Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");

    if (!conn) {
        cerr << "Unexpected NULL conn." << endl;
        return 1;
    }

	string q = "explore customer1 : distance 500";
    cout << "**** "<< q << " ****" << endl;
    cout << conn->attribute(q) << endl;
    cout << endl;

	q = "connect customer1 : port1";
    cout << "**** "<< q << " ****" << endl;
    cout << conn->attribute(q) << endl;
    cout << endl;


    // -- Statistics queries
    cout << "===== Stats attributes =====" << endl;
    cout << " --- Segments --- " << endl;
    cout << "# Truck segments : " << stats->attribute("Truck segment") << endl;
    cout << "# Plane segments : " << stats->attribute("Plane segment") << endl;
    cout << "# Boat segments : " << stats->attribute("Boat segment") << endl;
    cout << "Expediting %     : " << stats->attribute("expedite percentage") << endl;
    cout << " --- Terminals --- " << endl;
    cout << "# Plane terminals: " << stats->attribute("Plane terminal") << endl;
    cout << "# Boat terminals: " << stats->attribute("Boat terminal") << endl;
    cout << "# Truck terminals: " << stats->attribute("Truck terminal") << endl;
    cout << " --- Ports and customers --- " << endl;
    cout << "# Ports          : " << stats->attribute("Port") << endl;
    cout << "# Customers      : " << stats->attribute("Customer") << endl;

    cerr << "Done!" << endl;

    getchar();

    return 0;
}
