#/usr/bin/env python3
#countasync.py

import asyncio

async def count(i):
    print("One" + str(i))
    await asyncio.sleep(0.5)
    print("Two" + str(i))

async def main():
    await asyncio.gather(count(1),count(2),count(3))

if __name__ == "__main__":
    import time
    s = time.perf_counter()
    asyncio.run(main())
    elapsed = time.perf_counter()-s
    print(f"{__file__} executed in {elapsed:0.2f} seconds.")
