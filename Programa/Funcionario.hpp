#ifndef PESSOA_H
#define PESSOA_H

#include "CPFInvalidoException.hpp"
#include "EnumTipoFuncionario.hpp"

#include <string>

namespace sistema
{

class Funcionario
{
    public:
        Funcionario();
        explicit Funcionario(const std::string nome, const long cpf, const int idade, const int salario, const int cargo);
        virtual ~Funcionario();

        long getCPF() const;
        void setCPF(const long cpf);

        std::string getNome() const;
        void setNome(const std::string nome);

        int getIdade() const;
        void setIdade(const int idade);

        int getSalario() const;
        void setSalario(const int salario);

        int getCargo() const;
        void setCargo(const int cargo);

        bool operator==(const Funcionario &funcionario) const; //sobrecarga e operador
        bool operator!=(const Funcionario &funcionario) const; //sobrecarga e operador

        void imprimirFuncionario() const;

    private:
        bool validarCPF(long cpf);

        std::string nome;
        long cpf;
        int idade;
        int salario;
        int cargo;
};

} // namespace sistema

#endif