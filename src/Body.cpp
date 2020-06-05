// Own header
#include "Body.h"

namespace Matinnia {

void Body::deepCopy(const Matinnia::Body &RHS) {
    // Prevent copying yourself
    if (&RHS != this) {
        geocentricData    = RHS.geocentricData;
        name              = RHS.name;
        index             = RHS.index;
    }
}

}   // namespace Matinnia