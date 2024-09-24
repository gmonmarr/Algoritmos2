def min_blocks_to_stair_step(heights):
    n = len(heights)
    
    # Initialize arrays to store minimum blocks for increasing and decreasing patterns
    dp_increasing = [0] * n
    dp_decreasing = [0] * n
    
    # Base case: No blocks needed for the first tower in both cases
    dp_increasing[0] = 0
    dp_decreasing[0] = 0
    
    # Calculate the dp arrays
    for i in range(1, n):
        # For increasing pattern, tower i must be exactly height of tower (i-1) + 1
        expected_increase = heights[i - 1] + 1
        if heights[i] >= expected_increase:
            dp_increasing[i] = dp_increasing[i - 1]
        else:
            dp_increasing[i] = dp_increasing[i - 1] + (expected_increase - heights[i])
        
        # For decreasing pattern, tower i must be exactly height of tower (i-1) - 1
        expected_decrease = heights[i - 1] - 1
        if heights[i] >= expected_decrease:
            dp_decreasing[i] = dp_decreasing[i - 1]
        else:
            dp_decreasing[i] = dp_decreasing[i - 1] + (expected_decrease - heights[i])
    
    # The answer is the minimum of the last values in both dp arrays
    return min(dp_increasing[-1], dp_decreasing[-1])

# Test cases
test_cases = [
    [1, 2, 3, 4, 5],      # Already increasing
    [1, 5, 6, 7, 11],     # Needs adjustments for increasing
    [5, 7, 9, 4, 11],     # Mixed, requires adjustments
    [11, 3, 5, 6, 7, 15]  # Mixed increasing and decreasing
]

# Execute the test cases with detailed output
for heights in test_cases:
    result = min_blocks_to_stair_step(heights)
    print(f"Array: {heights} => Minimum blocks to stair-step: {result}")
