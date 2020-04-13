//
// Created by Luca Sbragi on 05/04/2020.
//

#ifndef UNTITLED4_MATRIX_H
#define UNTITLED4_MATRIX_H

#include <cmath>

template <typename T, int R, int C>
class Matrix{
private:
    int rows, columns;
    T** A;
    T** I;
    T** B;  //Martrice [A|I] che servirà per il calcolo dell'inversa
    T** Inv; //Matrice inversa
    T** Transposed; //Matrice trasposta
    T** sub_m; //Matrice per la sottomatrice del determinante

public:
    Matrix();
    ~Matrix();
    bool isSquared(); //Metodo per vedere se la matrice è quadrata
    T insertValue(); //Metodo per inserire i valori da tastiera
    T det(T** A2, T car); //Metodo per calcolare il determinante
    T creationIdentity(); //Metodo per creare la matrice identità
    void stampa(); //Metodo per stampare la matrice
    void createB(); //Metodo per creare la matrice B, che servirà per calcolare l'inversa
    void eliminazioniGauss(); //Metodo per fare le eliminazioni di Gauss, tecnica utilizzata per calcolare la matrice inversa
    void copiaInversa();
    void stampaInversa(); //Metodo per stampare l'inversa
    T transposed(); //Metodo per calcolare la matrice trasposta
    void stampaTransposed();
    void inverse(); //Metodo per calcolare la matrice inversa
    void riprova(); //Metodo per vedere se la matrice inversa appena calcolata è quella giusta
    void stampaRiprova();
    void stampaB();
    void showColumn();
    void showRow();
    T getValue(int x, int y);
    int getCol();
    int getRow();

    int operator==(Matrix&);
    int operator!=(Matrix&);
    Matrix& operator=(Matrix&);
    Matrix& operator+(const Matrix&);
    Matrix& operator-(Matrix&);
    Matrix&operator*(Matrix&);


};

template<typename T, int R, int C>
Matrix<T, R, C>::Matrix() {
    rows = R;   //associo al valore delle righe il valore di R
    columns = C;   //associo al valore delle colonne il valore di C
    std::cout << "Creazione matrice RxC, con R: " << rows << " e C: " << columns << "\n";
    A = new T*[rows];
    for(int i = 0; i < rows; i++){
        A[i] = new T[rows];
    }

    I = new T*[rows];
    for (int i = 0; i < rows ; i++) {
        I[i] = new T[rows];
    }

    B = new T*[rows];
    for(int i = 0; i < rows; i++){
        B[i] = new T[2*rows];
    }

    Inv=new T*[rows];
    for(int i = 0; i < rows; i++){
        Inv[i]=new T[rows];
    }

    Transposed = new T* [rows];
    for(int i = 0; i < rows; i++){
        Transposed[i] = new T[rows];
    }

    sub_m = new T*[rows];
    for(int i = 0; i < rows; i++){
        sub_m[i] = new T[rows];
    }
}

template<typename T, int R, int C>
Matrix<T, R, C>::~Matrix() {
    if(A != 0){
        delete A;
    }

    if(B != 0){
        delete B;
    }

    if(Inv != 0){
        delete Inv;
    }

    if(sub_m != 0){
        delete sub_m;
    }

    if(Transposed != 0){
        delete Transposed;
    }
}

template<typename T, int R, int C>
bool Matrix<T, R, C>::isSquared() {
    if(R == C) {
        std::cout << "La matrice A e' quadrata" << std::endl;
        return true;
    }else {
        std::cout << "La matrice A non e' quadrata\n" << std::endl;
        return false;
    }
}

template<typename T, int R, int C>
T Matrix<T, R, C>::insertValue() {
    std::cout << "----------INSERIMENTO----------\n";
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            std::cout << "Elemento " << "(" << i << ","  << j << "):";
            std::cin >> A[i][j];
        }
    }
    std::cout << "----------FINE INSERIMENTO----------\n";
    stampa();
    return **A;
}

template<typename T, int R, int C>
Matrix<T, R, C> &Matrix<T, R, C>::operator=(Matrix &m) {
    if(m.rows != rows || m.columns != columns){
        throw "noaction";
    }else
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                m.A[i][j] = (T)A[i][j];
            }
        }
    return *this;
}

template<typename T, int R, int C>
int Matrix<T, R, C>::operator==(Matrix &m) {
    if(m.rows != rows || m.columns != columns)
        return 0;
    else
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                if(m.A[i][j] != (T)A[i][j])
                    return 0;
            }
        }
    return 1;
}

template<typename T, int R, int C>
int Matrix<T, R, C>::operator!=(Matrix &m) {
    if(m.rows != rows || m.columns != columns)
        return 1;
    else
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                if(m.A[i][j] != (T)A[i][j])
                    return 1;
            }
        }
    return 0;
}

