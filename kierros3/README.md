```
Case A:
Initial:
[ empty ]

push 'a':
Stack
┌───┐
│ a │
└───┘

push 'b':
Stack
┌───┐
│ b │
├───┤
│ a │
└───┘

push 'c':
Stack
┌───┐
│ c │
├───┤
│ b │
├───┤
│ a │
└───┘

pop()  -> removes 'c':
Stack
┌───┐
│ b │
├───┤
│ a │
└───┘

pop()  -> removes 'b':
Stack
┌───┐
│ a │
└───┘

pop()  -> removes 'a':
[ empty ]


Case B: 
Initial:
[ empty ]

push 'a':
Stack
┌───┐
│ a │
└───┘

push 'b':
Stack
┌───┐
│ b │
├───┤
│ a │
└───┘

push 'c':
Stack
┌───┐
│ c │
├───┤
│ b │
├───┤
│ a │
└───┘

copy top 'c':
Char x
┌───┐
│ c │
└───┘

pop()  -> removes 'c':
Stack
┌───┐
│ b │
├───┤
│ a │
└───┘

copy top 'b':
Char y
┌───┐
│ b │
└───┘

pop()  -> removes 'b':
Stack
┌───┐
│ a │
└───┘

push() -> add 'c'
Stack
┌───┐
│ c │
├───┤
│ a │
└───┘

push() -> add 'b'
Stack
┌───┐
│ b │
├───┤
│ c │
├───┤
│ a │
└───┘

pop()  -> removes 'b':
Stack
┌───┐
│ c │
├───┤
│ a │
└───┘

Case C:
Initial:
[ empty ]

push 'a':
Stack
┌───┐
│ a │
└───┘

push 'b':
Stack
┌───┐
│ b │
├───┤
│ a │
└───┘

push 'c':
Stack
┌───┐
│ c │
├───┤
│ b │
├───┤
│ a │
└───┘


pop()  -> removes 'c':
Stack
┌───┐
│ b │
├───┤
│ a │
└───┘

pop()  -> removes 'b':
Stack
┌───┐
│ a │
└───┘

pop()  -> removes 'a':
[ empty ]

Case D:
Initial:
[ empty ]

push 'a':
Stack
┌───┐
│ a │
└───┘

push 'b':
Stack
┌───┐
│ b │
├───┤
│ a │
└───┘

copy top 'b':
Char x
┌───┐
│ b │
└───┘

pop()  -> removes 'b':
Stack
┌───┐
│ a │
└───┘

copy top 'a':
Char x
┌───┐
│ a │
└───┘

pop()  -> removes 'a':
[ empty ]

push 'c':
Stack
┌───┐
│ c │
└───┘

pop()  -> removes 'c':
[ empty ]

push 'a':
Stack
┌───┐
│ a │
└───┘

pop()  -> removes 'a':
[ empty ]

push 'b':
Stack
┌───┐
│ b │
└───┘

pop()  -> removes 'b':
[ empty ]
```