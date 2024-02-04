int getLoopSize(Node* startNode)
{
	if (startNode == nullptr)
	{
		return 0;
	}

	Node* turtleptr = startNode;
	Node* rabbitptr = startNode;

	while (rabbitptr != nullptr && rabbitptr->getNext() != nullptr)
	{
		turtleptr = turtleptr->getNext();
		rabbitptr = rabbitptr->getNext()->getNext();

		if (turtleptr == rabbitptr)
		{
			int loopSize = 1;
			Node* current = turtleptr;

			while (current->getNext() != turtleptr)
			{
				loopSize++;
				current = current->getNext();
			}

			return loopSize;
		}
	}

	return 0;
}
