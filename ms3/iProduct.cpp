#include "iProduct.h"

namespace sdds {
   std::ostream& operator << (std::ostream& ostr, const iProduct& prdToPrint) {
      return prdToPrint.display(ostr);
   }

   std::istream& operator >> (std::istream& istr, iProduct& prdToRead) {
      return prdToRead.read(istr);
   }
}