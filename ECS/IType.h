#pragma once
#include <string>
#include <iostream>

namespace gecs {
    /**
     * @brief A templated class representing an index-like object.
     *
     * This class provides functionality for creating and manipulating index-like objects.
     *
     * @tparam T The underlying type of the index.
     * @tparam _Type The type of the index-like object.
     * @tparam NULL_VALUE The null value of the index.
     */
    template <typename T, typename _Type, T NULL_VALUE = static_cast<T>(-1)>
    struct IType {
        using ValueType = T;
        enum : T {
            kNull = NULL_VALUE
        };

        template <typename T1>
        [[nodiscard]] static constexpr _Type make(T1&& t) noexcept {
            _Type result;
            result.value_ = static_cast<T>(t);
            return result;
        }

        [[nodiscard]] static constexpr _Type make(T t) noexcept {
            _Type result;
            result.value_ = t;
            return result;
        }

        explicit constexpr IType(IType&& v) noexcept :
            value_{ v.value_ } {
        }

        explicit constexpr IType(const IType& v) noexcept :
            value_{ v.value_ } {
        }

        explicit constexpr IType(T v) noexcept :
            value_{ v } {
        }

        IType& operator=(const IType& rhs) noexcept {
            value_ = rhs.value_;
            return *this;
        }

        IType& operator=(IType&& rhs) noexcept {
            value_ = rhs.value_;
            return *this;
        }

        template <typename T1 = T>
        [[nodiscard]] constexpr T1 toInt() const noexcept {
            return static_cast<T1>(value_);
        }

        [[nodiscard]] static constexpr _Type null() noexcept {
            return make(kNull);
        }

        //constexpr IType() = default;
        constexpr IType() noexcept = default;

        [[nodiscard]] constexpr bool isValid() const {
            return value_ != kNull;
        }

        [[nodiscard]] constexpr bool isNull() const {
            return value_ == kNull;
        }

        [[nodiscard]] constexpr bool operator <(const IType& rhs) const noexcept {
            return value_ < rhs.value_;
        }

        [[nodiscard]] constexpr bool operator >(const IType& rhs) const noexcept {
            return value_ > rhs.value_;
        }

        [[nodiscard]] constexpr bool operator <=(const IType& rhs) const noexcept {
            return value_ <= rhs.value_;
        }

        [[nodiscard]] constexpr bool operator >=(const IType& rhs) const noexcept {
            return value_ >= rhs.value_;
        }

        [[nodiscard]] constexpr bool operator ==(const IType& rhs) const noexcept {
            return value_ == rhs.value_;
        }

        [[nodiscard]] constexpr bool operator !=(const IType& rhs) const noexcept {
            return value_ != rhs.value_;
        }
        [[nodiscard]] constexpr _Type next() const noexcept {
            return _Type::make(value_ + 1);
        }

        constexpr _Type& operator++() noexcept {
            ++value_;
            return *static_cast<_Type*>(this);
        }

        constexpr _Type operator++(int) noexcept {
            _Type copy = _Type::make(value_);
            ++value_;
            return copy;
        }

        // Hash function
        std::size_t hash() const noexcept {
            return std::hash<T>()(value_);
        }

        std::string toString() const {
            return std::to_string(value_); 
        }

       /* struct Hash {
            size_t operator()(const T& tag) const noexcept {
                return tag.toInt<size_t >();
            }
        };*/

        std::size_t operator()(const T& type) const {
            return static_cast<std::size_t>(type);
        }
    protected:
        T value_{ kNull };
    };

    /*template <typename T>
    struct ITypeHash {
        size_t operator()(const T& tag) const noexcept {
            return tag.toInt<size_t >();
        }
    };*/

    template <typename T, typename _Type, T NULL_VALUE = static_cast<T>(-1)>
    struct ITypeHash {
        size_t operator()(const IType<T, _Type, NULL_VALUE>& tag) const noexcept {
            return tag.toInt<size_t>();
        }
    };


    
    /* std::size_t operator()(const T& type) const {
     return static_cast<std::size_t>(type);
 }*/

