*scale(1)	circuit type(Coupled RC tree)

VIN0 10 0 0
VIN1 11 0 1
R10 10 20 100
C10 20 0 1p
R11 11 21 100
C11 21 0 1p
C1C 20 21 1p

.OP
.PRINT V(20) V(21)
.ENDS
