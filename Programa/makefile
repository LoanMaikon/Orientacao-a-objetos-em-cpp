parametrosCompilacao=-Wall #-Wshadow
nomePrograma = server

all: $(nomePrograma)

$(nomePrograma): main.o Servidor.o Produto.o Funcionario.o Fornecedor.o Menus.o CNPJInvalidoException.o CodigoBarrasInvalidoException.o CPFInvalidoException.o
	g++ -o $(nomePrograma) main.o Servidor.o Produto.o Funcionario.o Fornecedor.o Menus.o CNPJInvalidoException.o CodigoBarrasInvalidoException.o CPFInvalidoException.o $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

Servidor.o: Servidor.hpp Servidor.cpp
	g++ -c Servidor.cpp $(parametrosCompilacao)

Produto.o: Produto.hpp Produto.cpp
	g++ -c Produto.cpp $(parametrosCompilacao)

Funcionario.o: Funcionario.hpp Funcionario.cpp
	g++ -c Funcionario.cpp $(parametrosCompilacao)

Fornecedor.o: Fornecedor.hpp Fornecedor.cpp
	g++ -c Fornecedor.cpp $(parametrosCompilacao)

Menus.o: Menus.hpp Menus.cpp
	g++ -c Menus.cpp $(parametrosCompilacao)

CNPJInvalidoException.o: CNPJInvalidoException.hpp CNPJInvalidoException.cpp
	g++ -c CNPJInvalidoException.cpp $(parametrosCompilacao)

CodigoBarrasInvalidoException.o: CodigoBarrasInvalidoException.hpp CodigoBarrasInvalidoException.cpp
	g++ -c CodigoBarrasInvalidoException.cpp $(parametrosCompilacao)

CPFInvalidoException.o: CPFInvalidoException.hpp CPFInvalidoException.cpp
	g++ -c CPFInvalidoException.cpp $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)