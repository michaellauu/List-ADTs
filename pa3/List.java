// Michael Lau
// mlau10
// CMPS 101 - PA3
// 10/25/17

public class List {
	private class Node {
		// fields
		Object data;
		Node prev;
		Node next;
		
		// constructor
		Node(Object data) {
			this.data = data;
			next = null;
			prev = null;
		}
	}

	private Node front;
	private Node back;
	private int length;
	private Node cursor;
	private int cursorIndex;

	// Constructor
	List() {
		front = back = null;
		length = 0;
		cursor = null;
		cursorIndex = -1;
	}
	// Access functions
	int length() { // Returns the number of elements in this List.
		return length;
	}

	// If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1.
	int index() {
		if(cursor == null) return -1;
		return cursorIndex;
	}

	// Returns front element.
	// Pre: length() > 0
	Object front() {
		if(length() < 1) throw new RuntimeException("List Error: Length is less than 1.");
		return front.data;
	}

	// Returns back element.
	// Pre: length() > 0
	Object back() {
		if(length() < 1) throw new RuntimeException("List Error: Length is less than 1.");
		return back.data;
	}

	// Returns cursor element.
	// Pre: length() > 0
	Object get() {
		if(length() < 1) throw new RuntimeException("List Error: Length is less than 1");
		else if(index() < 0) throw new RuntimeException("List Error: Cursor index is less than 0");
		return cursor.data;
	}

	// Returns true if this List and L are the same object
	// sequence. The cursor is ignored in both lists.
	public boolean equals(Object x) {		// Returns true if and only if this List and L are the same
		boolean eq = true;
		List L = (List) x;
		Node A = front;
		Node B = L.front; 
		if(length == L.length) {
			while(A != null) {
				eq = (A.data==B.data);
				A = A.next;
				B = B.next;
			}
			return eq;
		}
		else return false;
	}
	

	// Resets this List to its original empty state.
	void clear() {
		front = back = cursor = null;
		length = 0;
		cursorIndex = -1;
	}

	// If List is non-empty, places the cursor under the front
	// element, otherwise does nothing.
	void moveFront() {
		if(length > 0) {
			cursor = front;
			cursorIndex = 0;
		} 
	}

	// If List is non-empty, places the cursor under the back
	// element, otherwise does nothing.
	void moveBack() {
		if(length > 0) {
			cursor = back;
			cursorIndex = length - 1;
		}
	}

	// If cursor is defined and not at front, moves cursor one step
	// toward front of this List, if cursor is defined and at front,
	// cursor becomes undefined, if cursor is undefined does nothing.
	void movePrev() {
		if(cursor != null && cursorIndex > 0) {
			cursor = cursor.prev;
			cursorIndex--;
		}
		else {
			cursor = null;
			cursorIndex = -1;
		}
	}

	// If cursor is defined and not at back, moves cursor one step
	// toward back of this List, if cursor is defined and at back,
	// cursor becomes undefined, if cursor is undefined does nothing.
	void moveNext() {
		if(cursorIndex < length-1 && cursor != null) {
			cursor = cursor.next;
			cursorIndex++;
		}
		else {
			cursor = null;
			cursorIndex = -1;
		}
	}
	// Insert new element into this List. If List is non-empty,
	// insertion takes place before the front element.
	void prepend(Object data) {
		Node t = new Node(data);
		if (length == 0) front = back = t;
		else {
			t.prev = null;
			t.next = front;
			front.prev = t;
			front = t;
		}
		length++;
	}

	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void append(Object data) {
		Node t = new Node(data);
		if (length == 0) {
			t.prev = null;
			t.next = null;
			front = back = t;
		}
		else {
			t.prev = back;
			t.next = null;
			back.next = t;
			back = t;
		}
		length++;
	}

	// Insert new element before cursor.
	// Pre: length() > 0, index() >= 0
	void insertBefore(Object data) {
		if(length() < 1) throw new RuntimeException("List Error: Length is less than 0"); // Pre: length()>0, index()>=0
		if(index() < 0) throw new RuntimeException("List Error: Cursor index is less than 0");
		Node t = new Node(data);
		if (cursorIndex == 0) {
			prepend(data);
		} 
		else {
			t.next = cursor;
			t.prev = cursor.prev;
			cursor.prev.next = t;
			cursor.prev = t;
			cursorIndex++;
			length++;
		}
	}

	// Inserts new element after cursor.
	// Pre: length() > 0, index() >= 0
	void insertAfter(Object data) {
		if(length() < 1) throw new RuntimeException("List Error: Length is less than 0"); // Pre: length()>0, index()>=0
		if(index() < 0) throw new RuntimeException("List Error: Cursor index is less than 0");
		Node t = new Node(data);
		if (cursorIndex == length - 1) append(data);
		else {
			t.next  = cursor.next;
			t.prev = cursor;
			cursor.next.prev = t;
			cursor.next = t;
			//	cursorIndex++;
			length++;
		}	
	}

	// Deletes the front element.
	// Pre: length() > 0
	void deleteFront() {
		if(length() < 1) throw new RuntimeException("List Error: Length is less than 1");
		if(cursor == front) {
			cursor = null;
			cursorIndex = -1;
		}
		front = front.next;
		front.prev = null;
		length--;
	}

	// Deletes the back element.
	// Pre: length() > 0
	void deleteBack() {
		if(length() < 1) throw new RuntimeException("List Error: Length is less than 1");
		if(cursor == back) {
			cursor = null;
			cursorIndex = -1;
		}
		back = back.prev;
		back.next = null;
		length--;
	}

	// Deletes cursor element, making cursor undefined.
	// Pre: length() > 0, index() >= 0
	void delete() {
		if(length() < 1) throw new RuntimeException("List Error: Length is less than 1");	// Pre: length()>0, index()>=0
		if(index() < 0)	throw new RuntimeException("List Error: Cursor index is less than 0");
		if(cursor == front) deleteFront();
		if(cursor == back) deleteBack();
		else {
			cursor.prev.next = cursor.next;
			cursor.next.prev = cursor.prev;
			cursor = null;
			cursorIndex = -1;
			length--;
		}
	}

	// Other methods
	public String toString() { // Overrides Object's toString method. Returns a String
		Node t = front;	// representation of this List consisting of a space
		String string = new String(); // separated sequence of integers, with front on left.
		while(t != null) {
			string += t.data;
			if(t.next != null) {
				string += " ";
			}
			t = t.next;
		}
		return string;
	}
}