import threading

semaphore = threading.Semaphore(3)

counter = 0

def increment():
    global counter
    for _ in range(100000):
        semaphore.acquire()
        try:
            counter += 1
        finally:
            semaphore.release()

threads = []
for _ in range(5):
    thread = threading.Thread(target=increment)
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()

print(f"Final counter value: {counter}")