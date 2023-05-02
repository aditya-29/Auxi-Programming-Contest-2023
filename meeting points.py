import math

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def equals(self, other):
        return self.x == other.x and self.y == other.y

def find_slope(p1, p2):
    if p1.x == p2.x:
        return math.inf
    return (p2.y - p1.y) / (p2.x - p1.x)

n = int(input())
lines = []

for i in range(n):
    x1, y1, x2, y2 = map(int, input().split())
    p1 = Point(x1,y1)
    p2 = Point(x2,y2)
    lines.append((p1,p2))
    
slopes = {}
for p1, p2 in lines:
    slope = find_slope(p1, p2)
    if slope in slopes:
        slopes[slope] += 1
    else:
        slopes[slope] = 1

count = 0
for slope, num_lines in slopes.items():
    count += num_lines * (n - num_lines)

print(count // 2)

