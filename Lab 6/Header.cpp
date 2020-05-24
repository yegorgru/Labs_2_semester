#include "Header.h"

std::string main_help = "\n\ndemomode - launch demomode\nbenchmark - launch benchmark\nlinked - create ordered list as linked list\narray - create ordered list as array\nbinary - create ordered list as binary tree\nAVL - create ordered list as AVL tree\n2-3 - create ordered list as 2-3 tree\nexit - close program\n\n";

bool operator>(const point& left, const point& right)
{
	return (left.x > right.x) || (left.x == right.x && left.y > right.y) || (left.x == right.x && left.y == right.y && left.z > right.z);
}

bool operator<(const point& left, const point& right)
{
	return right > left;
}

bool operator==(const point& left, const point& right)
{
	return !(right > left || left > right);
}

bool operator>=(const point& left, const point& right)
{
	return left > right || left == right;
}

bool operator<=(const point& left, const point& right)
{
	return right > left || left == right;
}

std::ostream& operator<<(std::ostream& out, const point& point)
{
	out << '(' << point.x << ", " << point.y << ", " << point.z << ')';
	return out;
}

void orderedListLinkedList::pop_back()
{
	if (size == 0) {

	}
	else if (size == 1) {
		delete tail;
		tail = nullptr;
		head = nullptr;
		size = 0;
	}
	else {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
		size--;
	}
}

void orderedListLinkedList::pop_front()
{
	if (size == 0) {

	}
	else if (size == 1) {
		delete tail;
		tail = nullptr;
		head = nullptr;
		size = 0;
	}
	else {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
		size--;
	}
}

void orderedListLinkedList::push(point value)
{
	ListNode* new_node = new ListNode(value);
	if (size == 0) {
		head = new_node;
		tail = head;
		size++;
	}
	else if (size == 1) {
		if (new_node->value < head->value) {
			tail->prev = new_node;
			new_node->next = tail;
			head = new_node;
		}
		else {
			head->next = new_node;
			new_node->prev = head;
			tail = new_node;
		}
		size++;
	}
	else
	{
		if (new_node->value < head->value) {
			head->prev = new_node;
			new_node->next = head;
			head = new_node;
		}
		else {
			ListNode* next_current = head;
			ListNode* current = head;
			while (next_current->next != nullptr && current->value < value)
			{
				current = next_current;
				next_current = next_current->next;
				if (next_current->next == nullptr && (next_current->value < value))
				{
					tail->next = new_node;
					new_node->prev = tail;
					tail = new_node;
				}
				else if (value < next_current->value)
				{
					current->next = new_node;
					new_node->next = next_current;
					break;
				}
			}
		}
	}
}

void orderedListLinkedList::push(point value, long long number)
{
	if (number < 1) {

	}
	else if (number == 1) {
		push(value);
	}
	else {
		ListNode** new_nodes = new ListNode * [number];
		for (long long i = 0; i < number; i++) {
			new_nodes[i] = new ListNode(value);
		}
		for (long long i = 1; i < number - 1; i++) {
			new_nodes[i]->next = new_nodes[i + 1];
			new_nodes[i]->prev = new_nodes[i - 1];
		}
		new_nodes[0]->next = new_nodes[1];
		new_nodes[number - 1]->prev = new_nodes[number - 2];
		if (size == 0) {
			head = new_nodes[0];
			tail = new_nodes[number - 1];
			size = number;
		}
		else if (size == 1) {
			if (value < head->value) {
				tail->prev = new_nodes[number - 1];
				new_nodes[number - 1]->next = tail;
				head = new_nodes[0];
			}
			else {
				head->next = new_nodes[0];
				new_nodes[0]->prev = head;
				tail = new_nodes[number - 1];
			}
			size++;
		}
		else
		{
			if (value < head->value) {
				head->prev = new_nodes[number - 1];
				new_nodes[number - 1]->next = head;
				head = new_nodes[0];
			}
			else {
				ListNode* next_current = head;
				ListNode* current = head;
				while (next_current->next != nullptr && current->value < value)
				{
					current = next_current;
					next_current = next_current->next;
					if (next_current->next == nullptr && (next_current->value < value))
					{
						tail->next = new_nodes[0];
						new_nodes[0]->prev = tail;
						tail = new_nodes[number - 1];
					}
					else if (value < next_current->value)
					{
						current->next = new_nodes[0];
						new_nodes[number - 1]->next = next_current;
						break;
					}
				}
			}
		}
		delete[] new_nodes;
	}
}

void orderedListLinkedList::push_random(long long number)
{
	std::vector<point> new_values;
	for (long long i = 0; i < number; i++) {
		new_values.push_back(point(number));
	}
	quicksort(new_values, 0, number - 1);
	int counter = 0;
	push(new_values[0]);
	if (number != 1) {
		push(new_values[new_values.size() - 1]);
	}
	ListNode* node = tail;
	while (counter != number-1 && node != nullptr) {
		if (node->value < new_values[number - 2 - counter]) {
			ListNode* new_node = new ListNode(new_values[number - 1 - counter]);
			new_node->prev = node;
			if (node->next) {
				ListNode* help = node->next;
				node->next = new_node;
				new_node->next = help;
			}
			else {
				node->next = new_node;
			}
			size++;
			counter++;
		}
		else {
			node = node->prev;
		}
	}
}

void orderedListLinkedList::erase(point value)
{
	if (size == 0) {

	}
	else {
		while (head->value == value) {
			pop_front();
		}
		ListNode* search = head;
		for (size_t i = 0; i < size - 1; i++) {
			search = search->next;
			if (search->value == value) {
				while (search && search->value == value) {
					if (search == tail) {
						pop_back();
					}
					else {
						ListNode* to_erase = search;
						search->prev->next = search->next;
						search->next->prev = search->prev;
						delete to_erase;
						size--;
					}
				}
				break;
			}
		}
	}
}

void orderedListLinkedList::erase(size_t pos)
{
	if (size == 0) {

	}
	else if (pos > size - 1) {

	}
	else {
		if (pos == size - 1) {
			pop_back();
		}
		else if (pos == 0) {
			pop_front();
		}
		else if (pos > 0 && pos < size - 1) {
			ListNode* search = head;
			for (size_t i = 0; i < pos + 1; i++) {
				search = search->next;
			}
			ListNode* to_erase = search->prev;
			to_erase->prev->next = search;
			search->prev = to_erase->prev;
			delete to_erase;
			size--;
		}
	}
}

