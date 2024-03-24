#pragma once

//Anyrhing that could be an object part should inherit this
class IObjectComponent
{
public:
	IObjectComponent() {};
	~IObjectComponent() {};

private:
	IObjectComponent** AttachedComponents;
};
