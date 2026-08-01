#ifndef MAIN_CHANNEL_H
#define MAIN_CHANNEL_H
#include <functional>
#include <mutex>
#include <thread>

#define BUFFER_SIZE 1024

using namespace std;

template <typename T>
class Chan {
private:
    mutex* read_lock = new mutex();
    mutex* write_lock = new mutex();


    const uint32_t max_size = BUFFER_SIZE;
    uint32_t size = 0;
    uint32_t reader_cursor = 0;
    uint32_t writer_cursor = 0;

    T* buffer = new T[this->max_size]; // This might be allways 1024 ?!
public:
    Chan() = default;

    explicit Chan(const uint32_t size): max_size(size) {}

    void send(T val) {
        const lock_guard<mutex> lock(*this->write_lock);

        // Atomic
        while (this->size >= this->max_size) { }

        ++this->size;
        if (this->writer_cursor == this->max_size) this->writer_cursor = 0;
        this->buffer[this->writer_cursor++] = val;
    }

    T recv() {
        const lock_guard<mutex> lock(*this->read_lock);

        // Atomic
        while (this->size <= 0) { }

        --this->size;
        if (this->reader_cursor == this->max_size) this->reader_cursor = 0;
        return buffer[this->reader_cursor++];
    }

    void operator<<(T val) {
        this->send(val);
    }
protected:

};

template <typename T>
void operator<<(T& target, Chan<T> chan) {
    target = chan.recv();
}

void go(const std::function<void()>& fnc);

void go(const std::function<void()>& fnc, std::thread& thread);

#endif //MAIN_CHANNEL_H