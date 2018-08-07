#include <cstring>
#include <type_traits>
#include <sstream>
#include <stdexcept>

template <typename DST, typename SRC>
inline DST memcpy(const SRC* source)
{
	// NOTE: is_trivially_copyable<T> should be used but gcc does not yet support it
	// https://gcc.gnu.org/onlinedocs/gcc-4.8.3/libstdc++/manual/manual/status.html#status.iso.2011
    static_assert(is_pod<DST>::value, "return must trivially copyable");
    DST dest;
    memcpy(&dest, source, sizeof(dest));
    return dest;
}

// Similar to bit_cast
// https://gist.github.com/socantre/3472964
template <typename DST, typename SRC>
inline DST memcpy(const SRC& source)
{
	static_assert(sizeof(DST)==sizeof(SRC), "size of DST and SRC must be equal");
    static_assert(is_pod<SRC>::value, "SRC must trivially copyable");
    static_assert(is_pod<DST>::value, "DST must trivially copyable");
    DST dest;
    memcpy(&dest, &source, sizeof(dest));
    return dest;
}

/**
 * You better know what your doing if you use this!
 */
template<typename T>
const T* rval_addr(const T& in)
{
	return &in;
}

/**
 * Examples:
 * from_string<int>(my_int, my_string, std::dec);
 *
 * to_string(my_string);
 */
template <typename T>
inline std::string to_string(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

template <typename T>
inline bool from_string(T& t,
		const std::string& s,
		bool throw_exception=false,
		std::ios_base& (*f)(std::ios_base&)=std::dec)
{
	std::istringstream iss(s);
	auto failed = (iss >> f >> t).fail();
	if (failed && throw_exception)
		throw std::runtime_error("from_string(): Could not parse string.");

	return failed;
}