void orderedListLinkedList::erase(size_t begin, size_t end)
{
	if (size == 0) {

	}
	if (begin > end || end > size - 1) {

	}
	else if (begin == end) {
		erase(begin);
		return;
	}
	else {
		for (size_t i = begin; i <= end; i++) {
			erase(begin);
		}
		return;
	}
}

void orderedListLinkedList::show()
{
	if (size == 0) {
		std::cout << "This list is empty" << std::endl;
	}
	else {
		ListNode* to_show = head;
		for (size_t i = 0; i < size; i++) {
			std::cout << to_show->value << std::endl;
			to_show = to_show->next;
		}
	}
}

void orderedListLinkedList::show(size_t pos)
{
	if (size == 0) {
		std::cout << "This list is empty" << std::endl;
	}
	else if (pos > size - 1) {
		//
	}
	else {
		ListNode* search = head;
		for (size_t i = 0; i < pos; i++) {
			search = search->next;
		}
		std::cout << search->value << std::endl;
	}
}

point orderedListLinkedList::operator[](size_t index)
{
	if (size == 0) {

	}
	if (index > size - 1) {
		//std::cout << "Error. Out of range" << std::endl;
	}
	else {
		ListNode* search = head;
		for (size_t i = 0; i < index; i++) {
			search = search->next;
		}
		return search->value;
	}
}

bool orderedListLinkedList::is_value(point value)
{
	if (size == 0) {
		return false;
	}
	else {
		ListNode* search = head;
		while(search->value<value && search->next) {
			search = search->next;
		}
		if (search->value == value) {
			return true;
		}
		else {
			return false;
		}
	}
}

node_abstraction orderedListLinkedList::value_search(point value)
{
	node_abstraction to_return(value, -1);
	ListNode* search = head;
	int pos=0;
	while (search->value < value && search->next) {
		search = search->next;
		pos++;
	}
	if (search->value == value) {
		to_return.position = pos;
	}
	return to_return;
}

std::vector<point> orderedListLinkedList::range_search_values(point down, point top)
{
	if (head && down < top) {
		std::vector<point>to_return;
		ListNode* search = head;
		while (search->value < top && search->next) {
			if (search->value > down) {
				to_return.push_back(search->value);
			}
			search = search->next;
		}
		return to_return;
	}
	else {
		//
	}
}

std::vector<node_abstraction> orderedListLinkedList::range_search_nodes(point down, point top)
{
	if (head && down < top) {
		std::vector<node_abstraction>to_return;
		ListNode* search = head;
		int i = 0;
		while (search->value < top && search->next) {
			if (search->value > down) {
				to_return.push_back({search->value, i});
			}
			search = search->next;
			i++;
		}
		return to_return;
	}
	else {
		//
	}
}

void orderedListLinkedList::action(void(*fooPointer)(point& a))
{
	ListNode* current = head;
	for (size_t i = 0; i < size; i++) {
		fooPointer(current->value);
		current = current->next;
	}
}


void orderedListArrayList::pop_back()
{
	if (size > 0) {
		size--;
		list[size];
	}
	else {
		//std::cout << "This list is empty" << std::endl;
	}
}

void orderedListArrayList::pop_front()
{
	if (size > 0) {
		for (size_t i = 1; i < size; i++) {
			list[i] = list[i + 1];
		}
		size--;
	}
	else {
		//std::cout << "This list is empty" << std::endl;
	}
}

void orderedListArrayList::push(point value)
{
	if (size == 0) {
		//std::cout << "You can't insert in empty list" << std::endl;
	}
	else if (size == max_size) {
		//std::cout << "Error. This list is full" << std::endl;
	}
	else {
		if (value > list[size - 1]) {
			list[size] = value;
			size++;
		}
		else if (value < list[0]) {
			for (int i = size; i > 0; i--) {
				list[i] = list[i - 1];
			}
			list[0] = value;
		}
		else {
			for (int i = size; i > 0; i--) {
				if (list[i - 1] > value) {
					list[i] = list[i - 1];
				}
				else {
					list[i] = value;
					break;
				}
			}
		}
		size++;
	}
}

void orderedListArrayList::quick_push(point value)
{
	if (size == 0) {
		//std::cout << "You can't insert in empty list" << std::endl;
	}
	else if (size == max_size) {
		//std::cout << "Error. This list is full" << std::endl;
	}
	else {
		if (value > list[size - 1]) {
			list[size] = value;
			size++;
		}
		else if (value < list[0]) {
			for (int i = size; i > 0; i--) {
				list[i] = list[i - 1];
			}
			list[0] = value;
		}
		else {
			int pos = 0;
			int down = 0;
			int top = size - 1;
			bool was = false;
			while (!was) {
				int pivot = (top + down) / 2;
				if (list[pivot] > value) {
					top = pivot;
				}
				else {
					down = pivot;
				}
				if (top - down < 2) {
					was = true;
					pos = top;
				}
			}
			for (int i = size; i > pos - 1; i--) {
				list[i] = list[i - 1];
			}
			list[pos] = value;
		}
		size++;
	}
}

void orderedListArrayList::push(point value, int number)
{
	if (size == 0) {
		//std::cout << "You can't insert in empty list" << std::endl;
	}
	else if (size + number > max_size) {
		//std::cout << "Error. This list is full" << std::endl;
	}
	else {
		if (value > list[size - 1]) {
			for (int i = 0; i < number; i++) {
				list[size + i] = value;
			}
			size += number;
		}
		else if (value < list[0]) {
			for (int i = size - 1; i > -1; i--) {
				list[i + number] = list[i];
			}
			for (int i = 0; i < number; i++) {
				list[i] = value;
			}
		}
		else {
			for (int i = size - 1; i > 0; i--) {
				if (list[i] > value) {
					list[i + number] = list[i];
				}
				else {
					for (int j = 0; j < number; j++) {
						list[i + 1 + j] = value;
					}
					break;
				}
			}
		}
		size += number;
	}
}

