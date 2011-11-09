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

	vector< vector<PathUnit> > path;
	vector<PathUnit> workingPath;
	// populate the path vector
	paths(startLocation_, path, workingPath, Segment::expNo());
	paths(startLocation_, path, workingPath, Segment::expYes());

	ostringstream result;
	if( queryType() == explore_ )
	{
		// for all paths, format the output
		for( vector< vector<PathUnit> >::iterator iter = path.begin(); iter != path.end(); ++iter )
		{
			// must match our expedited constraint
			if( iter->back().expVal_ != expedited() && expedited() == Segment::expYes() )
			{
				continue;
			}

			// ignore the trivial path consisting of just the starting location
			if( iter->size() == 1 )
			{
				continue;
			}

			// skip any expedited paths if we're not required to select expedited paths,
			// because there will always be an unexpedited version of this path in the list
			else if( iter->back().expVal_ == Segment::expYes() && expedited() != Segment::expYes() )
			{
				continue;
			}
			for(vector<PathUnit>::iterator i = iter->begin(); i != iter->end();++i)
			{
				result << i->output() << ' ';
			}
			result << '\n';
		}
	}
	else // connect
	{
		// for all paths, format the output
		for( vector< vector<PathUnit> >::iterator iter = path.begin(); iter != path.end(); ++iter )
		{
			if( iter->back().location_ == endLocation_ )
			{
				result << iter->back().cost_.value() << ' ' << iter->back().time_.value() << ' ';
				if( iter->back().expVal_ == Segment::expYes() ) result << "yes;";
				else result << "no;";
				
				for(vector<PathUnit>::iterator i = iter->begin(); i != iter->end();++i)
				{
					result << ' ' << i->output();
				}
				result << '\n';
			}
		}
	}
	return result.str();
}

void Conn::paths(Fwk::Ptr<Location const> cur, vector< vector<PathUnit> >& path, vector<PathUnit> workingPath, Segment::ExpVal _expVal )
{
	// check for cycles
	for( vector<PathUnit>::iterator iter =workingPath.begin(); iter != workingPath.end(); ++iter)
	{
		if( cur == iter->location_ )
		{
			return;
		}
	}

	PathUnit u;
	u.location_ = cur;
	u.expVal_ = _expVal;
	if( workingPath.size() > 0 )
	{
		PathUnit& p = workingPath.back();
		if( _expVal == Segment::expYes() )
		{
			Dollar costNew( p.cost_.value() + p.segment_->difficulty().value() * engine_->fleet()->cost( p.segment_->mode() ).value() * p.segment_->length().value() * 1.5 );
			Hour timeNew( p.time_.value() + p.segment_->length().value() / ( engine_->fleet()->speed( p.segment_->mode() ).value() * 1.3 ) );
			Mile distanceNew(p.distance_.value() + p.segment_->length().value());
			u.cost_ = costNew;
			u.time_ = timeNew;
			u.distance_ = distanceNew;
		}
		else
		{
			Dollar costNew( p.cost_.value() + p.segment_->difficulty().value() * engine_->fleet()->cost( p.segment_->mode() ).value() * p.segment_->length().value() );
			Hour timeNew( p.time_.value() + p.segment_->length().value() / engine_->fleet()->speed( p.segment_->mode() ).value() );
			Mile distanceNew(p.distance_.value() + p.segment_->length().value());
			u.cost_ = costNew;
			u.time_ = timeNew;
			u.distance_ = distanceNew;
		}
	}

	// check if we exceeded our limits
	if( u.cost_ > cost() || u.time_ > time() || u.distance_ > distance() )
	{
		return;
	}

	// add the current path to our list of candidate paths
	workingPath.push_back(u);
	path.push_back(workingPath);

	// If we're not at a customer location, Go through all the segments
	// and recurse
	if( cur->type() == Location::customer() && cur != startLocation_ )
	{
		workingPath.pop_back();
		return;
	}

	// Go through all the segments
	Segment::SegmentId _segId = 1;
	Segment::PtrConst _segment = cur->segment( _segId );
	while( _segment != Segment::PtrConst(NULL) )
	{
		// expedited supported segments can both expedite or not. Unexpedited
		// segments must be skipped if we are required to expedite
		if( _expVal != Segment::expYes() || _segment->expedite() == Segment::expYes() )
		{
			// if a segment leads to another location, then
			// add the location to our working path and recurse
			Segment::PtrConst _returnSegment = _segment->returnSegment();
			if( _returnSegment != Segment::PtrConst(NULL) )
			{
				Fwk::Ptr<Location> next = _returnSegment->source();
					workingPath.back().segment_ = _segment;
					paths( next, path, workingPath, _expVal );
			}
		}

		_segment = cur->segment( ++_segId );
	}
	workingPath.pop_back();

	return;
}


