////////////////////////////////
////////////////////
//////////


#include <iostream>
#include <format>
#include <chrono>
#include <functional>

int to_seconds(std::chrono::nanoseconds nanos) {
	return nanos.count() / 1'000'000'000LL;
}

int to_millis(std::chrono::nanoseconds nanos) {
	return nanos.count() / 1'000'000;
}

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

int main() {

	auto timed_fib = timer(fibonacci);

	timed_fib(500);
}