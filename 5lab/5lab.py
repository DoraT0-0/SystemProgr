import threading
import time
import random
import sys

def worker(priority):
    while True:
        result = sum(random.randint(1, 100) for _ in range(50))
        print(f"Worker with priority {priority} completed iteration with result {result}")
        time.sleep(1)

def main():
    priority1 = int(sys.argv[1])
    priority2 = int(sys.argv[2])

    thread1 = threading.Thread(target=worker, args=(priority1,))
    thread2 = threading.Thread(target=worker, args=(priority2,))

    thread1.start()
    thread2.start()

    iteration_count = 0
    start_time = time.time()
    while True:
        time.sleep(1)
        iteration_count += 1
        print(f"Main thread: {iteration_count} iterations completed in {time.time() - start_time:.2f} seconds")

if __name__ == "__main__":
    main()