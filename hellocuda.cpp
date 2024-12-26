/*
1. g++：编译C++代码并生成可执行文件
g++ 是 GNU 编译器套件 (GNU Compiler Collection, GCC) 中的 C++
编译器。它是一个开源的 C++ 编译器，通常用于 Linux、MacOS 和其他类 Unix
操作系统中。g++ 可以编译 C++ 源代码文件并生成可执行文件。 g++ -std=c++20
.\hellocuda.cpp -o hellocuda标准，hellocuda; -std选项可以指定C++标准，-o
选项可以指定生成的可执行文件名。即使用C++20标准编译 hellocuda.cpp，生成名为
hellocuda 的可执行文件
./hellocuda.exe 运行可执行文件

2. nvcc：编译 CUDA 代码并生成可执行文件

3. cl:编译 C++ 代码，专为 Windows 平台设计。 置于VS中

4. CMake:跨平台构建工具，生成适合编译器的构建文件（如 Makefile、Visual Studio
文件等）
# 1. 创建一个构建目录
mkdir build
cd build

# 2. 运行 CMake 生成构建系统文件（如 Makefile）
cmake ..

# 3. 使用生成的构建文件进行构建（例如使用 Makefile）
make
*/
#include <iostream>

int main() {
  int *a{new int[10]};
  // a 是地址，*a 得到的值就是这块内存中地址的值
  int &b = *a; // 希望 b 成为对 a[0] 的引用，而不是一个新的独立变量，你可以将 b
               // 声明为对 a[0] 的引用。这样，修改 b 会直接影响 a[0] 的值。
  int c = *a;  // a 是指向动态数组的首地址（即 a[0]），而 *a
              // 是解引用操作，意味着访问 a 指向的内存中的值，即数组的第一个元素
              // a[0]。所以： b 被赋值为 *a，也就是 a[0] 的值。 b = 10;
  std::cout << "a[0] = " << a[0] << std::endl;
}