void orderedListArrayList::quick_push(point value, int number)
{
	if (size == 0) {
		//std::cout << "You can't insert in empty list" << std::endl;
	}
	else if (size + number > max_size) {
		//std::cout << "Error. This list is full" << std::endl;
	}
	else {
		if (value > list[size - 1]) {
			for (int i = 0; i < number; i++) {
				list[size + i] = value;
			}
			size += number;
		}
		else if (value < list[0]) {
			for (int i = size - 1; i > -1; i--) {
				list[i + number] = list[i];
			}
			for (int i = 0; i < number; i++) {
				list[i] = value;
			}
		}
		else {
			int pos = 0;
			int down = 0;
			int top = size - 1;
			bool was = false;
			while (!was) {
				int pivot = (top + down) / 2;
				if (list[pivot] > value) {
					top = pivot;
				}
				else {
					down = pivot;
				}
				if (top - down < 2) {
					was = true;
					pos = top;
				}
			}
			for (int i = size; i > pos - 1; i--) {
				list[i + number - 1] = list[i - 1];
			}
			for (int i = 0; i < number; i++) {
				list[pos + i] = value;
			}
		}
		size += number;
	}
}

void orderedListArrayList::push_random(long long number)
{
	std::vector<point>new_values;
	for (long long i = 0; i < number; i++) {
		new_values.push_back(point(number));
	}
	quicksort(new_values, 0, number - 1);
	int counter = number - 1;
	size_t position = size - 1;
	while (counter >= 0) {
		if (list[position] < new_values[counter]) {
			list[position + counter + 1] = new_values[counter];
			counter--;
		}
		else {
			list[position + counter + 1] = list[position];
			position--;
		}
	}
	size += number;
}

void orderedListArrayList::erase(point value)
{
	int pos = 0;
	int difference = 0;
	for (size_t i = 0; i < size - 1; i++) {
		if (list[i] == value) {
			pos = i;
			while (list[i] == value) {
				i++;
			}
			difference = i - pos;
			break;
		}
	}
	for (size_t i = pos; i < size - 1; i++) {
		list[i] = list[i + difference];
	}
	size -= difference;
}

void orderedListArrayList::erase(size_t pos)
{
	if (size == 0) {
		//std::cout << "ERROR. This list is empty.\n";
	}
	else if (pos > size - 1) {
		//std::cout << "Incorrect position\n";
	}
	else {
		for (size_t i = pos; i < size - 1; i++) {
			list[i] = list[i + 1];
		}
		size--;
	}
}

void orderedListArrayList::erase(size_t begin, size_t end)
{
	if (size == 0) {
		//std::cout << "ERROR. This list is empty.\n";
	}
	else if (end < begin || end > size - 1) {
		//std::cout << "Incorrect position\n";
	}
	else {
		for (size_t i = begin; i < size - end + begin - 1; i++) {
			list[i] = list[i + end - begin + 1];
		}
		size -= end - begin + 1;
	}
}

void orderedListArrayList::show()
{
	system("cls");
	if (size == 0) {
		std::cout << "This list is empty" << std::endl;
	}
	else {
		for (size_t i = 0; i < size; i++) {
			std::cout << list[i] << std::endl;
		}
	}
}

void orderedListArrayList::show(size_t pos)
{
	system("cls");
	if (size == 0) {
		//std::cout << "This list is empty" << std::endl;
	}
	else if (pos > size - 1) {
		//std::cout << "Incorrect position" << std::endl;
	}
	else {
		std::cout << list[pos];
	}
}

point orderedListArrayList::operator[](size_t index)
{
	if (size == 0) {

	}
	if (index > size - 1) {
		//std::cout << "Error. Out of range" << std::endl;
	}
	else {
		return list[index];
	}
}

bool orderedListArrayList::is_value(point value)
{
	if (size == 0) {
		return false;
	}
	else {
		for (size_t i = 0; i < size; i++) {
			if (list[i] == value) {
				return true;
			}
		}
		return false;
	}
}

node_abstraction orderedListArrayList::value_search(point value)
{
	node_abstraction to_return(value, -1);
	for (size_t i = 0; i < size; i++) {
		if (list[i] == value) {
			to_return.position = i;
			return to_return;
		}
	}
	return to_return;
}

std::vector<point> orderedListArrayList::range_search_values(point down, point top)
{
	if (down < top) {
		std::vector<point>to_return;
		for (size_t i = 0; i < size; i++) {
			if (down < list[i] && list[i] < top) {
				to_return.push_back(list[i]);
			}
			else if (top < list[i]) {
				break;
			}
		}
		return to_return;
	}
}

std::vector<node_abstraction> orderedListArrayList::range_search_nodes(point down, point top)
{
	if (down < top) {
		std::vector<node_abstraction>to_return;
		for (size_t i = 0; i < size; i++) {
			if (down < list[i] && list[i] < top) {
				to_return.push_back({ list[i], (int)i });
			}
			else if (top < list[i]) {
				break;
			}
		}
		return to_return;
	}
}

void orderedListArrayList::action(void(*fooPointer)(point& a))
{
	for (size_t i = 0; i < size; i++) {
		fooPointer(list[i]);
	}
}


void binaryTree::push(point item)
{
	if (!root) {
		root = new binaryNode(item);
		size = 1;
	}
	else {
		push(item, root);
	}
}

void binaryTree::push(point item, int number)
{
	if (number > 0) {
		if (!root) {
			last_push(item, number, root, nullptr);
		}
		else {
			push(item, number, root);
		}
	}
	else {
		//
	}
}

void binaryTree::push_random(long long number)
{
	for (long long i = 0; i < number; i++) {
		push(point(number));
	}
}

void binaryTree::show(size_t pos)
{
	//std::cout << &this[pos];
	if (size == 0) {
		//std::cout << "This list is empty" << std::endl;
	}
	else if (pos > size - 1) {
		//std::cout << "Incorrect position" << std::endl;
	}
	else {
		size_t counter = 0;
		binaryNode* to_show = get_node(pos, counter, root);
		if (to_show) {
			std::cout << to_show->item;
		}
	}
}

point binaryTree::operator[](size_t index)
{
	if (size == 0) {

	}
	if (index > size - 1) {
		//std::cout << "Error. Out of range" << std::endl;
	}
	else {
		size_t counter = 0;
		binaryNode* to_return = get_node(index, counter, root);
		if (to_return) {
			return to_return->item;
		}
	}
}

node_abstraction binaryTree::value_search(point value)
{
	if (size == 0) {
		return { value,-1 };
	}
	else {
		int counter = 0;
		int index = value_search(value, counter, root) - 1;
		return { value, index };
	}
}

