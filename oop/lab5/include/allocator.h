#include <iostream>
#include <array>
#include <cstdint>
#include <vector>

namespace lab5 {

template<class T>
class BinAllocator {
private:
    static constexpr size_t N = 10;
    static constexpr size_t maxCount = (1 << N) * (N + 1);
    char *_buffer;

    std::array<size_t, N + 1> bucketCounts;
    std::array<std::vector<void*>, N + 1> buckets;

    size_t getBucketCountByPointer(void * vptr) {
        char * ptr = static_cast<char*>(vptr);
        char * left = _buffer;
        char * right = _buffer + (1 << N) * sizeof(T);
        if (ptr >= left && ptr < right) {
            return 0;
        }
        for (size_t i = 1; i < N + 1; i++) {
            left = right;
            right = left + (1 << N) * sizeof(T);
            if (ptr >= left && ptr < right) {
                return i;
            }
        }
        return N + 1;
    }
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    BinAllocator() {
        _buffer = new char[maxCount * sizeof(T)];
        char *curPtr = _buffer;
        for (size_t i = 0; i < N + 1; i++) {
            bucketCounts[i] = (1 << (N - i));
            buckets[i].resize(bucketCounts[i]);
            for (size_t j = 0; j < bucketCounts[i]; j++) {
                buckets[i][j] = curPtr;
                curPtr = curPtr + (1 << i) * sizeof(T);
            }
        }
    }

    ~BinAllocator() {
        delete[] _buffer;
    }

    template<class U>
    struct rebind {
        using value = BinAllocator<U>;
    };

    // MEOW // ================================================ //

    T* allocate(size_t n) {
        if (n == 0) return nullptr;
        for (size_t currentBucket = 0; currentBucket < N + 1; currentBucket++) {
            size_t bucketSize = (1 << currentBucket);
            if (n <= bucketSize && bucketCounts[currentBucket] != 0) {
                return static_cast<T*>(buckets[currentBucket][--bucketCounts[currentBucket]]);
            }
        }
        return nullptr;
    }

    void deallocate(T *pointer, size_t) {
        size_t bucketNum = getBucketCountByPointer(pointer);
        if (bucketNum == N + 1) {
            throw std::invalid_argument("This pointer not from allocator's buffer.");
        }
        buckets[bucketNum][bucketCounts[bucketNum]++] = pointer;
    }

    // MEOW END // ============================================ //

    template <typename U, typename... Args>
    void construct(U *p, Args &&...args) {
        new (p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }

};

template <class T, class U>
constexpr bool operator==(const BinAllocator<T> &lhs, const BinAllocator<U> &rhs)
{
    return true;
}

template <typename T, typename U, size_t BLOCK_COUNT>
constexpr bool operator!=(const BinAllocator<T> &lhs, const BinAllocator<U> &rhs)
{
    return false;
}

}
