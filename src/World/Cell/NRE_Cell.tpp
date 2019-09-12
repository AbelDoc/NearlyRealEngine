
    /**
     * @file NRE_Cell.tpp
     * @brief Implementation of Engine's World's Object : Cell
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace World {

             inline Cell::Cell(CellCorners cs) : corners(cs) {
             }

             inline CellCorners Cell::getWeight() const {
                 return corners;
             }

             inline Utility::String Cell::toString() const {
                 Utility::String res;
                 res << ((corners & 0b1000) ? ('1') : ('0'));
                 res << ((corners & 0b0100) ? ('1') : ('0'));
                 res << ((corners & 0b0010) ? ('1') : ('0'));
                 res << ((corners & 0b0001) ? ('1') : ('0'));
                 return res;
             }

             inline std::ostream& operator <<(std::ostream& stream, Cell const& o) {
                 return stream << o.toString();
             }


         }
     }
