/**
    Estrutura inicial para um jogo de labirinto
    versão: 0.1 (Felski)

    Trabalho M1 - Bomberman | Disciplina: Algoritimos e Programacao ||
    Integrantes do Grupo: Felipe Muller Schuvuchov;
                          Gabriel Pavan Marquevicz;
                          Luidgi De Carvalho Poffo;
*/
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

    void imprimir(int x, int y, int m[11][15]) {
        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<11;i++){
            for(int j=0;j<15;j++){
                if(i==x&& j==y) {
                    if(m[x][y] == 3) {
                        cout<<char(2);
                    } else {
                    cout<<char(1); //personagem
                    }
                } else {
                    switch (m[i][j]){
                        case 0: cout<<" "; break; //caminho
                        case 1: cout<<char(219); break; //parede
                        case 2: cout<<char(177); break; //parede quebravel
                        case 3: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
						cout<<char(169); break; //bomba
                        case 4: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
						cout<<char(244); break; // inimigo
                        case 5: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14); 
						cout<<char(42); break; // explosao bomba

                        //default: cout<<"-"; //erro
                    } //fim switch
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                }
            }
            cout<<"\n";
        }
    }

void movimento(int &x, int &y, int m[11][15], bool &bombaAtiva,char &tecla, int &bombaX, int &bombaY, clock_t &tempoBomba, clock_t &fim) {
        if ( _kbhit() ){
            tecla = getch();
            switch(tecla)
            {
                case 72: case 'w': ///cima
                    if(m[x-1][y]!=2 && m[x-1][y]!=1){
                        x--;
                    }
                break;
                case 80: case 's': ///baixo
                    if(m[x+1][y]!=2 && m[x+1][y]!=1){
                        x++;
                    }
                break;
                case 75:case 'a': ///esquerda
                    if(m[x][y-1]!=2 && m[x][y-1]!=1){
                        y--;
                    }
                break;
                case 77: case 'd': ///direita
                    if(m[x][y+1]!=2 && m[x][y+1]!=1){
					    y++;
                    }
                break;
                case 'g':
                if (!bombaAtiva) { // Verifica se a bomba não está ativa
                        bombaAtiva = true;
                        bombaX = x;
                        bombaY = y;
                        tempoBomba = (fim / CLOCKS_PER_SEC) + 5;
                        m[x][y] = 3;
                }
                break;
            }
         }
    }

void moverInimigos(int inimigoX[], int inimigoY[], int m[11][15], int numInimigos, bool inimigoVivo[]) {
    for (int i = 0; i < numInimigos; i++) {
        if(inimigoVivo[i] == true) {
            int movimentos = rand() % 3 + 1; // Movimento aleatório de 1 a 3 posições

            for (int j = 0; j < movimentos; j++) {
                int direcao = rand() % 4;
                int novoX = inimigoX[i];
                int novoY = inimigoY[i];

                switch (direcao) {
                    case 0: // CIMA
                        if (m[inimigoX[i] - 1][inimigoY[i]] != 2 && m[inimigoX[i] - 1][inimigoY[i]] != 1) {
                            novoX--;
                        }
                        break;
                    case 1: // BAIXO
                        if (m[inimigoX[i] + 1][inimigoY[i]] != 2 && m[inimigoX[i] + 1][inimigoY[i]] != 1) {
                            novoX++;
                        }
                        break;
                    case 2: // Esquerda
                        if (m[inimigoX[i]][inimigoY[i] - 1] != 2 && m[inimigoX[i]][inimigoY[i] - 1] != 1) {
                            novoY--;
                        }
                        break;
                    case 3: // Direita
                        if (m[inimigoX[i]][inimigoY[i] + 1] != 2 && m[inimigoX[i]][inimigoY[i] + 1] != 1) {
                            novoY++;
                        }
                        break;
                }

                // Limpa a posição anterior do inimigo
                m[inimigoX[i]][inimigoY[i]] = 0;
                // Atualiza a nova posição do inimigo
                inimigoX[i] = novoX;
                inimigoY[i] = novoY;
                m[inimigoX[i]][inimigoY[i]] = 4;
            }
        }
    }
}

