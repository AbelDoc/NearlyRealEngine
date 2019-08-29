
    /**
     * @file NRE_Surface.hpp
     * @brief Implementation of Engine's GL's Object : Surface
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline Surface::Surface() : pixels(nullptr), format(0), internalFormat(0), allocated(false)  {
            }

            inline Surface::Surface(IO::File const& file) : pixels(nullptr), format(0), internalFormat(0), allocated(false) {
                load(file);
            }

            inline Surface::Surface(Math::Vector2D<GLsizei> const& s, TextureFormat f, TextureInternalFormat iF) : size(s), pixels(nullptr), format(f), internalFormat(iF), allocated(false) {
            }

            inline Surface::Surface(Surface && s) : size(std::move(s.size)), pixels(std::move(s.pixels)), format(s.format), internalFormat(s.internalFormat), allocated(s.pixels) {
                s.pixels = nullptr;
                s.allocated = false;
            }

            inline Surface::~Surface() {
                deallocate();
            }

            inline bool Surface::isAllocated() const {
                return allocated;
            }

            inline Math::Vector2D<GLsizei> const& Surface::getSize() const {
                return size;
            }

            inline TextureFormat Surface::getFormat() const {
                return format;
            }

            inline TextureInternalFormat Surface::getInternalFormat() const {
                return internalFormat;
            }

            inline const unsigned char* Surface::getPixels() const {
                return pixels;
            }

            inline void Surface::setSize(Math::Vector2D<GLsizei> const& s) {
                assert(!isAllocated());
                size = s;
            }

            inline void Surface::setFormat(TextureFormat f) {
                assert(!isAllocated());
                format = f;
            }

            inline void Surface::setInternalFormat(TextureInternalFormat f) {
                assert(!isAllocated());
                internalFormat = f;
            }

            inline void Surface::setPixels(unsigned char* px) {
                pixels = px;
            }

            inline void Surface::allocate() {
                if (allocated) {
                    deallocate();
                }
                allocated = true;
            }

            inline void Surface::deallocate() {
                deallocateSurface();
                size = Math::Vector2D<GLsizei>(0, 0);
                format = 0;
                internalFormat = 0;
                assert(pixels == nullptr);
                allocated = false;
            }

            inline void Surface::deallocateSurface() {
                delete[] pixels;
                pixels = nullptr;
            }

            inline void Surface::load(IO::File const& file) {
                int w, h, n;
                stbi_set_flip_vertically_on_load(true);
                pixels = stbi_load(file.getPath().getCData(), &w, &h, &n, 0);
                allocate();
                size = Math::Vector2D<GLsizei>(w, h);
                if (n == 3) {
                    internalFormat = GL_RGB;
                    format = GL_RGB;
                } else if (n == 4) {
                    internalFormat = GL_RGBA;
                    format = GL_RGBA;
                } else {
                    throw (Exception::STBException("Unknown Pixel Format"));
                }
            }

            inline void Surface::update(IO::File const& file) {
                deallocate();
                load(file);
            }

            inline Surface& Surface::operator =(Surface && s) {
                if (this != &s) {
                    size = std::move(s.size);
                    pixels = std::move(s.pixels);
                    allocated = s.allocated;
                    format = s.format;
                    internalFormat = s.internalFormat;
                    s.pixels = nullptr;
                    s.allocated = false;
                }
                return *this;
            }
        }
    }
