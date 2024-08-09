#include "Shape.hpp"

const char* Shape::getModelTypeString(ModelType type) {
    switch (type) {
        case ModelType::Sphere: return "Sphere";
        case ModelType::Cube: return "Cube";
        case ModelType::Mesh: return "Mesh";
    }

    return "Error";
}