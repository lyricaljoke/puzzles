#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <cstdint>

/**
 * Euler problem 43.  Solves it by creating the entire set of permutations of
 * the ten base-10 digits, then cycles through the list of candidates once per
 * set of three digits to check.  In retrospect, rather than a "build the whole
 * set and then reduce it" approach, it might have been more efficient to build
 * just the first three digits such that the divisor criterion is fulfilled,
 * add all possible values for the next digit for each of those candidates, and
 * so on.
 */
int main(int argc, char** argv)
{
    // Ignore these for now.  Maybe later we'll add command line opts.
    (void)argc;
    (void)argv;

    // Set up our divisors.  We include the trivial case of '1' so that it
    // doesn't become a special case and we can more easily zero-index.
    std::array<uint64_t, 8> divisors = {1, 2, 3, 5, 7, 11, 13, 17};

    // populate the candidates
    std::array<uint64_t, 10> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::sort(digits.begin(), digits.end());
    auto candidates = std::vector<uint64_t>(); // 10 factorial
    candidates.reserve(3628800);

    do
    {
        uint64_t candidate = 0;
        uint64_t significance = 1;
        for (auto digit : digits)
        {
            candidate += significance * digit;
            significance *= 10;
        }
        candidates.push_back(candidate);
    } while (std::next_permutation(digits.begin(), digits.end()));

    // This should be 10 factorial.
    std::cout << "Added " << candidates.size() << " candidates.\n";

    const std::array<uint64_t, 11> pow_of_ten = {1, 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000, 1000000000, 10000000000};
    // Pseudo-code:
    // For starting digits 0 through 7
    std::array<uint16_t, 8> digit_indices = {0, 1, 2, 3, 4, 5, 6, 7};
    for (auto digit : digit_indices)
    {   
        auto intermediates = candidates;     
        // Compute the three digit number of the frame:
        for (auto& intermediate : intermediates)
        {
            // Take modulo with (10^(10 - digit index))
            intermediate = intermediate % pow_of_ten[10 - digit];
            // Truncate divide by (10^(10 - digit index - 3))
            intermediate /= pow_of_ten[10 - digit - 3];
        }
        // Check if divisible by divisors[digit index] and remove if not

        for (size_t idx = 0; idx < intermediates.size(); ++idx)
        {
            if (intermediates[idx] % divisors[digit] != 0)
            {
                // If the intermediate result is not divisible by the divisor,
                // then the candidate fails.  Set it to zero.
                candidates[idx] = 0;
            }
        }

        // Remove all the candidates that became zero.
        candidates.erase(std::remove(candidates.begin(), candidates.end(), 0),
            candidates.end());

        // Resize candidates to fit
        candidates.shrink_to_fit();
    }

    // Sum up the candidates which fulfilled all of the division criteria.
    uint64_t sum = 0;
    for (auto& candidate : candidates)
    {
        sum += candidate;
    }

    // Display the result.
    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
