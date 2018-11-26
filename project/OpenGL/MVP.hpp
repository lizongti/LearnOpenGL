#ifndef MVP_HPP
#define MVP_HPP

#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

class MVP
{
public:
    enum TYPE
    {
        MODEL = 1,
        VIEW = 2,
        PROJECTION = 3,
    };
    MVP()
    {};
    
    virtual ~MVP()
    {};

public:
    void Reset(TYPE mvp_type, const glm::mat4& mat = glm::mat4())
    {
        switch(mvp_type)
        {
            case MODEL:
                set_model(mat);
                break;
            case VIEW:
                set_view(mat);
                break;
            case PROJECTION:
                set_projection(mat);
                break;
            default:
                std::cerr << "[MVP] MVP type is no correct! type : " << mvp_type << std::endl;
        }
    };

    void Operate(TYPE mvp_type, const glm::mat4& mat = glm::mat4())
    {
        switch(mvp_type)
        {
            case MODEL:
                model_ = mat * model_;
                break;
            case VIEW:
                view_ = mat * view_;
                break;
            case PROJECTION:
                projection_ = mat * projection_;
                break;
            default:
                std::cerr << "[MVP] MVP type is no correct! type : " << mvp_type << std::endl;
        }   
    };

    glm::mat4 Value() 
    { 
        return projection_ * view_ * model_; 
    };

public:
    void set_model(const glm::mat4& model) { model_ = model; };
    void set_view(const glm::mat4& view) { view_ = view; };
    void set_projection(const glm::mat4& projection) { projection_ = projection; };

    glm::mat4& model() { return model_; };
    glm::mat4& view() { return view_; };
    glm::mat4& projection() { return projection_; };

protected:
    glm::mat4 model_;
    glm::mat4 view_;
    glm::mat4 projection_;
};

class ApplicatedMVP : public MVP
{
public:
    ApplicatedMVP():MVP(), width_(SCREEN_WIDTH), height_(SCREEN_HEIGHT), near_(1), far_(5000), cull_angle_(45)
    {};

    virtual ~ApplicatedMVP()
    {};

public: // object related
    MVP* ResetObject()
    {
        model_ = glm::mat4();
        return this;
    };

    MVP* MoveObjectAbs(const glm::vec3& vec)
    {
        object_pos_ = vec;
        model_ = glm::translate(model_, object_pos_);
        return this;
    };

    MVP* RotateObjectAbs(const glm::vec3& vec, const float angle)
    {
        object_rotate_axis_ = vec;
        object_rotate_angle_ = angle;
        model_ = glm::rotate(model_, glm::radians(object_rotate_angle_), object_rotate_axis_);
        return this;
    };

    MVP* ScaleObjectAbs(const glm::vec3& vec)
    {
        object_scale_ = vec;
        model_ = glm::scale(model_, vec); 
        return this;
    };

public:// view related
    MVP* MoveSituationRef(const glm::vec3& vec) 
    {
        camera_pos_ = camera_pos_ + vec;
        view_ = glm::lookAt(camera_pos_, camera_pos_ + camera_front_, camera_up_);
        return this;
    };

    MVP* RotateDirectionAbs(const glm::vec3& vec)
    {
        camera_front_ = vec;
        view_ = glm::lookAt(camera_pos_, camera_pos_ + camera_front_, camera_up_);
        return this;
    };

    MVP* RotateUpAbs(const glm::vec3& vec)
    {
        camera_up_ = vec;
        view_ = glm::lookAt(camera_pos_, camera_pos_ + camera_front_, camera_up_);
        return this;
    };

public:// projection related
    MVP* ZoomRefAbs(const float angle)
    {
        cull_angle_ = angle;
        projection_ = glm::perspective(glm::radians(cull_angle_), width_ / height_, near_, far_);
        return this;
    };
    
    MVP* ViewPortAbs(const float width, const float height)
    {
        width_ = width;
        height_ = height;

        projection_ = glm::perspective(glm::radians(cull_angle_), width_ / height_, near_, far_);
        return this;
    };

    MVP* ViewDistanceAbs(const float near, const float far)
    {
        near_ = near;
        far_ = far;

        projection_ = glm::perspective(glm::radians(cull_angle_), width_ / height_, near_, far_);
        return this;
    };
public:
    glm::vec3 object_pos() { return object_pos_; };
    glm::vec3 object_scale() { return object_scale_; };
    glm::vec3 object_rotate_axis() { return object_rotate_axis_; };
    float object_rotate_angle() { return object_rotate_angle_; };

    glm::vec3 camera_pos() { return camera_pos_; };
    glm::vec3 camera_front() { return camera_front_; };
    glm::vec3 camera_up() { return camera_up_; };

