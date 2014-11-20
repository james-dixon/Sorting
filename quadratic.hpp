#ifndef QUADRATIC_SORT_HPP
#define QUADRATIC_SORT_HPP


// need to comment each method!

// could do 'binary search' for insertion step in insertion sort
// reduced to nlog(n) comparisons but still n^2 swaps

namespace sort
{
	namespace quad
	{
		template<class Iterator>
		void selection(const Iterator start, const Iterator end)
		{
			// find the minimum of the remaining 'unsorted' elements
			// move it to the back of the sorted elements
			// shorten the list of unsorted elements by 1
			for(auto it=start; it<end; ++it)
			{
				auto itt_min = it;
				for(auto it_l=std::next(it); it_l!=end; ++it_l)
				{
					if( *(it_l) < *(itt_min) )
						itt_min = it_l;
				}
	
				if(it!=itt_min)
					std::swap( *it, *itt_min );
			}
		}
		
		template<class Iterator>
		void insertion(const Iterator start, const Iterator end)
		{
			// builds up a sorted list at the start
			
			for(auto it_s=std::next(start); it_s!=end; ++it_s)
			{
				// we know all elements before it_s is sorted
				// => move back through elements until we find the correct place
				// for the item at it_s
				auto it = it_s;
				while( it!=start && *std::prev(it) > *(it))
				{
					std::swap( *std::prev(it), *(it) );
					it = std::prev(it);
				}
			}
		}

		template<class Iterator>
		void bubble(const Iterator start, Iterator end)
		{
			// this 'sinks' the biggest elements down to the bottom
			// performs particularly poorly with small elements at the end
			// since they only move one space each time
			bool swap = true;

			while(swap)
			{
				// continue until we don't make any swaps => sorted
				swap = false;
				for(auto position=std::next(start); position!=end; ++position)
				{
				
					if( *std::prev(position) > *(position) )
					{
						// if 'following' element is larger then previous, swap them
						std::swap( *std::prev(position), *(position) );
						swap = true;
					}
					// then move to next pair 
				}

				// after the first iteration, we know the largest item must be in the correct place
				// similar for second iteration, largest item is at the second last place
				// generalise, after nth iteration, final 'n' items are in correct place
				// therefore can reduce length of loop by 1 each time
				end = std::prev(end);  // slight optimisation
			}
		}

	}


}


#endif
