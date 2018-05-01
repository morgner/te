Building with the documentation
===============================

```bash
cd <project_root>
mkdir -p build
cd build
cmake ..
cmake --build .
or:
cmake --build . --target all -- -j2 (amount of cpu's to use)
```
------------------- OR (e.g.)
```bash
mkdir -p build/CodeBlocks
cd build/CodeBlocks
cmake ../../ -G "CodeBlocks - Unix Makefiles"
codeblocks odb.cbp
```
------------------- OR

use a different CMAKE Generator suitable to you environment

