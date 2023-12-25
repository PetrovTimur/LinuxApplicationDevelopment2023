### Building

```
mkdir build && cd build
cmake ..
make all install
```

### View manual

```
man ./guess.man
```

### View documentaion

```
python3 -m http.server -d doxygen-doc/html/
```

Then go to http://localhost:8000 in your browser.

### Run executable

```
./guess [OPTION]
```

### Clean

```
cd .. && rm -rf build
```