std::vector<point> binaryTree::range_search_values(point down, point top)
{
	std::vector<point>to_return;
	size_t position = 0;
	range_search_values(down, top, to_return, root);
	return to_return;
}

bool binaryTree::is_value(point value, binaryNode* node)
{
	if (node) {
		if (node->item > value) {
			return is_value(value, node->left);
		}
		else if (node->item == value) {
			return true;
		}
		else {
			return is_value(value, node->right);
		}
	}
	else {
		return false;
	}
}

int binaryTree::value_search(point value, int& counter, binaryNode* node)
{
	if (node) {
		if (node->item > value) {
			return value_search(value, counter, node->left);
		}
		else if (node->item == value) {
			counter++;
			return counter;
		}
		else {
			counter++;
			return value_search(value, counter, node->right);
		}
	}
	else {
		return -1;
	}
}

void binaryTree::range_search_values(point down, point top, std::vector<point>& to_return, binaryNode* node)
{
	if (node) {
		if (down < node->item && node->item < top) {
			to_return.push_back(node->item);
			range_search_values(down, top, to_return, node->left);
			range_search_values(down, top, to_return, node->right);
		}
		else if (node->item < down) {
			range_search_values(down, top, to_return, node->right);
		}
		else if (node->item > top) {
			range_search_values(down, top, to_return, node->left);
		}
	}
}

void binaryTree::push(point value, binaryNode* node)
{
	if (value < node->item) {
		if (node->left) {
			push(value, node->left);
		}
		else {
			node->left = new binaryNode(value);
			node->left->parent = node;
			size++;
		}
	}
	else {
		if (node->right) {
			push(value, node->right);
		}
		else {
			node->right = new binaryNode(value);
			node->right->parent = node;
			size++;
		}
	}
}

void binaryTree::push(point value, int number, binaryNode*& node)
{
	if (value < node->item) {
		if (node->left) {
			push(value, node->left);
		}
		else {
			last_push(value, number, node->left, node);
		}
	}
	else {
		if (node->right) {
			push(value, node->right);
		}
		else {
			last_push(value, number, node->right, node);
		}
	}
}

void binaryTree::last_push(point value, int number, binaryNode*& node, binaryNode* parent)
{
	if (number == 0) {
		return;
	}
	else {
		node = new binaryNode(value);
		node->parent = parent;
		last_push(value, number - 1, node->right, node);
		size++;
	}
}

void binaryTree::last_push(point value, int number, binaryNode*& node, binaryNode* left, binaryNode* right, binaryNode* parent)
{
	node = new binaryNode(value);
	node->parent = parent;
	last_push(value, number - 1, node->right, node);
	size++;
	number--;
	if (number == 0) {
		node->left = left;
		node->right = right;
		return;
	}
	else {
		last_push(value, number, node->right, left, right, node);
	}
}

bool binaryTree::erase(size_t pos, int& counter, binaryNode*& node)
{
	if (node) {
		if (erase(pos, counter, node->left) == false) {
			counter++;
			if (counter == pos) {
				if (node->right == nullptr && node->left) {
					binaryNode* help = node->left;
					if (node->parent) {
						if (node->parent->left == node) {
							node->parent->left = help;
							help->parent = node->parent;
						}
						else if (node->parent->right == node) {
							node->parent->right = help;
							help->parent = node->parent;
						}
					}
					delete node;
					node = help;
				}
				else if (node->right == nullptr) {
					if (node->parent->left == node) {
						node->parent->left = nullptr;
					}
					else if (node->parent->right == node) {
						node->parent->right = nullptr;
					}
					delete node;
				}
				else if (node->right && node->right->left == nullptr) {
					binaryNode* help1 = node->left;
					binaryNode* help2 = node->right;
					if (node->parent) {
						if (node->parent->left == node) {
							node->parent->left = help2;
							help2->parent = node->parent;
						}
						else if (node->parent->right == node) {
							node->parent->right = help2;
							help2->parent = node->parent;
						}
					}
					delete node;
					node = help2;
					node->left = help1;
					help1->parent = node;
				}
				else {
					binaryNode* search = node->right->left;
					while (search->left) {
						search = search->left;
					}
					node->item = search->item;
					search->parent->left = nullptr;
					delete search;
				}
				size--;
				return true;
			}
			if (erase(pos, counter, node->right) == true) {
				return true;
			}
		}
		else {
			return true;
		}
	}
}

void binaryTree::erase(point value, binaryNode*& node)
{
	if (node) {
		if (value < node->item) {
			erase(value, node->left);
		}
		if (value == node->item) {
			if (node->right == nullptr && node->left) {
				binaryNode* help = node->left;
				if (node->parent) {
					if (node->parent->left == node) {
						node->parent->left = help;
						help->parent = node->parent;
					}
					else if (node->parent->right == node) {
						node->parent->right = help;
						help->parent = node->parent;
					}
				}
				delete node;
				node = help;
			}
			else if (node->right == nullptr) {
				if (node->parent->left == node) {
					node->parent->left = nullptr;
				}
				else if (node->parent->right == node) {
					node->parent->right = nullptr;
				}
				delete node;
			}
			else if (node->right && node->right->left == nullptr) {
				binaryNode* help1 = node->left;
				binaryNode* help2 = node->right;
				if (node->parent) {
					if (node->parent->left == node) {
						node->parent->left = help2;
						help2->parent = node->parent;
					}
					else if (node->parent->right == node) {
						node->parent->right = help2;
						help2->parent = node->parent;
					}
				}
				delete node;
				node = help2;
				node->left = help1;
				help1->parent = node;
			}
			else {
				binaryNode* search = node->right->left;
				while (search->left) {
					search = search->left;
				}
				node->item = search->item;
				search->parent->left = nullptr;
				delete search;
			}
			size--;
		}
		if (value >= node->item) {
			erase(value, node->right);
		}
	}
}

void binaryTree::delete_subtree(binaryNode*& node)
{
	if (node) {
		if (node->left) {
			delete_subtree(node->left);
		}
		if (node->right) {
			delete_subtree(node->right);
		}
		delete node;
		node = nullptr;
	}
}

void binaryTree::show(binaryNode* node)
{
	if (node) {
		if (node->left) {
			show(node->left);
		}
		std::cout << node->item;
		std::cout << ' ';
		if (node->right) {
			show(node->right);
		}
	}
}

