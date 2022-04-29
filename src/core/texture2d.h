#pragma once

#include <raylib.h>

namespace game::core {
    /**
     * @note A Raylib Texture2D structure contains width and height information as well as the ID of the associated graphics
     * texture in VRAM. Copy and assignment operators of this class are therefore deleted, since a copy of an object of
     * this class should correctly also mean a copy of the VRAM texture, which is not normally wanted.
     * Of course, it still makes sense to use one texture for several use cases (e.g. two sprite objects that use the
     * same texture) and to keep it in VRAM only once. The Texture2D class should therefore preferably be used with
     * smart pointers. With the last release of the object, the texture is then unloaded from the VRAM via the destructor.
     *
     * @brief The class Texture2D encapsulates the Raylib structure Texture2D and takes care of the correct loading and unloading of the texture into the VRAM.
     */
    class Texture2D final {
    public:
        Texture2D() = delete;

        /**
         * Creates a new Texture2D object and loads the image file specified as parameter as texture into the VRAM.
         * @brief Constructor.
         * @param filename File name of the image file to load. All Raylib compatible file types are supported.
         */
        explicit Texture2D(const char *filename);

        Texture2D(const game::core::Texture2D &texture) = delete;

        Texture2D &operator=(const Texture2D &) = delete;

        /**
         * Defines if the mouse support should be activated
         * @brief Destructor
         */
        ~Texture2D();

        /**
         * @return A reference to the embedded Raylib Texture2D structure.
         */
        [[nodiscard]] const ::Texture2D &texture() const;

        /**
         * @return The width of the associated texture.
         */
        [[nodiscard]] const int &width() const;

        /**
         * @return The height of the associated texture.
         */
        [[nodiscard]] const int &height() const;

    private:
        /// Raylib Texture2D structure which contains width, height and the ID of the associated VRAM texture.
        ::Texture2D texture_ = { };
    };

}
