with open("test_1M_lines.rw", "w") as file:
    file.write("main: () -> () {\n\ti :: 15")
    for _ in range(1000000):
        file.write("\tif i == 128 { print(\"Hello, World!\"); i += cast(int, 472.047/34.17) + cast(int, true) % 5 }\n")
    file.write("}\n")
    file.close()