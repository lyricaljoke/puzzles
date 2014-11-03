#include <iostream>
#include <cstdint>

int main( int argc, char** argv)
{
    // FIXME make configurable with args
    const int dimension = 1001;

    int64_t sum = 1;
    int currValue = 1;
    for (int currDimension = 3; currDimension <= dimension; currDimension += 2)
    {
        int increment = currDimension - 1;
        for (int i = 0; i < 4; ++i)
        {
            currValue += increment;
            if (currValue < 50)
            {
                std::cout << "currValue: " << currValue << std::endl;
            }
            sum += currValue;
        }
    }

    std::cout << "Sum after " << dimension << " rows: " << sum << std::endl;
    return 0;
}

