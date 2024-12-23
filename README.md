# Comparison of sequental and parallel BFS implementation

For parallel implementation [parlaylib](https://github.com/cmuparlay/parlaylib) used (primitives and runtime).

## build-and-run

CMake and `parlaylib` should be installed

### build
```console
$ cmake . --preset Debug/Release # choose needed preset
$ cd cmake-build-Debug/Release # use preset name from previous step
$ cmake --build . --target test/bench # two independent targets present
```

### run
Just run built executable with environment variable for workers, if needed:
```console
$ PARLAY_NUM_THREADS=4 ./bench
$ ./test
```

You also can use default clion settings (don't forget to set env var in run configuration, if needed).

## Runs

```
Run #1
	sequental: 60059ms
	parallel: 25763ms
	acceleration: 2.3312114272406164

Run #2
	sequental: 56920ms
	parallel: 24770ms
	acceleration: 2.2979410577311263

Run #3
	sequental: 50689ms
	parallel: 23364ms
	acceleration: 2.1695343263139875

Run #4
	sequental: 48973ms
	parallel: 25098ms
	acceleration: 1.951271017610965

Run #5
	sequental: 53334ms
	parallel: 24342ms
	acceleration: 2.1910278530934186

sequental avg time: 53995ms
parallel avg time: 24667ms
parallel 2.1889214104445545 times faster than sequental⏎ 
```
