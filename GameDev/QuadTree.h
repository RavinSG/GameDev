#pragma once

#include <memory>
#include <vector>

#include "C_BoxCollider.h"
#include "Object.h"


class QuadTree
{
public:
	QuadTree();
	QuadTree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, QuadTree* parent);

	// Insert and remove objects to/from the quadtree.
	void Insert(std::shared_ptr<C_BoxCollider> object);
	void Remove(std::shared_ptr<C_BoxCollider> object);

	// Removes all objects from tree.
	void Clear();

	// Returns a vector of colliders that intersetc with the search area.
	std::vector<std::shared_ptr<C_BoxCollider>> Search(const sf::FloatRect& area);

	// Get the bounds of the node
	const sf::FloatRect& GetBounds() const;

private:
	void Search(const sf::FloatRect& area, std::vector<std::shared_ptr<C_BoxCollider>>& overlappingObjects);

	// Returns the index of the node that contains the object. -1 if this node.
	int GetChildIndexForObject(const sf::FloatRect& objectBounds);

	// Create child nodes
	void Split();

	// Indicies of the array of children
	static const int thisTree = -1;
	static const int childNE = 0;
	static const int childNW = 1;
	static const int childSW = 2;
	static const int childSE = 3;

	int maxObjects;
	int maxLevels;

	// Nullptr if the base
	QuadTree* parent;
	std::shared_ptr<QuadTree> children[4]{ nullptr };

	// Objects in the current node
	std::vector<std::shared_ptr<C_BoxCollider>> objects;

	// How deep the current node is from the base. For base this is 0;
	int level;

	// Bounds of this node
	sf::FloatRect bounds;

};

