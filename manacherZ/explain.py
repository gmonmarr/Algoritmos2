def preprocess_string(s):
    """Preprocess the string to insert '#' between characters for uniform handling."""
    return '#' + '#'.join(s) + '#'

def manacher_algorithm(s):
    preprocessed_s = preprocess_string(s)
    n = len(preprocessed_s)
    
    mirror_length = [0] * n
    center = 0
    right_boundary = 0
    longest_palindrome = (0, 0)  # (start index in original string, length)
    
    print(f"Preprocessed string: {preprocessed_s}")
    
    for i in range(n):
        mirror_i = 2 * center - i  # Mirror index of i around the current center
        
        print(f"\n--- Iteration {i} ---")
        print(f"Cursor (i): {i}")
        print(f"Value at cursor: {preprocessed_s[i]}")
        print(f"Center: {center}")
        print(f"RightBoundary: {right_boundary}")
        print(f"MirrorPointer (mirror_i): {mirror_i}")
        
        if i < right_boundary:
            mirror_length[i] = min(right_boundary - i, mirror_length[mirror_i])
            print(f"Using mirror value: {mirror_length[i]} at {mirror_i}")
        
        # Try to expand the palindrome centered at i
        while (i + mirror_length[i] + 1 < n) and (i - mirror_length[i] - 1 >= 0) and \
              preprocessed_s[i + mirror_length[i] + 1] == preprocessed_s[i - mirror_length[i] - 1]:
            mirror_length[i] += 1
            print(f"Expanding around center {i}: {mirror_length[i]}")
            print(f"Left: {i - mirror_length[i]}, Right: {i + mirror_length[i]}")
            print(f"Left value: {preprocessed_s[i - mirror_length[i]]}, Right value: {preprocessed_s[i + mirror_length[i]]}")

        print(f"MirrorLength[{i}]: {mirror_length[i]}")
        
        # Update the right boundary if the expanded palindrome goes beyond it
        if i + mirror_length[i] > right_boundary:
            center = i
            right_boundary = i + mirror_length[i]
            print(f"Updated Center: {center}, RightBoundary: {right_boundary}")
        
        # Keep track of the longest palindrome
        if mirror_length[i] > longest_palindrome[1]:
            longest_palindrome = (i, mirror_length[i])
            print(f"Longest palindrome updated at center {i} with length {mirror_length[i]}")
    
    # Find the start and length of the longest palindrome in the original string
    start = (longest_palindrome[0] - longest_palindrome[1]) // 2
    length = longest_palindrome[1]
    
    print(f"\nFinal longest palindrome in original string: {s[start:start + length]}")
    return s[start:start + length]

# Test the algorithm
input_string = "ababba"
longest_palindrome = manacher_algorithm(input_string)
print("Longest Palindrome Substring:", longest_palindrome)
