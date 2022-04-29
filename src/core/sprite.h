#pragma once

#include <memory>

#include <raylib.h>

#include "texture2d.h"

namespace game::core {
    /**
     * Besides the position and rotation angle, a sprite object is further defined by its rotation origin,
     * its tint and its visibility attribute. In addition, the visible section ("frame") of the associated
     * VRAM texture can be specified. This is especially important for the SpriteAnimated class derived from this class.
     *
     * Sprites can be drawn using the game::core::Renderer::DrawTexture function. However, the preferred way is to
     * create Actor objects. These contain a sprite and are automatically drawn if they are referenced in the actors map
     * of a Scene object.
     *
     * @brief The Sprite class specifies position and degree of rotation on the screen for an associated VRAM texture.
     */
    class Sprite {
    protected:
        /// The sprites Texture2D
        std::shared_ptr<game::core::Texture2D> texture_;

        /// The section of the associated VRAM texture to be displayed as Raylib Rectangle structure.
        Rectangle frame_;

    public:
        /// Visibility of the Sprite.
        bool visible = true;

        /// The Raylib tint applied to the VRAM texture when drawing. Defulat ist Raylib WHITE.
        Color tint = WHITE;

        /// The sprites rotation origin, centered by default.
        Vector2 rotation_origin;

        /// The sprites rotation angle. Default is 0.
        float rotation = 0.0f;

        /// The sprites x position
        int pos_x = 0;

        /// The sprites y position
        int pos_y = 0;

        Sprite() = delete;

        /**
         * This constructor sets the section of the texture to be displayed to its full size.
         * In addition, the rotation origin is set to its center and rotation angle = 0. The sprites default position is {0, 0}.
         * @brief Constructor
         * @param texture Shared pointer to a Texture2D object.
         */
        explicit Sprite(std::shared_ptr<game::core::Texture2D> texture);

        /**
         * This constructor sets the section of the texture to be displayed to its full size.
         * In addition, the rotation origin is set to its center and rotation angle = 0. The sprites position can be specified.
         * @brief Constructor
         * @param texture Shared pointer to a Texture2D object.
         * @param pos_x The sprites x position.
         * @param pos_y The sprites y position.
         */
        Sprite(std::shared_ptr<game::core::Texture2D> texture, int pos_x, int pos_y);

        /**
         * This constructor sets the section of the texture to be displayed to its full size.
         * In addition, the rotation origin is set to its center. The sprites position and rotation angle can be specified.
         * @brief Constructor
         * @param texture Shared pointer to a Texture2D object.
         * @param pos_x The sprites x position.
         * @param pos_y The sprites y position.
         * @param rotation The sprites rotation angle.
         */
        Sprite(std::shared_ptr<game::core::Texture2D> texture, int pos_x, int pos_y, float rotation);

        /**
         * Using this constructor the sprites position, rotation angle and rotation and a Raylib Rectangle,
         * which describes the texture section to be displayed can be specified.
         * @brief Constructor
         * @param texture Shared pointer to a Texture2D object.
         * @param pos_x The sprites x position.
         * @param pos_y The sprites y position.
         * @param rotation_origin The rotation origin.
         * @param rotation The sprites rotation angle.
         * @param frame The section of the associated VRAM texture to be displayed.
         */
        Sprite(std::shared_ptr<game::core::Texture2D> texture, int pos_x, int pos_y, Vector2 rotation_origin, float rotation, Rectangle frame);

        virtual ~Sprite();

        /**
         * The section of the texture to be displayed is set to its full size. In addition, the rotation origin is set to its center.
         * @brief Replaces the Texture2D object.
         * @param texture Shared pointer to a Texture2D object.
         */
        void texture(const std::shared_ptr<game::core::Texture2D> &texture);

        /**
         * @return Returns a shared pointer to the objects Texture2D member.
         */
        [[maybe_unused]] [[nodiscard]] const std::shared_ptr<game::core::Texture2D> &texture_object() const;

        /**
         * @return Returns a reference to the Raylib Texture2D structure associated with this object.
         */
        [[nodiscard]] const ::Texture2D &texture() const;

        /**
         * @return Returns the objects coordinates as Raylib Vector structure.
         */
        [[nodiscard]] Vector2 position() const;

        /**
         * @return The section of the associated VRAM texture to be displayed as Raylib Rectangle structure.
         */
        [[nodiscard]] const Rectangle &frame() const;

        /**
         * @brief Sets the section of the associated VRAM texture to be displayed.
         * @param frame Raylib Rectangle, which describes the texture section to be displayed.
         */
        void frame(const Rectangle &frame);

        /**
         * Only relevant in derived classes, like SpiteAnimated.
         */
        virtual void Update() { };
    };
}
