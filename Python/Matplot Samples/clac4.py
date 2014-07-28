from math import *
L1=5
L2=5
def s(U):
    return U*U
for x in range(1,11):
  for y in range(1,11):
    X=x
    Y=y
    Z=hypot(X,Y)
    M1=(s(Z)+s(L1)-s(L2))/(2*Z*L1)
    M2=(s(Z)+s(L2)-s(L1))/(2*Z*L2)
    try:
            A1=acos(M1)
            B1=acos(M2)
    except:
            continue
    A=asin(Y/Z)-A1
    B=acos(X/Z)+B1
    print degrees(A),degrees(B)
    #print L1*cos(A)+L2*cos(B),L1*sin(A)+L2*sin(B)
