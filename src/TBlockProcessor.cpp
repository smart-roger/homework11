#include "TBlockProcessor.h"

TBlockProcessor::TBlockProcessor(void* handle):
    TObserver(handle),
    _blockCounter(0),
    _timeStart(0),
    _store()
{
    //ctor
}

TBlockProcessor::~TBlockProcessor()
{
    //dtor
}

void TBlockProcessor::startBlock(){
    if(0==_blockCounter)
        _timeStart = std::time(nullptr);
    ++_blockCounter;
}

void TBlockProcessor::finishBlock(){

    if(0<_blockCounter) --_blockCounter;
    //  ��� ������ ����������� ��� ��������� ����������?
    //else{}

    if(0==_blockCounter){
            _store.printCommands();
            logBlock();
            _store.clear();
    }
}

void TBlockProcessor::handleCommand(const std::string& command){
    if(0<_blockCounter)
        _store.addCommand(command);

    //  ������� �������������� � ������ �����������.
    //  else{}
}

void TBlockProcessor::logBlock(){
    std::stringstream sstream;
    sstream << "bulk"<<_timeStart<<"_"<<_handle<<"_"<<rand()<<".log";
    std::ofstream fileLog(sstream.str());
    _store.printCommands(fileLog);
}
