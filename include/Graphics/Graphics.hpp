#pragma once

#include "Graphics/Window.hpp"

class IGraphics {
public:
	virtual ~IGraphics() = default;

	virtual void Initialize(IWindow*) = 0;
	virtual void Finalize() = 0;

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

	virtual void Draw() = 0;
	// virtual void DrawMesh(const Mesh& mesh, const Transform& transform) = 0; 
};