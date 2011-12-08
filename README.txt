user: dagarcia
user: bhh1988

=======================
= Shipping API README =
=======================

This README is provided as companion documentation to the interface specifications given at 

http://www.stanford.edu/class/cs249a/asgn2/
and
http://www.stanford.edu/class/cs249a/asgn3/


Implementation
--------------

Our interface consists of Rep classes (SegmentRep, LocationRep, StatsRep, FleetRep, and ConnRep, which are created and managed by the Manager class) and Engine classes (Segment, Location, Stats, Fleet, Conn). The rep classes are responsible for parsing the client-specified attributes and setting the corresponding attributes in the respective engine classes (each Rep instance points to its engine class analogue). This was done to separate the task of parsing from the actual entities. The engine classes are managed by the Engine, which keeps track of them and registers the correct notifiees when a new instance is added to it. 

There are two Reactor types in Engine.h, LocationSegmentReactor and SegmentExpediteReactor. LocationSegmentReactor is responsible for updating the stats object when a new segment is added or deleted, and SegmentExpediteReactor changes the count of expedited segments when the expedite() attribute of a segment is changed.

We have notifiees in other base classes, though they aren't currently used. This is for future extensibility.


Engine
------

The Engine is created upon creation of the Manager, and Stats/Conn/Fleet objects are restricted to one instance. Attempting to create one of these objects with a different name will return the pre-existing Stats/Conn/Fleet object.


Conn
----

The Conn object does no caching; that is, an explore or connect query will take the same amount of time each time they are called. Furthermore, explore and connect queries both do the same underlying search: a recursive depth-first search whose base case is either when a cycle is detected or when the cost/time/distance limits are violated (connect queries are set up with infinite limits). The queries only differ in which paths to output after retrieving them. This design decision was due to the commonality of the two queries. However, this is all hidden from the client. Also, we enforce that customer locations may only be found at the end points of a path, and the end points of a path must be customer locations.

In general, when a query or input is invalid, the default value returned is the empty string.


Fleet
-----

To specify fleet attributes for two periods of time, such as one from 8pm to 8am, and one from 8am to 8pm, it's necessary to set the fleet's "AtTime" attribute as follows:

	fleet->attributeIs("AtTime", "8 Plane cost 2");
	fleet->attributeIs("AtTime", "20 Plane cost 1");

Where 8 and 20 refer to 8am and 8pm respectively. More generally, scheduled fleet attributes changes can be set with fleet->attributeIs("AtTime", "t [attribute] [value]");


Segments
--------

The default segment length is 100 miles, and fleet speed is 60mph. A segment's support for expediting will be reflected in queries to the Conn instance, but it has no effect on the speed or cost of shipping in the simulation.

Refused packages are stored at the segment until a vehicle becomes available to transport them.


Shipment Injection
------------------
Once transfer rate, shipment size, and destination are set for a Customer, shipments get injected once per day. When a Customer's attributes change such that it no longer injects shipments, shipments that were already scheduled will still be sent out.

Location attributes that trigger shipment injection should only be set after the Conn object is initialized, otherwise there won't be routing information for the shipment. an exception will be thrown if this happens.


Activity/RealTime manager
-------------------------

The real-time manager scales time down to 0.1 second per hour, that is, it is equivalent to creating an activity manager and advancing the clock 1 hour every 1/10 second.


Stats
-----

Additional statistics collected are:

Customers:
- total cost of deliveries
- total number of shipments received
- average shipment latency

Segments:
- total number of shipments received
- total number of shipments fragmented into smaller shipments due to limited vehicle carrying capacity
- total number of shipments rejected (put on hold)


Analysis
--------

Diamond:

       CN
       |
	   n
	 /   \
CW--w-----e--CE
	 \   /
	   s
	   |
	   CS

	   
This topology consists of three customer locations, CN, CW, and CE sending packages to one destination, CS. The customers are connected via four ports, n, w, e, and s. Three experiments were run, each varying the speed shipment injection and segment capacity.

The first experiment was a very light load and large segment capacity, and thus din't have any rejected packages. Average latency was 5.56 hours.

The second experiment put the network under heavy load, injecting 10 packages per day of twice the capacity of vehicles. Segments connected to only one shipment source on the line behaved normally (note that shipments don't count as fragmented if they travel side-by side in separate vehicles, only if they become separated in the network). Segments with shipments coming from multiple locations, however, experienced a large amount of shipment rejections and fragmenting. This was especially bad in the last leg of the trip, where shipments became congested.

The third experiment alleviated the congestion a bit by keeping the volume the same but making shipments the same size as vehicles, meaning that shipments didn't need to be fragmented and rejoined. It also used BFS as the algorithm to highlight the different route taken along the diamond.


Below are the results.
--- Experiment #1

Algorithm - Dijkstra
Vehicle speed - 60
Vehicle capacity - 50
Segment capacity - 10
CW, CE, CN shipping 10 packages twice a day to CS for 1000 hours (41.6 days) 

cost CS: 4980000.00
received CS: 249
latency CS: 5.56

forwarded CNnr: 84
refused CNnr: 0
fragmented CNnr: 0

forwarded ner: 84
refused ner: 0
fragmented ner: 0

forwarded CWwr: 84
refused CWwr: 0
fragmented CWwr: 0

forwarded eCE: 84
refused eCE: 0
fragmented eCE: 0

forwarded wsr: 84
refused wsr: 0
fragmented wsr: 0


forwarded esr: 168
refused esr: 0
fragmented esr: 0

forwarded sCSr: 251
refused sCSr: 0
fragmented sCSr: 0

--- Experiment #2
Algorithm - Dijkstra
Vehicle speed - 60
Vehicle capacity - 50
Segment capacity - 3
CW, CE, CN shipping 100 packages 10 times a day to CS for 1000 hours (41.6 days) 

cost CS: 14040000.00
received CS: 897
latency CS: 145.18

forwarded CNnr: 417
refused CNnr: 0
fragmented CNnr: 0

forwarded ner: 416
refused ner: 0
fragmented ner: 0

forwarded ne: 0
refused ne: 0
fragmented ne: 0

forwarded CWwr: 417
refused CWwr: 0
fragmented CWwr: 0

forwarded eCE: 417
refused eCE: 0
fragmented eCE: 0

forwarded wsr: 416
refused wsr: 0
fragmented wsr: 0

forwarded esr: 832
refused esr: 414
fragmented esr: 831

forwarded sCSr: 2076
refused sCSr: 2073
fragmented sCSr: 300

--- Experiment #3

Algorithm - BFS
Vehicle speed - 60
Vehicle capacity - 50
Segment capacity - 3
CW, CE, CN shipping 50 packages 20 times per day to CS for 1000 hours (41.6 days) 

cost CS: 20424000.00
received CS: 1196
latency CS: 144.60

forwarded CNnr: 417
refused CNnr: 0
fragmented CNnr: 0

forwarded CNn: 0
refused CNn: 0
fragmented CNn: 0

forwarded nwr: 416
refused nwr: 0
fragmented nwr: 0

forwarded CWwr: 417
refused CWwr: 0
fragmented CWwr: 0

forwarded eCE: 834
refused eCE: 0
fragmented eCE: 0

forwarded wsr: 832
refused wsr: 414
fragmented wsr: 831

forwarded esr: 832
refused esr: 0
fragmented esr: 0

forwarded sCSr: 2491
refused sCSr: 2487
fragmented sCSr: 0