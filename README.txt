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

   n
 /   \
w-----e
 \   /
   s

