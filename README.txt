user: dagarcia
user: bhh1988

=======================
= Shipping API README =
=======================

Our interface consists of Rep classes (SegmentRep, LocationRep, StatsRep, FleetRep, and ConnRep, which are created and managed by the Manager class) and Engine classes (Segment, Location, Stats, Fleet, Conn). The rep classes were added to Instance.cpp. These classes are responsible for parsing the client-specified attributes and setting the corresponding attributes in the respective engine classes (each Rep instance points to its engine class analogue). This was done to separate the task of parsing from the actual entities. The engine classes are managed by the Engine, which keeps track of them and registers the correct notifiees when a new instance is added to it. 

There are two Reactor types in Engine.h, LocationSegmentReactor and SegmentExpediteReactor. LocationSegmentReactor is responsible for updating the stats object when a new segment is added or deleted, and SegmentExpediteReactor changes the count of expedited segments when the expedite() attribute of a segment is changed.

We have notifiees in other base classes, though they aren't currently used. This is for future extensibility.

The Engine is created upon creation of the Manager, and Stats/Conn/Fleet objects are restricted to one instance. Attempting to create one of these objects with a different name will return the pre-existing Stats/Conn/Fleet object.

The Conn object does no caching; that is, an explore or connect query will take the same amount of time each time they are called. Furthermore, explore and connect queries both do the same underlying search: a recursive depth-first search whose base case is either when a cycle is detected or when the cost/time/distance limits are violated (connect queries are set up with infinite limits). The queries only differ in which paths to output after retrieving them. This design decision was due to the commonality of the two queries. However, this is all hidden from the client. Also, we enforce that customer locations may only be found at the end points of a path, and the end points of a path must be customer locations.

In general, when a query or input is invalid, the default value returned is the empty string.


Notes for assignment3:

default segment length is now 100 miles, and fleet speed is 60mph.
once transfer rate, shipment size, and destination are set for a Customer, shipments get injected once per day.
activity manager scales time down to 0.1 second per hour, real time manager advances clock 1 hour per (real-time) 1/10 second.