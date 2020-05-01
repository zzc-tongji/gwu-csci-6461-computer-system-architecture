#  Project 5

Zhicheng Zhang - G45149856



### 1. Introduction

The project is about Grover's algorithm in quantum computing.

Based on [wikipedia](https://en.wikipedia.org/wiki/Grover%27s_algorithm), "Grover's algorithm is a quantum algorithm that finds with high probability the unique input to a black box function that produces a particular output value, using just O(sqrt N) evaluations of the function, where N is the size of the function's domain. It was devised by Lov Grover in 1996."

Use IBM Quantum Experience to realize the algorithm.



### 2. Environment

- [IBM Quantum Experience](https://quantum-computing.ibm.com/)

<div style="page-break-after: always;"></div>

### 3. Implementation

https://www.youtube.com/watch?v=pYD6bvKLI_c

![image-1](./image-1.png)

![image-2](./image-2.png)

<div style="page-break-after: always;"></div>

### 4. Result

![image-3](./image-3.png)

``` json
{
  "type": "QASM",
  "experiments": [
    {
      "config": {
        "memory_slots": 5,
        "n_qubits": 5
      },
      "header": {
        "memory_slots": 5,
        "clbit_labels": [
          [ "c", 0 ],
          [ "c", 1 ],
          [ "c", 2 ],
          [ "c", 3 ]
        ],
        "qreg_sizes": [
          [ "q", 5 ]
        ],
        "qubit_labels": [
          [ "q", 0 ],
          [ "q", 1 ],
          [ "q", 2 ],
          [ "q", 3 ],
          [ "q", 4 ]
          ]
        ],
        "n_qubits": 5,
        "creg_sizes": [
          [ "c", 5 ]
        ],
        "name": "circuit376"
      },
      "instructions": [
        {
          "qubits": [ 1 ],
          "name": "h"
        },
        {
          "qubits": [ 2 ],
          "name": "h"
        },
        {
          "qubits": [ 2 ],
          "name": "h"
        },
        {
          "qubits": [ 1, 2 ],
          "name": "cx"
        },
        {
          "qubits": [ 1 ],
          "name": "h"
        },
        {
          "qubits": [ 1 ],
          "name": "x"
        },
        {
          "qubits": [ 2 ],
          "name": "h"
        },
        {
          "qubits": [ 2 ],
          "name": "h"
        },
        {
          "qubits": [ 2 ],
          "name": "x"
        },
        {
          "qubits": [ 2 ],
          "name": "h"
        },
        {
          "qubits": [ 1, 2 ],
          "name": "cx"
        },
        {
          "qubits": [ 1 ],
          "name": "x"
        },
        {
          "qubits": [ 1 ],
          "name": "h"
        },
        {
          "qubits": [ 2 ],
          "name": "h"
        },
        {
          "qubits": [ 2 ],
          "name": "x"
        },
        {
          "qubits": [ 2 ],
          "name": "h"
        },
        {
          "qubits": [ 1 ],
          "name": "measure",
          "memory": [ 1 ]
        },
        {
          "qubits": [ 2 ],
          "name": "measure",
          "memory": [ 2 ]
        }
      ]
    }
  ],
  "qobj_id": "dd8ff687-eb09-4e97-8e30-6ebf4fd61c8f",
  "config": {
    "memory_slots": 5,
    "memory": false,
    "n_qubits": 5,
    "parameter_binds": [],
    "shots": 1024
  },
  "schema_version": "1.1.0",
  "header": {}
}
```



### 5. Conclusion

It is a simple project about quantum computing. I have learnt some basic concepts and useful tools.