import threading


counter = 0

rlock = threading.RLock()

def increment():
    global counter
    for _ in range(100000):
        rlock.acquire()
        try:
            counter += 1
        finally:
            rlock.release()

threads = []
for _ in range(5):
    thread = threading.Thread(target=increment)
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()

print(f"Final counter value: {counter}")