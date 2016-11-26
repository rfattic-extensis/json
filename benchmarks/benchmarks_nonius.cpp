#define NONIUS_RUNNER
#include <nonius.h++>
#include <json.hpp>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

void parse_test(const std::string& filename, nonius::chronometer& meter)
{
    // read file into string stream
    std::stringstream istr;
	{
    	std::ifstream input_file(filename);
    	istr << input_file.rdbuf();
    	input_file.close();
	}

	// the actual benchmark
    meter.measure([&](int i) {
        // clear flags and rewind
        istr.clear();
        istr.seekg(0);
		// parse input
        json j;
        j << istr;
	});
}

NONIUS_BENCHMARK("parse jeopardy.json", [](nonius::chronometer meter) {
	parse_test("benchmarks/files/jeopardy/jeopardy.json", meter);
});
