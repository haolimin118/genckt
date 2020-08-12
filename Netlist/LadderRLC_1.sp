*scale (1), circuit type (ladderrlc)

RLC ladder --scale=1
VIN 1 0 1
C0 1 0 1p
R1 1 2 100
L1 2 3 1m
C1 3 0 1p

.OP
.PRINT V(3)
.ends
