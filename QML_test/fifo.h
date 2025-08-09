#ifndef FIFO_H
#define FIFO_H

#include <QObject>
#include <cstdint>
#include <array>

template <std::size_t Size>
class FIFO {
public:
    FIFO() : head(0), tail(0) {}

    bool isFull() const { return count() == Size; }

    bool isEmpty() const { return head == tail; }

    //Колтчество байт
    std::size_t count() const {
        return (head >= tail) ? (head - tail) : (Size - tail + head);
    }
//Свободное место
    std::size_t space() const { return Size - count(); }
//Добавить байт
    void push(uint8_t byte) {
        if (!isFull()) {
            buffer[head % Size] = byte;
            head++;
        }
    }
//Взять крайний
    uint8_t front() const { return buffer[tail % Size]; }

    uint8_t getN(std::size_t n) const { return buffer[(tail + n) % Size]; }

    void pop() {
        if (!isEmpty()) {
            tail++;
        }
    }

    void flush() {
        head = 0;
        tail = 0;
    }

    //Установили хвост на нужную позицию
    void shiftTail(std::size_t _tail){
        tail = _tail;
    }


private:
    std::array<uint8_t, Size> buffer;
    std::size_t head;
    std::size_t tail;
};


#endif // FIFO_H
