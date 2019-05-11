/* Copyright Octoshark Studios, All rights reserved. */

#ifndef mdl_validator_hpp
#define mdl_validator_hpp

#include <filesystem>
#include <stdint.h>
#include <fstream>
#include <memory>
#include <vector>

#include "octoshark/string/string_helpers.hpp"

namespace octoshark
{
	namespace mdl
	{
		namespace validator
		{
			constexpr auto INVALID_MDL_VERSION = -1;
			constexpr auto INVALID_MDL_SIZE = 0;

			struct validation_info_t
			{
				std::filesystem::path Path;
				uintmax_t FileSize;
				int32_t Version;
			};

			validation_info_t ProcessMDL( const std::filesystem::path &Path )
			{
				uintmax_t fileSize = std::filesystem::file_size( Path );

				if ( fileSize < 8 )
					return { Path, INVALID_MDL_SIZE, INVALID_MDL_VERSION };

				std::ifstream file( Path, std::ifstream::binary );
				file.seekg( 4 ); // skip the first 4 bytes

				int32_t version = INVALID_MDL_VERSION;

				file.read( ( char* )&version, sizeof( version ) );
				return { Path, fileSize, version };
			}

			template < const bool SubFolders = true >
			std::unique_ptr< std::vector< validation_info_t > > ProcessDirectory( const std::filesystem::path Path )
			{
				std::unique_ptr< std::vector< validation_info_t > > validationInfos = std::make_unique< std::vector< validation_info_t > >();
				const std::filesystem::directory_iterator it( Path );

				for ( const auto &entry : it )
				{
					if constexpr ( SubFolders )
					{
						if ( std::filesystem::is_directory( entry.status() ) )
						{
							auto subInfos = ProcessDirectory( entry.path() );
							validationInfos->insert( validationInfos->end(), subInfos->begin(), subInfos->end() );
							continue;
						}
					}
					if ( std::filesystem::is_regular_file( entry.status() ) && octoshark::string::IsStrEqual< false >( entry.path().extension().string(), ".mdl" ) )
					{
						validationInfos->push_back( ProcessMDL( entry.path() ) );
						continue;
					}
				}

				return validationInfos;
			}
		}
	}
}

#endif // mdl_validator_hpp