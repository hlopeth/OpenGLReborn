#pragma once
#include <list>
#include <vector>
#include "Rect.h"
#include "Transform2DComponent.h"
#include "EventComponent.h"
#include "Shader.h"
#include "MouseMoveEvent.h"

namespace UI
{
	using glm::vec4;
	class UIWiget : public Transform2DComponent, public EventComponent
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
		//добавляет дочерний элемент, если это возможно
		virtual bool addChild(UIWiget* wiget);
		virtual void call(const Event& event) override;
		virtual int getMaxChildren() = 0;
		//renderArea - координаты родительского контейнера
		virtual void draw() = 0;
		bool pointInShape(float x, float y);

		UIWiget* parent = nullptr;
		Rect transform;
		bool visible = true;
	protected:
		void drawChildren();

		//позиция в локальных координатаъ элемента
		ShaderProgram shader;
		std::list<UIWiget*> children;
	};
}