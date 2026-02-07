Which of these is easiest to write?
- **Version A** on the easiest to write since there is no any loop or extra implementation with top,pop,empty.
Which will run most quickly if the stack is nearly full? Which will run most quickly if the stack is nearly empty? 
- This could be difficult to say, the answer could be A or C, since it copies directly. However, C is using one loop, maybe **version A** could be a bit faster in the case. However, A cannot catch overflow or underflow correctly because the algorithm forces it return always success.  
Which would be the best method if the implementation might be changed?
- The question is not very clear in what kind of implementation, so **no idea**.
In which could we pass the parameter source as a constant reference?
- **A & C** can pass the parameter source, B isnot possbile since it is using pop() to modify the source, and the requirement of the exericse is **source is unchanged**