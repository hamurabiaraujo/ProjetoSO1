#include "mainwindow.h"
#include "ui_mainwindow.h"

//Ativado quando o texto no campo 'Número de Iterações" é modificado,
//verifica se o valor informado é válido.
void MainWindow::on_numeroIteracoes_textChanged(const QString &arg1)
{
    entrouComNumeroIteracoes = true;
    if (ui->numeroIteracoes->text().toInt() <= 0){
        ui->numeroIteracoes->setText("");
        entrouComNumeroIteracoes = false;
    }
}

//Ativado após o preenchimento do campo "Dimensão",
//ou seja depois que preenche o campo e dá um enter ou clica em outro componente,
//verifica se os valores informados são válidos.
void MainWindow::on_dimensao_editingFinished()
{
    entrouComDimensao = true;
    QStringList aux = ui->dimensao->text().split(":");
    if ( (aux.size() < 3) || (aux.at(0).toInt() <= 0 || aux.at(1).toInt() <= 0 || aux.at(2).toInt() <= 0) ){
        ui->dimensao->setText("");
        entrouComDimensao = false;
    }
}

void MainWindow::selectSort(){
    int menor = 0, aux = 0;
    int tamanho = vetorSelectSort.size();

    for (int i = 0; i < tamanho; i++){
        menor = i;
        for (int j = (i + 1); j < tamanho; j++){
            if (vetorSelectSort[j] < menor){
                menor = j;
            }
        }
        if (menor != i){
            aux = vetorSelectSort[menor];
            vetorSelectSort[menor] = vetorSelectSort[i];
            vetorSelectSort[i] = aux;
        }
    }
}

//Algoritmos de ordenacao bubble sort
void MainWindow::bubbleSort() {
  int aux = 0;
  int tamanho = vetorBubbleSort.size();

  for (int i = 0; i < tamanho-1; i++) {
     for (int j = 0; j < tamanho-1; j++) {
        if (vetorBubbleSort[j] > vetorBubbleSort[j+1]) {
          aux = vetorBubbleSort[j];
          vetorBubbleSort[j] = vetorBubbleSort[j+1];
          vetorBubbleSort[j+1] = aux;
        }
     }
  }
}

void MainWindow::quickSort(int esquerda, int direita)
{
    int i, j, x, y;
    i = esquerda;
    j = direita;
    x = vetorQuickSort[(esquerda + direita) / 2];

    while(i <= j)
    {
        while(vetorQuickSort[i] < x && i < direita)
        {
            i++;
        }
        while(vetorQuickSort[j] > x && j > esquerda)
        {
            j--;
        }
        if(i <= j)
        {
            y = vetorQuickSort[i];
            vetorQuickSort[i] = vetorQuickSort[j];
            vetorQuickSort[j] = y;
            i++;
            j--;
        }
    }
    if(j > esquerda)
    {
        quickSort(esquerda, j);
    }
    if(i < direita)
    {
        quickSort(i, direita);
    }
}

//Observe que os numeros sao gerados aleatorios baseados
//em uma semente. Se for passado a mesma semente, os
//numeros aleatorios serao os mesmos
vector<int> MainWindow::criarVetor(int tamanhoVetor, int semente){
  srand (semente);
  vector<int> novoVetor  = vector<int> (tamanhoVetor);

  for (int i = 0; i < tamanhoVetor; i++){
      novoVetor[i] =  rand() % tamanhoVetor;
  }
  return novoVetor;
}

void MainWindow::calculaTempoQuickSorte(){
    time_t tempo_inicial, tempo_final;
    double aux;
    double desvioPadrao;
    double media;
    ofstream arquivoSaida;
    arquivoSaida.open("saidaQuickSort.txt");

    ui->console->setText(ui->console->toPlainText() + "ALGORITMO QUICKSORT: \n");
    for (int i = 0; i < numeroPassos; i++){
        vetorQuickSort.clear();
        vetorQuickSort = criarVetor(tamanhos[i], sementes[i]);
        aux = 0.0;
        for (int j = 0; j < numeroIteracoes; j++){
            tempo_inicial = time((time_t*)0);
            quickSort(0, (tamanhos[i] - 1));
            tempo_final = time((time_t*)0);
            tempos[j] = (tempo_final - tempo_inicial);
            aux += tempos[j];
            numIteracoes++;
            ui->progressBar->setValue((numIteracoes * 100) / totalIteracoes);
        }
        media = medias[i] = (double) (aux / numeroIteracoes);
        desvioPadrao = calcularDesvioPadrao(tempos, media);
        arquivoSaida << tamanhos[i] << "\t" << (int)media << "\t" << (int)(media - desvioPadrao) << "\t" << (int)(media + desvioPadrao) << "\n";
        ui->console->setText(ui->console->toPlainText() + "PASSO: " + QString::number(i+1) + " Tamanho: "
                             + QString::number(tamanhos[i]) + "\tTempo Médio: " + QString::number(media) + " s \n");
    }
    arquivoSaida.close();
}