    float width() { return width_; };
    float height() { return height_; };
    float near() { return near_; };
    float far() { return far_; }; 
    float cull_angle() { return cull_angle_; };  

protected:
    glm::vec3 object_pos_;
    glm::vec3 object_scale_;
    glm::vec3  object_rotate_axis_;
    float object_rotate_angle_;

    glm::vec3 camera_pos_;
    glm::vec3 camera_front_;
    glm::vec3 camera_up_;

    float width_;
    float height_;
    float near_;
    float far_; 
    float cull_angle_;
 
};

class FPSMVP : public ApplicatedMVP
{
public:
    FPSMVP()
    {
        ZoomRefAbs(45.0);
        ViewPortAbs(SCREEN_WIDTH, SCREEN_HEIGHT);
        ViewDistanceAbs(1.0f, 5000.0f);

        camera_up_ = glm::vec3(0.0f, 1.0f, 0.0f);
        camera_pos_ = glm::vec3(0.0f, 0.0f, 3.0f);
        camera_front_ = glm::vec3(0.0f, 0.0f, -1.0f);

        glm::vec3 front;
        front.x = cos(glm::radians(direction_yaw_)) * cos(glm::radians(direction_pitch_));
        front.y = sin(glm::radians(direction_pitch_));
        front.z = sin(glm::radians(direction_yaw_)) * cos(glm::radians(direction_pitch_));

        auto Front = glm::normalize(front);
        RotateDirectionAbs(Front);
        auto Right = glm::normalize(glm::cross(Front, glm::vec3(0.0f, 1.0f, 0.0f)));
        RotateUpAbs(glm::normalize(glm::cross(Right, Front)));
    };

    virtual ~FPSMVP()
    {};
    
    enum MoveAction
    {
        FORWARD = 1,
        BACKWARD = 2,
        LEFT = 3,
        RIGHT = 4,
    };
public:
    void Move(MoveAction action, float move_time)
    {
        auto velocity = move_speed_ * move_time;
        auto Front = glm::normalize(camera_front_);
        auto Right = glm::normalize(glm::cross(Front, glm::vec3(0.0f, 1.0f, 0.0f)));
        switch(action)
        {
            case FORWARD:
                MoveSituationRef(Front * velocity);
                break;
            case BACKWARD:
                MoveSituationRef(- Front * velocity);
                break;
            case LEFT:
                MoveSituationRef(- Right * velocity);
                break;
            case RIGHT:
                MoveSituationRef(Right * velocity);
                break;
        }
    };

    void Zoom(float distance)
    {
        float cull_angle = cull_angle_;
        if(cull_angle >= 1.0f && cull_angle <= 45.0f)
            cull_angle -= distance * zoom_speed_;
        if(cull_angle <= 1.0f)
            cull_angle = 1.0f;
        if(cull_angle >= 45.0f)
            cull_angle = 45.0f;

        ZoomRefAbs(cull_angle);
    };

    void Direction(float direction_x, float direction_y)
    {
        direction_x *= direction_sensibility_;
        direction_y *= direction_sensibility_;

        direction_yaw_   += direction_x;
        direction_pitch_ += direction_y;

        if(direction_pitch_ > 89.0f)
            direction_pitch_ = 89.0f;
        if(direction_pitch_ < -89.0f)
            direction_pitch_ = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(direction_yaw_)) * cos(glm::radians(direction_pitch_));
        front.y = sin(glm::radians(direction_pitch_));
        front.z = sin(glm::radians(direction_yaw_)) * cos(glm::radians(direction_pitch_));

        auto Front = glm::normalize(front);
        auto Right = glm::normalize(glm::cross(Front, glm::vec3(0.0f, 1.0f, 0.0f)));
        
        RotateDirectionAbs(Front);
        RotateUpAbs(glm::normalize(glm::cross(Right, Front)));
    };

public:
    void set_move_speed(float camera_speed) { move_speed_ =  camera_speed; };
    float move_speed() { return move_speed_; };
    void set_zoom_speed(float zoom_speed) { zoom_speed_ = zoom_speed; };
    float zoom_speed() { return zoom_speed_; };
    void set_direction_sensibility(float direction_sensibility) { direction_sensibility_ = direction_sensibility; };
    float direction_sensibility() { return direction_sensibility_; };
    void set_direction_yaw(float direction_yaw) { direction_yaw_ = direction_yaw; };
    float direction_yaw() { return direction_yaw_; };
    void set_direction_pitch(float direction_pitch) { direction_pitch_ = direction_pitch; };
    float direction_pitch() { return direction_pitch_; };

protected:
    float move_speed_ = 2.5f;
    float zoom_speed_ = 1.0f;
    float direction_sensibility_ = 0.1f;

    float direction_yaw_ = -90.0f;
    float direction_pitch_ = 0.0f;
};

#endif