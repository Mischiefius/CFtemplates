import sys
input = sys.stdin.readline
trace = lambda *a,**kw: None;separator = lambda : None
end = lambda : None
dash = '-'*16
def __end():
    print(dash,'R',dash*2,'R',dash,file=sys.stderr)
def __separator():
    global _t
    print(dash,_t+1,dash,_t+1,dash,
          file=sys.stderr,sep='')
def __trace(*args,**kwargs):
    print(*args,sep=', ',end=' |#| ',file=sys.stderr)
    for name,val in kwargs.items():
        print(name,'=',val,end=' | \n',file=sys.stderr)
if sys.platform == 'linux':
    trace = __trace;separator = __separator
    end = __end
getInts = lambda : map(int,input().split()) 


def test():
    return None

for _t in range(int(input())):
    separator()
    print(test())
end()
