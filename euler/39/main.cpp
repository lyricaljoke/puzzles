#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

float hypotenuse(int a, int b)
{
    using namespace std;
    return sqrt(pow(a, 2) + pow(b, 2));
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    const int max_perimeter = 1000;
    // Array of solution count.  Array index corresponds to n.
    auto solution_count = std::vector<int>(max_perimeter + 1);
    for (int side_a = 1; side_a < max_perimeter; ++side_a)
    {
        for (int side_b = 1; side_b < max_perimeter; ++side_b)
        {
            // first check if it's a right triangle
            float hyp = hypotenuse(side_a, side_b);
            if (std::floor(hyp) == hyp)
            {
                std::cout << "Found right triangle: " << side_a << ", " <<
                    side_b << ", " << hyp << std::endl;
            }
            else
            {
                continue;
            }

            int perimeter = side_a + side_b + hyp;
            // then check if the perimeter's too large
            if (perimeter > max_perimeter)
            {
                // b's too large.
                break;
            }

            solution_count[perimeter] = solution_count[perimeter] + 1;
        }
    }

    auto result = std::max_element(solution_count.begin(),
                                   solution_count.end());
    std::cout << "Max num solutions is " << *result << " at "
        << std::distance(solution_count.begin(), result) << std::endl;
    return 0;
}
