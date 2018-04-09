#include "async.h"

#include "TConsole.h"
#include <map>
#include <memory>
#include <cassert>
#include <mutex>
namespace async {

std::mutex  async_mutex;

using TConsolePtr = std::shared_ptr<TConsole>;
using mapConsole = std::map<handle_t, TConsolePtr>;

mapConsole  allConsoles;

handle_t connect(std::size_t bulk) {
    std::lock_guard<std::mutex> lock(async_mutex);
    TConsolePtr newConsole = std::make_shared<TConsole>(bulk);
    handle_t handle = static_cast<void*>(newConsole.get());
    assert(0==allConsoles.count(handle));
    allConsoles[handle] = newConsole;
    return handle;
}

void receive(handle_t handle, const char *data, std::size_t size) {
    std::lock_guard<std::mutex> lock(async_mutex);
    TConsolePtr console = allConsoles.at(handle);
    console->addToBuffer(data, size);
}

void disconnect(handle_t handle) {
    std::lock_guard<std::mutex> lock(async_mutex);
    assert(0!=allConsoles.count(handle));
    allConsoles.erase(handle);
}

}
