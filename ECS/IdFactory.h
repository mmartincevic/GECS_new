#ifndef GECS_IDFACTORY_H
#define GECS_IDFACTORY_H

#pragma once

#include <iostream>
#include <cstdint>
#include <mutex>

namespace gecs {

    class IdFactory {
    private:
        // Private constructor
        IdFactory();

        // Delete copy constructor and assignment operator
        IdFactory(const IdFactory&) = delete;
        IdFactory& operator=(const IdFactory&) = delete;

        // The single instance of the class
        static IdFactory instance;

        // Mutex for thread-safe singleton initialization and ID generation
        static std::mutex mtx;

        // Current ID
        uint32_t currentId;

    public:
        // Method to get the single instance of the class
        static IdFactory& getInstance();

        // Method to get the next ID
        uint32_t getNextId();

        // Method to reset the ID back to 1
        void Reset();
    };

} // namespace gecs

#endif // GECS_IDFACTORY_H