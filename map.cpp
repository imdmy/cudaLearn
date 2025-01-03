/*
map 容器中的元素都是 pair类
std::map<std::string, int> myMap;
myMap["apple"] = 10;
myMap["banana"] = 20;

const std::pair<std::string, int>& p = myMap.begin()->second;
std::cout << p.first << " " << p.second << std::endl; // apple 10
*/

/*
在 C++ 中，如果你想返回两个值（例如 `int` 和
`std::string`），你有几种方式可以实现。以下是几种常用的做法：

### 1. 使用 `std::pair`

`std::pair` 是一个容器，它可以存储两个不同类型的值。你可以使用 `std::pair`
来返回一个 `int` 和一个 `std::string`。

#### 示例代码：

```cpp
#include <iostream>
#include <string>
#include <utility>  // for std::pair

std::pair<int, std::string> process() {
    int status = 1;  // 假设状态是 1，表示成功
    std::string message = "Operation succeeded";  // 操作消息

    // 你可以根据不同的条件修改 status 和 message
    // 如果处理失败，可以做如下更改：
    // status = -1;
    // message = "Operation failed";

    return std::make_pair(status, message);  // 返回两个值
}

int main() {
    // 获取返回值
    auto result = process();

    // 通过 result.first 获取 int 状态，通过 result.second 获取 string 消息
    if (result.first == 1) {
        std::cout << "Success: " << result.second << std::endl;
    } else {
        std::cout << "Error: " << result.second << std::endl;
    }

    return 0;
}
```

### 解释：
- **`std::pair<int, std::string>`**：返回一个包含两个值的 `pair`，第一个值是
`int`，第二个值是 `std::string`。
- **`std::make_pair(status, message)`**：创建并返回一个 `pair`，它包含了状态值
`status` 和消息 `message`。
- 在 `main()` 中，你可以通过 `.first` 和 `.second` 来访问返回的 `int` 和
`std::string`。

### 2. 使用 `std::tuple`

如果你需要返回更多的值，或者返回的值类型比较复杂，可以使用
`std::tuple`。`std::tuple` 可以容纳任意数量和类型的值。

#### 示例代码：

```cpp
#include <iostream>
#include <string>
#include <tuple>  // for std::tuple

std::tuple<int, std::string> process() {
    int status = 1;  // 假设状态是 1，表示成功
    std::string message = "Operation succeeded";  // 操作消息

    return std::make_tuple(status, message);  // 返回一个包含多个值的元组
}

int main() {
    // 获取返回的元组
    auto result = process();

    // 通过 std::get 获取元组中的值
    if (std::get<0>(result) == 1) {
        std::cout << "Success: " << std::get<1>(result) << std::endl;
    } else {
        std::cout << "Error: " << std::get<1>(result) << std::endl;
    }

    return 0;
}
```

### 解释：
- **`std::tuple<int,
std::string>`**：返回一个包含多个不同类型值的元组。你可以通过
`std::get<index>(tuple)` 来访问元组中的每个元素。
- `std::make_tuple(status, message)` 创建并返回一个元组，包含了 `int` 和
`std::string`。

### 3. 使用自定义结构体（推荐方式）

另一种常见的方式是使用自定义结构体。这样你可以为返回值提供更有意义的名称，增加代码的可读性。

#### 示例代码：

```cpp
#include <iostream>
#include <string>

struct ProcessResult {
    int status;      // 状态
    std::string message;  // 返回消息
};

ProcessResult process() {
    ProcessResult result;
    result.status = 1;  // 假设状态是 1，表示成功
    result.message = "Operation succeeded";  // 操作消息

    return result;  // 返回自定义结构体
}

int main() {
    // 获取返回值
    ProcessResult result = process();

    if (result.status == 1) {
        std::cout << "Success: " << result.message << std::endl;
    } else {
        std::cout << "Error: " << result.message << std::endl;
    }

    return 0;
}
```

### 解释：
- **`struct ProcessResult`**：定义了一个结构体，包含两个成员：`int status` 和
`std::string message`。
- 返回的类型是 `ProcessResult`，可以直接访问 `status` 和 `message`。

### 总结：
1. **`std::pair`**：适用于返回两个值，简单且方便，适用于返回少量的值。
2. **`std::tuple`**：适用于返回多个值，特别是当返回的值数量不固定时。
3.
**自定义结构体**：适用于需要更多语义化、可维护性和扩展性较强的场景。返回结构体中的字段更加清晰和可读。

在实际使用中，**推荐使用结构体**，因为它能为返回的值提供清晰的语义，尤其是当返回值的含义较为复杂时。
*/