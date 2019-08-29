
    /**
     * @file NRE_Attachable.tpp
     * @brief Implementation of Engine's GL's Object : Attachable
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline Attachable::Attachable() : id(0), allocated(false) {
            }

            inline Attachable::Attachable(Attachable && a) : id(a.id), allocated(a.allocated) {
                a.id = 0;
                a.allocated = false;
            }

            inline Attachable::~Attachable() {
                deallocate();
            }

            inline bool Attachable::isAllocated() const {
                return allocated;
            }

            inline Id Attachable::getId() const {
                return id;
            }

            inline void Attachable::allocate() {
                if (isAllocated()) {
                    deallocate();
                    createId();
                }
                allocated = true;
            }

            inline void Attachable::deallocate() {
                deleteId();
                allocated = false;
            }

            inline Attachable& Attachable::operator =(Attachable && a) {
                if (this != &a) {
                    id = a.id;
                    a.id = 0;
                    allocated = a.allocated;
                    a.allocated = false;
                }
                return *this;
            }

            inline std::ostream& operator <<(std::ostream& stream, Attachable const& o) {
                return stream << o.toString();
            }
        }
    }
