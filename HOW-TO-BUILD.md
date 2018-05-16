Building the te
===============

```bash
cd <project_root>
git submodule add git@github.com:PeterSommerlad/CUTE.git cute
mkdir -p build
cd build
cmake ..
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

