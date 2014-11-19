#ifndef QUADRATIC_SORT_HPP
#define QUADRATIC_SORT_HPP


namespace sort
{
	namespace quad
	{
		template<typename Iterator>
		void selection(const Iterator start, const Iterator end)
		{
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
		
		template<typename Iterator>
		void insertion(const Iterator start, const Iterator end)
		{
			for(auto it_s=start+1; it_s!=end; ++it_s)
			{
				auto it = it_s;
				while( it!=start && *std::prev(it) > *(it))
				{
					std::swap( *std::prev(it), *(it) );
					it = std::prev(it);
				}


			}
		}

		template<typename Iterator>
		void bubble(const Iterator start, const Iterator end)
		{
			bool swap = true;

			while(swap)
			{
				swap = false;
				for(auto position=start+1; position!=end; ++position)
				{
					if( *std::prev(position) > *(position) )
					{
						std::swap( *std::prev(position), *(position) );
						swap = true;
					}
				}
		
			}
		}

	}


}


#endif
