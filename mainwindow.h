#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>
#include <time.h>
#include<iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <vector>


using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    //variaveis globais
    vector<int> vetorBubbleSort;
    vector<int> vetorQuickSort;
    vector<int> vetorSelectSort;
    vector<int> sementes;
    vector<int> tamanhos;
    vector<double> medias;
    vector<int> tempos;
    int numeroIteracoes;
    int tamanhoInicial;
    int passo;
    int tamanhoFinal;
    int totalIteracoes;
    int numeroPassos;
    bool escolheuOrdenacao;
    bool entrouComNumeroIteracoes;
    bool entrouComDimensao;
    QString dimensao;
    QStringList aux;
    int numIteracoes;
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);

private slots:

    void bubbleSort();

    void quickSort(int esquerda, int direita);

    void selectSort();

    vector<int> criarVetor(int tamanhoVetor, int semente);

    void iniciar();

    void on_executar_clicked();

    void calculaTempoBubleSorte();

    void calculaTempoQuickSorte();

    void calculaTempoSelectSort();

    bool validacao();

    void reset();

    double calcularDesvioPadrao(vector<int> vetorTempos, double media);

    void on_numeroIteracoes_textChanged(const QString &arg1);

    void on_dimensao_editingFinished();

    void on_pushButtonMostrarGrafico_clicked();

    void gerarGrafico(bool selecionouQuickSort, bool selecionouSelectSort, bool selecionouBubbleSort, int tempoTotal);

private:
    Ui::MainWindow *ui;
    //Vetores usados pelos metodos de ordenacao

};

#endif // MAINWINDOW_H
