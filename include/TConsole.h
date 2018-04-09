#ifndef TCONSOLE_H
#define TCONSOLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <mutex>

#include "TObserver.h"
#include "TCommandProcessor.h"
#include "TBlockProcessor.h"
/*!
    ����� ��� ���������� ����� ������ �� �������
*/
class TConsole
{
    public:
        TConsole(size_t bulk_size);
        virtual ~TConsole();

        void addToBuffer(const char* buffer, const size_t buf_size);

        void finish();
    protected:

    private:
        std::mutex  _mutex;

        std::string _input;

        //  ����������� ��� ������
        std::vector <ptrObserver>   _observers;
};

#endif // TCONSOLE_H
