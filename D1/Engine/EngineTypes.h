#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>
#include <list>
#include <array>

// Smart Pointer
template<typename T>
using UniquePtr = std::unique_ptr<T>;

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T>
using WeakPtr = std::weak_ptr<T>;

template<typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
UniquePtr<T> MakeUnique(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

// STL
template<typename T>
using Vector = std::vector<T>;

template<typename T, size_t N>
using Array = std::array<T, N>;

template<typename K, typename T>
using HashMap = std::unordered_map<K, T>;

template<typename K, typename T>
using Map = std::map<K, T>;

template<typename T>
using List = std::list<T>;

template<typename T>
using Stack = std::stack<T>;

template<typename T>
using Queue = std::queue<T>;

template<typename T>
using PriorityQueue = std::priority_queue<T>;

using String = std::string;
using WString = std::wstring;

MAKE_SHARED_REF(Actor);
MAKE_SHARED_REF(ComponentBase);
MAKE_SHARED_REF(SceneComponent);
MAKE_SHARED_REF(StaticMeshComponent);
MAKE_SHARED_REF(MonoBehaviour);
MAKE_SHARED_REF(MeshAsset);
