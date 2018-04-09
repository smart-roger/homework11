#include "TCommandProcessor.h"

TCommandProcessor::TCommandProcessor(void* handle, size_t bulkSize):
    TObserver(handle),
    _bulkSize(bulkSize),
    _blockCounter(0),
    _store(bulkSize)
{

}

TCommandProcessor::~TCommandProcessor()
{
    //≈сли окончен ввод - надо вывести накопленные команды
    if(!_store.empty()){
        _store.printCommands();
        logBlock();
        _store.clear();
    }
}

void TCommandProcessor::newCommand(const std::string& newCommand){
    if(_store.empty())
        _timeStart = std::time(nullptr);
    _store.addCommand(newCommand);
}

void TCommandProcessor::startBlock(){
    if(0==_blockCounter && 0<_store.size()){
        _store.printCommands();
        logBlock();
        _store.clear();
    }
    ++_blockCounter;
}

void TCommandProcessor::finishBlock(){

    if(0<_blockCounter) --_blockCounter;
    //  „то должно происходить при нарушении синтаксиса?
    //else{}
}

void TCommandProcessor::handleCommand(const std::string& command){
    if(0==_blockCounter)
    {
        newCommand(command);
        if(_bulkSize == _store.size()){
            _store.printCommands();
            logBlock();
            _store.clear();
        }
    }
    //  Ѕлоки обрабатываютс€ в другом наблюдателе.
    //  else{}

}

void TCommandProcessor::logBlock(){
    std::stringstream sstream;
    sstream << "bulk"<<_timeStart<<"_"<<_handle<<"_"<<rand()<<".log";
    std::ofstream fileLog(sstream.str());
    _store.printCommands(fileLog);
}
