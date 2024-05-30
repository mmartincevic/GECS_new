#include "IDFactory.h"

namespace gecs {

    // Initialize static members
    IdFactory IdFactory::instance;
    std::mutex IdFactory::mtx;

    IdFactory::IdFactory() : currentId(0) {}

    IdFactory& IdFactory::getInstance() {
        return instance;
    }

    uint32_t IdFactory::getNextId() {
        std::lock_guard<std::mutex> lock(mtx);
        return ++currentId;
    }

    void IdFactory::Reset() {
        std::lock_guard<std::mutex> lock(mtx);
        currentId = 0;
    }

} // namespace gecs