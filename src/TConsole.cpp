#include "TConsole.h"

TConsole::TConsole(size_t bulk_size):
    _mutex(),
    _input(""),
    _observers()
{
    //  Создать класс
    //  Создать обработчики
    _observers.push_back(std::make_shared<TCommandProcessor>(static_cast<void*>(this), bulk_size));
    _observers.push_back(std::make_shared<TBlockProcessor>(this));
    //ctor
}

TConsole::~TConsole()
{
    //  Обработка завершения ввода
    //  Удаление обработчиков
    //dtor
}

void TConsole::addToBuffer(const char* buffer, const size_t buf_size){
        std::lock_guard<std::mutex> guard(_mutex);

        _input.append(buffer, buf_size);

        for (auto posNewLine = _input.find("\n");
             posNewLine!= std::string::npos;
             posNewLine = _input.find("\n"))
        {
            std::string command = _input.substr(0, posNewLine);
            _input.erase(0, posNewLine+1);
            try{
                //  В обработчиках могут быть проблемы. На всякий сдучай обернём
                std::for_each(_observers.begin(), _observers.end(),[command](auto ptrProcessor){
                        ptrProcessor->parseCommand(command);
                        }
                );
                //command.clear();
            }catch(std::exception e){
                std::cerr << "Exception in observer! " << e.what() << std::endl;
            }
            catch(...){
                std::cerr << "Unknown exception in observer! " << std::endl;
            }
        };
}
