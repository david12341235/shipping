user: dagarcia
user: bhh1988

=======================
= Shipping API README =
=======================

Our interface consists of Rep classes (SegmentRep, LocationRep, StatsRep, FleetRep, and ConnRep, which are created and managed by the Manager class) and Engine classes (Segment, Location, Stats, Fleet, Conn). The rep classes were added to Instance.cpp. These classes are responsible for parsing the client-specified attributes and setting the corresponding attributes in the respective engine classes (each Rep instance points to its engine class analogue). This was done to separate the task of parsing from the actual entities. The engine classes are managed by the Engine, which keeps track of them and registers the correct notifiees when a new instance is added to it. 

There are two Reactor types in Engine.h, LocationSegmentReactor and SegmentExpediteReactor. LocationSegmentReactor is responsible for updating the stats object when a new segment is added or deleted, and SegmentExpediteReactor changes the count of expedited segments when the expedite() attribute of a segment is changed.

We have notifiees in other base classes, though they aren't currently used. This is for future extensibility.

The Engine is created upon creation of the Manager, and Stats/Conn/Fleet objects are restricted to one instance. Attempting to create one of these objects with a different name will return the pre-existing Stats/Conn/Fleet object.