template<typename T, int R, int C>
Matrix<T, R, C> &Matrix<T, R, C>::operator+(const Matrix &m) {
    if(m.rows != rows || m.columns != columns)
        throw "noaddiction";

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            A[i][j] = (T)A[i][j] + m.A[i][j];
        }
    }
}

template<typename T, int R, int C>
Matrix<T, R, C> &Matrix<T, R, C>::operator-(Matrix &m) {
    if(m.rows != rows || m.columns != columns)
        throw "nosubtraction";

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            A[i][j] = (T)A[i][j] - m.A[i][j];
        }
    }
}

template<typename T, int R, int C>
Matrix<T, R, C> &Matrix<T, R, C>::operator*(Matrix &m) {
    if(m.rows != columns)   //se non vale questo if non posso operare
        throw "nooperation";

    for(int i = 0; i < R; i++){
        for(int j = 0; j < m.C; j++){
            T sum = (T)0;
            for(int k = 0; k < C; k++){
                sum = sum + (T)A[i][k] * m.A[k][j];
            }
            A[i][j] = sum;
        }
    }
}

template<typename T, int R, int C>
T Matrix<T, R, C>::transposed() {
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            Transposed[j][i] = A[i][j];
        }
    }
    stampaTransposed();
    return **Transposed;
}


template<typename T, int R, int C>
T Matrix<T, R, C>::det(T** A2, T car) {
    T determinant = 0;
    if(isSquared() == false)
        std::cout<<"Determinante impossibile da creare!"<<std::endl;
    if(car == 1) {
        determinant == A2[0][0];
        std::cout << "Il determinante e': " << determinant;
    }else if(car == 2){
        determinant = A2[0][0]*A2[1][1] - A2[0][1]*A2[1][0];
        std::cout << "Il determinante e': " << determinant;
    } else{
        for(int row = 0; row < R; row++){
            std::cout << "\nCalcolo la sottomatrice\n";
            for(int i = 0; i < R-1; i++){
                for(int j = 0; j < C-1; j++){
                    int sub_row = (i < row ? i : i+1);
                    int sub_col = j + 1;
                    sub_m[i][j] = A2[sub_row][sub_col];
                }
            }
            if(row % 2 == 0){
                determinant += A2[row][0] * det(sub_m, car-1);
            }else{
                determinant -= A2[row][0] * det(sub_m, car -1);
            }
        }
        std::cout << "\nIl determinante finale e': " << determinant;
    }
    return determinant;
}

template<typename T, int R, int C>
T Matrix<T, R, C>::creationIdentity() {
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(i == j){
                I[i][j] = 1;
            } else{
                I[i][j] = 0;
            }
        }
    }
    return **I;
}

template<typename T, int R, int C>
void Matrix<T, R, C>::stampa() {
    std::cout << "\n----------Stampa matrice A----------\n\n";
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            std::cout << A[i][j] <<"\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n----------Fine stampa----------\n";
}

template<typename T, int R, int C>
void Matrix<T, R, C>::createB() {
    for(int i = 0; i < R; i++) {
        for (int j = 0; j < R; j++) {
            B[i][j] = A[i][j];
        }
    }

    for(int i = 0; i < R; i++) {
        for(int k = R; k < 2*R; k++){
            if(i == k-R){
                B[i][k] = 1;
            } else
                B[i][k] = 0;
        }
    }
    stampaB();
}

template<typename T, int R, int C>
void Matrix<T, R, C>::inverse() {
    if(!this->isSquared() || this->det(A, R) == 0){
        std::cout << "\nInversa impossibile da creare!\n";
    }else{
        eliminazioniGauss();
    }
}

