#ifndef QEC_H
#define QEC_H

#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <random>

using namespace std;

using Complex = complex<double>;
const Complex I(0, 1); // Imaginary unit
random_device rd;
mt19937 gen(rd());

// Class representing a 3-qubit quantum state
class QuantumState {
public:
    vector<Complex> state;

    QuantumState() {
        // Initialize the system in |000>
        state.resize(8, Complex(0, 0)); 
        state[0] = Complex(1, 0); // Initial state |000>
    }

    // Apply an X (bit-flip) gate to qubit k
    void applyX(int k) {
        vector<Complex> newState(8, Complex(0, 0));
        for (int i = 0; i < 8; ++i) {
            if ((i >> k) & 1) {
                newState[i ^ (1 << k)] = state[i];
            } else {
                newState[i ^ (1 << k)] = state[i];
            }
        }
        state = newState;
    }

    // Apply a Z (phase-flip) gate to qubit k
    void applyZ(int k) {
        for (int i = 0; i < 8; ++i) {
            if ((i >> k) & 1) {
                state[i] *= Complex(-1, 0); // Apply phase flip
            }
        }
    }

    // Measure a specific qubit
    int measureQubit(int k) {
        double prob_0 = 0;
        for (int i = 0; i < 8; ++i) {
            if (!((i >> k) & 1)) {
                prob_0 += norm(state[i]);
            }
        }
        bernoulli_distribution dist(prob_0);
        return dist(gen) ? 0 : 1;
    }

    // Encode the logical qubit into 3 physical qubits (Bit-flip Code)
    void encodeBitFlip() {
        // Encoding: |ψ> = α|0> + β|1> -> α|000> + β|111>
        state[0] = Complex(1 / sqrt(2), 0); // (|000> + |111>)/sqrt(2)
        state[7] = Complex(1 / sqrt(2), 0);
    }

    // Encode the logical qubit into 3 physical qubits (Phase-flip Code)
    void encodePhaseFlip() {
        // Encoding: |ψ> = α|0> + β|1> -> α(|+++>) + β(|--->)
        state[0] = Complex(1 / sqrt(2), 0); // (|000> + |111>)/sqrt(2)
        state[7] = Complex(1 / sqrt(2), 0);
    }

    // Introduce a random X error on any of the 3 qubits
    void introduceBitFlipError() {
        uniform_int_distribution<> dist(0, 2); // Randomly select qubit 0, 1, or 2
        int errorQubit = dist(gen);
        cout << "Introducing X (bit-flip) error on qubit: " << errorQubit << endl;
        applyX(errorQubit);
    }

    // Introduce a random Z error on any of the 3 qubits
    void introducePhaseFlipError() {
        uniform_int_distribution<> dist(0, 2); // Randomly select qubit 0, 1, or 2
        int errorQubit = dist(gen);
        cout << "Introducing Z (phase-flip) error on qubit: " << errorQubit << endl;
        applyZ(errorQubit);
    }

    // Correct bit-flip error using majority voting
    void correctBitFlipError() {
        int bit0 = measureQubit(0);
        int bit1 = measureQubit(1);
        int bit2 = measureQubit(2);

        cout << "Syndrome bits: " << bit0 << " " << bit1 << " " << bit2 << endl;

        // Majority voting logic: flip qubits if needed
        if (bit0 != bit1 && bit0 != bit2) {
            cout << "Correcting error on qubit 0" << endl;
            applyX(0);
        } else if (bit1 != bit0 && bit1 != bit2) {
            cout << "Correcting error on qubit 1" << endl;
            applyX(1);
        } else if (bit2 != bit0 && bit2 != bit1) {
            cout << "Correcting error on qubit 2" << endl;
            applyX(2);
        }
    }

    // Correct phase-flip error using majority voting
    void correctPhaseFlipError() {
        int bit0 = measureQubit(0);
        int bit1 = measureQubit(1);
        int bit2 = measureQubit(2);

        cout << "Syndrome bits: " << bit0 << " " << bit1 << " " << bit2 << endl;

        // Majority voting logic for phase-flip errors
        if (bit0 != bit1 && bit0 != bit2) {
            cout << "Correcting phase error on qubit 0" << endl;
            applyZ(0);
        } else if (bit1 != bit0 && bit1 != bit2) {
            cout << "Correcting phase error on qubit 1" << endl;
            applyZ(1);
        } else if (bit2 != bit0 && bit2 != bit1) {
            cout << "Correcting phase error on qubit 2" << endl;
            applyZ(2);
        }
    }

    // Print the state of the quantum system
    void printState() {
        for (int i = 0; i < 8; ++i) {
            cout << "|"<< i << ">: " << state[i] << endl;
        }
    }
};

#endif // QEC_H
