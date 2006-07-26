// $Id$

/***********************************************************************
Moses - factored phrase-based language decoder
Copyright (C) 2006 University of Edinburgh

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
***********************************************************************/

#pragma once

#include <set>
#include <iostream>

struct CompareLatticePathCollection
{
	bool operator()(const LatticePath* pathA, const LatticePath* pathB) const
	{
		return (pathA->GetScore(ScoreType::Total) > pathB->GetScore(ScoreType::Total));
	}
};

class LatticePathCollection : public std::multiset<LatticePath*, CompareLatticePathCollection>
{
public:
	~LatticePathCollection()
	{
		// clean up
		RemoveAllInColl<LatticePathCollection::iterator> (*this);
	}
};

inline std::ostream& operator<<(std::ostream& out, const LatticePathCollection& pathColl)
{
	LatticePathCollection::const_iterator iter;
	
	for (iter = pathColl.begin() ; iter != pathColl.end() ; ++iter)
	{
		const LatticePath &path = **iter;
		out << path << std::endl;
	}
	return out;
}

