#ifndef MY03_H__
#define MY03_H__

typedef struct my03 {
    int tempo;      // BPM 20-500 {140}
    int steps;      // 1-16 {16}
    int saw_squ;    // 1-0 {1}
    int tune, cutoff, reso, envmod, decay, accent;  // 0-100 {0}
    struct {
        struct {
            struct {
                int note;   // 0-12 {0}
                int on_off; // 0-1 {0}
                int octave; // 0-2 {1}
                int accent; // 0-1 {0}
                int slide;  // 0-1 {0}
            } steps[16];
        } patterns[8];
    } banks[4];
    int bank;       // 0-3 {0}
    int pattern;    // 0-7 {0}
    int step;       // 0-15 {0}
} my03_t;

#endif/*MY03_H__*/
