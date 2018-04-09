#ifndef TOBSERVER_H
#define TOBSERVER_H

//#include <async.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <ctime>
#include <fstream>
#include <sstream>
//  Базовый класс для обработки ввода

class TObserver
{
    public:
        //  Управляющие символы
        enum charType{blockStart='{',blockFinish='}'};
        TObserver(void* handle);
        virtual ~TObserver();
        //  Метод вызываемый классом, подключающего обработчики
        void parseCommand(const std::string& input);

        //  Метод, вызываемый, если подана команда
        virtual void handleCommand(const std::string& command) = 0;
        //  Метод вызываемый, если получено начало блока
        virtual void startBlock() = 0;
        //  Метод, вызываемый, если получено окончание блока
        virtual void finishBlock() = 0;

    protected:
        void*    _handle;

    private:
};

//  Указатель на объект обработчика
using ptrObserver = std::shared_ptr<TObserver>;

#endif // TOBSERVER_H