void binaryTree::action(void(*fooPointer)(point& a), binaryNode* node)
{
	if (node) {
		if (node->left) {
			action(fooPointer, node->left);
		}
		fooPointer(node->item);
		if (node->right) {
			action(fooPointer, node->right);
		}
	}
}


void AVL_tree::push(point item)
{
	if (!root) {
		root = new Node(item);
		size = 1;
	}
	else {
		push(item, root);
		balance(root);
	}
}

void AVL_tree::push_random(long long number)
{
	for (long long i = 0; i < number; i++) {
		push(point(number));
	}
}

void AVL_tree::show(size_t pos)
{
	if (size == 0) {
		//std::cout << "This list is empty" << std::endl;
	}
	else if (pos > size - 1) {
		//std::cout << "Incorrect position" << std::endl;
	}
	else {
		size_t counter = 0;
		Node* to_show = get_node(pos, counter, root);
		if (to_show) {
			std::cout << to_show->item;
		}
	}
}

point AVL_tree::operator[](size_t index)
{
	if (size == 0) {

	}
	if (index > size - 1) {
		//std::cout << "Error. Out of range" << std::endl;
	}
	else {
		size_t counter = 0;
		Node* to_return = get_node(index, counter, root);
		if (to_return) {
			return to_return->item;
		}
	}
}

node_abstraction AVL_tree::value_search(point value)
{
	if (size == 0) {
		return { value,-1 };
	}
	else {
		int counter = 0;
		int index = value_search(value, counter, root) - 1;
		return { value, index };
	}
}

std::vector<point> AVL_tree::range_search_values(point down, point top)
{
	std::vector<point>to_return;
	range_search_values(down, top, to_return, root);
	return to_return;
}

bool AVL_tree::is_value(point value, Node* node)
{
	if (node) {
		if (node->item > value) {
			return is_value(value, node->left);
		}
		else if (node->item == value) {
			return true;
		}
		else {
			return is_value(value, node->right);
		}
	}
	else {
		return false;
	}
}

int AVL_tree::value_search(point value, int& counter, Node* node)
{
	if (node) {
		if (node->item > value) {
			return value_search(value, counter, node->left);
		}
		else if (node->item == value) {
			counter++;
			return counter;
		}
		else {
			counter++;
			return value_search(value, counter, node->right);
		}
	}
	else {
		return -1;
	}
}

void AVL_tree::range_search_values(point down, point top, std::vector<point>& to_return, Node* node)
{
	if (node) {
		if (down < node->item && node->item < top) {
			to_return.push_back(node->item);
			range_search_values(down, top, to_return, node->left);
			range_search_values(down, top, to_return, node->right);
		}
		else if (node->item < down) {
			range_search_values(down, top, to_return, node->right);
		}
		else if (node->item > top) {
			range_search_values(down, top, to_return, node->left);
		}
	}
}

void AVL_tree::delete_subtree(Node*& node)
{
	if (node) {
		if (node->left) {
			delete_subtree(node->left);
		}
		if (node->right) {
			delete_subtree(node->right);
		}
		delete node;
		node = nullptr;
	}
}

bool AVL_tree::erase(size_t pos, int& counter, Node*& node)
{
	if (node) {
		if (erase(pos, counter, node->left) == false) {
			counter++;
			if (counter == pos) {
				if (node->right == nullptr && node->left) {
					Node* help = node->left;
					if (node->parent) {
						if (node->parent->left == node) {
							node->parent->left = help;
							help->parent = node->parent;
						}
						else if (node->parent->right == node) {
							node->parent->right = help;
							help->parent = node->parent;
						}
					}
					delete node;
					node = help;
				}
				else if (node->right == nullptr) {
					if (node->parent->left == node) {
						node->parent->left = nullptr;
					}
					else if (node->parent->right == node) {
						node->parent->right = nullptr;
					}
					delete node;
				}
				else if (node->right && node->right->left == nullptr) {
					Node* help1 = node->left;
					Node* help2 = node->right;
					if (node->parent) {
						if (node->parent->left == node) {
							node->parent->left = help2;
							help2->parent = node->parent;
						}
						else if (node->parent->right == node) {
							node->parent->right = help2;
							help2->parent = node->parent;
						}
					}
					delete node;
					node = help2;
					node->left = help1;
					help1->parent = node;
				}
				else {
					Node* search = node->right->left;
					while (search->left) {
						search = search->left;
					}
					node->item = search->item;
					search->parent->left = nullptr;
					delete search;
				}
				size--;
				return true;
			}
			if (erase(pos, counter, node->right) == true) {
				return true;
			}
		}
		else {
			return true;
		}
	}
}

void AVL_tree::show(Node* node)
{
	if (node) {
		if (node->left) {
			show(node->left);
		}
		std::cout << node->item;
		std::cout << ' ';
		if (node->right) {
			show(node->right);
		}
	}
}

void AVL_tree::action(void(*fooPointer)(point& a), Node* node)
{
	if (node) {
		if (node->left) {
			action(fooPointer, node->left);
		}
		fooPointer(node->item);
		if (node->right) {
			action(fooPointer, node->right);
		}
	}
}


void Tree_2_3::delete_subtree(Node*& node)
{
	if (node) {
		delete_subtree(node->first);
		delete_subtree(node->second);
		delete_subtree(node->third);
		delete node;
		node = nullptr;
	}
}

bool Tree_2_3::is_value(point value)
{
	if (size == 0) {
		return false;
	}
	else {
		if (get_node(root, value)) {
			return true;
		}
		else {
			return false;
		}
	}
}

std::vector<point> Tree_2_3::range_search_values(point down, point top)
{
	if (down < top) {
		std::vector<point>to_return;
		range_search_values(down, top, to_return, root);
		return to_return;
	}
}

