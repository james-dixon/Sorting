#ifndef RADIX_HPP
#define RADIX_HPP

#include <vector>
#include <utility>
#include <cstdint>
#include <type_traits>

namespace sort
{

	namespace radix{
		
		template<typename T>
		typename std::enable_if<std::is_unsigned<T>::value, void>::type
		single(std::vector<T>& data)
		{
			std::vector<T> spare(data.size(),0);
			const uint64_t mask_size = 8;
			const uint64_t mask = (1<<(mask_size))-1;
			const uint64_t depth_limit = 8*sizeof(T);
			for(uint64_t depth=0; depth<depth_limit; depth += mask_size)
			{
				const auto start = data.begin();
				const auto end = data.end();
				uint64_t totals[mask+1] = {0};
				
				for(auto itt=start; itt!=end; ++itt)
				{
					++totals[ (*(itt)>>depth)&mask ];
				}
				
				
				for(uint64_t i=mask; i>0; --i)
					totals[i] = totals[i-1];
				totals[0]=0;
				for(uint64_t i=1; i<=mask; ++i)
					totals[i] += totals[i-1];
				
				uint64_t counts[mask+1] = {0};
				
				for(auto itt=start; itt!=end; ++itt)
				{
					spare[  totals[ ((*(itt)>>depth)&mask) ] + counts[ (*(itt)>>depth)&mask]++ ] = *itt;
				}
				
				data.swap(spare);
			}
			
		}
	
	}
}



#endif
