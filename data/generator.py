import random

SEED = 0
random.seed(SEED)

def generate_example(file_name, line_count, reuse_chance = 0.5, min_line_len = 4, max_line_len = 4095, character_range = range(63, 127)):
    with open(file_name + ".in", "w") as infile:
        with open(file_name + ".out", "w") as outfile:
            generated_lines = []
            for i in range(line_count):
                if len(generated_lines) and random.random() < reuse_chance:
                    choice = random.choice(generated_lines)
                    rotation = random.randrange(len(choice))
                    line = choice[rotation:] + choice[:rotation]
                else:
                    line = "".join(map(chr, random.choices(character_range, k=random.randint(min_line_len, max_line_len))))
                    generated_lines.append(line)
                    outfile.write(line + "\n")
                infile.write(line + "\n")

if __name__ == "__main__":
    generate_example("small", 100, max_line_len=32)
    generate_example("medium", 10_000, max_line_len=1024)
    generate_example("large", 100_000, max_line_len=4095)
