#include "QuadTree.h"

QuadTree::QuadTree() : QuadTree(5, 5, 0, { 0.f,0.f,1920,1080 }, nullptr) {}

QuadTree::QuadTree(int maxObjects, int maxLevels, int levels, sf::FloatRect bounds, QuadTree* parent)
	: maxObjects{ maxObjects },
	maxLevels{ maxLevels },
	bounds{ bounds },
	parent{ parent } {}

void QuadTree::Insert(std::shared_ptr<C_BoxCollider> object)
{
	// If the node is subdivided find the relevant child node.
	if (children[0] != nullptr)
	{
		int indexToPlaceObject = GetChildIndexForObject(object->GetCollidable());

		if (indexToPlaceObject != thisTree)
		{
			children[indexToPlaceObject]->Insert(object);
			return;
		}
	}

	objects.emplace_back(object);

	// If the node is not subdivided, not on the final level and the max object limit is reached
	if (static_cast<int>(objects.size()) > maxObjects && level < maxLevels && children[0] == nullptr)
	{
		Split();
		auto objIterator = objects.begin();
		while (objIterator != objects.end())
		{
			auto obj = *objIterator;
			int indexToPlace = GetChildIndexForObject(obj->GetCollidable());

			if (indexToPlace != thisTree)
			{
				children[indexToPlace]->Insert(obj);
				objIterator = objects.erase(objIterator);
			}
			else
			{
				++objIterator;
			}
		}
	}
}


void QuadTree::Remove(std::shared_ptr<C_BoxCollider> object)
{
	int index = GetChildIndexForObject(object->GetCollidable());

	if (index == thisTree || children[index] == nullptr)
	{
		for (int i = 0; objects.size(); i++)
		{
			if (objects.at(i)->owner->instanceID->Get()
				== object->owner->instanceID->Get())
			{
				objects.erase(objects.begin() + i);
				break;
			}
		}
	}
	else
	{
		children[index]->Remove(object);
	}
}

void QuadTree::Clear()
{
	objects.clear();

	for (int i = 0; i < 4; i++)
	{
		children[i]->Clear();
		children[i] = nullptr;
	}
}

std::vector<std::shared_ptr<C_BoxCollider>> QuadTree::Search(const sf::FloatRect& area)
{
	std::vector<std::shared_ptr<C_BoxCollider>> possibleOverlaps;
	Search(area, possibleOverlaps);

	std::vector <std::shared_ptr<C_BoxCollider>> returnList;

	for (auto collider : possibleOverlaps)
	{
		if (area.intersects(collider->GetCollidable()))
		{
			returnList.emplace_back(collider);
		}
	}
	return returnList;
}

void QuadTree::Search(const sf::FloatRect& area,
	std::vector<std::shared_ptr<C_BoxCollider>>& overlappingObjects)
{
	overlappingObjects.insert(overlappingObjects.end(), objects.begin(), objects.end());

	if (children[0] != nullptr)
	{
		int index = GetChildIndexForObject(area);

		if (index == thisTree)
		{
			for (int i = 0; i < 4; i++)
			{
				if (children[i]->GetBounds().intersects(area))
				{
					children[i]->Search(area, overlappingObjects);
				}
			}
		}
		else
		{
			children[index]->Search(area, overlappingObjects);
		}
	}
}

const sf::FloatRect& QuadTree::GetBounds() const
{
	return bounds;
}

int QuadTree::GetChildIndexForObject(const sf::FloatRect& objectBounds)
{
	int index = -1;

	double verticalDividindLine = static_cast<double>(bounds.left + bounds.width * 0.5f);
	double horizontalDividingLine = static_cast<double>(bounds.top + bounds.height * 0.5f);

	bool north = objectBounds.top < horizontalDividingLine
		&& (static_cast<double>(objectBounds.height + objectBounds.top) < horizontalDividingLine);
	bool south = objectBounds.top > horizontalDividingLine;
	bool east = objectBounds.left < verticalDividindLine
		&& (static_cast<double>(objectBounds.left + objectBounds.width) < verticalDividindLine);
	bool west = objectBounds.left > verticalDividindLine;

	// Only objects that are fully contained inside a bounding box are added to children
	if (east)
	{
		if (north)
		{
			index = childNE;
		}
		else if (south)
		{
			index = childSE;
		}
	}
	else if (west)
	{
		if (north)
		{
			index = childNW;
		}
		else if (south)
		{
			index = childSW;
		}
	}
	return index;
}

void QuadTree::Split()
{
	const float childWidth = bounds.width / 2;
	const float childHeight = bounds.height / 2;

	children[childNE] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left + childWidth, bounds.top, childWidth, childHeight), this);
	children[childNW] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left, bounds.top, childWidth, childHeight), this);
	children[childSW] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left, bounds.top + childHeight, childWidth, childHeight), this);
	children[childSE] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left + childWidth, bounds.top + childHeight, childWidth, childHeight), this);
}