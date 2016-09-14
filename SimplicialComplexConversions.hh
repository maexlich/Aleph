#ifndef ALEPH_CONVERSIONS_HH__
#define ALEPH_CONVERSIONS_HH__

#include "BoundaryMatrix.hh"
#include "SimplicialComplex.hh"

#include <algorithm>

namespace aleph
{

template <
  class Representation,
  class Simplex
> BoundaryMatrix<Representation> makeBoundaryMatrix( const SimplicialComplex<Simplex>& K )
{
  using Index = typename BoundaryMatrix<Representation>::Index;

  BoundaryMatrix<Representation> M;
  M.setNumColumns( static_cast<Index>( K.size() ) );

  Index j = Index(0);

  for( auto&& itSimplex = K.begin(); itSimplex != K.end(); ++itSimplex )
  {
    std::vector<Index> column;
    column.reserve( itSimplex->size() );

    for( auto&& itBoundary = itSimplex->begin_boundary();
         itBoundary != itSimplex->end_boundary();
         ++itBoundary )
    {
      // TODO: This lookup is *not* optimal. A hash map or something similar
      // should be used here. Else, every access incurs a cost of at least
      // O(log n) instead of O(1).
      auto index = K.index( *itBoundary );

      column.push_back( static_cast<Index>( index ) );
    }

    // TODO: Is this something that should be done by the boundary
    // matrix automatically?
    std::sort( column.begin(), column.end() );

    M.setColumn( j, column.begin(), column.end() );

    ++j;
  }

  return M;
}

}

#endif