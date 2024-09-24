def MaxSubarray(A):
    safeSum = float('-inf')
    leftIndex = 0
    rightIndex = 0

    expSum = 0
    expLeftIndex = 0

    for i in range(len(A)):
        expSum += A[i]

        if expSum > safeSum:
            safeSum = expSum
            leftIndex = expLeftIndex
            rightIndex = i

        if expSum < 0:
            expSum = 0
            expLeftIndex = i + 1

    return A[leftIndex:rightIndex]

# Test cases
print(MaxSubarray([1, 2, 3, 4, 5]))
print(MaxSubarray([-1, -2, -3, -4, -5]))
print(MaxSubarray([1, -2, 3, -4, 5]))
print(MaxSubarray([1, -2, 3, -4, 5, 6]))
print(MaxSubarray([1, -2, 3, -4, 5, 6, -7]))
print(MaxSubarray([1, -2, 3, -4, 5, 6, -7, 8]))
print(MaxSubarray([1, -2, 3, -4, 5, 6, -7, 8, -9]))
print(MaxSubarray([1, -2, 3, -4, 5, 6, -7, 8, -9, 10]))
print(MaxSubarray([1, -2, 3, -4, 5, 6, -7, 8, -9, 10, -11]))
print(MaxSubarray([1, -2, 3, -4, 5, 6, -7, 8, -9, 10, -11, 12]))
print(MaxSubarray([1, -2, 3, -4, 5, 6, -7, 8, -9, 10, -11, 12, -13]))
print(MaxSubarray([1, -2, 3, -4, 5, 6, -7, 8, -9, 10, -11, 12, -13, 14]))
print(MaxSubarray([1, -2, 3, -4, 5, 6, -7, 8, -9, 10, -11, 12, -13, 14, -15]))