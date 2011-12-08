#include "Engine.h"
#include "Stats.h"

using namespace Shipping;

Dollar Stats::totalCost(string name) {
    		Customer* c = dynamic_cast<Customer*>(engine()->location(name).ptr());
		if( c ) return c->totalCost();
		else throw Fwk::UnknownAttrException("Specified location does not have a totalcost attribute");
}

NumPackages Stats::received(string name) {
	Customer* c = dynamic_cast<Customer*>(engine_->location(name).ptr());
	if( c ) return c->shipmentsReceived();
	else throw Fwk::UnknownAttrException("Specified location does not have a shipments received attribute");
}

Hour Stats::latency(string name)
{
	Customer* c = dynamic_cast<Customer*>(engine_->location(name).ptr());
	if( c ) return c->averageLatency();
	else throw Fwk::UnknownAttrException("Specified location does not have an average latency attribute");
}

NumPackages Stats::forwarded(string name)
{
	Segment::Ptr segment = engine_->segment(name);
	if( segment.ptr() == NULL )
		throw Fwk::EntityNotFoundException("Specified segment cannot be found");
	else
		return segment->shipmentsReceived();
}

NumPackages Stats::refused(string name)
{
	Segment::Ptr segment = engine_->segment(name);
	if( segment.ptr() == NULL )
		throw Fwk::EntityNotFoundException("Specified segment cannot be found");
	else
		return segment->shipmentsRefused();
}

NumPackages Stats::fragmented(string name)
{
	Segment::Ptr segment = engine_->segment(name);
	if( segment.ptr() == NULL )
		throw Fwk::EntityNotFoundException("Specified segment cannot be found");
	else
		return segment->shipmentsFragmented();
}
