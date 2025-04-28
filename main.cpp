#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <sstream>

using namespace std;

// Classe Data
class Data {
private:
    int dia;
    int mes;
    int ano;

public:
    Data() : dia(1), mes(1), ano(2000) {}
    Data(int d, int m, int a) : dia(d), mes(m), ano(a) {}

    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAno() const { return ano; }

    void setDia(int d) { dia = d; }
    void setMes(int m) { mes = m; }
    void setAno(int a) { ano = a; }
};

// Classe Contato
class Contato {
private:
    string email;
    string nome;
    string telefone;
    Data dtnasc;

public:
    Contato() : email(""), nome(""), telefone(""), dtnasc() {}
    Contato(string e, string n, string t, Data d) : email(e), nome(n), telefone(t), dtnasc(d) {}

    string getEmail() const { return email; }
    string getNome() const { return nome; }
    string getTelefone() const { return telefone; }
    Data getDataNascimento() const { return dtnasc; }

    void setEmail(string e) { email = e; }
    void setNome(string n) { nome = n; }
    void setTelefone(string t) { telefone = t; }
    void setDataNascimento(Data d) { dtnasc = d; }

    int idade() const {
        time_t t = time(0);
        tm* agora = localtime(&t);
        int anoAtual = agora->tm_year + 1900;
        return anoAtual - dtnasc.getAno();
    }
};

// Função para formatar nome em citação bibliográfica
string formatarNome(string nome) {
    stringstream ss(nome);
    vector<string> palavras;
    string palavra;

    // Separar nome completo em palavras
    while (ss >> palavra) {
        palavras.push_back(palavra);
    }

    if (palavras.size() < 2) return nome; // Caso não tenha sobrenome

    // Último nome (sobrenome) fica em maiúsculas
    string sobrenome = palavras.back();
    transform(sobrenome.begin(), sobrenome.end(), sobrenome.begin(), ::toupper);

    // Primeiro nome e nomes do meio abreviados
    string nomeFormatado = sobrenome + ", " + palavras[0][0] + ".";
    for (size_t i = 1; i < palavras.size() - 1; i++) {
        nomeFormatado += " " + std::string(1, palavras[i][0]) + ".";
    }

    return nomeFormatado;
}

int main() {
    Contato contatos[10]; // Agora com 10 contatos

    cout << "=== Cadastro de 10 contatos ===\n\n";

    for (int i = 0; i < 10; i++) {
        string nome, email, telefone;
        int dia, mes, ano;

        cout << "Contato " << i + 1 << endl;

        cout << "Digite o nome (sem acento): ";
        getline(cin, nome);

        cout << "Digite o email: ";
        getline(cin, email);

        cout << "Digite o telefone: ";
        getline(cin, telefone);

        cout << "Digite a data de nascimento (dia mes ano): ";
        cin >> dia >> mes >> ano;
        cin.ignore(); // limpa buffer do cin

        Data dataNascimento(dia, mes, ano);
        contatos[i] = Contato(email, nome, telefone, dataNascimento);

        cout << "\n";
    }

    cout << "\n=== Lista de Contatos ===\n\n";

    int somaIdades = 0;
    int maiorIdade = 0;
    vector<Contato> contatosMaisVelhos;
    
    // Média de idades
    for (int i = 0; i < 10; i++) {
        somaIdades += contatos[i].idade();
        if (contatos[i].idade() > maiorIdade) {
            maiorIdade = contatos[i].idade();
            contatosMaisVelhos.clear(); // Limpa a lista de contatos mais velhos
            contatosMaisVelhos.push_back(contatos[i]);
        } else if (contatos[i].idade() == maiorIdade) {
            contatosMaisVelhos.push_back(contatos[i]);
        }
    }

    double mediaIdades = somaIdades / 10.0;
    cout << "Média das idades: " << mediaIdades << " anos\n\n";

    cout << "Contatos com idade maior que a média:\n";
    for (int i = 0; i < 10; i++) {
        if (contatos[i].idade() > mediaIdades) {
            cout << formatarNome(contatos[i].getNome()) << endl;
        }
    }

    // Contagem de contatos maiores de idade (idade >= 18)
    int maioresDeIdade = 0;
    for (int i = 0; i < 10; i++) {
        if (contatos[i].idade() >= 18) {
            maioresDeIdade++;
        }
    }
    cout << "\nQuantidade de contatos maiores de idade: " << maioresDeIdade << endl;

    // Exibir contato(s) mais velho(s)
    cout << "\nContato(s) mais velho(s):\n";
    for (const auto& contato : contatosMaisVelhos) {
        cout << formatarNome(contato.getNome()) << ", " 
             << contato.getEmail() << ", "
             << contato.getTelefone() << endl;
    }

    return 0;
}
