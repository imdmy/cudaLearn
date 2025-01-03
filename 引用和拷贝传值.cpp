/*
在 C++ 中，`ptr` 和 `&ptr` 作为参数传递有不同的语义，它们的区别主要体现在
**传值**、**传引用** 和 **传指针**
上。让我们逐步解释一下这两者的不同，并讨论它们在传递 `std::shared_ptr`
参数时的影响。

### 1. **传递 `std::shared_ptr` 的方式**

#### (a) **传值：`std::shared_ptr<T> ptr`**

当你将一个 `std::shared_ptr` 按值传递时，**会创建一个新的 `shared_ptr`
副本**，并且该副本会独立地管理对象的引用计数。

- **副本**：创建了一个新的 `shared_ptr`，它会增加引用计数。这意味着原来的
`shared_ptr` 和新的副本会共享同一个资源。
- **引用计数**：传值时，引用计数会增加，因为新的 `shared_ptr`
副本也指向了相同的对象。

**示例：**
```cpp
void process(std::shared_ptr<int> ptr) {
    std::cout << "Value: " << *ptr << std::endl;
    std::cout << "Use count in function: " << ptr.use_count() << std::endl;
}

int main() {
    auto sp = std::make_shared<int>(10);  // 引用计数为 1
    process(sp);                          // 引用计数变为 2
    std::cout << "Use count in main: " << sp.use_count() << std::endl; //
引用计数为 2
}
```

- 在 `process` 函数中，`ptr` 是 `shared_ptr` 的副本。传递进去后，引用计数增加。
- 原 `sp` 和 `ptr` 指向同一个对象，所以引用计数为 2。

**优点**：
- 不会影响外部的 `shared_ptr`，不会修改原来的 `shared_ptr`。

**缺点**：
- 会增加引用计数，可能导致性能上的开销。
- 如果你只是想修改传递给函数的
`shared_ptr`，需要重新赋值（不可直接修改传入的指针）。

#### (b) **传递引用：`std::shared_ptr<T>& ptr`**

当你将 `std::shared_ptr` 按引用传递时，**传递的是指向原始 `shared_ptr`
的引用**，这意味着你可以在函数内修改原始 `shared_ptr`。

- **引用**：没有创建副本，传递的是原始 `shared_ptr` 的引用。
- **引用计数**：引用计数不会因为传递引用而改变，因为没有创建副本。

**示例：**
```cpp
void process(std::shared_ptr<int>& ptr) {
    std::cout << "Value: " << *ptr << std::endl;
    std::cout << "Use count in function: " << ptr.use_count() << std::endl;
    ptr.reset();  // 将 ptr 重置为 null，原 shared_ptr 也被影响
}

int main() {
    auto sp = std::make_shared<int>(10);  // 引用计数为 1
    process(sp);                          // 引用计数仍然为 1，sp 被 reset 为空
    std::cout << "Use count in main: " << sp.use_count() << std::endl; //
引用计数为 0
}
```

- 在 `process` 函数中，`ptr` 是传入 `sp` 的引用，因此对 `ptr` 的任何修改都会影响
`sp`。
- `reset()` 调用会清除 `ptr` 和 `sp` 指向的对象，从而将引用计数减至 0。

**优点**：
- 传递引用不会增加引用计数，因此可以避免不必要的性能开销。
- 你可以直接修改原始 `shared_ptr`，例如可以使用 `reset()` 或重新赋值。

**缺点**：
- 可能会修改原始 `shared_ptr`，需要小心使用。

#### (c) **传递常量引用：`const std::shared_ptr<T>& ptr`**

当你将 `std::shared_ptr` 按常量引用传递时，你不能在函数中修改 `shared_ptr`
本身（即不能 `reset` 或重新赋值），但你仍然可以访问其所管理的对象。

- **常量引用**：传递的是原始 `shared_ptr`
的常量引用，因此无法修改它，但可以读取它指向的对象。
- **引用计数**：引用计数也不会因为传递引用而增加。

**示例：**
```cpp
void process(const std::shared_ptr<int>& ptr) {
    std::cout << "Value: " << *ptr << std::endl;
    std::cout << "Use count in function: " << ptr.use_count() << std::endl;
    // ptr.reset(); // 错误，无法修改 ptr
}

int main() {
    auto sp = std::make_shared<int>(10);  // 引用计数为 1
    process(sp);                          // 引用计数仍然为 1
    std::cout << "Use count in main: " << sp.use_count() << std::endl; //
引用计数为 1
}
```

**优点**：
- 不会增加引用计数，避免性能开销。
- 不会修改传递的 `shared_ptr`，可以保证其值不变。

**缺点**：
- 不能在函数内修改 `shared_ptr` 本身（例如不能 `reset()` 或重新赋值）。

### 2. **总结**

- **传值（按值传递）**：会创建 `shared_ptr`
的副本，增加引用计数。适用于你希望传递给函数的 `shared_ptr`
在函数结束后独立于原始对象。
- **传引用（按引用传递）**：传递原始 `shared_ptr`
的引用，不会增加引用计数。适用于你希望函数内修改 `shared_ptr`
或者节省性能开销的情况。
- **常量引用（按常量引用传递）**：传递 `shared_ptr` 的常量引用，不能修改
`shared_ptr` 本身。适用于你不想修改 `shared_ptr`，但希望访问其指向的对象。

### 3. **什么时候使用 `&` 和 `std::shared_ptr`**

- 使用 `std::shared_ptr<T>&` 时，如果你想在函数内修改 `shared_ptr`
的值（例如，重新赋值或调用 `reset()`）。
- 使用 `const std::shared_ptr<T>&` 时，你只需要访问 `shared_ptr`
指向的对象，但不希望修改 `shared_ptr` 本身（最常见的情况）。
- 使用 `std::shared_ptr<T>`（按值传递）时，适用于函数内的操作不会修改原始
`shared_ptr`，但需要副本并且不关心引用计数增加。
*/