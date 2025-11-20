import random
import sys

def generate(nJobs: int, nMachines: int, tau: float) -> None:
    with open("generated_data.txt", "w", encoding="utf-8") as f:
        f.write(f"{nJobs} {nMachines} {tau}\n")
        for i in range(nJobs):
            row = [str(random.randint(1, 100)) for _ in range(nMachines)]
            f.write(" ".join(row) + "\n")

    print("Generated data. Filename: generated_data.txt")

if __name__ == "__main__":
    try:
        nJobs, nMachines, tau = sys.argv[1:]
        nJobs = int(nJobs)
        nMachines = int(nMachines)
        tau = float(tau)
    except Exception:
        print("Cannot generate. Make sure you pass arguments like this: <nJobs> <nMachines> <tau>")
        exit()
    generate(nJobs, nMachines, tau)