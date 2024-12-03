#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Esta función se utiliza para establecer las condiciones de frontera
    void setCondicFront(const vector<vector<double>>& condicFront) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (condicFront[i][j] != -1) {
                    phi[i][j] = condicFront[i][j];
                }
            }
        }
    }

    // Ahora para resolver el sistema utilizando el método de Gauss-Seidel
    bool solve() {
        int iter = 0;
        vector<vector<double>> phi_old = phi; // Se guarda la malla anterior para verificar que exista convergencia

        while (iter < maxIter) {
            bool converged = true;

            // Se itera sobre todos los puntos de la malla, con excepción de los bordes
            for (int i = 1; i < m - 1; ++i) {
                for (int j = 1; j < n - 1; ++j) {
                    if (phi[i][j] == 0) continue; 

                    double phi_new = 0.25 * (phi[i + 1][j] + phi[i - 1][j] + phi[i][j + 1] + phi[i][j - 1]);
                    phi[i][j] = phi_new;

                    // Se verifica la convergencia
                    double change = fabs(phi[i][j] - phi_ant[i][j]);
                    if (change > tolerance) {
                        converged = false;
                    }
                }
            }

            // Ahora se verifica la convergencia global
            if (converged) {
                cout << "Convergencia alcanzada en " << iter + 1 << " iteraciones." << endl;
                return true;
            }

            // Se copia la malla actual a la malla anterior para la siguiente iteración
            phi_old = phi;
            iter++;
        }

        cout << "No se alcanzó la convergencia después de " << maxIter << " iteraciones." << endl;
        return false;
    }

    // Se imprime la malla de potenciales
    void printSolution() const {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << std::fixed << std::setprecision(4) << phi[i][j] << " ";
            }
            cout << endl;
        }
    }
