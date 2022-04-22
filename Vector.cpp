#include "Vector.h"

#include <cmath>


Vector::Vector(const Value* rawArray, const size_t size, float coef){
    _size = size;
    _capacity = size;
    _data = new Value[_size];
    _multiplicativeCoef = coef;
    for(size_t i = 0; i < size; i++){
        _data[i] = rawArray[i];
    }
}

Vector::Vector(const Vector& other){
    _size = other._size; 
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _data = new Value[_capacity];
    for (size_t i = 0; i < other._size; i++){
        _data[i] = other._data[i];
    }
}

Vector& Vector::operator=(const Vector& other){
    if (this != &other){
        reserve(other._size);
        _size = other._size;
        _multiplicativeCoef = other._multiplicativeCoef;
        for (size_t i = 0; i < _size; i++){
            _data[i] = other._data[i];
        }
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept{
    _capacity = other._size;
    _size = other._size;
    _data = other._data;
    _multiplicativeCoef = other._multiplicativeCoef;
    other._capacity = 0;
    other._size = 0;
    other._data = nullptr;
    other._multiplicativeCoef = 0;
}

Vector& Vector::operator=(Vector&& other) noexcept{
    if (this != &other){
        _capacity = other._size;
        _size = other._size;
        _data = other._data;
        _multiplicativeCoef = other._multiplicativeCoef;
        other._capacity = 0;
        other._size = 0;
        other._data = nullptr;
        other._multiplicativeCoef = 0;
    }
    return *this;
}

Vector::~Vector(){
    delete[] _data;
}

void Vector::pushBack(const Value& value){
    insert(value, _size);
}

void Vector::pushFront(const Value& value){
    insert(value, 0);
}

void Vector::insert(const Value& value, size_t pos){
    if (_capacity == 0){
        reserve(1);
        reserve(_capacity * size_t(_multiplicativeCoef));
    }
    if (loadFactor() == 1){
        reserve(_capacity * size_t(_multiplicativeCoef));
    }
    for(size_t i = _size; i > pos; i--){
        _data[i] = _data[i - 1];
    }
    _size++;
    _data[pos] = value;
}

void Vector::insert(const Value* values, size_t size, size_t pos){
    if (_capacity < _size + size){
        reserve((round((_size + size)/ _multiplicativeCoef) + 1)* _multiplicativeCoef);
    }
    for (size_t i = 0; i < size; i++){
        insert(values[i], pos + i);
    }
}

void Vector::insert(const Vector& vector, size_t pos){
    insert(vector._data, vector._size, pos);
}


void Vector::popBack(){
    erase(_size - 1, 1);
}

void Vector::popFront(){
    erase(0, 1);
}

void Vector::reserve(size_t capacity){
    if (capacity > _capacity){
        Value* tmp = new Value[capacity];
        if (_data != nullptr){
            for (size_t i = 0; i < _size; i++){
                tmp[i] = _data[i];
            }
            delete[] _data;
        }
        _data = tmp;
        _capacity = capacity;
    }
}

void Vector::shrinkToFit(){
    Value*tmp = new Value[_size];
    if (_data != nullptr){
        for (auto i = 0; i < _size; i++){
            tmp[i] = _data[i];
        }
        delete[] _data;
    }
    _data = tmp;
    _capacity = _size;
}

size_t Vector::size() const{
    return _size;
}

size_t Vector::capacity() const{
    return _capacity;
}

double Vector::loadFactor() const{
    return static_cast<double>(_size) / _capacity;
}

Value& Vector::operator[](size_t idx){
    return _data[idx];
}

const Value& Vector::operator[](size_t idx) const{
    return _data[idx];
}


void Vector::erase(size_t pos, size_t count){
    if (_size == 0) {
        throw out_of_range("Vector is empty");
    }
    if(pos + count > _size){
        for(size_t i = _size - pos; i > 0; i--){
            popBack();
        }
    }
    else{
        for(size_t c = 0; c < count; c++){
            for(size_t i = pos + 1; i < _size; i++){
                _data[i - 1] = _data[i];
            }
            _size--;
        }
    }
}


void Vector::eraseBetween(size_t beginPos, size_t endPos){
    erase(beginPos, endPos - beginPos);
}


long long Vector::find(const Value& value) const{
    for(long long i = 0; i < _size; i++){
        if(_data[i] == value){
            return i;
        }
    }
    return -1;
}


Vector::Iterator Vector::begin(){
    return Vector::Iterator(&(_data[0]));
}

Vector::Iterator Vector::end(){
    return Vector::Iterator(&_data[_size]);
}

Vector::Iterator::Iterator(Value* ptr) : _ptr(ptr)
{}

Value& Vector::Iterator::operator*(){
    return *_ptr;
}

const Value& Vector::Iterator::operator*() const{
    return *_ptr;
}

Value* Vector::Iterator::operator->(){
    return _ptr;
}

const Value* Vector::Iterator::operator->() const{
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++(){
    ++_ptr;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int val){
    Vector::Iterator iter = *this;
    ++(*this);
    return iter;
}

bool Vector::Iterator::operator==(const Vector::Iterator& other) const{
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Vector::Iterator& other) const{
    return _ptr != other._ptr;
}