void explodirBomba(int m[11][15], int &bombaX, int &bombaY, int &InimigosRestantes, int inimigoX[], int inimigoY[], int numInimigos, bool inimigoVivo[]) {
    int radio = 1;
    int explosaoX, explosaoY;

        m[bombaX][bombaY] = 5;
        if(m[bombaX-1][bombaY] == 0 || m[bombaX-1][bombaY] == 2 || m[bombaX-1][bombaY] != 1) { // posiçao cima
            explosaoX = bombaX-1;
            explosaoY = bombaY;
            m[explosaoX][explosaoY] = 5;
        }
        if(m[bombaX+1][bombaY] == 0 || m[bombaX+1][bombaY] == 2 || m[bombaX+1][bombaY] != 1) { //posiçao baixo
            explosaoX = bombaX+1;
            explosaoY = bombaY;
            m[explosaoX][explosaoY] = 5;
        }
        if(m[bombaX][bombaY-1] == 0 || m[bombaX][bombaY-1] == 2 || m[bombaX][bombaY-1] != 1) { // posiçao esquerda
            explosaoX = bombaX;
            explosaoY = bombaY-1;
            m[explosaoX][explosaoY] = 5;
        }
        if(m[bombaX][bombaY+1] == 0 || m[bombaX][bombaY+1] == 2 || m[bombaX][bombaY+1] != 1) { // posiçao direita
            explosaoX = bombaX;
            explosaoY = bombaY+1;
            m[explosaoX][explosaoY] = 5;
        }

        // Verificar se algum inimigo está dentro da área da bomba na hora em que ela explode
                for (int k = 0; k < numInimigos; k++) {
                    if (inimigoVivo[k] == true && inimigoX[k] == explosaoX && inimigoY[k] == explosaoY || inimigoVivo[k] == true && inimigoX[k] == bombaX && inimigoY[k] == bombaY) {
                        InimigosRestantes--; // inimigo morre para a explosao
                        inimigoVivo[k] = false; // marcar o inimigo em especifico como morto
                        m[explosaoX][explosaoY] = 0; // Remover o inimigo do mapa
                    }
                }
        }


int main() {

    int x=1, y=1;    //Posicao inicial do personagem no console
    char tecla;     //Variavel para tecla precionada

    int inimigoX[3], inimigoY[3];
    int numInimigos = 3;
    int InimigosRestantes = numInimigos;
    bool bombaAtiva = false;
    bool explosaoAtiva = false;
    bool inimigoVivo[3];
    int bombaX , bombaY;
    int m[11][15]={ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,1,0,1,0,1,2,1,0,1,0,1,0,1,
                    1,0,0,0,0,0,0,2,0,0,0,0,0,0,1,
                    1,0,1,0,1,0,1,0,1,2,1,0,1,0,1,
                    1,0,0,0,0,2,0,2,0,0,0,0,2,0,1,
                    1,0,1,0,1,2,1,0,1,2,1,0,1,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    for (int i = 0; i < numInimigos; i++) {
        inimigoVivo[i] = true;
    }
    clock_t inicio, fim;
    clock_t tempoBomba = 0;
    clock_t tempoExplosao = 0;
    inicio = clock();

    ///ALERTA: N?O MODIFICAR O TRECHO DE C?DIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR N?O FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR N?O FIQUE PISCANDO NA TELA
        //IN?CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN?CIO DA TELA
        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN?CIO DA TELA
    ///ALERTA: N?O MODIFICAR O TRECHO DE C?DIGO, ACIMA.
    srand(time(NULL));
    
// INIMIGO INICIO
    for (int i = 0; i < numInimigos; i++) {
        do {
            inimigoX[i] = rand()%11;
            inimigoY[i] = rand()%15;
        } while (m[inimigoX[i]][inimigoY[i]] != 0);
            if(m[inimigoX[i]][inimigoY[i]] != 2 && m[inimigoX[i]][inimigoY[i]] != 1) {
                m[inimigoX[i]][inimigoY[i]] = 4;
            }
    }
// INIMIGO FIM
    while(true){

        //bomba(x, y, m, bombaAtiva, bombaX, bombaY, tempoBomba,fim);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // seta o cursor para o inicio da tela
    imprimir(x,y,m); //imprime o mapa, jogador, inimigos, etc

    fim = clock();
    if((fim - inicio) / CLOCKS_PER_SEC == 1) {
    moverInimigos(inimigoX,inimigoY,m,numInimigos,inimigoVivo);
    inicio = clock();
    }
    movimento(x, y, m, bombaAtiva,tecla, bombaX, bombaY, tempoBomba, fim);  ///executa os movimentos

        if (bombaAtiva) {
            if (fim / CLOCKS_PER_SEC >= tempoBomba) {
                bombaAtiva = false; 
                m[bombaX][bombaY] = 0;
                explodirBomba(m,bombaX,bombaY,InimigosRestantes,inimigoX,inimigoY,numInimigos,inimigoVivo);
                tempoExplosao = (fim / CLOCKS_PER_SEC) + 1;
            }
        }
            if (fim / CLOCKS_PER_SEC >= tempoExplosao) {
                for(int i = 0 ; i < 11 ; i++) {
                    for(int j = 0 ; j < 15 ; j++) {
                        if(m[i][j] == 5) {
                        m[i][j] = 0;
                }
            }
        }
    }
    //Colisao do jogador com a explosao da bomba e com os inimigos
    if(m[x][y] == 5 || m[x][y] == 4) { //Condiçao jogador perder
        cout << "Jogo Encerrado, voce perdeu";
        break;
    }
    if(InimigosRestantes == 0) {
        cout << "Voce venceu, conseguiu derrotar todos os inimigos !";
        break;
    }
    } //fim do laço do jogo
    return 0;
} //fim main
