
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_CONTAS = 100;
const int MAX_MOV = 500;

int numeroConta[MAX_CONTAS], tipoConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS], cpf[MAX_CONTAS];
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];

int contaMov[MAX_MOV];
char tipoMov[MAX_MOV];
double valorMov[MAX_MOV];

int qtdContas = 0, qtdMov = 0;

// Busca uma conta pelo numero
int buscar(int numero) {
    for (int i = 0; i < qtdContas; i++) {
        if (numeroConta[i] == numero && contaAtiva[i])
            return i;
    }
    return -1;
}

// Registra uma movimentacao
void registrar(int conta, char tipo, double valor) {
    contaMov[qtdMov] = conta;
    tipoMov[qtdMov] = tipo;
    valorMov[qtdMov] = valor;
    qtdMov++;
}

int main() {
    int op;

    cout << fixed << setprecision(2);

    do {
        cout << "\n===== SISTEMA BANCARIO =====\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Listar contas\n";
        cout << "3 - Consultar conta\n";
        cout << "4 - Depositar\n";
        cout << "5 - Sacar\n";
        cout << "6 - Transferir\n";
        cout << "7 - Extrato\n";
        cout << "0 - Sair\n";
        cout << "Opcao: ";
        cin >> op;

        // CADASTRAR
        if (op == 1) {
            int n;

            if (qtdContas >= MAX_CONTAS) {
                cout << "Limite de contas atingido!\n";
                continue;
            }

            cout << "Numero da conta: ";
            cin >> n;

            if (buscar(n) != -1) {
                cout << "Conta ja existe!\n";
                continue;
            }

            numeroConta[qtdContas] = n;

            cout << "Nome: ";
            cin.ignore();
            getline(cin, nomeCliente[qtdContas]);

            cout << "CPF: ";
            getline(cin, cpf[qtdContas]);

            cout << "Tipo (1-Corrente / 2-Poupanca): ";
            cin >> tipoConta[qtdContas];

            cout << "Saldo inicial: ";
            cin >> saldo[qtdContas];

            if (saldo[qtdContas] < 0 ||
                (tipoConta[qtdContas] != 1 && tipoConta[qtdContas] != 2)) {
                cout << "Dados invalidos!\n";
                continue;
            }

            contaAtiva[qtdContas] = true;
            qtdContas++;

            cout << "Conta cadastrada!\n";
        }

        // LISTAR
        else if (op == 2) {
            for (int i = 0; i < qtdContas; i++) {
                if (contaAtiva[i]) {
                    cout << "\nConta: " << numeroConta[i]
                         << "\nCliente: " << nomeCliente[i]
                         << "\nSaldo: R$ " << saldo[i] << "\n";
                }
            }
        }

        // CONSULTAR
        else if (op == 3) {
            int n;
            cout << "Numero da conta: ";
            cin >> n;

            int i = buscar(n);

            if (i == -1)
                cout << "Conta nao encontrada!\n";
            else
                cout << "Cliente: " << nomeCliente[i]
                     << "\nCPF: " << cpf[i]
                     << "\nSaldo: R$ " << saldo[i] << "\n";
        }

        // DEPOSITAR OU SACAR
        else if (op == 4 || op == 5) {
            int n;
            double v;

            cout << "Numero da conta: ";
            cin >> n;

            int i = buscar(n);

            if (i == -1) {
                cout << "Conta nao encontrada!\n";
                continue;
            }

            cout << "Valor: ";
            cin >> v;

            if (v <= 0) {
                cout << "Valor invalido!\n";
                continue;
            }

            if (op == 5 && v > saldo[i]) {
                cout << "Saldo insuficiente!\n";
                continue;
            }

            if (qtdMov >= MAX_MOV) {
                cout << "Historico cheio!\n";
                continue;
            }

            if (op == 4) {
                saldo[i] += v;
                registrar(n, 'D', v);
                cout << "Deposito realizado!\n";
            } else {
                saldo[i] -= v;
                registrar(n, 'S', v);
                cout << "Saque realizado!\n";
            }
        }

        // TRANSFERIR
        else if (op == 6) {
            int origem, destino;
            double v;

            cout << "Conta de origem: ";
            cin >> origem;

            cout << "Conta de destino: ";
            cin >> destino;

            int i = buscar(origem);
            int j = buscar(destino);

            if (i == -1 || j == -1 || i == j) {
                cout << "Contas invalidas!\n";
                continue;
            }

            cout << "Valor: ";
            cin >> v;

            if (v <= 0 || v > saldo[i]) {
                cout << "Valor ou saldo invalido!\n";
                continue;
            }

            if (qtdMov + 2 > MAX_MOV) {
                cout << "Historico cheio!\n";
                continue;
            }

            saldo[i] -= v;
            saldo[j] += v;

            registrar(origem, 'S', v);
            registrar(destino, 'D', v);

            cout << "Transferencia realizada!\n";
        }

        // EXTRATO
        else if (op == 7) {
            int n;
            cout << "Numero da conta: ";
            cin >> n;

            int i = buscar(n);

            if (i == -1) {
                cout << "Conta nao encontrada!\n";
                continue;
            }

            cout << "\n===== EXTRATO =====\n";

            for (int j = 0; j < qtdMov; j++) {
                if (contaMov[j] == n) {
                    if (tipoMov[j] == 'D')
                        cout << "Deposito: R$ " << valorMov[j] << "\n";
                    else
                        cout << "Saque: R$ " << valorMov[j] << "\n";
                }
            }

            cout << "Saldo atual: R$ " << saldo[i] << "\n";
        }

        else if (op != 0) {
            cout << "Opcao invalida!\n";
        }

    } while (op != 0);

    cout << "Programa encerrado!\n";

    return 0;
}
