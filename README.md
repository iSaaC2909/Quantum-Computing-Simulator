# Quantum Computing Simulator

A comprehensive C++ library for simulating quantum computing operations, algorithms, and phenomena. This simulator provides implementations of various quantum algorithms, quantum error correction, quantum machine learning, and quantum physics simulations.

## Features

### Quantum Algorithms
- Shor's Algorithm
- Grover's Algorithm
- Quantum Fourier Transform
- Deutsch-Jozsa Algorithm
- Simon's Algorithm
- Bernstein-Vazirani Algorithm
- Quantum Phase Estimation
- Quantum Counting Algorithm

### Quantum Machine Learning
- Quantum Approximate Optimization Algorithm (QAOA)
- Quantum K-Means Clustering (2D)
- Variational Quantum Eigensolver (VQE)

### Quantum Error Correction
- Shor Code
- 3-Qubit Error Correction
- General QEC Framework

### Quantum Communication Protocols
- Quantum Teleportation
- Superdense Coding
- Entanglement Swapping
- Distributed CNOT Operations

### Quantum Physics Simulations
- Schrödinger Equation
- Ising Model
- Matrix Product State (MPS) Simulator
- Pauli String Simulations

### Quantum Games and Paradoxes
- Magic Square Game
- Hardy's Paradox
- CHSH Inequality
- Elitzur-Vaidman Bomb Tester
- Quantum Coin Flipping

### Core Components
- Qubit Register Management
- Quantum Gates (Single-qubit, Multi-qubit, Controlled operations)
- Quantum Measurements
- Quantum Circuit Construction
- Oracle Implementation

## Requirements

- C++ compiler with C++11 support or higher
- Standard Template Library (STL)

## Project Structure

The project is organized into multiple header files, each focusing on specific quantum computing aspects:

- Core functionality: `QubitRegister.h`, `QuantumGate.h`, `Operators.h`
- Algorithms: `ShorAlgorithm.h`, `GroverAlgorithm.h`, `QuantumFourierTransform.h`
- Error Correction: `QEC.h`, `ShorCode.h`, `ErrorCorrection3Qubits.h`
- Machine Learning: `QAOA.h`, `QMeansClustering2D.h`, `VQE.h`
- Physics Simulations: `Schrodinger.h`, `IsingModel.h`, `MPSSimulator.h`
- Test Files: Various `*Tests.cpp` files for each component

## Getting Started

1. Clone the repository
2. Include the necessary header files in your project
3. Create a QubitRegister instance to start working with quantum states
4. Use the provided quantum gates and algorithms as needed

Example usage:

```cpp
#include "QubitRegister.h"
#include "QuantumGate.h"

int main() {
    // Create a 2-qubit register
    QubitRegister qreg(2);
    
    // Apply Hadamard gate to first qubit
    qreg.ApplyGate(HadamardGate(), 0);
    
    // Measure the state
    auto result = qreg.Measure();
    
    return 0;
}
```

## Testing

The project includes comprehensive test files for each component. Run the test files to verify the functionality:

- `GatesTests.cpp` - Tests for quantum gates
- `SimulationTests.cpp` - Tests for quantum simulations
- `ErrorCorrectionTests.cpp` - Tests for error correction codes
- `QMLTests.cpp` - Tests for quantum machine learning algorithms

## Contributing

Contributions are welcome! Please feel free to submit pull requests, create issues, or suggest improvements.

## License

[Insert appropriate license information here]

## References

This simulator implements quantum algorithms and concepts from various quantum computing textbooks and papers. Key references include:

- Nielsen, M. A., & Chuang, I. L. (2010). Quantum Computation and Quantum Information
- Quantum Algorithm Implementations for Beginners (arXiv:1804.03719)
- [Add other relevant references] 