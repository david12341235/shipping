user: dagarcia
user: bhh1988

=======================
= Shipping API README =
=======================

Our interface consists of Rep classes (SegmentRep, LocationRep, StatsRep, FleetRep, ConnRep) and Engine classes (Segment, Location, Stats, Fleet, Conn). The rep classes were added to Instance.cpp. These classes are responsible for parsing the client-specified attributes and setting the corresponding attributes in the respective engine classes (a pointer is held by each Rep instance to its engine class analogue). This was done to separate the task of parsing from the actual entities. The engine classes are managed by the Engine, which keeps track of them. The Engine also registers the correct notifiees when a new instance is added to it. There are two Reactor types in Engine.h, LocationSegmentReactor and SegmentExpediteReactor. LocationSegmentReactor is responsible for updating the stats object when a new segment 

Currently, we use notifications only to have Stats respond to whenever a Location or Segment is created (the Engine notifies the Stats class of this, since newly created Locations and Segments are added to the engine with the LocationIs and SegmentIs methods) and for when a Segment's expedited attribute changes.

Also, we have notifiees in basically all of the base classes, but that doesn't necessarily mean we will use all of them.