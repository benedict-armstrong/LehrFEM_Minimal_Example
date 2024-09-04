# LehrFEM++ Project Scaffold

To start a new project using LehrFEM++, you can use this scaffold as a template.

1. Create a build directory and change into it

```bash
mkdir build
cd build
```

2. Run cmake and make

> [!TIP]
> The recommended complier is `llvm@14` and the recommended version of `cmake` is `3.27.9`.

```bash
cmake ..
make
```

3. Run the executable

```bash
./src/lehrfem_project
```

The output should be

```txt
Information about node:
NODE

Information about segment:
EDGE

Information about triangle:
TRIA

Information about quad:
QUAD
```
