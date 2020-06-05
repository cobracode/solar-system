#ifndef MATINNIA_MISCDEFINITIONS_H
#define MATINNIA_MISCDEFINITIONS_H

namespace Matinnia {

// Data Types

enum IS_VALID {
    VALID = 0,
    INVALID
};

enum OUTCOME {
    SUCCESS = 0,
    FAILURE
};

#define C(TYPE, VALUE) static_cast<TYPE >(VALUE)

}   // namespace Matinnia

#endif //   MATINNIA_MISCDEFINITIONS_H