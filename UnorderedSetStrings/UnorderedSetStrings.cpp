#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <cstdint>
#include <chrono>

uint64_t Measure(const std::vector<std::string>& base64_vector, const uint32_t iter, const bool reserve)
{
	uint64_t sum = 0;
	for (uint32_t i = 0; i < iter; ++i)
	{
		std::unordered_set<std::string> base64_set;
		if (reserve)
		{
			base64_set.reserve(base64_vector.size());
		}
		auto t1 = std::chrono::high_resolution_clock::now();
		for (const auto& checksum : base64_vector)
		{
			base64_set.insert(checksum);
		}
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		sum += duration;
	}
	return sum / iter;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "args: <filename> <iterations>\n";
		return EXIT_FAILURE;
	}
	std::string filename(argv[1]);
	const uint32_t iter = std::stoi(argv[2]);

	try
	{
		std::ifstream conf_file(filename);
		if (!conf_file.is_open())
		{
			std::cerr << "Error while opening file '" << filename << "'\n";
			return EXIT_FAILURE;
		}

		std::vector<std::string> base64_vector;
		do
		{
			std::string line;
			std::getline(conf_file, line);
			if (!line.empty())
			{
				base64_vector.push_back(line);
			}
		} while (conf_file.good());

		conf_file.close();

		uint64_t duration, duration_reserved;
		duration = Measure(base64_vector, iter, false);
		duration_reserved = Measure(base64_vector, iter, true);

		if (duration > duration_reserved)
		{
			std::cout << "std::unordered_set with reserved space is faster.\n";
		}
		else
		{
			std::cout << "std::unordered_set WITHOUT reserved space is faster.\n";
		}

		std::cout << "Duration of version without reserved space: " << duration << "\n";
		std::cout << "Duration of version with    reserved space: " << duration_reserved << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

	return EXIT_SUCCESS;
}

