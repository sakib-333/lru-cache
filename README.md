# LRU Cache — C++ Implementation

A simple and efficient implementation of a **Least Recently Used (LRU) Cache** using C++ STL.

The cache supports:

* `get(key)` — Retrieve a value by key.
* `put(key, value)` — Insert or update a key/value pair.
* Automatic eviction of the **Least Recently Used (LRU)** entry when the cache reaches its capacity.

## Features

* Fixed positive cache capacity
* `get()` returns `-1` when the key does not exist
* Successful `get()` updates the key as **Most Recently Used (MRU)**
* `put()` inserts new entries or updates existing ones
* Automatically removes the LRU entry when the cache is full
* `O(1)` average time complexity for both `get()` and `put()`
* Implemented using standard C++ STL containers

---

## Data Structures

Two STL containers are used:

### 1. `std::unordered_map`

The hash map stores each key along with its value and its position in the LRU list.

```cpp
unordered_map<string, pair<int, list<string>::iterator>> cache;
```

It allows us to find a key in **O(1) average time**.

The iterator stored with each entry points directly to the corresponding key in the LRU list.

### 2. `std::list`

A doubly linked list is used to maintain the LRU order.

```cpp
list<string> lru;
```

The ordering is maintained as:

```text
Front                         Back
  ↓                             ↓
Most Recently Used        Least Recently Used
```

For example:

```text
A → C → B
```

means:

* `A` is the most recently used key.
* `B` is the least recently used key.

`std::list` is suitable because insertion and deletion at known positions are `O(1)` operations.

---

## How LRU Ordering Works

Whenever a key is accessed or inserted, it is moved to the **front** of the list.

### Example

Assume the cache capacity is `2`.

```cpp
cache.put("A", 10);
cache.put("B", 20);
```

The LRU list becomes:

```text
A → B
```

Here:

```text
A = MRU
B = LRU
```

Now if:

```cpp
cache.get("B");
```

`B` becomes the most recently used:

```text
B → A
```

If we then execute:

```cpp
cache.put("C", 30);
```

The cache is full, so the entry at the back of the list (`A`) is removed:

```text
C → B
```

Therefore:

```cpp
cache.get("A"); // -1
cache.get("B"); // 20
cache.get("C"); // 30
```

---

## Operations

### `get(key)`

If the key exists:

1. Find the key using `unordered_map`.
2. Remove its current position from the list.
3. Move it to the front.
4. Return its stored value.

If the key does not exist, return `-1`.

```cpp
int get(string key);
```

### `put(key, value)`

If the key already exists:

1. Remove its old position from the list.
2. Update its value.
3. Move it to the front.

If the key does not exist:

1. Check whether the cache is full.
2. If full, remove the key at the back of the list.
3. Insert the new key at the front.
4. Store its value and list iterator in the hash map.

```cpp
void put(string key, int value);
```

---

## Complexity

| Operation | Time Complexity |
| --------- | --------------- |
| `get()`   | `O(1)` average  |
| `put()`   | `O(1)` average  |
| Eviction  | `O(1)`          |
| Lookup    | `O(1)` average  |

### Space Complexity

The cache stores at most `capacity` entries.

Therefore:

```text
Space Complexity: O(capacity)
```

---

## Project Structure

```text
lru-cache/
│
├── main.cpp
└── README.md
```

* `main.cpp` — LRU Cache implementation and example/test code
* `README.md` — Project documentation

---

## Requirements

To run this project, you need:

* A C++ compiler supporting C++11 or later
* Standard C++ STL

Recommended:

* GCC
* MinGW
* Clang
* MSVC

---

## How to Run

### 1. Clone the repository

```bash
git clone git@github.com:sakib-333/lru-cache.git
cd lru-cache
```

### 2. Compile

Using GCC:

```bash
g++ -std=c++17 main.cpp -o lru-cache
```

### 3. Run

On Windows:

```bash
lru-cache.exe
```

On Linux/macOS:

```bash
./lru-cache
```

---

## Example

The included example demonstrates insertion, retrieval, recent-use updates, and LRU eviction.

```cpp
Cache cache(2);

cache.put("A", 10);
cache.put("B", 20);

cout << cache.get("A") << endl;

cache.put("C", 30);

cout << cache.get("B") << endl;
cout << cache.get("C") << endl;
cout << cache.get("A") << endl;
```

Expected output:

```text
10
-1
30
10
```

The `-1` result confirms that `B` was evicted because it was the **Least Recently Used** entry when `C` was inserted.

---

## Implementation Approach

The implementation combines:

```text
unordered_map + doubly linked list
```

The hash map provides fast key lookup, while the doubly linked list maintains the usage order.

Each hash-map entry stores:

```text
key
value
iterator → corresponding list node
```

This allows the implementation to locate an entry and update its position without traversing the list.

---

## Scope

This implementation focuses on the core LRU Cache requirements:

* Key/value storage
* LRU ordering
* Constant-time average lookup
* Constant-time average insertion/update
* Automatic eviction

TTL/expiration support is not included in the base implementation.
