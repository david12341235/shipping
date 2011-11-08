#include "Engine.h"
#include "Conn.h"

using namespace Shipping;

void Conn::startLocationIs(const Fwk::String& name ) { 
	if( name == "" )
		startLocation_ = NULL;
	else
		startLocation_ = engine_->location(name); 
}

void Conn::endLocationIs(const Fwk::String& name ) { 
	if( name == "" )
		endLocation_ = NULL;
	else
		endLocation_ = engine_->location(name); 
}

string Conn::PathUnit::output() const
{
	ostringstream s;
	s << location_->name();
	if( segment_ )
	{
		s << "(" << segment_->name() << ":" << segment_->length().value() << ":" << segment_->returnSegment()->name() << ")";
	}
	return s.str();
}

string Conn::value()
{
	if( startLocation() == endLocation() )
	{
		return "";
	}

	vector< vector<PathUnit*> > path;
	vector<PathUnit*> workingPath;
	// populate the path vector
	connectPaths(startLocation_, path, workingPath);

	ostringstream result;
	if( queryType() == explore_ )
	{
		// for all paths, format the output
		for( vector< vector<PathUnit*> >::iterator iter = path.begin(); iter != path.end(); ++iter )
		{
			// must match our expedited constraint
			if( iter->back()->expVal_ != expedited() )
			{
				continue;
			}
			for(vector<PathUnit*>::iterator i = iter->begin(); i != iter->end();++i)
			{
				result << (*i)->output() << ' ';
			}
			result << '\n';
		}
	}
	else // connect
	{
		// for all paths, format the output
		for( vector< vector<PathUnit*> >::iterator iter = path.begin(); iter != path.end(); ++iter )
		{
			result << iter->back()->cost_.value() << ' ' << iter->back()->time_.value() << ' ';
			if( iter->back()->expVal_ == Segment::expYes() ) result << "yes;";
			else result << "no;";
			
			for(vector<PathUnit*>::iterator i = iter->begin(); i != iter->end();++i)
			{
				result << ' ' << (*i)->output();
			}
			result << '\n';
		}
	}
	return result.str();
}

void Conn::connectPaths(Fwk::Ptr<Location const> cur, vector< vector<PathUnit*> >& path, vector<PathUnit*>& workingPath )
{
	// check for cycles
	for( vector<PathUnit*>::iterator iter =workingPath.begin(); iter != workingPath.end(); ++iter)
	{
		if( cur == (*iter)->location_ )
		{
			return;
		}
	}

	PathUnit* u = new PathUnit();
	u->location_ = cur;
	if( workingPath.size() > 0 )
	{
		PathUnit* p = workingPath.back();
		Dollar costNew( p->cost_.value() + p->segment_->difficulty().value() * engine_->fleet()->cost( p->segment_->mode() ).value() * p->segment_->length().value() );
		Hour timeNew( p->time_.value() + p->segment_->length().value() / engine_->fleet()->speed( p->segment_->mode() ).value() );
		Mile distanceNew(p->distance_.value() + p->segment_->length().value());
		u->cost_ = costNew;
		u->time_ = timeNew;
		u->distance_ = distanceNew;
		u->expVal_ = p->expVal_;
	}

	// check for destination reached
	if( cur == endLocation_ || u->cost_ > cost() || u->time_ > time() || u->distance_ > distance() )
	{
		cout << u->cost_.value() << " " << cost().value() << " " << u->time_.value() << " " << time().value() << " " << u->distance_.value() << " " << distance().value();
		workingPath.push_back(u);
		path.push_back(workingPath);
		workingPath.pop_back();
		return;
	}

	// Go through all the segments
	Segment::SegmentId _segId = 1;
	Segment::PtrConst _segment = cur->segment( _segId );
	while( _segment != Segment::PtrConst(NULL) )
	{
		// consistency in expedited
		if( workingPath.size() == 0 || _segment->expedite() == workingPath.back()->expVal_ )
		{
			if( workingPath.size() == 0 )
			{
				u->expVal_ = _segment->expedite();
			}

			// if a segment leads to another location, then
			// add the location to our working path and recurse
			Segment::PtrConst _returnSegment = _segment->returnSegment();
			if( _returnSegment != Segment::PtrConst(NULL) )
			{
				Fwk::Ptr<Location> next = _returnSegment->source();
				u->segment_ = _segment;
				workingPath.push_back(u);
				connectPaths( next, path, workingPath );
				workingPath.pop_back();
			}
		}

		_segment = cur->segment( ++_segId );
	}

	return;
}


