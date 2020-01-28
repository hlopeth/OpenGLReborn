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
		//UIEvent � ��������� �����������
		//��������� �������� �������, ���� ��� ��������
		virtual bool addChild(UIWiget* wiget);
		virtual void call(UIEvent& event);
		virtual int getMaxChildren() = 0;
		//renderArea - ���������� ������������� ����������
		virtual void draw() = 0;

		UIWiget* parent = nullptr;
		Rect transform;
	protected:
		void drawChildren();

		//������� � ��������� ����������� ��������
		ShaderProgram shader;
		std::list<UIWiget*> children;
	};
}