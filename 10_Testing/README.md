### Building

```
mkdir build && cd build
cmake ..
make all
```

### Test

```
ctest -T Test
```

### Check coverage

```
ctest -T Coverage
```
### Clean

```
cd .. && rm -rf build
```