    //template <typename T, typename _Type, T NULL_VALUE = static_cast<T>(-1)>
    //struct IType {
    //    using ValueType = T;
    //    enum : T {
    //        kNull = NULL_VALUE
    //    };

    //    template <typename T1>
    //    [[nodiscard]] static constexpr _Type make(T1&& t) noexcept {
    //        _Type result;
    //        result.value_ = static_cast<T>(t);
    //        return result;
    //    }

    //    [[nodiscard]] static constexpr _Type make(T t) noexcept {
    //        _Type result;
    //        result.value_ = t;
    //        return result;
    //    }

    //    explicit constexpr IType(IType&& v) noexcept :
    //        value_{ v.value_ } {
    //    }

    //    explicit constexpr IType(const IType& v) noexcept :
    //        value_{ v.value_ } {
    //    }

    //    explicit constexpr IType(T v) noexcept :
    //        value_{ v } {
    //    }

    //    IType& operator=(const IType& rhs) noexcept {
    //        value_ = rhs.value_;
    //        return *this;
    //    }

    //    IType& operator=(IType&& rhs) noexcept {
    //        value_ = rhs.value_;
    //        return *this;
    //    }

    //    template <typename T1 = T>
    //    [[nodiscard]] constexpr T1 toInt() const noexcept {
    //        return static_cast<T1>(value_);
    //    }

    //    [[nodiscard]] static constexpr _Type null() noexcept {
    //        return make(kNull);
    //    }

    //    constexpr IType() = default;
    //    [[nodiscard]] constexpr bool isValid() const {
    //        return value_ != kNull;
    //    }

    //    [[nodiscard]] constexpr bool isNull() const {
    //        return value_ == kNull;
    //    }

    //    [[nodiscard]] constexpr bool operator <(const IType& rhs) const noexcept {
    //        return value_ < rhs.value_;
    //    }

    //    [[nodiscard]] constexpr bool operator >(const IType& rhs) const noexcept {
    //        return value_ > rhs.value_;
    //    }

    //    [[nodiscard]] constexpr bool operator <=(const IType& rhs) const noexcept {
    //        return value_ <= rhs.value_;
    //    }

    //    [[nodiscard]] constexpr bool operator >=(const IType& rhs) const noexcept {
    //        return value_ >= rhs.value_;
    //    }

    //    [[nodiscard]] constexpr bool operator ==(const IType& rhs) const noexcept {
    //        return value_ == rhs.value_;
    //    }

    //    [[nodiscard]] constexpr bool operator !=(const IType& rhs) const noexcept {
    //        return value_ != rhs.value_;
    //    }
    //    [[nodiscard]] constexpr _Type next() const noexcept {
    //        return _Type::make(value_ + 1);
    //    }

    //    constexpr _Type& operator++() noexcept {
    //        ++value_;
    //        return *static_cast<_Type*>(this);
    //    }

    //    constexpr _Type operator++(int) noexcept {
    //        _Type copy = _Type::make(value_);
    //        ++value_;
    //        return copy;
    //    }


    //    std::string toString() const {
    //        return std::to_string(value_); // + ...
    //    }

    //    size_t hash() const {
    //        return std::hash<std::string>()(toString());
    //    }

    //    /*std::size_t operator()(const T& type) const {
    //        return static_cast<std::size_t>(type);
    //    }*/

    //protected:
    //    T value_{ kNull };
    //};

    //template <typename T>
    //struct ITypeHash {
    //    std::size_t operator()(const T& type) const {
    //        return static_cast<std::size_t>(type.toInt());
    //    }
    //};
    //
};

//namespace std {
//    // Define a hash function for any type derived from IType
//    template<typename T, typename _Type, T NULL_VALUE>
//    struct hash<gecs::IType<T, _Type, NULL_VALUE>> {
//        std::size_t operator()(const gecs::IType<T, _Type, NULL_VALUE>& obj) const noexcept {
//            return std::hash<T>{}(obj.toInt());
//        }
//    };
//};