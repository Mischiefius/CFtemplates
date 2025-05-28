##----------------------hash----------------------## 18
import random
fr = random.randrange(2**63)
def hash(x):
    # x ^= fr # reintroduce when using outside wrap 
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9
    x &= 0xFFFFFFFFFFFFFFFF 
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb
    x &= 0xFFFFFFFFFFFFFFFF
    x = x ^ (x >> 31)
    x &= 0xFFFFFFFFFFFFFFFF
    return x

def wrap(cls):
    class inner(cls):
        def __hash__(self):
            return super().__hash__()^fr 
    return inner        
# t = wrap(int)

#----@cache----
def cache(func):
    vals = {}
    def wrapper(x):
        if w:=vals.get(x,None):
            return w
        else:
            w = func(x)
            if vals.__len__() < 1000:
                vals[x] = w
            return w
    return wrapper

 
