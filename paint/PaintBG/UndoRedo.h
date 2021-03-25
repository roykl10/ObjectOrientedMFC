#pragma once

#include <vector>
#include <stack>
#include "Shapes.h"
using namespace std;


class UndoRedo
{
public:
	UndoRedo() {};
	//every new shapes goes to undo-stack, when undo pops, push to redo.
	// temp vector equals to myShape vectors. Editing vector.
	vector <Shapes*> Undo()
	{
		if (!undo.empty()) //if undo stack isn't empty
		{
			redo.push(undo.top()); //pushes first undo value to redo stack
			undo.pop(); //pops from stack
			temp.pop_back(); //pops from vector
		}

		return temp;
	}

	vector <Shapes*> Redo()
	{
		if (!redo.empty())
		{
			undo.push(redo.top());
			temp.push_back(redo.top());
			redo.pop();
		}
		return temp;
	}

	void delAll()
	{
		while (!redo.empty())
			redo.pop();
		while (!undo.empty())
			undo.pop();
		while (!temp.empty())
			temp.pop_back();
	}

	void move(Shapes *s) //pushes shape to temp array and undo stack
	{
		temp.push_back(s);
		undo.push(s);
	}

private:
	//stacks
	stack <Shapes*> undo;
	stack <Shapes*> redo;
	//vector
	vector <Shapes*> temp;
};