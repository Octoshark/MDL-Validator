/* Copyright Octoshark Studios, All rights reserved. */

#ifndef string_helpers_hpp
#define string_helpers_hpp

#include <string>
#include <algorithm>

namespace octoshark
{
	namespace string
	{
		template < const bool CaseSensitive = true >
		bool IsStrEqual( const std::string &str1, const std::string &str2 )
		{
			if constexpr ( CaseSensitive )
				return ( str1 == str2 );
			else
			{
				return ( str1.size() == str2.size() &&
					std::equal( str1.begin(), str1.end(), str2.begin(),
						[]( const char &c1, const char &c2 )
						{
							return ( c1 == c2 || std::toupper( c1 ) == std::toupper( c2 ) );
						} ) );
			}
		}

		template< const bool CaseSensitive = true >
		bool StrContains( const std::string &str, const std::string &substr )
		{
			if constexpr ( CaseSensitive )
				return ( str.find( substr ) != std::string::npos );
			else
			{
				return ( std::search( str.begin(), str.end(), substr.begin(), substr.end(),
					[]( const char &c1, const char &c2 )
					{
						return ( ( c1 == c2 || std::toupper( c1 ) == std::toupper( c2 ) ) );
					} ) != str.end() );
			}
		}
	}
}

#endif // string_helpers_hpp