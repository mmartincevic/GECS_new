#pragma once

class ISystem {
	public:
		virtual ~ISystem();
		virtual void PreUpdate(float dt) = 0;
		virtual void Update(float dt) = 0;
		virtual void PostUpdate(float dt) = 0;
		virtual void Clear() = 0;

	protected:
		ISystem();
};