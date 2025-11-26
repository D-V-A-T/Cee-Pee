t = int(input())
for _ in range(t):
    n = int(input())
    ans = 0
    i = 0
    while n >= i*2:
        rem = n - i*2
        if(rem % 4 == 0) :
            ans += 1
        i += 1
    print(ans)
