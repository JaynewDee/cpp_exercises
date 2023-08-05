////////////////////////////////
////////////////////
//////////


#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <chrono>
#include <functional>

using namespace std;

int to_seconds(std::chrono::nanoseconds nanos) {
	return nanos.count() / 1'000'000'000LL;
}

int to_millis(std::chrono::nanoseconds nanos) {
	return nanos.count() / 1'000'000;
}

// in angle brackets goes the `template argument list`
//   that is, any generics 
template <typename Func>
auto timer(Func func) {
	return [func](auto&&... args) {
		auto start = std::chrono::high_resolution_clock::now();

		auto result = func(std::forward<decltype(args)>(args)...);

		auto elapsed = std::chrono::high_resolution_clock::now() - start;

		std::cout << "Elapsed nanoseconds: " << elapsed << "\n";

		std::cout << "Elapsed milliseconds: " << to_millis(elapsed) << "\n";

		std::cout << "Elapsed seconds: " << to_seconds(elapsed) << "\n";

		return result;
	};
};

int fibonacci(int count) {
	double first = 0;
	double second = 1;

	for (int i = 2; i < count; ++i) {
		double next = first + second;

		first = second;
		second = next;

	}

	std::cout << "Total: " << second << "\n";

	return second;
}

void write_file(const char* filepath, const char* content) {
	std::cout << "Writing file to " << filepath << "\n";

	std::ofstream ofile(filepath);

	ofile << content << "\n";

	ofile.close();
}

string read_file(const char* filepath) {
	static char buf[128];

	std::ifstream infile(filepath);

	string content((istreambuf_iterator<char>(infile)),
		(istreambuf_iterator<char>()));

	infile.close();

	return content;
}


int main() {

	auto timed_fib = timer(fibonacci);

	timed_fib(500);

	const char* file_path = { "test_out.txt" };
	const char* write_content = { "This is the test text content!" };

	write_file(file_path, write_content);

	string read_contents = read_file(file_path);

	std::cout << "Read file contents:\n" << "::: " << read_contents;
}