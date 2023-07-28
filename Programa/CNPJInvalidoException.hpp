#ifndef CNPJ_INVALIDO_EXCEPTION
#define CNPJ_INVALIDO_EXCEPTION

#include <stdexcept>

namespace sistema
{

class CNPJInvalidoException : public std::runtime_error{
    public:
        CNPJInvalidoException(const std::string cnpj);
        virtual ~CNPJInvalidoException() = default;

        const std::string cnpj;
};

} // namespace sistema

#endif