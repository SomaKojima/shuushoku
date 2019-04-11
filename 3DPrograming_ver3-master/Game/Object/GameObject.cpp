#include "../../pch.h"
#include "GameObject.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

GameObject::GameObject() 
	: 
	BidirectionalList<GameObject>(this)
{
}

GameObject::~GameObject()
{
}
