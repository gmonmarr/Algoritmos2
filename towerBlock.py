def ascendTower(userList) -> int:
    ascendingMoves = 0
    for i in range(len(userList) - 1):
        while userList[i] >= userList[i + 1]:
            userList[i + 1] += 1
            ascendingMoves += 1

    return ascendingMoves

def descendTower(userList) -> int:
    descendingMoves = 0
    for i in range(len(userList) - 1):
        while userList[i] <= userList[i + 1]:
            userList[i + 1] -= 1
            descendingMoves += 1

    return descendingMoves

def checkList(userList) -> bool:
    for i in range(len(userList) - 1):
        if userList[i] == (userList[i + 1] + 1):
            return True
        else:
            break
    
    for i in range(len(userList) - 1):
        if userList[i] == (userList[i + 1] - 1):
            return True
        else:
            break
    
    return False

def towerBlock (userList) -> int:
    ascendingMoves = 0
    descendingMoves = 0

    difference = userList[0] - userList[len(userList) - 1]

    if checkList(userList): 
        return 0
    
    ascendingMoves = ascendTower(userList)
    descendingMoves = descendTower(userList)

    return min(ascendingMoves, descendingMoves)

# Test cases
print(towerBlock([1, 2, 3, 4, 5]))
print(towerBlock([1, 5, 6, 7, 11]))
print(towerBlock([5, 7, 9, 4, 11]))
print(towerBlock([11,3,5,6,7,15]))