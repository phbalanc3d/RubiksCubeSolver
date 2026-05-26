import os

files = [
    'patternDatabase/CornerDB.h',
    'patternDatabase/nibbleArray.h',
    'patternDatabase/patternDatabase.h',
    'patternDatabase/PermutationIndexer.h',
    'scanner/main.cpp',
    'solvers/bfsolver.h',
    'solvers/dfssolver.h',
    'solvers/idastarsolver.h',
    'solvers/iddfs.h',
]

replacement = """#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>
#include <climits>
#include <functional>
#include <numeric>"""

base = r'C:\Users\hp\OneDrive\Desktop\sem4\proj\cube'

for f in files:
    path = os.path.join(base, f)
    with open(path, 'r') as file:
        content = file.read()
    new_content = content.replace('#include <bits/stdc++.h>', replacement)
    with open(path, 'w') as file:
        file.write(new_content)
    print('Fixed: ' + f)

print('All done!')