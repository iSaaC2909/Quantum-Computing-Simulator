#ifndef QAOA_H
#define QAOA_H

#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <random>
#include <functional>

using namespace std;
using Complex = complex<double>;

const Complex I(0, 1); // Imaginary unit
const double PI = 3.14159265358979323846;

// Random number generator for measurement
random_device rd;
mt19937 gen(rd());

// QuantumState class to handle quantum state vector and gate operations
class QuantumState {
public:
    vector<Complex> state;

    QuantumState(int n_qubits) {
        int size = 1 << n_qubits; // 2^n_qubits
        state.resize(size, Complex(0, 0));
        state[0] = Complex(1, 0); // Initial state |00...0>
    }

    // Apply Hadamard gate to qubit k
    void applyHadamard(int k, int n_qubits) {
        int size = 1 << n_qubits;
        for (int i = 0; i < size; ++i) {
            if ((i >> k) & 1) continue;
            int j = i | (1 << k);
            Complex temp = state[i];
            state[i] = (state[i] + state[j]) / sqrt(2);
            state[j] = (temp - state[j]) / sqrt(2);
        }
    }

    // Apply Pauli-X gate to qubit k
    void applyX(int k, int n_qubits) {
        int size = 1 << n_qubits;
        for (int i = 0; i < size; ++i) {
            if ((i >> k) & 1) continue;
            swap(state[i], state[i | (1 << k)]);
        }
    }

    // Apply Z-rotation gate to qubit k with angle theta
    void applyRz(int k, int n_qubits, double theta) {
        int size = 1 << n_qubits;
        for (int i = 0; i < size; ++i) {
            if ((i >> k) & 1) {
                state[i] *= exp(-I * theta / 2);
            } else {
                state[i] *= exp(I * theta / 2);
            }
        }
    }

    // Apply a controlled-Z gate between qubits k1 and k2
    void applyCZ(int k1, int k2, int n_qubits) {
        int size = 1 << n_qubits;
        for (int i = 0; i < size; ++i) {
            if (((i >> k1) & 1) && ((i >> k2) & 1)) {
                state[i] *= -1.0;
            }
        }
    }

    // Measure the state and return a bitstring
    string measure(int n_qubits) {
        vector<double> probabilities(state.size());
        for (size_t i = 0; i < state.size(); ++i) {
            probabilities[i] = norm(state[i]);
        }

        discrete_distribution<int> dist(probabilities.begin(), probabilities.end());
        int result = dist(gen);
        string bitstring = "";
        for (int i = 0; i < n_qubits; ++i) {
            bitstring = to_string((result >> i) & 1) + bitstring;
        }
        return bitstring;
    }
};

// Define the Max-Cut problem on a simple 2-qubit graph
int costFunction(const string& bitstring) {
    return (bitstring[0] != bitstring[1]) ? 1 : 0; // Cut between two nodes
}

// QAOA Circuit for Max-Cut
QuantumState qaoaCircuit(int p, int n_qubits, double gamma, double beta) {
    QuantumState qs(n_qubits);

    // Apply Hadamard to all qubits
    for (int i = 0; i < n_qubits; ++i) {
        qs.applyHadamard(i, n_qubits);
    }

    // QAOA loop for p layers
    for (int i = 0; i < p; ++i) {
        // Cost Hamiltonian (for Max-Cut: apply a controlled-Z gate between qubits)
        qs.applyCZ(0, 1, n_qubits); // Assume a simple 2-qubit problem
        qs.applyRz(0, n_qubits, gamma);
        qs.applyRz(1, n_qubits, gamma);

        // Mixer Hamiltonian (apply X-rotation)
        for (int j = 0; j < n_qubits; ++j) {
            qs.applyX(j, n_qubits);
        }
    }
    return qs;
}

#endif // QAOA_H
