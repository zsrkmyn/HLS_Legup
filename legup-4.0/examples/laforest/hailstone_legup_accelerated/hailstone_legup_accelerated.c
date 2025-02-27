
// Transformed Hailstone variant, calculating every 8th sequence value via
// pre-computed table lookups. 

// See "Collatz Conjecture" Wikipedia page, specifically the parity sequence
// and acceleration sections if you care to know how the tables were generated.
// (and ask me for the Python code)

// Original formula for verification:
// if (seed & 1 == 1)
//     seed = ((3 * seed) + 1) / 2
// else
//     seed = seed / 2
//
// Also expressible as:
// if (seed & 1 == 1)
//     seed = (3 * seed) + 1
// seed = seed / 2

// The full 222 term sequence, starting with 77031, is:
// 77031, 115547, 173321, 259982, 129991, 194987, 292481, 438722, 219361, 329042,
// 164521, 246782, 123391, 185087, 277631, 416447, 624671, 937007, 1405511,
// 2108267, 3162401, 4743602, 2371801, 3557702, 1778851, 2668277, 4002416,
// 2001208, 1000604, 500302, 250151, 375227, 562841, 844262, 422131, 633197,
// 949796, 474898, 237449, 356174, 178087, 267131, 400697, 601046, 300523, 450785,
// 676178, 338089, 507134, 253567, 380351, 570527, 855791, 1283687, 1925531,
// 2888297, 4332446, 2166223, 3249335, 4874003, 7311005, 10966508, 5483254,
// 2741627, 4112441, 6168662, 3084331, 4626497, 6939746, 3469873, 5204810,
// 2602405, 3903608, 1951804, 975902, 487951, 731927, 1097891, 1646837, 2470256,
// 1235128, 617564, 308782, 154391, 231587, 347381, 521072, 260536, 130268, 65134,
// 32567, 48851, 73277, 109916, 54958, 27479, 41219, 61829, 92744, 46372, 23186,
// 11593, 17390, 8695, 13043, 19565, 29348, 14674, 7337, 11006, 5503, 8255, 12383,
// 18575, 27863, 41795, 62693, 94040, 47020, 23510, 11755, 17633, 26450, 13225,
// 19838, 9919, 14879, 22319, 33479, 50219, 75329, 112994, 56497, 84746, 42373,
// 63560, 31780, 15890, 7945, 11918, 5959, 8939, 13409, 20114, 10057, 15086, 7543,
// 11315, 16973, 25460, 12730, 6365, 9548, 4774, 2387, 3581, 5372, 2686, 1343,
// 2015, 3023, 4535, 6803, 10205, 15308, 7654, 3827, 5741, 8612, 4306, 2153, 3230,
// 1615, 2423, 3635, 5453, 8180, 4090, 2045, 3068, 1534, 767, 1151, 1727, 2591,
// 3887, 5831, 8747, 13121, 19682, 9841, 14762, 7381, 11072, 5536, 2768, 1384,
// 692, 346, 173, 260, 130, 65, 98, 49, 74, 37, 56, 28, 14, 7, 11, 17, 26, 13, 20,
// 10, 5, 8, 4, 2, 1

// Every 8th term, starting from the same seed:
// 77031 219361 624671 1778851 562841 178087 507134 4332446 4112441 3903608
// 1235128 130268 41219 13043 12383 11755 33479 31780 10057 9548 3023 8612 8180
// 2591 7381 260 28 10 

#include <stdio.h>

volatile unsigned int seed = 77031;

