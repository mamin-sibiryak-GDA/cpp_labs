#include "rna.h"

rna::nucl_ref::nucl_ref(rna &entity, size_t index)
{
    rna_entity = &entity;
    nucl_index = index;
}

rna::nucl_ref &rna::nucl_ref::operator=(nucl elem)
{
    rna_entity->push(nucl_index, elem);
    return *this;
}

rna::nucl_ref &rna::nucl_ref::operator=(const nucl_ref &other_rna_ref)
{
    if (this == &other_rna_ref)
        return *this;

    rna_entity->push(nucl_index, other_rna_ref.rna_entity->get_elem_by_index(other_rna_ref.nucl_index));
    return *this;
}

rna::nucl_ref::operator nucl()
{
    return rna_entity->get_elem_by_index(nucl_index);
}