void Tree_2_3::range_search_values(point down, point top, std::vector<point>& to_return, Node* node)
{
	if (node) {
		if (node->size == 1) {
			if (down < node->key[0] && node->key[0] < top) {
				to_return.push_back(node->key[0]);
				range_search_values(down, top, to_return, node->first);
				range_search_values(down, top, to_return, node->second);
			}
			else if (node->key[0] < down) {
				range_search_values(down, top, to_return, node->second);
			}
			else if (node->key[0] > top) {
				range_search_values(down, top, to_return, node->first);
			}
		}
		else if (node->size == 2) {
			if (down < node->key[0] && node->key[0] < top) {
				to_return.push_back(node->key[0]);
				range_search_values(down, top, to_return, node->first);
				range_search_values(down, top, to_return, node->second);
			}
			else if (down < node->key[1] && node->key[1] < top) {
				to_return.push_back(node->key[1]);
				range_search_values(down, top, to_return, node->second);
				range_search_values(down, top, to_return, node->third);
			}
			else if (node->key[0] > top) {
				range_search_values(down, top, to_return, node->first);
			}
			else if (node->key[1] < down) {
				range_search_values(down, top, to_return, node->third);
			}
			else if (node->key[0] < down || node->key[1] > top) {
				range_search_values(down, top, to_return, node->second);
			}
		}
	}
}

void Tree_2_3::show(Node* node)
{
	if (node) {
		if (node->first) {
			show(node->first);
		}
		if (node->size > 0) {
			std::cout << node->key[0] << std::endl;
		}
		if (node->second) {
			show(node->second);
		}
		if (node->size > 1) {
			std::cout << node->key[1] << std::endl;
		}
		if (node->third) {
			show(node->third);
		}
	}
}

void Tree_2_3::action(void(*fooPointer)(point& a), Node* node)
{
	if (node) {
		if (node->first) {
			action(fooPointer, node->first);
		}
		if (node->size > 0) {
			fooPointer(node->key[0]);
		}
		if (node->second) {
			action(fooPointer, node->second);
		}
		if (node->size > 1) {
			fooPointer(node->key[1]);
		}
		if (node->third) {
			action(fooPointer, node->third);
		}
	}
}

void Tree_2_3::push_random(long long number)
{
	for (long long i = 0; i < number; i++) {
		push(point(number));
	}
}

void demomode()
{
	try
	{
		std::ifstream in("in.txt");
		std::streambuf* cinbuf = std::cin.rdbuf();
		std::cin.rdbuf(in.rdbuf());

		commands();

		std::cin.rdbuf(cinbuf);
	}
	catch (const std::exception&)
	{
		std::cout << "Problems with file" << std::endl;
	}
}

void benchmark()
{

}