// Look-ahead table, indexed by low-order 8 bits of current seed.
volatile unsigned int lookahead [] = {0, 1, 2, 2, 1, 1, 1, 8, 2, 10, 2, 4, 2,
2, 5, 5, 1, 2, 20, 20, 1, 1, 8, 8, 1, 26, 1, 242, 10, 10, 10, 91, 2, 11, 4, 4,
13, 13, 13, 38, 2, 121, 2, 14, 5, 5, 5, 137, 2, 17, 17, 17, 2, 2, 161, 161, 20,
56, 20, 19, 20, 20, 182, 182, 1, 7, 22, 22, 8, 8, 8, 206, 26, 71, 26, 8, 26,
26, 76, 76, 1, 80, 242, 242, 1, 1, 28, 28, 10, 29, 10, 263, 10, 10, 91, 91, 4,
94, 11, 11, 11, 11, 11, 890, 4, 101, 4, 103, 107, 107, 107, 319, 13, 4, 37, 37,
13, 13, 38, 38, 40, 350, 40, 118, 121, 121, 364, 1093, 2, 125, 14, 14, 44, 44,
44, 43, 5, 395, 5, 134, 5, 5, 137, 137, 17, 47, 47, 47, 17, 17, 16, 16, 17, 49,
17, 445, 152, 152, 152, 1367, 2, 155, 53, 53, 161, 161, 161, 479, 2, 1457, 2,
164, 56, 56, 56, 167, 20, 19, 19, 19, 20, 20, 175, 175, 20, 59, 20, 179, 182,
182, 182, 1640, 8, 62, 188, 188, 7, 7, 7, 190, 22, 64, 22, 65, 22, 22, 593,
593, 8, 67, 202, 202, 8, 8, 206, 206, 71, 23, 71, 209, 71, 71, 638, 638, 26,
647, 8, 8, 74, 74, 74, 661, 26, 668, 26, 674, 76, 76, 76, 2051, 80, 26, 233,
233, 80, 80, 236, 236, 242, 238, 242, 719, 728, 728, 2186, 6560};

// Number of odd numbers (cubed) found while calculating lookahead table.
// Indexed by low-order 8 bits of current seed.
volatile unsigned int odd_count_cubed [] = {1, 81, 81, 81, 27, 27, 27, 243, 27,
243, 27, 81, 27, 27, 81, 81, 9, 27, 243, 243, 9, 9, 81, 81, 9, 243, 9, 2187,
81, 81, 81, 729, 9, 81, 27, 27, 81, 81, 81, 243, 9, 729, 9, 81, 27, 27, 27,
729, 9, 81, 81, 81, 9, 9, 729, 729, 81, 243, 81, 81, 81, 81, 729, 729, 3, 27,
81, 81, 27, 27, 27, 729, 81, 243, 81, 27, 81, 81, 243, 243, 3, 243, 729, 729,
3, 3, 81, 81, 27, 81, 27, 729, 27, 27, 243, 243, 9, 243, 27, 27, 27, 27, 27,
2187, 9, 243, 9, 243, 243, 243, 243, 729, 27, 9, 81, 81, 27, 27, 81, 81, 81,
729, 81, 243, 243, 243, 729, 2187, 3, 243, 27, 27, 81, 81, 81, 81, 9, 729, 9,
243, 9, 9, 243, 243, 27, 81, 81, 81, 27, 27, 27, 27, 27, 81, 27, 729, 243, 243,
243, 2187, 3, 243, 81, 81, 243, 243, 243, 729, 3, 2187, 3, 243, 81, 81, 81,
243, 27, 27, 27, 27, 27, 27, 243, 243, 27, 81, 27, 243, 243, 243, 243, 2187, 9,
81, 243, 243, 9, 9, 9, 243, 27, 81, 27, 81, 27, 27, 729, 729, 9, 81, 243, 243,
9, 9, 243, 243, 81, 27, 81, 243, 81, 81, 729, 729, 27, 729, 9, 9, 81, 81, 81,
729, 27, 729, 27, 729, 81, 81, 81, 2187, 81, 27, 243, 243, 81, 81, 243, 243,
243, 243, 243, 729, 729, 729, 2187, 6561};

unsigned int hailstone_every_8th (volatile unsigned int seed) {
    unsigned int lower = seed &  0xFF;
    unsigned int upper = seed >> 8;
    unsigned int new_seed = (upper * odd_count_cubed[lower]) + lookahead[lower];
    return new_seed;
}

// #define DEBUG

int main () {
    loop : for (int i = 0; i < 28; i++) {
        #ifdef DEBUG
        printf("%u ", seed);
        printf("\n");
        #endif
        seed = hailstone_every_8th(seed);
    }
    return seed;
}

