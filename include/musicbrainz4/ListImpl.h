/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_LIST_IMPL_H
#define _MUSICBRAINZ4_LIST_IMPL_H

#include "musicbrainz4/List.h"

namespace MusicBrainz4
{
	template <class T>
	class CListImpl: public CList
	{
	public:
		CListImpl(const XMLNode& Node=XMLNode::emptyNode())
		:	CList()
		{
			if (!Node.isEmpty())
			{
				//std::cout << T::GetElementName() << " List node: " << std::endl << Node.createXMLString(true) << std::endl;

				Parse(Node);
			}
		}

		CListImpl(const CListImpl<T>& Other)
		:	CList()
		{
			*this=Other;
		}

		MusicBrainz4::CListImpl<T>& operator =(const CListImpl<T>& Other)
		{
			if (this!=&Other)
			{
				CList::operator =(Other);
			}

			return *this;
		}

		virtual ~CListImpl()
		{
		}

		CListImpl<T> *Clone()
		{
			return new CListImpl<T>(*this);
		}

		virtual std::ostream& Serialise(std::ostream& os) const
		{
			os << T::GetElementName() << " List (impl):" << std::endl;

			CList::Serialise(os);

			for (int count=0;count<NumItems();count++)
			{
				T *ThisItem=Item(count);

				os << *ThisItem << std::endl;
			}

			return os;
		}

		static std::string GetElementName()
		{
			return "";
		}

		T *Item(int Item) const
		{
			return dynamic_cast<T *>(CList::Item(Item));
		}

		void AddItem(T *Item)
		{
			CList::AddItem(Item);
		}

	protected:
		bool ParseElement(const XMLNode& Node)
		{
			bool RetVal=true;

			std::string NodeName=Node.getName();

			if (T::GetElementName()==NodeName)
			{
				T *Item=0;

				RetVal=ProcessItem(Node,Item);
				if (RetVal)
					AddItem(Item);
			}
			else
				RetVal=CList::ParseElement(Node);

			return RetVal;
		}

	};
}

#endif
