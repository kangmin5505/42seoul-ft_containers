#include "../system/system_methods.ipp"
#include UTILITIES

bool is_integral_test_() {
	std::vector<int> v;
	bool res = 1;
	g_start2 = timer(); g_end2 = timer(); g_start1 = timer(); g_end1 = timer();
	(_is_integral<float>::value == std::is_integral<float>()) ? 0 : res = 0;
	(_is_integral<int>::value == std::is_integral<int>()) ? 0 : res = 0;
	(_is_integral<bool>::value == std::is_integral<bool>()) ? 0 : res = 0;
	(_is_integral<char>::value == std::is_integral<char>()) ? 0 : res = 0;
	(_is_integral<signed char>::value == std::is_integral<signed char>()) ? 0 : res = 0;
	(_is_integral<unsigned char>::value == std::is_integral<unsigned char>()) ? 0 : res = 0;
	(_is_integral<wchar_t>::value == std::is_integral<wchar_t>()) ? 0 : res = 0;
	(_is_integral<char16_t>::value == std::is_integral<char16_t>()) ? 0 : res = 0;
	(_is_integral<short>::value == std::is_integral<short>()) ? 0 : res = 0;
	(_is_integral<unsigned short>::value == std::is_integral<unsigned short>()) ? 0 : res = 0;
	(_is_integral<unsigned int>::value == std::is_integral<unsigned int>()) ? 0 : res = 0;
	(_is_integral<long>::value == std::is_integral<long>()) ? 0 : res = 0;
	(_is_integral<unsigned long>::value == std::is_integral<unsigned long>()) ? 0 : res = 0;
	(_is_integral<long long>::value == std::is_integral<long long>()) ? 0 : res = 0;
	(_is_integral<unsigned long long>::value == std::is_integral<unsigned long long>()) ? 0 : res = 0;
	return res;
}

int main() {
	exit(run_bool_unit_test("is_integral", is_integral_test_));
}
