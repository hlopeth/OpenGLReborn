#pragma once
#include <list>
#include <vector>
#include "Rect.h"
#include "Transform2DComponent.h"
#include "Shader.h"
#include "MouseMoveEvent.h"
#include "EventHandler.h"

namespace UI
{
	using glm::vec4;
	class UIWiget : public Transform2DComponent
	{
	public:
		UIWiget();
		UIWiget(float x, float y, float width, float height);
		UIWiget(Rect transform);
		virtual vec2 getPosition() override;
		virtual vec2 getSize() override;
		void setPosition(const vec2 position) override;
		void setSize(const vec2 size)  override;
		void setSize(float width, float height);
		std::vector<const UIWiget*> getChildren();
		//UIEvent в локальных координатах
		virtual void call(UIEvent& event);
		virtual bool addChild(UIWiget* wiget);
		virtual int getMaxChildren() = 0;
		//renderArea - координаты родительского контейнера
		virtual void draw(const Rect& renderArea) = 0;
		//пересчитывает положение элемента в звисимости от положения родителя
		virtual void align(Rect parentTransform);

		UIWiget* parent = nullptr;
		vec4 useNormalizedCoords = vec4(false, false, false, false);
		bool alignChildren = true;
	protected:
		void drawChildren(const Rect& renderArea);

		//позиция в локальных координатаъ элемента
		Rect transform;
		//положение элемента в координатах экрана
		Rect globalTransform;
		ShaderProgram shader;
		std::list<UIWiget*> children;

	private:
		bool inShape(UIEvent& event);
	};
}