#include "my03.h"

#include "tigr.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    my03_t m = {.steps = 16};
    Tigr* screen = tigrWindow(800, 600, "Hello", 0
        //| TIGR_FULLSCREEN
        | TIGR_AUTO
    );
    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        if (tigrKeyDown(screen, 'A')) { m.bank = 0; }
        if (tigrKeyDown(screen, 'B')) { m.bank = 1; }
        if (tigrKeyDown(screen, 'C')) { m.bank = 2; }
        if (tigrKeyDown(screen, 'D')) { m.bank = 3; }
        if (tigrKeyDown(screen, '1')) { m.pattern = 0; }
        if (tigrKeyDown(screen, '2')) { m.pattern = 1; }
        if (tigrKeyDown(screen, '3')) { m.pattern = 2; }
        if (tigrKeyDown(screen, '4')) { m.pattern = 3; }
        if (tigrKeyDown(screen, '5')) { m.pattern = 4; }
        if (tigrKeyDown(screen, '6')) { m.pattern = 5; }
        if (tigrKeyDown(screen, '7')) { m.pattern = 6; }
        if (tigrKeyDown(screen, '8')) { m.pattern = 7; }
        if (tigrKeyDown(screen, TK_PADADD)) {
            if (m.step < m.steps - 1) {
                m.step++;
            }
        }
        if (tigrKeyDown(screen, TK_PADSUB)) {
            if (m.step > 0) {
                m.step--;
            }
        }
        if (tigrKeyDown(screen, TK_PADMUL)) {
            m.banks[m.bank].patterns[m.pattern].steps[m.step].on_off =
                1 - m.banks[m.bank].patterns[m.pattern].steps[m.step].on_off;
        }
        tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
        int x = 0, y = 0;
        char buf[256];
        snprintf(buf, sizeof(buf), "tempo=%d steps=%d saw_squ=%d", m.tempo, m.steps, m.saw_squ);
        tigrPrint(screen, tfont, x, y, tigrRGB(0xff, 0xff, 0xff), buf);
        y += tigrTextHeight(tfont, buf);
        snprintf(buf, sizeof(buf), "tune=%d c.off=%d res=%d env=%d dec=%d acc=%d", m.tune, m.cutoff, m.reso, m.envmod, m.decay, m.accent);
        tigrPrint(screen, tfont, x, y, tigrRGB(0xff, 0xff, 0xff), buf);
        y += tigrTextHeight(tfont, buf);
        for (int b = 0; b < sizeof(m.banks) / sizeof(m.banks[0]); b++) {
            for (int p = 0; p < sizeof(m.banks[b].patterns) / sizeof(m.banks[b].patterns[0]); p++) {
                x = 0;
                snprintf(buf, sizeof(buf), "%s%d%s%d",
                    b == m.bank ? "B" : "b",
                    b,
                    b == m.bank && p == m.pattern ? "P" : "p", p);
                tigrPrint(screen, tfont, x, y, tigrRGB(0xff, 0xff, 0xff), buf);
                x += tigrTextWidth(tfont, buf);
                for (int s = 0; s < sizeof(m.banks[b].patterns[p].steps) / sizeof(m.banks[b].patterns[p].steps[0]); s++) {
                    snprintf(buf, sizeof(buf), "%s%s%do%d%s%s",
                        b == m.bank && p == m.pattern && s == m.step ? "=" : "-",
                        m.banks[b].patterns[p].steps[s].on_off ? "N" : "n",
                        m.banks[b].patterns[p].steps[s].note,
                        m.banks[b].patterns[p].steps[s].octave,
                        m.banks[b].patterns[p].steps[s].accent ? "A" : "a",
                        m.banks[b].patterns[p].steps[s].slide ? "S" : "s"
                    );
                    tigrPrint(screen, tfont, x, y, tigrRGB(0xff, 0xff, 0xff), buf);
                    x += tigrTextWidth(tfont, buf);
                }
                y += tigrTextHeight(tfont, "H");
            }
        }
        x = 0;
        snprintf(buf, sizeof(buf), "bank=%d pattern=%d step=%d", m.bank, m.pattern, m.step);
        tigrPrint(screen, tfont, x, y, tigrRGB(0xff, 0xff, 0xff), buf);
        y += tigrTextHeight(tfont, buf);
        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;
}
