#include "Engine.h"
#include "Conn.h"

using namespace Shipping;

void Conn::startLocationIs(const Fwk::String& name )
{
    if( name == "" )
        startLocation_ = NULL;
    else
        startLocation_ = engine_->location(name);
}

void Conn::endLocationIs(const Fwk::String& name )
{
    if( name == "" )
        endLocation_ = NULL;
    else
        endLocation_ = engine_->location(name);
}

string Conn::PathUnit::output() const
{
    ostringstream s;
    s << location_->name();
    if( segment_  != NULL ) {
        s << "(" << segment_->name() << ":" << segment_->length() << ":" << segment_->returnSegment()->name() << ")";
    }
    return s.str();
}

void Conn::simulationStartedIs( bool _simulationStarted )
{
	simulationStarted_ = _simulationStarted;
	if( algorithm_ == dijkstra_ )
	{
		vector<Location::Ptr> nodeVector;
		for( Engine::LocationIterator iter = engine_->locationIter(); iter.ptr(); ++iter )
		{
			nodeVector.push_back(*iter);
		}

		for( vector<Location::Ptr>::iterator iter = nodeVector.begin(); iter != nodeVector.end(); ++iter )
		{
			// initialization
			Location::Ptr start = *iter;
			vector<Location::Ptr> unvisited;
			map<string, Mile> tentativeDistance;
			map<string, Segment::PtrConst> nextSegment;
			for( Engine::LocationIterator i = engine_->locationIter(); i.ptr(); ++i )
			{
				string const & name = (*i)->name();
				if( name == start->name() )
				{
					tentativeDistance.insert( pair<string, Mile>(name, Mile(0) ) );
				}
				else
				{
					tentativeDistance.insert( pair<string, Mile>(name, Mile::max() ) );
					if( (*i)->type() != Location::customer() )
					{
						unvisited.push_back(*i);
					}
				}
				nextSegment[ name ] = NULL;
			}

		    // initialize nextSegment for neighbors of initial starting node
		    Segment::SegmentId segId = 1;
		    Segment::PtrConst segment = start->segment( segId );
		    while( segment != Segment::PtrConst(NULL) )
		    {
				if( segment->returnSegment() && segment->returnSegment()->source() )
				{
					string neighborName = segment->returnSegment()->source()->name();
					nextSegment[ neighborName ] = segment;
					tentativeDistance.find( neighborName )->second =  segment->length();
				}
				segment = start->segment( ++segId );
		    }

			while( !unvisited.empty() )
			{
				// find the minimum tentative distance so far
				Mile min( Mile::max() );
				vector<Location::Ptr>::iterator visitingIter;
				for( vector<Location::Ptr>::iterator i = unvisited.begin(); i != unvisited.end(); ++i )
				{
					map< string, Mile >::iterator found = tentativeDistance.find( (*i)->name() );
					if( found->second < min )
					{
						min = found->second;
						visitingIter = i;
					}
				}
				if( min == Mile::max() )
				{
					// the remaining unvisited nodes are not connected to are start node
					break;
				}

				Location::Ptr visiting = *visitingIter;
				unvisited.erase( visitingIter );
				Mile distanceSoFar( tentativeDistance.find( visiting->name() )->second );
			    segId = 1;
			    segment = visiting->segment( segId );
			    while( segment != Segment::PtrConst(NULL) )
			    {
					if( segment->returnSegment() && segment->returnSegment()->source() )
					{
						Mile neighborDistance( distanceSoFar.value() + segment->length().value() ) ;
						string neighborName = segment->returnSegment()->source()->name();
						map< string, Mile >::iterator neighborIter = tentativeDistance.find(neighborName);
						if( neighborIter->second > neighborDistance )
						{
							neighborIter->second = neighborDistance;
							nextSegment[ neighborName ] = nextSegment[ visiting->name() ];
						}
					}

					segment = visiting->segment( ++segId );
			    }
			}

			for( map<string, Segment::PtrConst>::iterator i = nextSegment.begin(); i != nextSegment.end(); ++i )
			{
				start->nextSegmentIs( i->first, const_cast<Segment*>(i->second.ptr()) );
			}
		}
	}
	else if( algorithm_ == bfs_ )
	{
		vector<Location::Ptr> nodeVector;
		for( Engine::LocationIterator iter = engine_->locationIter(); iter.ptr(); ++iter )
		{
			nodeVector.push_back(*iter);
		}

		for( vector<Location::Ptr>::iterator iter = nodeVector.begin(); iter != nodeVector.end(); ++iter )
		{
			Location::Ptr start = *iter;
			map<string, Segment::PtrConst> nextSegment;
			queue< Location::Ptr > q;
			map<string, bool> visited;

		    Segment::SegmentId segId = 1;
		    Segment::PtrConst segment = start->segment( segId );
		    while( segment != Segment::PtrConst(NULL) )
		    {
				if( segment->returnSegment() && segment->returnSegment()->source() )
				{
					q.push( segment->returnSegment()->source() );
					nextSegment[ segment->returnSegment()->source()->name() ] = segment;
					visited[ segment->returnSegment()->source()->name() ] = true;
				}
				segment = start->segment( ++segId );
			}
			visited[start->name()] = true;

			while( !q.empty() )
			{
			    Location::Ptr cur = q.front();
			    q.pop();
			    if( cur->type() == Location::customer() )
			    {
			    	  continue;
			    }
			    segId = 1;
			    segment = cur->segment( segId );
			    while( segment != Segment::PtrConst(NULL) )
			    {
					if( segment->returnSegment() && segment->returnSegment()->source() && !visited[ segment->returnSegment()->source()->name() ] )
					{
						q.push( segment->returnSegment()->source() );

						nextSegment[ segment->returnSegment()->source()->name() ] = nextSegment[ cur->name() ];
						visited[ segment->returnSegment()->source()->name() ] = true;
					}
					segment = cur->segment( ++segId );
			    }
			}
			

			for( map<string, Segment::PtrConst>::iterator i = nextSegment.begin(); i != nextSegment.end(); ++i )
			{
				start->nextSegmentIs( i->first, const_cast<Segment*>(i->second.ptr()) );
			}
		}
	}
}

