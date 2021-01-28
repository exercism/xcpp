#if !defined(LEVENSHTEIN_DISTANCE)
#define LEVENSHTEIN_DISTANCE

#include <string>

namespace levenshtein {

	int distance(const std::string& source, const std::string& target);

}

#endif // LEVENSHTEIN_DISTANCE
