import sys
input = sys.stdin.readline
trace = lambda *a,**kw: None;separator = lambda : None
def __separator():
    global _t
    print('----------------------',_t+1,'----------------------',
          file=sys.stderr,sep='')
def __trace(*args,**kwargs):
    print(*args,sep=', ',end=' |#| ',file=sys.stderr)
    for name,val in kwargs.items():
        print(name,'=',val,end=' | ',file=sys.stderr)
    print(file=sys.stderr)
if sys.platform == 'linux':
    trace = __trace;separator = __separator
getInts = lambda : map(int,input().split()) 


def test():
    return None

for _t in range(int(input())):
    separator()
    print(test())
