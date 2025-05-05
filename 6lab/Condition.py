import threading

condition = threading.Condition()

counter = 0

def increment():
    global counter
    for _ in range(100000):
        with condition:
            counter += 1
            condition.notify()

threads = []
for _ in range(5):
    thread = threading.Thread(target=increment)
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()

print(f"Final counter value: {counter}")