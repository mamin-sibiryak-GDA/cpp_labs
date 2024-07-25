#ifndef CUSTOM_VECTOR_H
#define CUSTOM_VECTOR_H

#include <iostream>
#include <unordered_map>

typedef enum nucl: unsigned char
{
    A, G, C, T
} nucl;

class rna
{
private:
    unsigned char* array;
    size_t current_size;
    size_t current_capacity;

    nucl get_elem_by_index(size_t index) const;

public:
    rna();

    rna(nucl, size_t);

    rna(const rna &);

    ~rna();

    void push(nucl);

    void push(size_t, nucl);

    void pop();

    size_t get_size() const;

    size_t get_capacity() const;

    void print_rna() const;

    class nucl_ref
    {
    private:
        rna* rna_entity = nullptr;
        size_t nucl_index;

    public:
        nucl_ref(rna &, size_t);

        ~nucl_ref() = default;;

        nucl_ref &operator=(nucl);

        nucl_ref &operator=(const nucl_ref &);

        explicit operator nucl();

    };

    nucl_ref operator[](size_t);

    nucl operator[](size_t) const;

    rna &operator=(const rna &);

    rna operator+(const rna &) const;

    rna operator!() const;

    bool operator==(const rna &);

    bool operator!=(const rna &);

    bool is_complementary(const rna &) const;

    void trim(size_t);

    rna split(size_t);

    size_t cardinality(nucl) const;

    std::unordered_map<nucl, size_t, std::hash<int>> cardinality() const;
};

std::ostream &operator<<(std::ostream &os, std::unordered_map<nucl, size_t, std::hash<int>> nucl_stat);

#endif
