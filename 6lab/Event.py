import threading


event = threading.Event()

counter = 0

def increment():
    global counter
    for _ in range(100000):
        event.wait()
        event.clear()
        counter += 1
        event.set()

threads = []
for _ in range(5):
    thread = threading.Thread(target=increment)
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()

print(f"Final counter value: {counter}")