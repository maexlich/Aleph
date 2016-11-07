#include <iostream>
#include <string>

#include "distances/detail/Matrix.hh"
#include "distances/detail/Munkres.hh"

#include "tests/Base.hh"

using namespace aleph::distances::detail;

template <class T> void threeByThree()
{
  ALEPH_TEST_BEGIN( "Solving a three-by-three matrix" );

  Matrix<T> m( 3 );

  m(0,0) = static_cast<T>(1); m(0,1) = static_cast<T>(2); m(0,2) = static_cast<T>(3);
  m(1,0) = static_cast<T>(2); m(1,1) = static_cast<T>(4); m(1,2) = static_cast<T>(6);
  m(2,0) = static_cast<T>(3); m(2,1) = static_cast<T>(6); m(2,2) = static_cast<T>(9);

  Munkres<T> solver( m );
  solver();

  auto cost = solver.cost( m );

  ALEPH_ASSERT_THROW( cost  > T()   );
  ALEPH_ASSERT_THROW( cost == T(10) );

  ALEPH_TEST_END();
}

template <class T> void fourByFour()
{
  ALEPH_TEST_BEGIN( "Solving a four-by-four matrix" );

  Matrix<T> m( 4 );

  m(0,0) = static_cast<T>(82); m(0,1) = static_cast<T>(83); m(0,2) = static_cast<T>(69); m(0,3) = static_cast<T>(92);
  m(1,0) = static_cast<T>(77); m(1,1) = static_cast<T>(37); m(1,2) = static_cast<T>(49); m(1,3) = static_cast<T>(92);
  m(2,0) = static_cast<T>(11); m(2,1) = static_cast<T>(69); m(2,2) = static_cast<T>( 5); m(2,3) = static_cast<T>(86);
  m(3,0) = static_cast<T>( 8); m(3,1) = static_cast<T>( 9); m(3,2) = static_cast<T>(98); m(3,3) = static_cast<T>(23);

  Munkres<T> solver( m );
  solver();

  auto cost = solver.cost( m );

  ALEPH_ASSERT_THROW( cost  > T()   );
  ALEPH_ASSERT_THROW( cost == T(140) );

  // TODO: Check...
  // 2,0
  // 1,1
  // 0,2
  // 3,3

  ALEPH_TEST_END();
}

int main()
{
  // 3x3 ---------------------------------------------------------------

  threeByThree<short>         ();
  threeByThree<unsigned short>();
  threeByThree<int>           ();
  threeByThree<unsigned int>  ();
  threeByThree<long>          ();
  threeByThree<unsigned long> ();
  threeByThree<float>         ();
  threeByThree<double>        ();

  // 4x4 ---------------------------------------------------------------

  fourByFour<short>         ();
  fourByFour<unsigned short>();
  fourByFour<int>           ();
  fourByFour<unsigned int>  ();
  fourByFour<long>          ();
  fourByFour<unsigned long> ();
  fourByFour<float>         ();
  fourByFour<double>        ();

}
