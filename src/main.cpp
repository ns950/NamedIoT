/**
 * Copyright (c) 2016,  NIST.
 *
 * This file is part of NDN IoT (A project within FIA).
 *
 * repo-ng is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * repo-ng is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * repo-ng, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "common.hpp"

static const std::string ndnRepoUsageMessage =
		/* argv[0] */ " - NDN IoT: In-Network composition\n "
		"-h: show help message\n "
		"-n: composition based name\n  ";

int
main(int argc, char** argv)
{
	std::string name = "/actuator";
	int opt;
	while ((opt = getopt(argc, argv, "hn:")) != -1) {
		switch (opt) {
		case 'h':
			std::cout << argv[0] << ndnRepoUsageMessage << std::endl;
			return 1;
		case 'n':
			name = std::string(optarg);
			break;
		default:
			std::cout << "setting name to "<< name << std::endl;
			break;
		}
	}
	
	try {
		std::cout << "Starting the node ..." <<  name << std::endl;
		
	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		return 2;
	}

	return 0;
}

