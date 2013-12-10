#include "motorhelp.h"

/* Scale values propotionally so no value is over 1 */
void MotorRescale(MotorState *s) {
    float *vals = (float*)s;
    int i;
    int max_ndx = 0;
    for(i = 1;i < 4;++i) {
        if(vals[i] > vals[max_ndx])
            max_ndx = i;
    }

    if(vals[max_ndx] > 1) {
        // Rescale
        float scale = 1 / vals[max_ndx];
        for(i = 0;i < 4;++i)
            vals[i] *= scale;
    }
}

