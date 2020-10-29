lines = [
    "\tif i == 128 { print(\"Hello, World!\"); i += cast(int, 472.047/34.17) + cast(int, true) % 5 }\n",
    "\twhile 'a <= c && c <= 'z || 'A <= c && c <= 'Z { current++ column_number++  i += cast(int, 472.047/34.17) + cast(int, true) % 5 }\n",
    "\tif c_or_f == 'C { result = celsius_to_fahrenheit(temp) result_type = 'F } else if c_or_f == 'F { result = fahrenheit_to_celsius(temp) result_type = 'C test := '\\n } else { print(\"Input is not 'C' or 'F'. Unable to convert!\") return 1; }",
    "\tif p_result <= snake_head_probability |grid, i, j| { grid[i][j] = i << 2 + j + 1; } else if p_result <= snake_head_probability + ladder_start_probability { }",
    "\tusing b c :: 12 d :: 15 SparseSet : struct { capacity : u32 = ---; max_val : s32 = ---; n : s32; sparse : s32[] = ---; /*indexes*/ dense  : s32[] = ---; /*Data*/}",
    "\tsearchSparseSet : (using set: ^SparseSet, x: s32) { if x > max_val { return -1; } if sparse[x] < n && dense[sparse[x]] == x { return (sparse[x]); } return -1; }"
]

import random

with open("test_2_4M_lines.rw", "w") as file:
    file.write("main: () -> () {\n\ti :: 15")
    for _ in range(2000000):
        file.write(random.choice(lines))
    file.write("}\n")
    file.close()
