#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class LeastSquaredRegressor {
private:
    vector<vector<double>> X;
    vector<double> y;
    double b0, b1, b2;

    // Función para multiplicar matrices
    vector<vector<double>> multiply(const vector<vector<double>>& A, const vector<vector<double>>& B) {
        int rA = A.size(), cA = A[0].size(), cB = B[0].size();
        vector<vector<double>> C(rA, vector<double>(cB, 0.0));
        for (int i = 0; i < rA; ++i)
            for (int j = 0; j < cB; ++j)
                for (int k = 0; k < cA; ++k)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }

    // Función para transponer una matriz
    vector<vector<double>> transpose(const vector<vector<double>>& A) {
        int rA = A.size(), cA = A[0].size();
        vector<vector<double>> T(cA, vector<double>(rA, 0.0));
        for (int i = 0; i < rA; ++i)
            for (int j = 0; j < cA; ++j)
                T[j][i] = A[i][j];
        return T;
    }

    // Función para sacar inversa de matriz 3x3 (método de la adjunta)
    vector<vector<double>> inverse3x3(const vector<vector<double>>& M) {
        double det = M[0][0]*(M[1][1]*M[2][2] - M[1][2]*M[2][1]) -
                     M[0][1]*(M[1][0]*M[2][2] - M[1][2]*M[2][0]) +
                     M[0][2]*(M[1][0]*M[2][1] - M[1][1]*M[2][0]);

        vector<vector<double>> inv(3, vector<double>(3, 0.0));
        inv[0][0] = (M[1][1]*M[2][2] - M[1][2]*M[2][1]) / det;
        inv[0][1] = (M[0][2]*M[2][1] - M[0][1]*M[2][2]) / det;
        inv[0][2] = (M[0][1]*M[1][2] - M[0][2]*M[1][1]) / det;
        inv[1][0] = (M[1][2]*M[2][0] - M[1][0]*M[2][2]) / det;
        inv[1][1] = (M[0][0]*M[2][2] - M[0][2]*M[2][0]) / det;
        inv[1][2] = (M[0][2]*M[1][0] - M[0][0]*M[1][2]) / det;
        inv[2][0] = (M[1][0]*M[2][1] - M[1][1]*M[2][0]) / det;
        inv[2][1] = (M[0][1]*M[2][0] - M[0][0]*M[2][1]) / det;
        inv[2][2] = (M[0][0]*M[1][1] - M[0][1]*M[1][0]) / det;
        return inv;
    }

public:
    // Constructor: DataSet predefinido quemado en el codigo
    LeastSquaredRegressor() {
        // MATRIZ X: {1 (intercepto), x1 (Factor 1), x2 (Factor 2)}
        X = {
            {1, 41.9, 29.1}, {1, 43.4, 29.3}, {1, 43.9, 29.5},
            {1, 44.5, 29.7}, {1, 47.3, 29.9}, {1, 47.5, 30.3},
            {1, 47.9, 30.5}, {1, 50.2, 30.7}, {1, 52.8, 30.8},
            {1, 53.2, 30.9}, {1, 56.7, 31.5}, {1, 57.0, 31.7},
            {1, 63.5, 31.9}, {1, 65.3, 32.0}, {1, 71.1, 32.1},
            {1, 77.0, 32.5}, {1, 77.8, 32.9}
        };

        // VECTOR y: {Yield}
        y = {
            251.3, 251.3, 248.3, 267.5, 273.0, 276.5, 270.3, 274.9,
            285.0, 290.0, 297.0, 302.5, 304.5, 309.3, 321.7, 330.7, 349.0
        };
    }

    void calculateParameters() {
        vector<vector<double>> XT = transpose(X);
        vector<vector<double>> XTX = multiply(XT, X);
        vector<vector<double>> XTX_inv = inverse3x3(XTX);
        
        vector<vector<double>> y_matrix(y.size(), vector<double>(1));
        for(size_t i=0; i<y.size(); i++) y_matrix[i][0] = y[i];

        vector<vector<double>> XTy = multiply(XT, y_matrix);
        vector<vector<double>> Beta = multiply(XTX_inv, XTy);

        b0 = Beta[0][0];
        b1 = Beta[1][0];
        b2 = Beta[2][0];
    }

    void printEquation() {
        cout << "\n=== Modelo de Regresion Multiple ===" << endl;
        cout << "Ecuacion resultante:" << endl;
        // Imprimiendo con 4 decimales por convencion matematica
        cout << fixed << setprecision(4);
        cout << "Yield = " << b0 << " + (" << b1 << " * Factor_1) + (" << b2 << " * Factor_2)" << endl;
    }

    void simulate() {
        cout << "\n=== Simulacion de 5 Experimentos Desconocidos ===" << endl;
        
        // 5 Valores elegidos arbitrariamente dentro y ligeramente fuera del rango del DataSet
        double test_x1[] = {45.0, 55.0, 60.0, 75.0, 80.0};
        double test_x2[] = {29.5, 31.0, 31.5, 32.0, 33.5};

        for(int i=0; i<5; i++) {
            double predicted_yield = b0 + (b1 * test_x1[i]) + (b2 * test_x2[i]);
            cout << "Experimento " << i+1 
                 << " -> Factor 1 (x1): " << test_x1[i] 
                 << ", Factor 2 (x2): " << test_x2[i] 
                 << " | Yield predicho: " << predicted_yield << endl;
        }
        cout << endl;
    }
};

int main() {
    LeastSquaredRegressor model;
    model.calculateParameters();
    model.printEquation();
    model.simulate();
    return 0;
}