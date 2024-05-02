# qSimulator
## Quantum computer simulator
Quantum computer simulators can model the behavior of quantum circuits, 
which are composed of quantum gates and qubits. Simulator aim to 
accurately emulate the probabilistic and superpositional characteristics 
of quantum mechanics. It simulates the evolution of qubits through quantum gates,
 taking into account entanglement and interference effects.

The simulator is convinient to test and debug quantum algorithms before implementing them on actual quantum hardware. This saves time and resources while ensuring the algorithms are well-optimized.

## Directory structure
* [`CMakeLists.txt`](./CMakeLists.txt) cmake project files
* [`include/`](./include) header files (`*.h`)
* [`src/`](./src) source files (`*.cpp`)
* [`test/`](./test) test files  (`*.cpp`)
* [`samples/`](./samples) examples of using the functionality  (`*.cpp`)


## Cloning the project
Use `git clone --recursive ...` to download the project and its git submodules.
Otherwise from the project root repository one needs to download the submodules: 
`git submodule update --init`.

## Building the project
1. Creating the executables follows standard `cmake` procedure:
```
cmake -B build
```

2. Compile the code:
```
cmake --build build
```

3. Run executable:
```
./build/bin/shor_sample
```
to run sample or
```
./build/bin/tests
```
to run unit tests