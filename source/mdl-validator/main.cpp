/* Copyright Octoshark Studios, All rights reserved. */

#include <iostream>
#include <filesystem>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <iomanip>
#include <ctime>

#include "octoshark/platform/platform.hpp"
#include "octoshark/mdl-validator/mdl-validator.hpp"

void PrintUsage()
{
	std::cout << "Valid Usage: mdl-validator" << octoshark::platform::EXT_EXECUTABLE << " -path <\"PATH/TO/MODELS\"> -mdlversion <version>\n";
}

int main( const int argc, const char *argv[] )
{
	if ( argc < 5 || argc % 2 == 0 )
	{
		PrintUsage();
		return 0;
	}

	std::map< std::string, std::string > Args;
	
	for ( int i = 1; i < argc - 1; i += 2 )
		Args[ argv[ i ] ] = argv[ i + 1 ];

	const std::filesystem::path modelPath( Args[ "-path" ] );
	const int mdlversion = std::atoi( Args[ "-mdlversion" ].c_str() ); // Using this instead of stoi so we don't throw exceptions

	if ( modelPath.empty() || !std::filesystem::is_directory( modelPath ) )
	{
		std::cout << "Invalid path specified\n";
		return 0;
	}

	auto ValidationInfos = octoshark::mdl::validator::ProcessDirectory( modelPath );

	uintmax_t SizeErrorCount = 0;
	uintmax_t OldMDLCount = 0;
	uintmax_t NewMDLCount = 0;

	std::stringstream SizeErrors;
	std::stringstream OldMDLs;
	std::stringstream NewMDLs;
	std::stringstream Log;
	std::stringstream LogFileName;

	for ( const auto &ValidationInfo : *ValidationInfos )
	{
		if ( ValidationInfo.FileSize == octoshark::mdl::validator::INVALID_MDL_SIZE )
		{
			SizeErrors << ValidationInfo.Path.string() << std::endl;
			++SizeErrorCount;
			continue;
		}

		if ( ValidationInfo.Version < mdlversion )
		{
			++OldMDLCount;
			OldMDLs << ValidationInfo.Path.lexically_relative( modelPath ).string() << ": " << ValidationInfo.Version << std::endl;
			continue;
		}
		else if ( ValidationInfo.Version > mdlversion )
		{
			++NewMDLCount;
			NewMDLs << ValidationInfo.Path.lexically_relative( modelPath ).string() << ": " << ValidationInfo.Version << std::endl;
			continue;
		}
	}

	
	Log << "-Invalid Size MDLs (Total: "<< SizeErrorCount << ")-\n" << SizeErrors.str() << std::endl;
	Log << "-Old Version MDLs (Total: " << OldMDLCount << ")-\n" << OldMDLs.str() << std::endl;
	Log << "-New Version MDLs (Total: " << NewMDLCount << ")-\n" << NewMDLs.str() << std::endl;

	std::cout << Log.str();

	auto now = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );	
	LogFileName << "mdl-validator-" << std::put_time( std::localtime( &now ), "%Y%m%d%H%M%S" ) << ".log";

	std::ofstream LogFile( LogFileName.str() );
	LogFile << Log.str();

	return 0;
}