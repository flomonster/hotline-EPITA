import numpy as np
from io import StringIO
from pprint import pprint


strmap = (
    '   ---   ----',
    '   ---   ----',
    '-------------',
    '-------------',
    '------   ----',
)

def mapize(m):
    return [[v != ' ' for v in s] for s in m]


def main(m, h, w):
    def fill_rect(x, y):
        lh, lw = 1, 0
        for i in range(x, w):
            if m[y][i]:
                lw += 1
                m[y][i] = False
            else:
                break

        while all(m[y + lh][i] for i in range(x, x + lw)):
            for i in range(x, x + lw):
                m[y + lh][i] = False
            lh += 1
            if y + lh >= h:
                break

        return lw, lh


    res = []
    for y in range(h):
        for x in range(w):
            if m[y][x]:
                res.append(((x, y), fill_rect(x, y)))

    return res

dmap = mapize(strmap)

height = len(dmap)
width = len(dmap[0])


pprint(main(dmap, height, width))