//Calcula o desvio padrão de cada passo de execução.
double MainWindow::calcularDesvioPadrao(vector<int> vetorTempos, double media){
    double aux;

    for (int i = 0; i < numeroIteracoes; i++){
        aux += pow((vetorTempos[i] - media), 2);
    }
    aux = aux/numeroIteracoes;
    return sqrt(aux);
}

//Calcula o Tempo de execuções do BubbleSort e já escreve no arquivo de saída.
void MainWindow::calculaTempoBubleSorte(){
    time_t tempo_inicial, tempo_final;
    double aux;
    double desvioPadrao;
    double media;
    ofstream arquivoSaida;
    arquivoSaida.open("saidaBubleSort.txt");
    ui->console->setText(ui->console->toPlainText() + "ALGORITMO BUBBLESORT: \n");

    for (int i = 0; i < numeroPassos; i++){
        vetorBubbleSort.clear();
        vetorBubbleSort = criarVetor(tamanhos[i], sementes[i]);
        aux = 0.0;
        for (int j = 0; j < numeroIteracoes; j++){
            tempo_inicial = time((time_t*)0);
            bubbleSort();
            tempo_final = time((time_t*)0);
            tempos[j] = (tempo_final - tempo_inicial);
            aux += tempos[j];
            numIteracoes++;
            ui->progressBar->setValue((numIteracoes * 100) / totalIteracoes);
        }
        media = medias[i] = (double) (aux / numeroIteracoes);
        desvioPadrao = calcularDesvioPadrao(tempos, media);
        arquivoSaida << tamanhos[i] << "\t" << (int)media << "\t" << (int)(media - desvioPadrao) << "\t" << (int)(media + desvioPadrao) << "\n";
        ui->console->setText(ui->console->toPlainText() + "PASSO: " + QString::number(i+1) + " Tamanho: "
                             + QString::number(tamanhos[i]) + "\tTempo Médio: " + QString::number(media) + " s \n");
    }
    arquivoSaida.close();
}

void MainWindow::calculaTempoSelectSort(){
    time_t tempo_inicial, tempo_final;
    double aux;
    double desvioPadrao;
    double media;
    ofstream arquivoSaida;
    arquivoSaida.open("saidaSelectSort.txt");
    ui->console->setText(ui->console->toPlainText() + "ALGORITMO SELECTSORT: \n");

    for (int i = 0; i < numeroPassos; i++){
        vetorSelectSort.clear();
        vetorSelectSort = criarVetor(tamanhos[i], sementes[i]);
        aux = 0.0;
        for (int j = 0; j < numeroIteracoes; j++){
            tempo_inicial = time((time_t*)0);
            selectSort();
            tempo_final = time((time_t*)0);
            tempos[j] = (tempo_final - tempo_inicial);
            aux += tempos[j];
            numIteracoes++;
            ui->progressBar->setValue((numIteracoes * 100) / totalIteracoes);
        }
        media = medias[i] = (double) (aux / numeroIteracoes);
        desvioPadrao = calcularDesvioPadrao(tempos, media);
        arquivoSaida << tamanhos[i] << "\t" << (int)media << "\t" << (int)(media - desvioPadrao) << "\t" << (int)(media + desvioPadrao) << "\n";
        ui->console->setText(ui->console->toPlainText() + "PASSO: " + QString::number(i+1) + " Tamanho: "
                             + QString::number(tamanhos[i]) + "\tTempo Médio: " + QString::number(media) + " s \n");
    }
    arquivoSaida.close();
}

