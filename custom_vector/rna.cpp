#include "rna.h"

using namespace std;

rna::rna()
{
    array = new unsigned char[1];
    current_size = 0;
    current_capacity = 4;
}

rna::rna(nucl elem, size_t rna_size)
{
    array = new unsigned char[1];
    current_size = 0;
    current_capacity = 4;
    for (size_t i = 0; i < rna_size; ++i)
        push(elem);
}

rna::rna(const rna &source_rna)
{
    size_t size_of_array = source_rna.current_capacity / 4;
    this->array = new unsigned char[size_of_array];
    for (size_t i = 0; i < size_of_array; ++i)
        this->array[i] = source_rna.array[i];
    this->current_size = source_rna.current_size;
    this->current_capacity = source_rna.current_capacity;
}

rna::~rna()
{
    delete[] array;
}

void rna::push(nucl new_nucl)
{
    if (current_size == current_capacity)
    {
        size_t size_of_array = current_capacity / 4;
        auto* tmp_array = new unsigned char[size_of_array * 2];

        for (int i = 0; i < size_of_array; ++i)
            tmp_array[i] = array[i];

        delete[] array;
        current_capacity *= 2;
        array = tmp_array;
    }

    unsigned char mask = 0b11111100;
    mask <<= (8 - 2 * (current_size % 4) - 2);
    new_nucl = (nucl)(new_nucl << (8 - 2 * (current_size % 4) - 2));
    array[current_size / 4] &= mask;
    array[current_size / 4] |= new_nucl;
    ++current_size;
}

void rna::push(size_t index, nucl new_nucl)
{
    if (index >= current_size)
    {
        cout << "index exceeds the size of the array" << endl;
        return;
    }

    unsigned char mask = 0b11111111;
    mask = (mask << (8 - 2 * (index % 4))) | (mask >> (2 * (index % 4) + 2));
    new_nucl = (nucl)(new_nucl << (8 - 2 * (index % 4) - 2));
    array[index / 4] &= mask;
    array[index / 4] |= new_nucl;
}

void rna::pop()
{
    if (current_size == 0)
        return;

    unsigned char mask = 0b11111111;
    array[current_size / 4] &= (mask << (8 - 2 * (current_size % 4) + 2));
    --current_size;

    if (current_size <= current_capacity / 2)
    {
        size_t size_of_array = current_capacity / 4;
        auto* tmp_array = new unsigned char[size_of_array / 2];

        for (int i = 0; i < size_of_array; ++i)
            tmp_array[i] = array[i];

        delete[] array;
        current_capacity /= 2;
        array = tmp_array;
    }
}

size_t rna::get_size() const
{
    return current_size;
}

size_t rna::get_capacity() const
{
    return current_capacity;
}

nucl rna::get_elem_by_index(size_t index) const
{
    return (nucl)((array[index / 4] >> (8 - 2 * (index % 4) - 2)) & 0b00000011);
}

void rna::print_rna() const
{
    for (size_t i = 0; i < current_size; ++i)
    {
        switch (rna::get_elem_by_index(i))
        {
            case A:
                cout << "A ";
                break;
            case G:
                cout << "G ";
                break;
            case C:
                cout << "C ";
                break;
            case T:
                cout << "T ";
                break;
            default:
                break;
        }
    }
    cout << endl;
}

rna::nucl_ref rna::operator[](size_t index)
{
    nucl_ref tmp_nucl_ref(*this, index);
    return tmp_nucl_ref;
}

nucl rna::operator[](size_t index) const
{
    return this->get_elem_by_index(index);
}

rna &rna::operator=(const rna &other_rna)
{
    if (this == &other_rna)
        return *this;

    current_size = other_rna.current_size;
    current_capacity = other_rna.current_capacity;
    if (current_size != 0)
    {
        size_t size_of_array = other_rna.current_capacity / 4;
        delete[] array;
        array = nullptr;
        array = new unsigned char[size_of_array];
        memcpy(array, other_rna.array, size_of_array * sizeof(unsigned char));
    }

    return *this;
}

rna rna::operator+(const rna &other_rna) const
{
    rna sum;
    for (size_t i = 0; i < this->current_size; ++i)
        sum.push((*this).get_elem_by_index(i));

    for (size_t i = 0; i < other_rna.current_size; ++i)
        sum.push(other_rna.get_elem_by_index(i));

    return sum;
}

rna rna::operator!() const
{
    for (size_t i = 0; i < current_capacity / 4; ++i)
        array[i] = ~(array[i]);

    return *this;
}

bool rna::operator==(const rna &other_rna)
{
    if ((current_size == 0) && (other_rna.current_size == 0))
        return true;

    if ((current_size != other_rna.current_size) && (current_capacity != other_rna.current_capacity))
        return false;

    for (size_t i = 0; i < current_size; ++i)
        if (this->get_elem_by_index(i) != other_rna.get_elem_by_index(i))
            return false;

    return true;
}

bool rna::operator!=(const rna &other_rna)
{
    return !(*this == other_rna);
}

bool rna::is_complementary(const rna &other_rna) const
{
    const rna &tmp_rna(other_rna);
    return ((rna)*this == !tmp_rna);
}

void rna::trim(size_t index)
{
    if (current_size <= 0)
    {
        cout << "Nothing to delete" << endl;
        return;
    }

    for (size_t i = current_size; i > index; --i)
        pop();
}

rna rna::split(size_t index)
{
    rna new_rna;
    for (size_t i = index; i < current_size; ++i)
        new_rna.push((*this).get_elem_by_index(i));

    this->trim(index);

    return new_rna;
}

size_t rna::cardinality(nucl value) const
{
    size_t cnt = 0;
    for (size_t i = 0; i < current_size; ++i)
        if (value == get_elem_by_index(i))
            ++cnt;

    return cnt;
}

std::unordered_map<nucl, size_t, std::hash<int>> rna::cardinality() const
{
    std::unordered_map<nucl, size_t, std::hash<int>> nucl_stat;

    nucl_stat[A] = this->cardinality(A);
    nucl_stat[G] = this->cardinality(G);
    nucl_stat[C] = this->cardinality(C);
    nucl_stat[T] = this->cardinality(T);

    return nucl_stat;
}

std::ostream &operator<<(std::ostream &os, std::unordered_map<nucl, size_t, std::hash<int>> nucl_stat)
{
    os << "A: " << nucl_stat.at(A) << endl;
    os << "G: " << nucl_stat.at(G) << endl;
    os << "C: " << nucl_stat.at(C) << endl;
    os << "T: " << nucl_stat.at(T) << endl;

    return os;
}
