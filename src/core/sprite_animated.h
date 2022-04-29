#pragma once

#include <vector>

#include <raylib.h>

#include "texture2d.h"
#include "sprite.h"

namespace game::core {
    /**
     * The position within the spritesheet from which the individual frames are taken, as well as the number of frames
     * in the animation, the size of an individual frame and the speed of the animation can be specified via the
     * constructor parameters.
     *
     * The sprite animation class also allows you to change the animation (called animation state) by selecting a new
     * section from the spritesheet texture using the AddState method. You can switch between the individual animation
     * states using the nextState function.
     *
     * Same as Sprite objects also animated sprites can be drawn using the game::core::Renderer::DrawTexture function.
     * However, the preferred way is to create Actor objects. These contain a sprite (or animated sprite) and are
     * automatically drawn if they are referenced in the actors map of a Scene object.
     *
     * Note that the frame-animation is only automatically updated when the SpriteAnimated object is referenced in
     * the actors-map of a scene.
     *
     * @see Sprite
     *
     * @brief The SpriteAnimated class enables frame-by-frame animations by displaying only a certain section of a spritesheet texture at a time.
     */
    class SpriteAnimated : public game::core::Sprite {
    public:
        SpriteAnimated() = delete;

        /**
         * This constructor requires as parameters a Texture2D object, the height and width specification of an animation
         * frame, an y-offset specified as a row number (the x-offset is always 0), the number of animation steps and
         * the desired speed of the animation.
         *
         * In addition, the rotation origin is set to its center and rotation angle = 0. The default position is {0, 0}.
         * @brief Constructor
         * @param texture Shared pointer to a Texture2D object.
         * @param frame_width Width of a single animation frame
         * @param frame_height Height of a single animation frame
         * @param row y-offset measured in rows (depending on the frame height, i.e. row 1 has a y-offset of 0px, row 2 has a y-offset of the height of an animation frame, etc.).
         * @param steps Number of steps of the animation.
         * @param speed Speed of the frame-by-frame animation
         */
        SpriteAnimated(std::shared_ptr<game::core::Texture2D> texture, float frame_width, float frame_height,
                       int row,
                       int steps,
                       int speed);

        /**
         * This constructor requires as parameters a Texture2D object, the height and width specification of an animation
         * frame, an y-offset specified as a row number (the x-offset is always 0), the number of animation steps and
         * the desired speed of the animation. Also the position on the screen can be specified.
         *
         * In addition, the rotation origin is set to its center and rotation angle = 0.
         * @brief Constructor
         * @param texture Shared pointer to a Texture2D object.
         * @param frame_width Width of a single animation frame
         * @param frame_height Height of a single animation frame
         * @param row y-offset measured in rows (depending on the frame height, i.e. row 1 has a y-offset of 0px, row 2 has a y-offset of the height of an animation frame, etc.).
         * @param steps Number of steps of the animation.
         * @param speed Speed of the frame-by-frame animation
         * @param pos_x The sprites x position.
         * @param pos_y The sprites y position.
         */
        SpriteAnimated(std::shared_ptr<game::core::Texture2D> texture, float frame_width, float frame_height,
                       int row,
                       int steps,
                       int speed,
                       int pos_x,
                       int pos_y);

        /**
         * This constructor requires as parameters a Texture2D object, the height and width specification of an animation
         * frame, an y-offset specified as a row number (the x-offset is always 0), the number of animation steps and
         * the desired speed of the animation. Also the position on the screen and the sprite rotation angle can be specified.
         *
         * @brief Constructor
         * @param texture Shared pointer to a Texture2D object.
         * @param frame_width Width of a single animation frame
         * @param frame_height Height of a single animation frame
         * @param row y-offset measured in rows (depending on the frame height, i.e. row 1 has a y-offset of 0px, row 2 has a y-offset of the height of an animation frame, etc.).
         * @param steps Number of steps of the animation.
         * @param speed Speed of the frame-by-frame animation
         * @param pos_x The sprites x position.
         * @param pos_y The sprites y position.
         * @param rotation The sprites rotation angle.
         */
        SpriteAnimated(std::shared_ptr<game::core::Texture2D> texture, float frame_width, float frame_height,
                       int row,
                       int steps,
                       int speed,
                       int pos_x,
                       int pos_y,
                       float rotation);

        /**
         * @return The sprites current animation state number.
         */
        [[nodiscard]] int state() const;

        /**
         * The method checks whether the next animation frame should be displayed based on the game time game::core::Store::ticks
         * and the set animation speed. The prerequisite for this is that the sprite is visible, or for invisible sprites
         * that update_if_invisible is set to true.
         *
         * @note If the animated sprite is used over an actor object and is in the actors map of a scene, this method is called automatically.
         *
         * @brief Updates the animation state of the sprite.
         */
        void Update() override;

        /**
         * Creates a new animation state. To do this, a new section of the sprite texture must be selected via the row
         * parameter (y-offset). Furthermore, the number of animation steps of the new animation state must be specified
         * as well as the desired speed. Since the new animation may have a different frame size, this is also specified.
         * Important: The y-offset refers to the new frame height set here.
         *
         * To switch to the new animation state call the nextState method.
         *
         * @brief Adds a new animation state
         * @param row y-offset measured in rows (depending on the frame height, i.e. row 1 has a y-offset of 0px, row 2 has a y-offset of the height of an animation frame, etc.).
         * @param steps Number of steps of the animation.
         * @param speed Speed of the frame-by-frame animation.
         * @param frame_width Width of a single animation frame.
         * @param frame_height Height of a single animation frame.
         */
        void AddState(int row, int steps, int speed, float frame_width,float frame_height);

        /**
         * @brief Switch to another animation state by its id. The switch will happen after the last animation cycle is completed.
         * @param nextState id of the animation state to switch to.
         */
        void nextState(int nextState);

        /// Defines whether the animation should be updated also if the sprite is not visible. Default is false.
        bool update_if_invisible = false;

    private:
        /**
         * @brief This structure contains all data necessary for the description of the frame-by-frame animation.
         */
        struct anim_state {
            /// y-offset measured in rows (depending on the frame height, i.e. row 1 has a y-offset of 0px, row 2 has a y-offset of the height of an animation frame, etc.).
            int row;
            /// Number of steps of the animation.
            int steps;
            /// Speed of the frame-by-frame animation.
            int speed;
            /// Width of a single animation frame.
            float frame_width;
            /// Height of a single animation frame.
            float frame_height;
        };

        /// Stores the id of the current state
        int state_ = 0;

        /// The id of the next state. The switch will happen after the current animation cycle is completed.
        int next_state_ = 0;

        /// Internal animation cycle step counter
        int current_step_ = 0;

        /// Vector that holds the individual state structs.
        std::vector<anim_state> states_;

        /**
         * The method is called internally by Update() and replaces the animation state with the one specified via this->next_state_.
         * The call is made by Update() only when the current animation cycle has finished.
         */
        void SwitchState();
    };
}