//Efetua a validações das entradas do usuário
//e mostra mensagens caso necessário
bool MainWindow::validacao(){
    escolheuOrdenacao = ui->checkBox->isChecked() || ui->checkBox_2->isChecked() || ui->checkBox_3->isChecked();

    bool contemEntradasValidas = entrouComDimensao && entrouComNumeroIteracoes && escolheuOrdenacao;

    if (!contemEntradasValidas){
        if (!entrouComNumeroIteracoes){
            QMessageBox::information(this,
              "Mensagem",
              tr("Entre com o Número de Iterações!"));
        }else if (!entrouComDimensao){
            QMessageBox::information(this,
                "Mensagem",
                tr("Entre com as Dimensões!"));
        }else{
            QMessageBox::information(this,
                "Mensagem",
                tr("Escolha pelo menos um Algoritmo de Ordenação!"));
        }
    }
    return contemEntradasValidas;
}


//Inicializa as variáveis do programa
void MainWindow::iniciar(){

    time_t tempo_inicial, tempo_final;

    if (!validacao()){
        return;
    }else{
        ui->console->setText(ui->console->toPlainText() + "INICIANDO... \n");
        tempo_inicial = time((time_t*)0);
        numIteracoes = 0;
        numeroIteracoes = MainWindow::ui->numeroIteracoes->text().toInt();
        dimensao = MainWindow::ui->dimensao->text();
        aux = dimensao.split(":");
        tamanhoInicial = aux.at(0).toInt();
        passo = aux.at(1).toInt();
        tamanhoFinal = aux.at(2).toInt();
        numeroPassos = ((tamanhoFinal-tamanhoInicial)/passo) + 1;

        tamanhos = vector<int> (numeroPassos);
        sementes = vector<int> (numeroPassos);
        tempos = vector<int> (numeroIteracoes);
        medias = vector<double> (numeroPassos);


        tamanhos[0] = tamanhoInicial;
        sementes[0] = ( rand() % (tamanhoFinal * 2) );

        for (int i = 1; i < numeroPassos ; i++){
            tamanhos[i] = ( tamanhoInicial + (passo * i) );
            sementes[i] = ( rand() % (tamanhoFinal * 2) );
        }

        bool selecionouQuickSort = ui->checkBox->isChecked();
        bool selecionouSelectSort = ui->checkBox_3->isChecked();
        bool selecionouBubbleSort = ui->checkBox_2->isChecked();

        if (selecionouBubbleSort && selecionouQuickSort && selecionouSelectSort)
        {
            totalIteracoes = (3 * (numeroPassos * numeroIteracoes ));
            calculaTempoBubleSorte();
            calculaTempoSelectSort();
            calculaTempoQuickSorte();
        }
        else if ( (selecionouBubbleSort && selecionouQuickSort) || (selecionouBubbleSort && selecionouSelectSort) || (selecionouQuickSort && selecionouSelectSort) )
            {
                totalIteracoes = (2 * (numeroPassos * numeroIteracoes));
                if (selecionouBubbleSort && selecionouQuickSort)
                {
                    calculaTempoBubleSorte();
                    calculaTempoQuickSorte();
                }
                else if (selecionouBubbleSort && selecionouSelectSort)
                {
                    calculaTempoSelectSort();
                    calculaTempoBubleSorte();
                }else
                {
                    calculaTempoSelectSort();
                    calculaTempoQuickSorte();
                }
        }
        else
        {
            totalIteracoes = (numeroPassos * numeroIteracoes);
            if (selecionouBubbleSort)
                calculaTempoBubleSorte();
            if (selecionouQuickSort)
                calculaTempoQuickSorte();
            if (selecionouSelectSort)
                calculaTempoSelectSort();

        }
        tempo_final = time((time_t*)0);
        int tempoTotalExecucao = tempo_final - tempo_inicial;

        QString mensagem = "Fim de Execução!\n Tempo total de execução = " + QString::number(tempoTotalExecucao) + " segundos.";

        QMessageBox::information(this,
          "Mensagem",
          mensagem);
    }
}

//Reseta as variáveis do Programa
void MainWindow::reset(){
    vetorBubbleSort.clear();
    vetorQuickSort.clear();
    sementes.clear();
    tamanhos.clear();
    medias.clear();
    tempos.clear();
    ui->console->setText("");
}

//Ativado quando clica-se no botão 'Executar'
void MainWindow::on_executar_clicked()
{
    reset();
    iniciar();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->console->setText("");
}
