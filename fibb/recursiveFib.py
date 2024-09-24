def fibRecursive(n):
    if n<= 2:
        f = 1
    else:
        f = fibRecursive(n-1) + fibRecursive(n-2)
    return f

def fibBottomUp(n):
    fibSeq = [0, 1]
    for i in range(2, n+1):
        fibSeq.append(fibSeq[i-1] + fibSeq[i-2])
    return fibSeq[n]

def fibTopDown(n, memo):
    if memo[n] > -1:
        return memo[n]
    if n <= 2:
        f = 1
    else:
        f = fibTopDown(n-1, memo) + fibTopDown(n-2, memo)
    memo[n] = f
    return f

memo = [-1] * 101

print(fibRecursive(10))
print(fibBottomUp(100))
print(fibTopDown(100, memo))