template<typename T, int R, int C>
void Matrix<T, R, C>::eliminazioniGauss() {
    std::cout << "\n----------APPLICO IL METODO DI GAUSS----------\n\n";
    T *tmp;
    tmp = new T[2*R];
    for(int j = 0; j < R-1; j++){
        for(int i = j+1; i < R; i++) {
            if(B[j][j] == 0){
                T *tmp2 = new T[2*R];
                T *tmp3 = new T[2*R];
                if(B[i][j] != 0){
                    for(int k = 0; k < 2*R; k++){
                        tmp2[k] = B[j][k];
                        tmp3[k] = B[i][k];
                    }
                    for(int k = 0; k < 2*R; k++){
                        B[i][k] = tmp2[k];
                        B[j][k] = tmp3[k];
                    }
                }
            }
            if (B[i][j] != 0) {
                T mol = B[i][j] / B[j][j];
                for (int k = 0; k < 2 * R; k++) {
                    tmp[k] = mol * B[j][k];
                }
                for (int k = 0; k < 2 * R; k++){
                    B[i][k] -= tmp[k];
                }
            }if(B[i][i] == 0){
                T *tmp2;
                T *tmp3;
                tmp2 = new T[2*R];
                tmp3 = new T[2*R];


            }
        }
    }
    std::cout << "Faccio l'eliminazione di Gauss sotto la diagonale:\n";
    for(int i = 0; i < R; i++){
        for(int k = 0; k < 2*R; k++){
            std::cout << B[i][k] << "\t";
        }
        std::cout << "\n";
    }
    for(int j = R-1; j > 0; j--) {
        for (int i = j-1; i >= 0; i--){
            if (B[i][j] != 0) {
                T mol = B[i][j] / B[j][j];
                for (int k = 0; k < 2 * R; k++){
                    tmp[k] = mol * B[j][k];
                }
                for (int k = 0; k < 2 * R; k++){
                    B[i][k] -= tmp[k];
                }
            }
        }
    }

    std::cout << "Faccio l'eliminazione di Gauss sopra la diagonale:\n";
    for(int i = 0; i < R; i++){
        for(int k = 0; k < 2*R; k++){
            std::cout << B[i][k] << "\t";
        }
        std::cout << "\n";
    }

    for(int i = 0; i < R; i++) {
        if (B[i][i] != 1) {
            T mol = B[i][i];
            for (int k = 0; k < 2 * R; k++) {
                B[i][k] = B[i][k] / mol;
            }
        }
    }

    std::cout << "Divido per i pivots\n";
    for(int i = 0; i < R; i++){
        for(int k = 0; k < 2*R; k++){
            std::cout << B[i][k] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n----------FINE METODO DI GAUSS-----------\n";
    copiaInversa();
}

template<typename T, int R, int C>
void Matrix<T, R, C>::copiaInversa() {
    int k = 0;
    for(int i = 0; i < R; i++) {
        for(int j = R; j < 2*R; j++,k++){
            Inv[i][k]=B[i][j];
        }
        k = 0;
    }
    stampaInversa();
}

template<typename T, int R, int C>
void Matrix<T, R, C>::stampaInversa() {
    std::cout << "\n\n----------MATRICE INVERSA----------\n\n";
    for(int i = 0; i < R; i++){
        for(int j = 0; j < R; j++){
            std::cout << Inv[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n----------FINE INVERSA----------\n\n";
    riprova();
}

template<typename T, int R, int C>
void Matrix<T, R, C>::stampaTransposed() {
    std::cout << "\n----------STAMPA TRASPOSTA----------\n\n";
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            std::cout << Transposed[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n----------FINE STAMPA TRASPOSTA----------\n";
}

template<typename T, int R, int C>
void Matrix<T, R, C>::riprova() {
    for(int i = 0; i < R; i++) {
        for (int j = 0; j < R; j++){
            I[i][j] = 0;
        }
    }
    // Ho azzerato l'inversa per usarla dopo nella riprova

    for(int i = 0; i < R; i++) {
        for (int j = 0; j < R; j++){
            for (int k = 0; k < R; k++){
                I[i][j] += (A[i][k] * Inv[k][j]);
            }
        }
    }
    stampaRiprova();
}

//Se ho calcolato bene la matrice inversa, il risultato di questo metodo sarà la matrice identità
template<typename T, int R, int C>
void Matrix<T, R, C>::stampaRiprova() {
    std::cout  << "\n----------Stampa di A*A^-1----------\n";
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < R; j++){
            std::cout << I[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "----------Fine Stampa di A*A^-1----------\n";
}

template<typename T, int R, int C>
void Matrix<T, R, C>::stampaB() {
    std::cout << "\n----------Affianco la matrice identita'----------\n";
    for(int i = 0; i < R; i++){
        for(int k = 0; k < 2*R; k++){
            std::cout << B[i][k] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n------------------------------\n";
}

template<typename T, int R, int C>
void Matrix<T, R, C>::showRow() {
    for(int i = 0; i < R; i++){
        std::cout << "\nLa riga i: " << i << "\t e' composta da:\n";
        for(int j = 0; j < C; j++){
            std::cout << A[i][j] << "\t";
        }
    }
}

template<typename T, int R, int C>
void Matrix<T, R, C>::showColumn() {
    for(int i = 0; i < R; i++){
        std::cout << "\nLa Colonna i: " << i << "\t e' composta da:\n";
        for(int j = 0; j < C; j++){
            std::cout << A[j][i] << "\n";
        }
    }
}

template<typename T, int R, int C>
T Matrix<T, R, C>::getValue(int x, int y) {
    if(x >= R || y >= C) {
        std::cout << "Attento! Hai inserito un indice che non rispetta i limiti posti\n";
    } else{
        std::cout << "Il valore scelto e':\t" << A[x][y];
    }
    return A[x][y];
}

template<typename T, int R, int C>
int Matrix<T, R, C>::getCol() {
    return C;
}

template<typename T, int R, int C>
int Matrix<T, R, C>::getRow() {
    return R;
}


#endif //UNTITLED4_MATRIX_H
