# Cmake 问题解疑

## 1 Windows cmake

### 1.1 Windows 下使用 cmake 指定 Visual Studio 版本

Windows 下 cmake 可以使用 `-G` 来指定 Visual Studio 的版本。



查看 cmake 支持的 generator, 使用下边的命令：

```c++
cmake -G
```



比如同时支持:

```powershell
Generators
* Visual Studio 16 2019        = Generates Visual Studio 2019 project files.
                                 Use -A option to specify architecture.
  Visual Studio 15 2017 [arch] = Generates Visual Studio 2017 project files.
                                 Optional [arch] can be "Win64" or "ARM".
```



则可通过以下命令：

```powershell
cmake .. -G "Visual Studio 15 2017 Win64"
```

来指定 cmake 的编译版本。

