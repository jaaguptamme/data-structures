import sys
input = sys.stdin.read#Use ctrl+d to end
sys.set_int_max_str_digits(0)
import decimal
with decimal.localcontext() as ctx:
    ctx.prec = decimal.MAX_PREC
    ctx.Emax = decimal.MAX_EMAX
    ctx.Emin = decimal.MIN_EMIN
    ctx.traps[decimal.Inexact] = 1
    inp=[decimal.Decimal(_) for _ in input().split()]
    ps=1
    for _ in range(int(inp[0])):
        a=inp[ps]
        b=inp[ps+1]
        ps+=2
        div=a//b
        mod=a-b*div
        print(div,mod)
