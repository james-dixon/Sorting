#ifndef RADIX_HPP
#define RADIX_HPP

#include <vector>
#include <utility>
#include <cstdint>

namespace sort
{

	void radix(std::vector<uint32_t>& data)
	{
		std::vector<uint32_t> spare(data.size(),0);
		const uint32_t mask_size = 8;
		const uint32_t mask = (1<<(mask_size))-1;
		
		for(uint32_t depth=0; depth<32; depth += mask_size)
		{
			const auto start = data.begin();
			const auto end = data.end();
			uint32_t totals[mask+1] = {0};
			
			for(auto itt=start; itt!=end; ++itt)
			{
				++totals[ (*(itt)>>depth)&mask ];
			}

		
			for(uint32_t i=mask; i>0; --i)
				totals[i] = totals[i-1];
			totals[0]=0;
			for(uint32_t i=1; i<=mask; ++i)
				totals[i] += totals[i-1];
	
			uint32_t counts[mask+1] = {0};
			
			for(auto itt=start; itt!=end; ++itt)
			{
				spare[  totals[ ((*(itt)>>depth)&mask) ] + counts[ (*(itt)>>depth)&mask]++ ] = *itt;
			}
			
			data.swap(spare);
		}

	}


}



#endif