string Conn::value()
{
    if( startLocation() == endLocation() ) {
        return "";
    }

    vector< vector<PathUnit> > path;
    vector<PathUnit> workingPath;
    // populate the path vector
    paths(startLocation_, path, workingPath, Segment::expNo());
    paths(startLocation_, path, workingPath, Segment::expYes());

    ostringstream result;
    bool appendNewline = false;
    if( queryType() == explore_ ) {
        // for all paths, format the output
        for( vector< vector<PathUnit> >::iterator iter = path.begin(); iter != path.end(); ++iter ) {
            // must match our expedited constraint
            if( iter->back().expVal_ != expedited() && expedited() == Segment::expYes() ) {
                continue;
            }

            // ignore the trivial path consisting of just the starting location
            if( iter->size() == 1 ) {
                continue;
            }

            // skip any expedited paths if we're not required to select expedited paths,
            // because there will always be an unexpedited version of this path in the list
            else if( iter->back().expVal_ == Segment::expYes() && expedited() != Segment::expYes() ) {
                continue;
            }
            // Tag on a new line to result only after we've processed at least one path
            if( appendNewline ) {
                result << '\n';
            }

            bool appendSpace = false;
            for(vector<PathUnit>::iterator i = iter->begin(); i != iter->end(); ++i) {
                if( appendSpace ) {
                    result << ' ';
                }
                result << i->output();
                appendNewline = appendSpace = true;
            }
        }
    } else { // connect
        // for all paths, format the output
        for( vector< vector<PathUnit> >::iterator iter = path.begin(); iter != path.end(); ++iter ) {
            if( iter->back().location_ == endLocation_ ) {
                // Tag on a new line to result only after we've processed at least one path
                if( appendNewline ) {
                    result << '\n';
                }

                result << iter->back().cost_ << ' ' << iter->back().time_ << ' ';
                if( iter->back().expVal_ == Segment::expYes() ) result << "yes;";
                else result << "no;";

                for(vector<PathUnit>::iterator i = iter->begin(); i != iter->end(); ++i) {
                    result << ' ' << i->output();
                    appendNewline = true;
                }
            }
        }
    }
    return result.str();
}

void Conn::paths(Fwk::Ptr<Location const> cur, vector< vector<PathUnit> >& path, vector<PathUnit> workingPath, Segment::ExpVal _expVal )
{
    if (cur == NULL) return;
    // check for cycles
    for( vector<PathUnit>::iterator iter =workingPath.begin(); iter != workingPath.end(); ++iter) {
        if( cur == iter->location_ ) {
            return;
        }
    }

    PathUnit u;
    u.location_ = cur;
    u.expVal_ = _expVal;
    if( workingPath.size() > 0 ) {
        PathUnit& p = workingPath.back();
        if( _expVal == Segment::expYes() ) {
            Dollar costNew( p.cost_.value() + p.segment_->difficulty().value() * engine_->fleet()->cost( p.segment_->mode() ).value() * p.segment_->length().value() * 1.5 );
            Hour timeNew( p.time_.value() + p.segment_->length().value() / ( engine_->fleet()->speed( p.segment_->mode() ).value() * 1.3 ) );
            Mile distanceNew(p.distance_.value() + p.segment_->length().value());
            u.cost_ = costNew;
            u.time_ = timeNew;
            u.distance_ = distanceNew;
        } else {
            Dollar costNew( p.cost_.value() + p.segment_->difficulty().value() * engine_->fleet()->cost( p.segment_->mode() ).value() * p.segment_->length().value() );
            Hour timeNew( p.time_.value() + p.segment_->length().value() / engine_->fleet()->speed( p.segment_->mode() ).value() );
            Mile distanceNew(p.distance_.value() + p.segment_->length().value());
            u.cost_ = costNew;
            u.time_ = timeNew;
            u.distance_ = distanceNew;
        }
    }

    // check if we exceeded our limits
    if( u.cost_ > cost() || u.time_ > time() || u.distance_ > distance() ) {
        return;
    }

    // add the current path to our list of candidate paths
    workingPath.push_back(u);
    path.push_back(workingPath);

    // If we're not at a customer location, Go through all the segments
    // and recurse
    if( cur->type() == Location::customer() && cur != startLocation_ ) {
        workingPath.pop_back();
        return;
    }

    // Go through all the segments
    Segment::SegmentId _segId = 1;
    Segment::PtrConst _segment = cur->segment( _segId );
    while( _segment != Segment::PtrConst(NULL) ) {
        // expedited supported segments can both expedite or not. Unexpedited
        // segments must be skipped if we are required to expedite
        if( _expVal != Segment::expYes() || _segment->expedite() == Segment::expYes() ) {
            // if a segment leads to another location, then
            // add the location to our working path and recurse
            Segment::PtrConst _returnSegment = _segment->returnSegment();
            if( _returnSegment != Segment::PtrConst(NULL) ) {
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