void commands() {
	std::cout << "help for reference" << std::endl << std::endl;
	while (true) {
		std::string input;
		std::getline(std::cin, input);
		std::stringstream ss;
		ss.str(input);
		std::string part;
		std::vector<std::string> all_commands;
		while (ss >> part) all_commands.push_back(part);
		if (all_commands.size() == 1 && all_commands[0] == "help") {
			std::cout << main_help << std::endl;
		}
		else if (all_commands.size() == 1 && all_commands[0] == "demomode") {
			demomode();
		}
		else if (all_commands.size() == 1 && all_commands[0] == "benchmark") {
			benchmark();
		}
		else if (all_commands.size() == 1 && all_commands[0] == "linked") {
			commands(1, -1);
		}
		else if (all_commands.size() == 2 && all_commands[0] == "array") {
			long long argument;
			bool correct = true;
			if (is_int(all_commands[1])) {
				argument = atoi(all_commands[1].c_str());
			}
			else {
				correct = false;
				break;
			}
			if (argument < 1) {
				correct = false;
			}
			if (correct) {
				try
				{
					commands(2,argument);
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else {
				std::cout << "Incorrect argument. help for reference" << std::endl;
			}
		}
		else if (all_commands.size() == 1 && all_commands[0] == "binary") {
			commands(3, -1);
		}
		else if (all_commands.size() == 1 && all_commands[0] == "AVL") {
			commands(4, -1);
		}
		else if (all_commands.size() == 1 && all_commands[0] == "2-3") {
			commands(5, -1);
		}
		else if (all_commands.size() == 1 && all_commands[0] == "exit") {
			std::cout << "goodby!" << std::endl;
			return;
		}
		else {
			std::cout << "Unclear command. help for reference" << std::endl;
		}
	}
}

bool is_int(const std::string& str)
{
	for (auto i : str) {
		if (i < 48 && i>57) {
			return false;
		}
	}
	return true;
}


void commands(int what_structure, long long number = -1)
{
	std::cout << "help for reference" << std::endl;
	if (what_structure == 1) {
		orderedListLinkedList structure;
		while (true) {
			std::string input;
			std::getline(std::cin, input);
			std::stringstream ss;
			ss.str(input);
			std::string part;
			std::vector<std::string> all_commands;
			while (ss >> part) all_commands.push_back(part);
			if (all_commands.size() == 1 && all_commands[0] == "help") {
				//std::cout << help_linked_answer << std::endl;
			}
			else if (all_commands.size() == 2 && all_commands[0] == "pop" && all_commands[1] == "front") {
				try
				{
					structure.pop_front();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "pop" && all_commands[1] == "back") {
				try
				{
					structure.pop_back();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 4 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if(ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]));
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}					
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size()-1; i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				std::stringstream ss(all_commands[4]);
				long long a;
				if (!(ss >> a)) {
					correct = false;
				}
				if (correct && a>0) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]),a);
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "push" && all_commands[1] == "random") {
				std::stringstream ss(all_commands[2]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a>0) {
					try
					{
						structure.push_random(a);
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 4 && all_commands[0] == "erase") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.erase(point(arguments[0], arguments[1], arguments[2]));
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "erase") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.erase(a);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "erase") {
				std::stringstream ss1(all_commands[1]);
				bool correct = true;
				long long a;
				if (!(ss1 >> a)) {
					correct = false;
				}
				std::stringstream ss2(all_commands[2]);
				long long b;
				if (!(ss2 >> b)) {
					correct = false;
				}
				if (correct && a > -1 && b>-1) {
					try
					{
						structure.erase(a,b);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 1 && all_commands[0] == "show") {
				try
				{
					structure.show();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "show") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.show(a);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[0] == "is" && all_commands[1] == "value") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						if (structure.is_value(point(arguments[0], arguments[1], arguments[2]))) {
							std::cout << "Yes" << std::endl;
						}
						else {
							std::cout << "No" << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[0] == "value" && all_commands[1] == "search") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						node_abstraction node = structure.value_search(point(arguments[0], arguments[1], arguments[2]));
						if (node.position == -1) {
							std::cout << "This value isn't here" << std::endl;
						}
						else {
							std::cout << "Position of that value: "<<node.position << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[1] == "values") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<point> values = structure.range_search_values(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout << values[i] << std::endl;
							}
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[1] == "nodes") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<node_abstraction> values = structure.range_search_nodes(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout <<"Position: " << values[i].position << " Value: "<< values[i].value << std::endl;
							}
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "action") {
				try
				{
					bool correct = true;
					if (all_commands[1] == "x") {
						if (all_commands[2] == "plus") {
							structure.action(x_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(x_minus);
						}
						else {
							correct = false;
						}
					}
					if (all_commands[1] == "y") {
						if (all_commands[2] == "plus") {
							structure.action(y_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(y_minus);
						}
						else {
							correct = false;
						}
					}
					if (all_commands[1] == "z") {
						if (all_commands[2] == "plus") {
							structure.action(z_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(z_minus);
						}
						else {
							correct = false;
						}
					}
					else {
						correct = false;
					}
					if (!correct) {
						std::cout << "Incorrect argument. help for reference" << std::endl;
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 1 && all_commands[0] == "end") {
				return;
			}
			else {
				std::cout << "Unclear command. help for reference" << std::endl;
			}
		}
	}
	else if(what_structure == 2) {
		orderedListArrayList structure(number);
		while (true) {
			std::string input;
			std::getline(std::cin, input);
			std::stringstream ss;
			ss.str(input);
			std::string part;
			std::vector<std::string> all_commands;
			while (ss >> part) all_commands.push_back(part);
			if (all_commands.size() == 1 && all_commands[0] == "help") {
				//std::cout << help_linked_answer << std::endl;
			}
			else if (all_commands.size() == 2 && all_commands[0] == "pop" && all_commands[1] == "front") {
				try
				{
					structure.pop_front();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "pop" && all_commands[1] == "back") {
				try
				{
					structure.pop_back();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 4 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]));
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size() - 1; i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				std::stringstream ss(all_commands[4]);
				long long a;
				if (!(ss >> a)) {
					correct = false;
				}
				if (correct && a > 0) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]), a);
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "push" && all_commands[1] == "random") {
				std::stringstream ss(all_commands[2]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > 0) {
					try
					{
						structure.push_random(a);
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 4 && all_commands[0] == "erase") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.erase(point(arguments[0], arguments[1], arguments[2]));
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "erase") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.erase(a);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "erase") {
				std::stringstream ss1(all_commands[1]);
				bool correct = true;
				long long a;
				if (!(ss1 >> a)) {
					correct = false;
				}
				std::stringstream ss2(all_commands[2]);
				long long b;
				if (!(ss2 >> b)) {
					correct = false;
				}
				if (correct && a > -1 && b > -1) {
					try
					{
						structure.erase(a, b);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 1 && all_commands[0] == "show") {
				try
				{
					structure.show();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "show") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.show(a);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[0] == "is" && all_commands[1] == "value") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						if (structure.is_value(point(arguments[0], arguments[1], arguments[2]))) {
							std::cout << "Yes" << std::endl;
						}
						else {
							std::cout << "No" << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[0] == "value" && all_commands[1] == "search") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						node_abstraction node = structure.value_search(point(arguments[0], arguments[1], arguments[2]));
						if (node.position == -1) {
							std::cout << "This value isn't here" << std::endl;
						}
						else {
							std::cout << "Position of that value: " << node.position << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[1] == "values") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<point> values = structure.range_search_values(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout << values[i] << std::endl;
							}
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[1] == "nodes") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<node_abstraction> values = structure.range_search_nodes(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout << "Position: " << values[i].position << " Value: " << values[i].value << std::endl;
							}
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "action") {
				try
				{
					bool correct = true;
					if (all_commands[1] == "x") {
						if (all_commands[2] == "plus") {
							structure.action(x_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(x_minus);
						}
						else {
							correct = false;
						}
					}
					if (all_commands[1] == "y") {
						if (all_commands[2] == "plus") {
							structure.action(y_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(y_minus);
						}
						else {
							correct = false;
						}
					}
					if (all_commands[1] == "z") {
						if (all_commands[2] == "plus") {
							structure.action(z_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(z_minus);
						}
						else {
							correct = false;
						}
					}
					else {
						correct = false;
					}
					if (!correct) {
						std::cout << "Incorrect argument. help for reference" << std::endl;
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 1 && all_commands[0] == "end") {
				return;
			}
			else {
				std::cout << "Unclear command. help for reference" << std::endl;
			}
		}
	}
	else if (what_structure == 3) {
		binaryTree structure;
		while (true) {
			std::string input;
			std::getline(std::cin, input);
			std::stringstream ss;
			ss.str(input);
			std::string part;
			std::vector<std::string> all_commands;
			while (ss >> part) all_commands.push_back(part);
			if (all_commands.size() == 1 && all_commands[0] == "help") {
				//std::cout << help_linked_answer << std::endl;
			}
			else if (all_commands.size() == 4 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]));
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size() - 1; i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				std::stringstream ss(all_commands[4]);
				long long a;
				if (!(ss >> a)) {
					correct = false;
				}
				if (correct && a > 0) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]), a);
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "push" && all_commands[1] == "random") {
				std::stringstream ss(all_commands[2]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > 0) {
					try
					{
						structure.push_random(a);
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 4 && all_commands[0] == "erase") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.erase(point(arguments[0], arguments[1], arguments[2]));
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "erase") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.erase(a);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "erase") {
				std::stringstream ss1(all_commands[1]);
				bool correct = true;
				long long a;
				if (!(ss1 >> a)) {
					correct = false;
				}
				std::stringstream ss2(all_commands[2]);
				long long b;
				if (!(ss2 >> b)) {
					correct = false;
				}
				if (correct && a > -1 && b > -1) {
					try
					{
						structure.erase(a, b);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 1 && all_commands[0] == "show") {
				try
				{
					structure.show();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "show") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.show(a);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[0] == "is" && all_commands[1] == "value") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						if (structure.is_value(point(arguments[0], arguments[1], arguments[2]))) {
							std::cout << "Yes" << std::endl;
						}
						else {
							std::cout << "No" << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[0] == "value" && all_commands[1] == "search") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						node_abstraction node = structure.value_search(point(arguments[0], arguments[1], arguments[2]));
						if (node.position == -1) {
							std::cout << "This value isn't here" << std::endl;
						}
						else {
							std::cout << "Position of that value: " << node.position << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[1] == "values") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<point> values = structure.range_search_values(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout << values[i] << std::endl;
							}
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "action") {
				try
				{
					bool correct = true;
					if (all_commands[1] == "x") {
						if (all_commands[2] == "plus") {
							structure.action(x_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(x_minus);
						}
						else {
							correct = false;
						}
					}
					if (all_commands[1] == "y") {
						if (all_commands[2] == "plus") {
							structure.action(y_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(y_minus);
						}
						else {
							correct = false;
						}
					}
					if (all_commands[1] == "z") {
						if (all_commands[2] == "plus") {
							structure.action(z_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(z_minus);
						}
						else {
							correct = false;
						}
					}
					else {
						correct = false;
					}
					if (!correct) {
						std::cout << "Incorrect argument. help for reference" << std::endl;
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 1 && all_commands[0] == "end") {
				return;
			}
			else {
				std::cout << "Unclear command. help for reference" << std::endl;
			}
		}
	}
	else if (what_structure == 4) {
		AVL_tree structure;
		while (true) {
			std::string input;
			std::getline(std::cin, input);
			std::stringstream ss;
			ss.str(input);
			std::string part;
			std::vector<std::string> all_commands;
			while (ss >> part) all_commands.push_back(part);
			if (all_commands.size() == 1 && all_commands[0] == "help") {
				//std::cout << help_linked_answer << std::endl;
			}
			else if (all_commands.size() == 4 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]));
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "push" && all_commands[1] == "random") {
				std::stringstream ss(all_commands[2]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > 0) {
					try
					{
						structure.push_random(a);
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 4 && all_commands[0] == "erase") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.erase(point(arguments[0], arguments[1], arguments[2]));
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "erase") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.erase(a);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 1 && all_commands[0] == "show") {
				try
				{
					structure.show();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "show") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.show(a);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[0] == "is" && all_commands[1] == "value") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						if (structure.is_value(point(arguments[0], arguments[1], arguments[2]))) {
							std::cout << "Yes" << std::endl;
						}
						else {
							std::cout << "No" << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[0] == "value" && all_commands[1] == "search") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						node_abstraction node = structure.value_search(point(arguments[0], arguments[1], arguments[2]));
						if (node.position == -1) {
							std::cout << "This value isn't here" << std::endl;
						}
						else {
							std::cout << "Position of that value: " << node.position << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[1] == "values") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<point> values = structure.range_search_values(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout << values[i] << std::endl;
							}
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "action") {
				try
				{
					bool correct = true;
					if (all_commands[1] == "x") {
						if (all_commands[2] == "plus") {
							structure.action(x_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(x_minus);
						}
						else {
							correct = false;
						}
					}
					if (all_commands[1] == "y") {
						if (all_commands[2] == "plus") {
							structure.action(y_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(y_minus);
						}
						else {
							correct = false;
						}
					}
					if (all_commands[1] == "z") {
						if (all_commands[2] == "plus") {
							structure.action(z_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(z_minus);
						}
						else {
							correct = false;
						}
					}
					else {
						correct = false;
					}
					if (!correct) {
						std::cout << "Incorrect argument. help for reference" << std::endl;
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 1 && all_commands[0] == "end") {
				return;
			}
			else {
				std::cout << "Unclear command. help for reference" << std::endl;
			}
		}
	}
	else if (what_structure == 5) {
		Tree_2_3 structure;
		while (true) {
			std::string input;
			std::getline(std::cin, input);
			std::stringstream ss;
			ss.str(input);
			std::string part;
			std::vector<std::string> all_commands;
			while (ss >> part) all_commands.push_back(part);
			if (all_commands.size() == 1 && all_commands[0] == "help") {
				//std::cout << help_linked_answer << std::endl;
			}
			else if (all_commands.size() == 4 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]));
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "push" && all_commands[1] == "random") {
				std::stringstream ss(all_commands[2]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > 0) {
					try
					{
						structure.push_random(a);
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 4 && all_commands[0] == "erase") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.erase(point(arguments[0], arguments[1], arguments[2]));
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "erase") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.erase(a);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 1 && all_commands[0] == "show") {
				try
				{
					structure.show();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			/*else if (all_commands.size() == 2 && all_commands[0] == "show") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.show(a);
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}*/
			else if (all_commands.size() == 5 && all_commands[0] == "is" && all_commands[1] == "value") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						if (structure.is_value(point(arguments[0], arguments[1], arguments[2]))) {
							std::cout << "Yes" << std::endl;
						}
						else {
							std::cout << "No" << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			/*else if (all_commands.size() == 5 && all_commands[0] == "value" && all_commands[1] == "search") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						node_abstraction node = structure.value_search(point(arguments[0], arguments[1], arguments[2]));
						if (node.position == -1) {
							std::cout << "This value isn't here" << std::endl;
						}
						else {
							std::cout << "Position of that value: " << node.position << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}*/
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[1] == "values") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<point> values = structure.range_search_values(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout << values[i] << std::endl;
							}
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3 && all_commands[0] == "action") {
				try
				{
					bool correct = true;
					if (all_commands[1] == "x") {
						if (all_commands[2] == "plus") {
							structure.action(x_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(x_minus);
						}
						else {
							correct = false;
						}
					}
					if (all_commands[1] == "y") {
						if (all_commands[2] == "plus") {
							structure.action(y_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(y_minus);
						}
						else {
							correct = false;
						}
					}
					if (all_commands[1] == "z") {
						if (all_commands[2] == "plus") {
							structure.action(z_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(z_minus);
						}
						else {
							correct = false;
						}
					}
					else {
						correct = false;
					}
					if (!correct) {
						std::cout << "Incorrect argument. help for reference" << std::endl;
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 1 && all_commands[0] == "end") {
				return;
			}
			else {
				std::cout << "Unclear command. help for reference" << std::endl;
			}
		}
	}
}

void x_plus(point& P)
{
	P.x += 1;
}

void x_minus(point& P)
{
	P.x -= 1;
}

void y_plus(point& P)
{
	P.y += 1;
}

void y_minus(point& P)
{
	P.y -= 1;
}

void z_plus(point& P)
{
	P.z += 1;
}

void z_minus(point& P)
{
	P.z -= 1;
}